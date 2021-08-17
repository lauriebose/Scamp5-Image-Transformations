#include "IMG_ROTATION_DIGITAL.hpp"

#include <scamp5.hpp>
#include <math.h>

using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace ROTATION
	{
		namespace DIGITAL
		{

			void ROT_3SKEWS(dreg_t reg, double angle_radians)
			{
				double skewY_val = IMGTF::tan_approx3(0.5*angle_radians);
				double skewX_val = IMGTF::sin_approx3(angle_radians);

				double tan_val_Y = IMGTF::tan_approx3(M_PI*skewY_val*0.25);
				double tan_val_X = IMGTF::tan_approx3(M_PI*skewX_val*0.25);

				IMGTF::SKEW::DIGITAL::SKEWY_TAN_RAD(reg,tan_val_Y,0.33);
				IMGTF::SKEW::DIGITAL::SKEWX_TAN_RAD(reg,tan_val_X,0.66);
				IMGTF::SKEW::DIGITAL::SKEWY_TAN_RAD(reg,tan_val_Y,0.33);
			}

			void ROT_2SKEWS(dreg_t reg, int rotation_steps)
			{
				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(R11,reg);
					scamp5_dynamic_kernel_end();
				}

				//EACH STEP APPROXIMATELY 0.555... DEGRESS (FROM 1.0/1.8)
				int current_rotation = rotation_steps;
				if(current_rotation > 0)
				{
					for(int n = 0 ; n < current_rotation ; n++)
					{
						IMGTF::SKEW::DIGITAL::STEP_SKEWX_CW_R11(n);
						IMGTF::SKEW::DIGITAL::STEP_SKEWY_CW_R11(n);
					}
				}
				else
				{
					for(int n = 0 ; n < -current_rotation ; n++)
					{
						IMGTF::SKEW::DIGITAL::STEP_SKEWX_ACW_R11(n);
						IMGTF::SKEW::DIGITAL::STEP_SKEWY_ACW_R11(n);
					}
				}

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(reg,R11);
					scamp5_dynamic_kernel_end();
				}
			}

			int STEP_ROT_2SKEWS(dreg_t reg, int current_rot_value, bool rot_ACW)
			{
				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(R11,reg);
					scamp5_dynamic_kernel_end();
				}

				//EACH STEP APPROXIMATELY 0.555... DEGRESS (FROM 1.0/1.8)
				if(current_rot_value > 0)
				{
					if(!rot_ACW)
					{
						IMGTF::SKEW::DIGITAL::	STEP_SKEWX_CW_R11(current_rot_value);
						IMGTF::SKEW::DIGITAL::	STEP_SKEWY_CW_R11(current_rot_value);
						current_rot_value = current_rot_value + 1;
					}
					else
					{
						current_rot_value = current_rot_value - 1;
						IMGTF::SKEW::DIGITAL::	STEP_SKEWY_ACW_R11(current_rot_value);
						IMGTF::SKEW::DIGITAL::STEP_SKEWX_ACW_R11(current_rot_value);
					}
				}
				else
				{
					if(current_rot_value < 0)
					{
						if(!rot_ACW)
						{
							current_rot_value = current_rot_value + 1;
							IMGTF::SKEW::DIGITAL::	STEP_SKEWY_CW_R11(-current_rot_value);
							IMGTF::SKEW::DIGITAL::	STEP_SKEWX_CW_R11(-current_rot_value);
						}
						else
						{
							IMGTF::SKEW::DIGITAL::	STEP_SKEWX_ACW_R11(-current_rot_value);
							IMGTF::SKEW::DIGITAL::	STEP_SKEWY_ACW_R11(-current_rot_value);
							current_rot_value = current_rot_value - 1;
						}
					}
					else
					{
						if(!rot_ACW)
						{
							IMGTF::SKEW::DIGITAL::	STEP_SKEWX_CW_R11(current_rot_value);
							IMGTF::SKEW::DIGITAL::STEP_SKEWY_CW_R11(current_rot_value);
							current_rot_value = current_rot_value + 1;
						}
						else
						{
							IMGTF::SKEW::DIGITAL::STEP_SKEWX_ACW_R11(current_rot_value);
							IMGTF::SKEW::DIGITAL::STEP_SKEWY_ACW_R11(current_rot_value);
							current_rot_value = current_rot_value - 1;
						}
					}
				}

				if(!dreg_eql(reg,R11))
				{
					scamp5_dynamic_kernel_begin();
						MOV(reg,R11);
					scamp5_dynamic_kernel_end();
				}

				return current_rot_value;
			}
		}
	}
}




