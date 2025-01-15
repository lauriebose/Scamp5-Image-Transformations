#include <scamp5.hpp>
#include <math.h>

#include "MISC_FUNCTIONS.hpp"
#include "REGISTER_ENUMS.hpp"

using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace TRANSLATE
	{
		namespace ANALOG
		{
			void POSITIVE_AREG_shift_via_R9_R10_R11(ENUM_AREG areg_to_shift,int shiftx, int shifty, int step_value = 25)
			{
				MISC_FUNCTIONS::copy_areg_into_F(areg_to_shift);

				scamp5_load_in(step_value);
				scamp5_kernel_begin();
					sub(F,F,IN);
					sub(F,F,IN);
					sub(F,F,IN);
					sub(F,F,IN);
					where(F);
						MOV(R9,FLAG);
					NOT(R1,FLAG);
					WHERE(R1);
						add(F,F,IN);
						add(F,F,IN);
						add(F,F,IN);
						add(F,F,IN);
					all();

					sub(F,F,IN);
					sub(F,F,IN);
					where(F);
						MOV(R10,FLAG);
					NOT(R1,FLAG);
					WHERE(R1);
						add(F,F,IN);
						add(F,F,IN);
					all();

					sub(F,F,IN);
					where(F);
						MOV(R11,FLAG);
					NOT(R1,FLAG);
					WHERE(R1);
						add(F,F,IN);
					all();
				scamp5_kernel_end();

				if(shiftx > 0)
				{
					scamp5_kernel_begin();
						CLR(R1,R2,R3,R4);
						SET(R2);
					scamp5_kernel_end();
				}
				else
				{
					if(shiftx < 0)
					{
						scamp5_kernel_begin();
							CLR(R1,R2,R3,R4);
							SET(R4);
						scamp5_kernel_end();
					}
				}

				for(int n = 0 ; n < abs(shiftx)/10 ; n++)
				{
					scamp5_kernel_begin();
						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						ALL();
					scamp5_kernel_end();
				}

				for(int n = 0 ; n < abs(shiftx)%10 ; n++)
				{
					scamp5_kernel_begin();
						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						ALL();
					scamp5_kernel_end();
				}

				if(shifty > 0)
				{
					scamp5_kernel_begin();
						CLR(R1,R2,R3,R4);
						SET(R1);
					scamp5_kernel_end();
				}
				else
				{
					if(shifty < 0)
					{
						scamp5_kernel_begin();
							CLR(R1,R2,R3,R4);
							SET(R3);
						scamp5_kernel_end();
					}
				}

				for(int n = 0 ; n < abs(shifty)/10 ; n++)
				{
					scamp5_kernel_begin();
						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						ALL();
					scamp5_kernel_end();
				}

				for(int n = 0 ; n < abs(shifty)%10 ; n++)
				{
					scamp5_kernel_begin();
						WHERE(R9);
						DNEWS0(R9,FLAG);

						WHERE(R10);
						DNEWS0(R10,FLAG);

						WHERE(R11);
						DNEWS0(R11,FLAG);

						ALL();
					scamp5_kernel_end();
				}

				scamp5_load_in(F,0);
				scamp5_load_in(step_value);
				scamp5_kernel_begin();
					WHERE(R9);
						add(F,F,IN);
						add(F,F,IN);
						add(F,F,IN);
						add(F,F,IN);

					WHERE(R10);
						add(F,F,IN);
						add(F,F,IN);

					WHERE(R11);
						add(F,F,IN);
					ALL();
				scamp5_kernel_end();

				MISC_FUNCTIONS::copy_F_into_areg(areg_to_shift);
			}
		}
	}
}
