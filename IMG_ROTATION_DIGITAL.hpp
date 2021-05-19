#include <scamp5.hpp>
#include <math.h>

#include "IMG_SKEW_DIGITAL.hpp"
#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_ROTATION_DIGITAL
#define IMG_ROTATION_DIGITAL

namespace IMGTF
{
	namespace ROTATION
	{
		namespace DIGITAL
		{
			void ROT_3SKEWS_R11(double angle_radians);
			void ROT_3SKEWS_DREG(DENUM target, double angle_radians);

			void ROT_2SKEWS_R11(int rotation_steps);
			void ROT_2SKEWS_DREG(DENUM target, int rotation_steps);

			int STEP_ROT_2SKEWS_R11(int current_rot_value, bool rot_ACW);
			int STEP_ROT_2SKEWS_DREG(DENUM target, int current_rot_value, bool rot_ACW);
		}
	}
}

#endif
