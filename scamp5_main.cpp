/*
 * Scamp5d M0 Example 1 - Image Capturing and Host Display
 *
 */

#include <scamp5.hpp>
#include "IMG_TF.hpp"

using namespace SCAMP5_PE;


int main(){

	// Initialization
	vs_init();

	// Setup Host GUI
	vs_gui_set_info(VS_M0_PROJECT_INFO_STRING);

    auto display_1 = vs_gui_add_display("capture",0,0);

	// Frame Loop
    while(1){
        vs_frame_loop_control();

        scamp5_kernel_begin();
            get_image(C,D);
		scamp5_kernel_end();

		if(vs_gui_is_on()){
			scamp5_output_image(C,display_1);
		}
    }

	return 0;
}
