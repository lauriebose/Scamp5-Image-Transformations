#include <scamp5.hpp>
#include <math.h>
#include "IMG_TF_HELPER.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_SKEW
#define IMG_SKEW

namespace IMGTF
{
	namespace SKEW
	{
		namespace ANALOG
		{
			void SKEWX(areg_t reg,int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWX_TAN_RAD(areg_t reg,double tan_of_angle,double offset);
			void SKEWX_RAD(areg_t reg,double angle,double offset);
			void SKEWX_DEG(areg_t reg,double angle,double offset);

			void SKEWY(areg_t reg,int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWY_TAN_RAD(areg_t reg,double tan_of_angle,double offset);
			void SKEWY_RAD(areg_t reg,double angle,double offset);
			void SKEWY_DEG(areg_t reg,double angle,double offset);

			void STEP_SKEWX_CW_F(int step_number);
			void STEP_SKEWX_ACW_F(int step_number);
			void STEP_SKEWY_CW_F(int step_number);
			void STEP_SKEWY_ACW_F(int step_number);
		}
	}
}
#endif
