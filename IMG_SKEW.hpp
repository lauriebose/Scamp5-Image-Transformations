#include <scamp5.hpp>
#include <math.h>

using namespace SCAMP5_PE;

#ifndef IMG_SKEW
#define IMG_SKEW

namespace IMGTF
{
	namespace SKEW
	{
		namespace ANALOG
		{
			void SKEWX_F(int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWX_F_TAN_RAD(double tan_of_angle,double offset);
			void SKEWX_F_RAD(double angle,double offset);
			void SKEWX_F_DEG(double angle,double offset);

			void SKEWY_F(int skew_mag, bool skew_anti_clockwise,double offset);

			void SKEWY_F_TAN_RAD(double tan_of_angle,double offset);
			void SKEWY_F_RAD(double angle,double offset);
			void SKEWY_F_DEG(double angle,double offset);

			void STEP_SKEWX_CW_F(int step_number);
			void STEP_SKEWX_ACW_F(int step_number);
			void STEP_SKEWY_CW_F(int step_number);
			void STEP_SKEWY_ACW_F(int step_number);
		}
	}
}
#endif
