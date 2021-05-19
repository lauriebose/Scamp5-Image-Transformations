#include <scamp5.hpp>
#include <math.h>

#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_SKEW_DIGITAL
#define IMG_SKEW_DIGITAL

namespace IMGTF
{
	namespace SKEW
	{
		namespace DIGITAL
		{
			void SKEWX_R11(int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWX_R11_TAN_RAD(double tan_of_angle,double offset);
			void SKEWX_R11_RAD(double angle,double offset);
			void SKEWX_R11_DEG(double angle,double offset);

			void SKEWY_R11(int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWY_R11_TAN_RAD(double tan_of_angle,double offset);
			void SKEWY_R11_RAD(double angle,double offset);
			void SKEWY_R11_DEG(double angle,double offset);

			void STEP_SKEWX_CW_R11(int step_number);
			void STEP_SKEWX_ACW_R11(int step_number);
			void STEP_SKEWY_CW_R11(int step_number);
			void STEP_SKEWY_ACW_R11(int step_number);
		}
	}
}

#endif
