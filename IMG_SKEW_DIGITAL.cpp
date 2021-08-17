#include <scamp5.hpp>
#include <math.h>

#include "IMG_ROTATION_DIGITAL.hpp"

using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace SKEW
	{
		namespace DIGITAL
		{
			void SKEWX(dreg_t reg,int skew_mag, bool skew_anti_clockwise,double offset)
			{
				if(skew_mag == 0)
				{
					return;
				}

				const int scalar_hack = 1000;
				int step_size = (int)(scalar_hack*127.0/skew_mag);

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(R11,reg);
					scamp5_dynamic_kernel_end();
				}

				scamp5_kernel_begin()
					CLR(R1,R3);
					SET(R0);
					MOV(R12,R11);
				scamp5_kernel_end();

				if(!skew_anti_clockwise)
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;

						scamp5_load_rect(R2,0,0,in,255);
						scamp5_load_rect(R4,255-in,0,255,255);
						scamp5_kernel_begin()
							DNEWS0(R11,R12);
							OR(R0,R2,R4);
							MOV(R12,R11);
						scamp5_kernel_end();
					}
				}
				else
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;

						scamp5_load_rect(R4,0,0,in,255);
						scamp5_load_rect(R2,255-in,0,255,255);
						scamp5_kernel_begin();
							DNEWS0(R11,R12);
							OR(R0,R2,R4);
							MOV(R12,R11);
						scamp5_kernel_end();
					}
				}

				scamp5_kernel_begin()
					MOV(R11,R12);
				scamp5_kernel_end();

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(reg,R11);
					scamp5_dynamic_kernel_end();
				}
			}

			void SKEWX_TAN_RAD(dreg_t reg,double tan_of_angle,double offset)
			{
				double skew_mag = 127.0*tan_of_angle;
				SKEWX( reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWX_RAD(dreg_t reg,double angle,double offset)
			{
				double skew_mag = 127.0*tan_approx3(angle);
				SKEWX(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWX_DEG(dreg_t reg,double angle,double offset)
			{
				double angle_in_radians = M_PI*angle/180.0;
				SKEWX_RAD(reg,angle_in_radians, offset);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			void SKEWY(dreg_t reg,int skew_mag, bool skew_anti_clockwise,double offset)
			{
				if(skew_mag == 0)
				{
					return;
				}

				const int scalar_hack = 1000;
				int step_size = (int)(scalar_hack*127.0/skew_mag);

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(R11,reg);
					scamp5_dynamic_kernel_end();
				}

				scamp5_kernel_begin()
					CLR(R2,R4);
					SET(R0);
					MOV(R12,R11);
				scamp5_kernel_end();

				if(!skew_anti_clockwise)
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;

						scamp5_load_rect(R3,0,0,255,in);
						scamp5_load_rect(R1,0,255-in,255,255);
						scamp5_kernel_begin()
							DNEWS0(R11,R12);
							OR(R0,R1,R3);
							MOV(R12,R11);
						scamp5_kernel_end();
					}
				}
				else
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;

						scamp5_load_rect(R1,0,0,255,in);
						scamp5_load_rect(R3,0,255-in,255,255);
						scamp5_kernel_begin()
							DNEWS0(R11,R12);
							OR(R0,R1,R3);
							MOV(R12,R11);
						scamp5_kernel_end();
					}
				}

				scamp5_kernel_begin()
					MOV(R11,R12);
				scamp5_kernel_end();

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(reg,R11);
					scamp5_dynamic_kernel_end();
				}
			}

			void SKEWY_TAN_RAD(dreg_t reg,double tan_of_angle,double offset)
			{
				double skew_mag = 127.0*tan_of_angle;
				SKEWY( reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWY_RAD(dreg_t reg,double angle,double offset)
			{
				double skew_mag = 127.0*tan_approx3(angle);
				SKEWY(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWY_DEG(dreg_t reg,double angle,double offset)
			{
				double angle_in_radians = M_PI*angle/180.0;
				SKEWY_RAD(reg,angle_in_radians,offset);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			void STEP_SKEWX_CW_R11(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R2,0,0,i,255);
				scamp5_load_rect(R4,255-i,0,255,255);

				scamp5_kernel_begin()
					CLR(R1,R3);
					SET(R0);
					MOV(R12,R11);
					DNEWS0(R11,R12);
					OR(R0,R2,R4);
					MOV(R12,R11);
					MOV(R11,R12);
				scamp5_kernel_end();
				return;
			}

			void STEP_SKEWX_ACW_R11(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R4,0,0,i,255);
				scamp5_load_rect(R2,255-i,0,255,255);

				scamp5_kernel_begin()
					CLR(R1,R3);
					SET(R0);
					MOV(R12,R11);
					DNEWS0(R11,R12);
					OR(R0,R2,R4);
					MOV(R12,R11);
					MOV(R11,R12);
				scamp5_kernel_end();
				return;
			}

			void STEP_SKEWY_CW_R11(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R3,0,0,255,i);
				scamp5_load_rect(R1,0,255-i,255,255);

				scamp5_kernel_begin()
					CLR(R2,R4);
					SET(R0);
					MOV(R12,R11);
					DNEWS0(R11,R12);
					OR(R0,R1,R3);
					MOV(R12,R11);
					MOV(R11,R12);
				scamp5_kernel_end();
				return;
			}

			void STEP_SKEWY_ACW_R11(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R1,0,0,255,i);
				scamp5_load_rect(R3,0,255-i,255,255);

				scamp5_kernel_begin()
					CLR(R2,R4);
					SET(R0);
					MOV(R12,R11);
					DNEWS0(R11,R12);
					OR(R0,R1,R3);
					MOV(R12,R11);
					MOV(R11,R12);
				scamp5_kernel_end();
				return;
			}
		}
	}
}




