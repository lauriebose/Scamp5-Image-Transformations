#include <scamp5.hpp>
#include <math.h>

#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

#ifndef IMG_TRANSLATE_ANALOG
#define IMG_TRANSLATE_ANALOG

namespace IMGTF
{
	namespace TRANSLATE
	{
		namespace ANALOG
		{
			void POSITIVE_AREG_shift_via_R9_R10_R11(AENUM areg_to_shift,int shiftx, int shifty, int step_value = 25);
		}
	}
}
#endif
