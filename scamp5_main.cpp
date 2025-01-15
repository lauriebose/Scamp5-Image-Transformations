
#include "scamp5.hpp"
#include <math.h>
#include "IMG_TF.hpp"
#include "EDGE_IMAGE_GENERATION.hpp"


using namespace SCAMP5_PE;

volatile bool host_on;

int test_angle_scalar;
int img_gain_level = 1;
int shiftx = 0;
int shifty = 0;
int scale = 0;
int scalex = 0;
int scaley = 0;
int half_scale = 0;
int rot_angle;
uint32_t dreg_tf_time,dreg_translation_time,dreg_scaling_time,dreg_3skewrot_time,dreg_2skewrot_time;
uint32_t areg_tf_time,areg_translation_time,areg_scaling_time,areg_3skewrot_time,areg_2skewrot_time;

void scamp5_main(){
    auto display_1 = vs_gui_add_display("3 skew rot",0,0,2);
    auto display_2 = vs_gui_add_display("2 skew stepwise rot",0,2,2);

    vs_gui_add_slider("scale: ",-64,64,0,&scale);
    vs_gui_add_slider("scalex: ",-100,100,0,&scalex);
    vs_gui_add_slider("scaley: ",-100,100,0,&scaley);
    vs_gui_add_switch("half_scale", false,&half_scale);
    vs_gui_add_slider("shiftx: ",-100,100,0,&shiftx);
    vs_gui_add_slider("shifty: ",-100,100,0,&shifty);
    vs_gui_add_slider("rot_angle: ",-90,90,0,&rot_angle);
    vs_gui_add_slider("test_angle_scalar: ",0,1000,180,&test_angle_scalar);
    auto areg_dreg_display_switch = vs_gui_add_switch("display areg/dreg", true);

    auto slider_vxc = vs_gui_add_slider("vxc: ",0,4095,2900);
    vs_on_gui_update(slider_vxc,[&](int32_t new_value){
    	vs_scamp5_configure_voltage(3,new_value);
       });

	 vs_on_gui_update(VS_GUI_FRAME_RATE,[&](int32_t new_value){
	        uint32_t framerate = new_value;
	        if(framerate > 0){
	            vs_frame_trigger_set(1,framerate);
	            vs_enable_frame_trigger();
	            vs_post_text("frame trigger: 1/%d\n",(int)framerate);
	        }else{
	            vs_disable_frame_trigger();
	            vs_post_text("frame trigger disabled\n");
	        }
	    });

	 vs_on_gui_update(VS_GUI_FRAME_GAIN,[&](int32_t new_value){
		 img_gain_level = new_value;
		    });

    vs_on_host_connect([&](){
        vs_post_text("\nScamp5d Vision Algorithm Demo\nloop_counter: %d\n",vs_loop_counter_get());
        scamp5_kernel::print_debug_info();
        vs_led_on(VS_LED_2);
        host_on = true;
    });

    vs_on_host_disconnect([&](){
        vs_enable_frame_trigger();
        vs_led_off(VS_LED_2);
        host_on = false;
    });

    vs_frame_trigger_set(1,60);

    vs_stopwatch timer;

    while(1){

    	vs_wait_frame_trigger();
		vs_process_message();

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//GET IMAGE AND EDGE IMAGE

		acquire_edge_image(img_gain_level, 50, 0, 30, 250);
		scamp5_get_image(A,E,img_gain_level);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TRANSFORM A AND B

		 //SCALING
        timer.reset();
		IMGTF::SCALING::ANALOG::SCALE(A,abs(scale),scale > 0 ? 0 : 1);
		IMGTF::SCALING::ANALOG::SCALE_X(A,abs(scalex),scalex > 0 ? 0 : 1);
		IMGTF::SCALING::ANALOG::SCALE_Y(A,abs(scaley),scaley > 0 ? 0 : 1);
		if(half_scale)
		{
			IMGTF::SCALING::ANALOG::HALF_SCALE(A);
		}
		areg_scaling_time = timer.get_usec();

		//SHIFTING
		timer.reset();
		scamp5_shift(A,shiftx,shifty);
		areg_translation_time = timer.get_usec();

		//ROTATION 2 SKEWS
		scamp5_kernel_begin();
			mov(B,A);
		scamp5_kernel_end();
		int k = (int)(-rot_angle*test_angle_scalar*0.01);
		timer.reset();
		IMGTF::ROTATION::ANALOG::ROT_2SKEWS(B,k);
		areg_2skewrot_time = timer.get_usec();

		//ROTATION 3 SKEWS
		timer.reset();
		IMGTF::ROTATION::ANALOG::ROT_3SKEWS(A,M_PI*rot_angle/180.0);
		areg_3skewrot_time = timer.get_usec();

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TRANSFORM R5 AND R6

		//SCALING
		timer.reset();
		if(abs(scale) != 0)
		{
			IMGTF::SCALING::DIGITAL::SCALE(R5,abs(scale),scale > 0 ? 0 : 1);
		}
		if(abs(scalex) != 0)
		{
			IMGTF::SCALING::DIGITAL::SCALE_X(R5,abs(scalex),scalex > 0 ? 0 : 1);
		}
		if(abs(scaley) != 0)
		{
			IMGTF::SCALING::DIGITAL::SCALE_Y(R5,abs(scaley),scaley > 0 ? 0 : 1);
		}

		if(half_scale)
		{
			IMGTF::SCALING::DIGITAL::HALF_SCALE(R5);
		}
		dreg_scaling_time = timer.get_usec();

		//SHIFTING
		timer.reset();
		if(abs(shiftx) > 0)
		{
			scamp5_dynamic_kernel_begin();
				CLR(R1,R2,R3,R4);
				if(shiftx > 0)
				{
					SET(R2);
				}
				else
				{
					SET(R4);
				}
			scamp5_dynamic_kernel_end();
			for(int x = 0 ; x < abs(shiftx) ; x++)
			{
				scamp5_kernel_begin();
					DNEWS0(R11,R5);
					MOV(R5,R11);
				scamp5_kernel_end();
			}
		}
		if(abs(shifty) > 0)
		{
			scamp5_dynamic_kernel_begin();
				CLR(R1,R2,R3,R4);
				if(shifty > 0)
				{
					SET(R3);
				}
				else
				{
					SET(R1);
				}
			scamp5_dynamic_kernel_end();
			for(int y = 0 ; y < abs(shifty) ; y++)
			{
				scamp5_kernel_begin();
					DNEWS0(R11,R5);
					MOV(R5,R11);
				scamp5_kernel_end();
			}
		}
		dreg_translation_time = timer.get_usec();

		//ROTATION 3 SKEWS
		scamp5_kernel_begin();
			MOV(R6,R5);
		scamp5_kernel_end();
		k = (int)(-rot_angle*test_angle_scalar*0.01);
		timer.reset();
		IMGTF::ROTATION::DIGITAL::ROT_2SKEWS(R6,k);
		dreg_2skewrot_time = timer.get_usec();


		scamp5_kernel_begin();
				MOV(R11,R5);
			scamp5_kernel_end();
		//ROTATION 3 SKEWS
		timer.reset();
		IMGTF::ROTATION::DIGITAL::ROT_3SKEWS(R11,M_PI*rot_angle/180.0);
		dreg_3skewrot_time = timer.get_usec();
		scamp5_kernel_begin();
				MOV(R5,R11);
			scamp5_kernel_end();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//OUTPUT

		//PRINT TIMINGS
		uint32_t temp_areg_tf_time = areg_scaling_time+areg_translation_time+areg_2skewrot_time+areg_3skewrot_time;
		uint32_t temp_dreg_tf_time = dreg_scaling_time+dreg_translation_time+dreg_2skewrot_time+dreg_3skewrot_time;
		if(temp_areg_tf_time != areg_tf_time || temp_dreg_tf_time != dreg_tf_time)
		{
			areg_tf_time = temp_areg_tf_time;
			dreg_tf_time = temp_dreg_tf_time;
			vs_post_text("AREG time(us):%d scale:%d 2skewrot:%d 3skewrot:%d trans:%d \n",areg_tf_time,areg_scaling_time,areg_2skewrot_time,areg_3skewrot_time,areg_translation_time);
			vs_post_text("DREG time(us):%d scale:%d 2skewrot:%d 3skewrot:%d trans:%d \n",dreg_tf_time,dreg_scaling_time,dreg_2skewrot_time,dreg_3skewrot_time,dreg_translation_time);
		}

		//OUTPUT DISPLAYS
		if(vs_gui_read_slider(areg_dreg_display_switch) == 1)
		{
		    scamp5_output_image(R5,display_1);
		    scamp5_output_image(R6,display_2);
		}
		else
		{
		   scamp5_output_image(A,display_1);
		   scamp5_output_image(B,display_2);
		}

        if(vs_loop_counter_get()%25==0){
        	vs_led_toggle(VS_LED_1);
        }

        vs_loop_counter_inc();
    }

}



int main(){

	vs_init();
	vs_post_bind_io_agent(vs_usb);
	scamp5_bind_io_agent(vs_usb);
	scamp5_main();

	return 0;
}




