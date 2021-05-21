#include <scamp5.hpp>
#include <math.h>

#include "IMG_SKEW_DIGITAL.hpp"
#include "IMG_TF_HELPER.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_ROTATION_DIGITAL
#define IMG_ROTATION_DIGITAL

namespace IMGTF
{
	namespace ROTATION
	{
		namespace DIGITAL
		{
			void ROT_3SKEWS(dreg_t reg, double angle_radians);
			void ROT_2SKEWS(dreg_t reg, int rotation_steps);
			int STEP_ROT_2SKEWS(dreg_t reg,int current_rot_value, bool rot_ACW);
		}
	}
}

#endif
