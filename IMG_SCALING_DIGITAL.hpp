#include <scamp5.hpp>
#include <math.h>

#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;


#ifndef IMG_SCALING_DIGITAL
#define IMG_SCALING_DIGITAL

namespace IMGTF
{
	namespace SCALING
	{
		namespace DIGITAL
		{
			void STEP_SCALE_UP_R11(int step_number);
			void STEP_SCALE_DOWN_R11(int step_number);

			void STEP_SCALE_UPY_R11(int step_number);
			void STEP_SCALE_DOWNY_R11(int step_number);

			void STEP_SCALE_UPX_R11(int step_number);
			void STEP_SCALE_DOWNX_R11(int step_number);

			int STEP_SCALE_R11(int current_scaling_value, bool scale_down);

			///////////////////////////////////////////

			void SCALE_Y_R11(int scaling_mag, bool scale_down);
			void SCALE_X_R11(int scaling_mag, bool scale_down);
			void SCALE_R11(int scaling_mag, bool scale_down);

			///////////////////////////////////////////

			void SCALE_Y_DREG(DENUM target,int scaling_mag, bool scale_down);
			void SCALE_X_DREG(DENUM target,int scaling_mag, bool scale_down);
			void SCALE_DREG(DENUM target,int scaling_mag, bool scale_down);

			int STEP_SCALE_DREG(DENUM target,int current_scaling_value, bool scale_down);

			void HALF_SCALE_DREG(DENUM target);
		}
	}
}
#endif
