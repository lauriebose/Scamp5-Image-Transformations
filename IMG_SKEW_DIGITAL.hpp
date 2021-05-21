#include <scamp5.hpp>
#include <math.h>

using namespace SCAMP5_PE;

#ifndef IMG_SKEW_DIGITAL
#define IMG_SKEW_DIGITAL

namespace IMGTF
{
	namespace SKEW
	{
		namespace DIGITAL
		{
			void SKEWX(dreg_t reg,int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWX_TAN_RAD(dreg_t reg,double tan_of_angle,double offset);
			void SKEWX_RAD(dreg_t reg,double angle,double offset);
			void SKEWX_DEG(dreg_t reg,double angle,double offset);

			void SKEWY(dreg_t reg,int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWY_TAN_RAD(dreg_t reg,double tan_of_angle,double offset);
			void SKEWY_RAD(dreg_t reg,double angle,double offset);
			void SKEWY_DEG(dreg_t reg,double angle,double offset);

			void STEP_SKEWX_CW_R11(int step_number);
			void STEP_SKEWX_ACW_R11(int step_number);
			void STEP_SKEWY_CW_R11(int step_number);
			void STEP_SKEWY_ACW_R11(int step_number);
		}
	}
}

#endif
