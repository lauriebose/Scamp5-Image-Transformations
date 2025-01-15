#include <scamp5.hpp>
#include <math.h>
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

#ifndef MISC_FUNCTIONS
#define MISC_FUNCTIONS
	void copy_dreg_into_R11(ENUM_DREG reg);
	void copy_R11_into_dreg(ENUM_DREG reg);

	void copy_areg_into_F(ENUM_AREG reg);
	void copy_F_into_areg(ENUM_AREG reg);
#endif
