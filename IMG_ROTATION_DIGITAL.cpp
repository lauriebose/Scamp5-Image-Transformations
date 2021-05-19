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
			void ROT_3SKEWS_R11(double angle_radians)
			{
				double skewY_val = tan_approx3(0.5*angle_radians);
				double skewX_val = sin_approx3(angle_radians);

				double tan_val_Y = tan_approx3(M_PI*skewY_val*0.25);
				double tan_val_X = tan_approx3(M_PI*skewX_val*0.25);

				double temp_val = 33;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::DIGITAL::SKEWY_R11_TAN_RAD(tan_val_Y,temp_val);

				temp_val = 66;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::DIGITAL::SKEWX_R11_TAN_RAD(tan_val_X,temp_val);

				temp_val = 33;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::DIGITAL::SKEWY_R11_TAN_RAD(tan_val_Y,temp_val);
			}

			void ROT_3SKEWS_DREG(DENUM target, double angle_radians)
			{
				copy_dreg_into_R11(target);
				ROT_3SKEWS_R11(angle_radians);
				copy_R11_into_dreg(target);
			}

			void ROT_2SKEWS_R11(int rotation_steps)
			{
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
			}

			void ROT_2SKEWS_DREG(DENUM target,int rotation_steps)
			{
				copy_dreg_into_R11(target);
				ROT_2SKEWS_R11(rotation_steps);
				copy_R11_into_dreg(target);
			}

			int STEP_ROT_2SKEWS_R11(int current_rot_value, bool rot_ACW)
			{
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
				return current_rot_value;
			}

			int STEP_ROT_2SKEWS_R11(DENUM target, int current_rot_value, bool rot_ACW)
			{
				copy_dreg_into_R11(target);
				int ret = STEP_ROT_2SKEWS_R11(current_rot_value, rot_ACW);
				copy_R11_into_dreg(target);
				return ret;
			}

		}
	}
}




