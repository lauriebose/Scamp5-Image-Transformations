#include "IMG_SKEW.hpp"
#include "IMG_ROTATION.hpp"

using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace ROTATION
	{
		namespace ANALOG
		{
			void ROT_3SKEWS(areg_t reg, double angle_radians)
			{
				double skewY_val = tan_approx3(0.5*angle_radians);
				double skewX_val = sin_approx3(angle_radians);

				double tan_val_Y = tan_approx3(M_PI*skewY_val*0.25);
				double tan_val_X = tan_approx3(M_PI*skewX_val*0.25);

				IMGTF::SKEW::ANALOG::SKEWY_TAN_RAD(reg,tan_val_Y,0.33);
				IMGTF::SKEW::ANALOG::SKEWX_TAN_RAD(reg,tan_val_X,0.66);
				IMGTF::SKEW::ANALOG::SKEWY_TAN_RAD(reg,tan_val_Y,0.33);
			}

			void ROT_2SKEWS(areg_t reg,int rotation_steps)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();

				//EACH STEP APPROXIMATELY 0.555... DEGRESS (FROM 1.0/1.8)
				int current_rotation = rotation_steps;
				if(current_rotation > 0)
				{
					for(int n = 0 ; n < current_rotation ; n++)
					{
						IMGTF::SKEW::ANALOG::STEP_SKEWX_CW_F(n);
						IMGTF::SKEW::ANALOG::STEP_SKEWY_CW_F(n);
					}
				}
				else
				{
					for(int n = 0 ; n < -current_rotation ; n++)
					{
						IMGTF::SKEW::ANALOG::STEP_SKEWX_ACW_F(n);
						IMGTF::SKEW::ANALOG::STEP_SKEWY_ACW_F(n);
					}
				}

				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}

			int STEP_ROT_2SKEWS(areg_t reg,int current_rot_value, bool rot_ACW)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();

				//EACH STEP APPROXIMATELY 0.555... DEGRESS (FROM 1.0/1.8)
				if(current_rot_value > 0)
				{
					if(!rot_ACW)
					{
						IMGTF::SKEW::ANALOG::STEP_SKEWX_CW_F(current_rot_value);
						IMGTF::SKEW::ANALOG::STEP_SKEWY_CW_F(current_rot_value);
						current_rot_value = current_rot_value + 1;
					}
					else
					{
						current_rot_value = current_rot_value - 1;
						IMGTF::SKEW::ANALOG::STEP_SKEWY_ACW_F(current_rot_value);
						IMGTF::SKEW::ANALOG::STEP_SKEWX_ACW_F(current_rot_value);
					}
				}
				else
				{
					if(current_rot_value < 0)
					{
						if(!rot_ACW)
						{
							current_rot_value = current_rot_value + 1;
							IMGTF::SKEW::ANALOG::STEP_SKEWY_CW_F(-current_rot_value);
							IMGTF::SKEW::ANALOG::STEP_SKEWX_CW_F(-current_rot_value);
						}
						else
						{
							IMGTF::SKEW::ANALOG::STEP_SKEWX_ACW_F(-current_rot_value);
							IMGTF::SKEW::ANALOG::STEP_SKEWY_ACW_F(-current_rot_value);
							current_rot_value = current_rot_value - 1;
						}
					}
					else
					{
						if(!rot_ACW)
						{
							IMGTF::SKEW::ANALOG::STEP_SKEWX_CW_F(current_rot_value);
							IMGTF::SKEW::ANALOG::STEP_SKEWY_CW_F(current_rot_value);
							current_rot_value = current_rot_value + 1;
						}
						else
						{
							IMGTF::SKEW::ANALOG::STEP_SKEWX_ACW_F(current_rot_value);
							IMGTF::SKEW::ANALOG::STEP_SKEWY_ACW_F(current_rot_value);
							current_rot_value = current_rot_value - 1;
						}
					}
				}

				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
				return current_rot_value;
			}
		}
	}
}

