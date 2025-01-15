#include "MISC_FUNCTIONS.hpp"

#define EAST	XE
#define WEST	XW
#define SOUTH	XS
#define NORTH	XN

void copy_dreg_into_R11(ENUM_DREG reg)
{
	switch(reg)
	{
		case ENUM_DREG::R0:
			scamp5_kernel_begin();
				MOV(R11,R0);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R1:
			scamp5_kernel_begin();
				MOV(R11,R1);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R2:
			scamp5_kernel_begin();
				MOV(R11,R2);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R3:
			scamp5_kernel_begin();
				MOV(R11,R3);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R4:
			scamp5_kernel_begin();
				MOV(R11,R4);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R5:
			scamp5_kernel_begin();
				MOV(R11,R5);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R6:
			scamp5_kernel_begin();
				MOV(R11,R6);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R7:
			scamp5_kernel_begin();
				MOV(R11,R7);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R8:
			scamp5_kernel_begin();
				MOV(R11,R8);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R9:
			scamp5_kernel_begin();
				MOV(R11,R9);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R10:
			scamp5_kernel_begin();
				MOV(R11,R10);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R11:
			break;
		case ENUM_DREG::R12:
			scamp5_kernel_begin();
				MOV(R11,R12);
			scamp5_kernel_end();
			break;
	}
}

void copy_R11_into_dreg(ENUM_DREG reg)
{
	switch(reg)
	{
		case ENUM_DREG::R0:
			scamp5_kernel_begin();
				MOV(R0,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R1:
			scamp5_kernel_begin();
				MOV(R1,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R2:
			scamp5_kernel_begin();
				MOV(R2,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R3:
			scamp5_kernel_begin();
				MOV(R3,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R4:
			scamp5_kernel_begin();
				MOV(R4,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R5:
			scamp5_kernel_begin();
				MOV(R5,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R6:
			scamp5_kernel_begin();
				MOV(R6,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R7:
			scamp5_kernel_begin();
				MOV(R7,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R8:
			scamp5_kernel_begin();
				MOV(R8,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R9:
			scamp5_kernel_begin();
				MOV(R9,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R10:
			scamp5_kernel_begin();
				MOV(R10,R11);
			scamp5_kernel_end();
			break;
		case ENUM_DREG::R11:
			break;
		case ENUM_DREG::R12:
			scamp5_kernel_begin();
				MOV(R12,R11);
			scamp5_kernel_end();
			break;
	}
}

void copy_F_into_areg(ENUM_AREG reg)
{
	switch(reg)
	{
		case ENUM_AREG::A:
				scamp5_kernel_begin();
					mov(A,F);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::B:
				scamp5_kernel_begin();
					mov(B,F);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::C:
				scamp5_kernel_begin();
					mov(C,F);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::D:
				scamp5_kernel_begin();
					mov(D,F);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::E:
				scamp5_kernel_begin();
					mov(E,F);
				scamp5_kernel_end();
				break;
	}
}

void copy_areg_into_F(ENUM_AREG reg)
{
	switch(reg)
	{
		case ENUM_AREG::A:
				scamp5_kernel_begin();
					mov(F,A);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::B:
				scamp5_kernel_begin();
					mov(F,B);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::C:
				scamp5_kernel_begin();
					mov(F,C);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::D:
				scamp5_kernel_begin();
					mov(F,D);
				scamp5_kernel_end();
				break;
		case ENUM_AREG::E:
				scamp5_kernel_begin();
					mov(F,E);
				scamp5_kernel_end();
				break;
	}
}

