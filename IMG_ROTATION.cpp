#include "IMG_SKEW.hpp"
#include "IMG_ROTATION.hpp"

#include "IMG_SKEW.hpp"
using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace ROTATION
	{
		namespace ANALOG
		{
			void ROT_3SKEWS_F(double angle_radians)
			{
				double skewY_val = tan_approx3(0.5*angle_radians);
				double skewX_val = sin_approx3(angle_radians);

				double tan_val_Y = tan_approx3(M_PI*skewY_val*0.25);
				double tan_val_X = tan_approx3(M_PI*skewX_val*0.25);

				double temp_val = 33;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::ANALOG::SKEWY_F_TAN_RAD(tan_val_Y,temp_val);

				temp_val = 66;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::ANALOG::SKEWX_F_TAN_RAD(tan_val_X,temp_val);

				temp_val = 33;
				temp_val = temp_val/100.0;

				IMGTF::SKEW::ANALOG::SKEWY_F_TAN_RAD(tan_val_Y,temp_val);
			}

			void ROT_3SKEWS_AREG(AENUM target,double angle_radians)
			{
				copy_areg_into_F(target);
				ROT_3SKEWS_F(angle_radians);
				copy_F_into_areg(target);
			}

			void ROT_2SKEWS_F(int rotation_steps)
			{
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
			}

			void ROT_2SKEWS_AREG(AENUM target,int rotation_steps)
			{
				copy_areg_into_F(target);
				ROT_2SKEWS_F(rotation_steps);
				copy_F_into_areg(target);
			}

			int STEP_ROT_2SKEWS_F(int current_rot_value, bool rot_ACW)
			{
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
				return current_rot_value;
			}

			int STEP_ROT_2SKEWS_AREG(AENUM target,int current_rot_value, bool rot_ACW)
			{
				copy_areg_into_F(target);
				int ret = STEP_ROT_2SKEWS_F( current_rot_value,  rot_ACW);
				copy_F_into_areg(target);
				return ret;
			}
		}
	}
}

