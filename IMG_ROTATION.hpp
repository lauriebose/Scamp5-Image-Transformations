#include <scamp5.hpp>
#include <math.h>

#include "IMG_SKEW.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_ROTATION
#define IMG_ROTATION

namespace IMGTF
{
	namespace ROTATION
	{
		namespace ANALOG
		{
			void ROT_3SKEWS_F(double angle_radians);
			void ROT_3SKEWS_AREG(AENUM target,double angle_radians);

			void ROT_2SKEWS_F(int current_rot_value);
			void ROT_2SKEWS_AREG(AENUM target,int current_rot_value);

			int STEP_ROT_2SKEWS_F(int current_rot_value, bool rot_ACW);
			int STEP_ROT_2SKEWS_AREG(AENUM target,int current_rot_value, bool rot_ACW);
		}
	}
}
#endif
