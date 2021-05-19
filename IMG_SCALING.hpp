#include <scamp5.hpp>
#include <math.h>

#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;


#ifndef IMG_SCALING
#define IMG_SCALING

namespace IMGTF
{
	namespace SCALING
	{
		namespace ANALOG
		{
			void STEP_SCALE_UP_F(int step_number);
			void STEP_SCALE_DOWN_F(int step_number);

			void STEP_SCALE_UPY_F(int step_number);
			void STEP_SCALE_DOWNY_F(int step_number);

			void STEP_SCALE_UPX_F(int step_number);
			void STEP_SCALE_DOWNX_F(int step_number);

			int STEP_SCALE_F(int current_scaling_value, bool scale_down);

			///////////////////////////////////////////

			void SCALE_Y_F(int scaling_mag, bool scale_down);
			void SCALE_X_F(int scaling_mag, bool scale_down);
			void SCALE_F(int scaling_mag, bool scale_down);

			///////////////////////////////////////////

			void SCALE_Y_AREG(AENUM target, int scaling_mag, bool scale_down);
			void SCALE_X_AREG(AENUM target, int scaling_mag, bool scale_down);
			void SCALE_AREG(AENUM target, int scaling_mag, bool scale_down);

			int STEP_SCALE_AREG(AENUM target, int current_scaling_value, bool scale_down);

			///////////////////////////////////////////

			void HALF_SCALE_AREG(AENUM target);
			void POSITIVE_HALF_SCALE_AREG_VIA_R9_R10_R11(AENUM areg_to_scale,int step_value);
		}
	}
}
#endif
