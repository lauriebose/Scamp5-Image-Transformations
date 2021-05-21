#include <scamp5.hpp>
#include <math.h>

#include "IMG_SKEW.hpp"
#include "IMG_TF_HELPER.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_ROTATION
#define IMG_ROTATION

namespace IMGTF
{
	namespace ROTATION
	{
		namespace ANALOG
		{
			void ROT_3SKEWS(areg_t reg,double angle_radians);
			void ROT_2SKEWS(areg_t reg,int current_rot_value);
			int STEP_ROT_2SKEWS(areg_t reg,int current_rot_value, bool rot_ACW);
		}
	}
}
#endif
