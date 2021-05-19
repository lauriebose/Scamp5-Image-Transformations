#include "MISC_FUNCTIONS.hpp"
#include "IMG_SCALING.hpp"

#include "MISC_FUNCTIONS.hpp"


static const int scaling_rowcol_order[] = {
		64, 32, 98, 16, 83, 50, 118, 8, 77, 43, 113, 26, 97, 62, 4, 77, 41, 114, 23, 97, 61, 14, 90, 53, 34, 113, 74, 2,
		83, 43, 125, 23, 105, 64, 13, 97, 55, 35, 121, 79, 8, 97, 52, 31, 121, 76, 20, 113, 67, 44, 92, 2, 98, 50, 26, 125,
		76, 14, 115, 65, 40, 92, 8, 113, 61, 35, 89, 22, 77, 50, 106, 5, 118, 62, 34, 91, 20, 78, 50, 110, 13, 74, 44, 106,
		29, 92, 61, 125,
};

namespace IMGTF
{
	namespace SCALING
	{
		namespace ANALOG
		{

			void STEP_SCALE_UP_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];
				scamp5_load_rect(R1,0,0,255,128-i);
				scamp5_load_rect(R2,0,i+128,255,255);

				scamp5_load_rect(R3,0,0,128-i,255);
				scamp5_load_rect(R4,i+128,0,255,255);

				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XW);
					all();

					WHERE(R2);
						bus(F,XE);
					all();

					bus(NEWS,F);

					WHERE(R3);
						bus(F,XS);
					all();

					WHERE(R4);
						bus(F,XN);
					all();
				scamp5_kernel_end();
				return;
			}

			void STEP_SCALE_DOWN_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];
				scamp5_load_rect(R1,0,0,255,128-i);
				scamp5_load_rect(R2,0,i+128,255,255);

				scamp5_load_rect(R3,0,0,128-i,255);
				scamp5_load_rect(R4,i+128,0,255,255);

				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XE);
					all();

					WHERE(R2);
						bus(F,XW);
					all();

					bus(NEWS,F);

					WHERE(R3);
						bus(F,XN);
					all();

					WHERE(R4);
						bus(F,XS);
					all();
				scamp5_kernel_end();
				return;
			}

			void STEP_SCALE_UPY_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];

				scamp5_load_rect(R1,0,0,128-i,255);
				scamp5_load_rect(R2,i+128,0,255,255);


				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XS);
					all();

					WHERE(R2);
						bus(F,XN);
					all();
				scamp5_kernel_end();
				return;

			}

			void STEP_SCALE_DOWNY_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];

				scamp5_load_rect(R1,0,0,128-i,255);
				scamp5_load_rect(R2,i+128,0,255,255);

				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XN);
					all();

					WHERE(R2);
						bus(F,XS);
					all();
				scamp5_kernel_end();
				return;
			}

			void STEP_SCALE_UPX_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];
				scamp5_load_rect(R1,0,0,255,128-i);
				scamp5_load_rect(R2,0,i+128,255,255);

				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XW);
					all();

					WHERE(R2);
						bus(F,XE);
					all();
				scamp5_kernel_end();
				return;
			}

			void STEP_SCALE_DOWNX_F(int step_number)
			{
				unsigned char i = scaling_rowcol_order[step_number];
				scamp5_load_rect(R1,0,0,255,128-i);
				scamp5_load_rect(R2,0,i+128,255,255);

				scamp5_kernel_begin();
					bus(NEWS,F);

					WHERE(R1);
						bus(F,XE);
					all();

					WHERE(R2);
						bus(F,XW);
					all();
				scamp5_kernel_end();
				return;
			}





			void SCALE_Y_F(int scaling_mag, bool scale_down)
			{
				if(!scale_down)
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_UPY_F(n);
					}
				}
				else
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_DOWNY_F(n);
					}
				}
			}


			void SCALE_X_F(int scaling_mag, bool scale_down)
			{
				if(!scale_down)
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_UPX_F(n);
					}
				}
				else
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_DOWNX_F(n);
					}
				}
			}


			void SCALE_F(int scaling_mag, bool scale_down)
			{
				if(!scale_down)
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_UP_F(n);
					}
				}
				else
				{
					for(unsigned char n = 0 ; n < scaling_mag ; n++)
					{
						STEP_SCALE_DOWN_F(n);
					}
				}
			}



			int STEP_SCALE_F(int current_scaling_value, bool scale_DOWN)
			{
				if(current_scaling_value > 0)
				{
					if(!scale_DOWN)
					{
						STEP_SCALE_UPX_F(current_scaling_value);
						STEP_SCALE_UPY_F(current_scaling_value);
						current_scaling_value = current_scaling_value + 1;
					}
					else
					{
						current_scaling_value = current_scaling_value - 1;
						STEP_SCALE_DOWNY_F(current_scaling_value);
						STEP_SCALE_DOWNX_F(current_scaling_value);
					}
				}
				else
				{
					if(current_scaling_value < 0)
					{
						if(!scale_DOWN)
						{
							current_scaling_value = current_scaling_value + 1;
							STEP_SCALE_UPY_F(-current_scaling_value);
							STEP_SCALE_UPX_F(-current_scaling_value);
						}
						else
						{
							STEP_SCALE_DOWNX_F(-current_scaling_value);
							STEP_SCALE_DOWNY_F(-current_scaling_value);
							current_scaling_value = current_scaling_value - 1;
						}
					}
					else
					{
						if(!scale_DOWN)
						{
							STEP_SCALE_UPX_F(current_scaling_value);
							STEP_SCALE_UPY_F(current_scaling_value);
							current_scaling_value = current_scaling_value + 1;
						}
						else
						{
							STEP_SCALE_DOWNX_F(current_scaling_value);
							STEP_SCALE_DOWNY_F(current_scaling_value);
							current_scaling_value = current_scaling_value - 1;
						}
					}
				}
				return current_scaling_value;
			}


			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			void SCALE_Y_AREG(AENUM target, int scaling_mag, bool scale_down)
			{
				copy_areg_into_F(target);
				SCALE_Y_F(scaling_mag, scale_down);
				copy_F_into_areg(target);
			}

			void SCALE_X_AREG(AENUM target, int scaling_mag, bool scale_down)
			{
				copy_areg_into_F(target);
				SCALE_X_F(scaling_mag, scale_down);
				copy_F_into_areg(target);
			}

			void SCALE_AREG(AENUM target, int scaling_mag, bool scale_down)
			{
				copy_areg_into_F(target);
				SCALE_F(scaling_mag, scale_down);
				copy_F_into_areg(target);
			}

			int STEP_SCALE_AREG(AENUM target, int current_scaling_value, bool scale_down)
			{
				copy_areg_into_F(target);
				int ret = STEP_SCALE_F(current_scaling_value, scale_down);
				copy_F_into_areg(target);
				return ret;
			}

			void HALF_SCALE_AREG(AENUM target) //USE R11
			{
				copy_areg_into_F(target);



				scamp5_load_pattern(R11,0,128,255,127);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R4,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,128,0,128,256);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XW);
							DNEWS0(R11,FLAG);
						ALL();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,0,0,255,127);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R2,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,0,128,256);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XE);
							DNEWS0(R11,FLAG);
						all();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,128,0,127,255);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R3,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,128,256,128);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XS);
							DNEWS0(R11,FLAG);
						all();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,0,0,127,255);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R1,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,0,256,128);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XN);
							DNEWS0(R11,FLAG);
						all();
					scamp5_kernel_end();
				}

				copy_F_into_areg(target);
			}

			void POSITIVE_HALF_SCALE_AREG_VIA_R9_R10_R11(AENUM areg_to_scale,int step_value)
			{
				MISC_FUNCTIONS::copy_areg_into_F(areg_to_scale);

				scamp5_load_in(D,-100);
				scamp5_load_in(E,-100);
				scamp5_load_in(step_value);
				scamp5_kernel_begin();
					sub(F,F,IN);
					sub(F,F,IN);
					sub(F,F,IN);
					sub(F,F,IN);
					where(F);
						mov(D,IN);
						add(D,D,IN);
						add(D,D,IN);
						add(D,D,IN);
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
						mov(E,IN);
						add(E,E,IN);
						add(E,E,IN);
						add(E,E,IN);
					NOT(R1,FLAG);
					WHERE(R1);
						add(F,F,IN);
						add(F,F,IN);
					all();

					sub(F,F,IN);
					where(F);
						mov(F,IN);
						add(F,F,IN);
						add(F,F,IN);
						add(F,F,IN);
					NOT(R1,FLAG);
					WHERE(R1);
						sub(F,F,IN);
						sub(F,F,IN);
						sub(F,F,IN);
						sub(F,F,IN);
					all();
				scamp5_kernel_end();

				scamp5_load_pattern(R11,0,128,255,127);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R4,R11);
				scamp5_kernel_end();
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,D);
						WHERE(R11);
							bus(D,XW);
						ALL();

						bus(NEWS,E);
						WHERE(R11);
							bus(E,XW);
						ALL();

						bus(NEWS,F);
						WHERE(R11);
							bus(F,XW);
							DNEWS0(R11,FLAG);
						ALL();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,0,0,255,127);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R2,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,0,128,256);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,D);
						WHERE(R11);
							bus(D,XE);
						ALL();

						bus(NEWS,E);
						WHERE(R11);
							bus(E,XE);
						ALL();

						bus(NEWS,F);
						WHERE(R11);
							bus(F,XE);
							DNEWS0(R11,FLAG);
						ALL();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,128,0,127,255);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R3,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,128,256,128);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,D);
						WHERE(R11);
							bus(D,XS);
						ALL();

						bus(NEWS,E);
						WHERE(R11);
							bus(E,XS);
						ALL();

						bus(NEWS,F);
						WHERE(R11);
							bus(F,XS);
							DNEWS0(R11,FLAG);
						ALL();
					scamp5_kernel_end();
				}

				scamp5_load_pattern(R11,0,0,127,255);

				scamp5_kernel_begin();
					CLR(R1,R2,R3,R4);
					MOV(R1,R11);
				scamp5_kernel_end();

//				load_rect_into_DREG(DENUM::R11,0,0,256,128);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,D);
						WHERE(R11);
							bus(D,XN);
						ALL();

						bus(NEWS,E);
						WHERE(R11);
							bus(E,XN);
						ALL();

						bus(NEWS,F);
						WHERE(R11);
							bus(F,XN);
							DNEWS0(R11,FLAG);
						ALL();
					scamp5_kernel_end();
				}


				scamp5_load_in(step_value);
				scamp5_kernel_begin();
					where(D);
					NOT(R1,FLAG);
					WHERE(R1);
						mov(D,IN);
						sub(D,D,IN);

					where(E);
						add(D,D,IN);
						add(D,D,IN);
					where(F);
						add(D,D,IN);
					all();

					mov(F,D);
				scamp5_kernel_end();

				copy_F_into_areg(areg_to_scale);

//				//SCALE DREGS STORING THE AREG DATA
//				scamp5_kernel_begin();
//					CLR(R1,R2,R3,R4);
//				scamp5_kernel_end();
//				load_rect_into_DREG(DENUM::R0,128,0,128,256);
//				for(int n = 0; n < 64 ; n++)
//				{
//					scamp5_kernel_begin();
//						SET(R2);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R11);
//						MOV(R0,FLAG);
//
//						//SHRINK R11
//						WHERE(R12);
//						DNEWS0(R11,FLAG);
//						MOV(R12,R11); //FLAGGED BY R0
//						MOV(R11,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R10);
//						MOV(R0,FLAG);
//
//						//SHRINK R10
//						WHERE(R12);
//						DNEWS0(R10,FLAG);
//						MOV(R12,R10); //FLAGGED BY R0
//						MOV(R10,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R9);
//						MOV(R0,FLAG);
//
//						//SHRINK R9
//						WHERE(R12);
//						DNEWS0(R9,FLAG);
//						MOV(R12,R9); //FLAGGED BY R0
//						MOV(R9,R12);
//
//						CLR(R2);
//
//						//MOV FLAG
//						SET(R4);
//						WHERE(R0);
//						DNEWS0(R0,FLAG);
//						CLR(R4);
//					scamp5_kernel_end();
//				}
//
//				load_rect_into_DREG(DENUM::R0,0,0,128,256);
//				for(int n = 0; n < 64 ; n++)
//				{
//					scamp5_kernel_begin();
//						SET(R4);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R11);
//						MOV(R0,FLAG);
//
//						//SHRINK R11
//						WHERE(R12);
//						DNEWS0(R11,FLAG);
//						MOV(R12,R11); //FLAGGED BY R0
//						MOV(R11,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R10);
//						MOV(R0,FLAG);
//
//						//SHRINK R10
//						WHERE(R12);
//						DNEWS0(R10,FLAG);
//						MOV(R12,R10); //FLAGGED BY R0
//						MOV(R10,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R9);
//						MOV(R0,FLAG);
//
//						//SHRINK R9
//						WHERE(R12);
//						DNEWS0(R9,FLAG);
//						MOV(R12,R9); //FLAGGED BY R0
//						MOV(R9,R12);
//
//						CLR(R4);
//
//						//MOV FLAG
//						SET(R2);
//						WHERE(R0);
//						DNEWS0(R0,FLAG);
//						CLR(R2);
//					scamp5_kernel_end();
//				}
//
//
//				load_rect_into_DREG(DENUM::R0,0,128,256,128);
//				for(int n = 0; n < 64 ; n++)
//				{
//					scamp5_kernel_begin();
//						SET(R1);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R11);
//						MOV(R0,FLAG);
//
//						//SHRINK R11
//						WHERE(R12);
//						DNEWS0(R11,FLAG);
//						MOV(R12,R11); //FLAGGED BY R0
//						MOV(R11,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R10);
//						MOV(R0,FLAG);
//
//						//SHRINK R10
//						WHERE(R12);
//						DNEWS0(R10,FLAG);
//						MOV(R12,R10); //FLAGGED BY R0
//						MOV(R10,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R9);
//						MOV(R0,FLAG);
//
//						//SHRINK R9
//						WHERE(R12);
//						DNEWS0(R9,FLAG);
//						MOV(R12,R9); //FLAGGED BY R0
//						MOV(R9,R12);
//
//						CLR(R1);
//
//						//MOV FLAG
//						SET(R3);
//						WHERE(R0);
//						DNEWS0(R0,FLAG);
//						CLR(R3);
//					scamp5_kernel_end();
//				}
//
//				load_rect_into_DREG(DENUM::R0,0,0,256,128);
//				for(int n = 0; n < 64 ; n++)
//				{
//					scamp5_kernel_begin();
//						SET(R3);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R11);
//						MOV(R0,FLAG);
//
//						//SHRINK R11
//						WHERE(R12);
//						DNEWS0(R11,FLAG);
//						MOV(R12,R11); //FLAGGED BY R0
//						MOV(R11,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R10);
//						MOV(R0,FLAG);
//
//						//SHRINK R10
//						WHERE(R12);
//						DNEWS0(R10,FLAG);
//						MOV(R12,R10); //FLAGGED BY R0
//						MOV(R10,R12);
//
//						//SET R0, LOAD R9 INTO R12 AND THEN RESTORE R0 FLAG
//						WHERE(R0);
//						SET(R0);
//						MOV(R12,R9);
//						MOV(R0,FLAG);
//
//						//SHRINK R9
//						WHERE(R12);
//						DNEWS0(R9,FLAG);
//						MOV(R12,R9); //FLAGGED BY R0
//						MOV(R9,R12);
//
//						CLR(R3);
//
//						//MOV FLAG
//						SET(R1);
//						WHERE(R0);
//						DNEWS0(R0,FLAG);
//						CLR(R1);
//					scamp5_kernel_end();
//				}
//
//
//				scamp5_kernel_begin();
//					all();
//				scamp5_kernel_end();
//
//				scamp5_load_in(F,0);
//				scamp5_load_in(step_value);
//				scamp5_kernel_begin();
//					WHERE(R9);
//						add(F,F,IN);
//						add(F,F,IN);
//						add(F,F,IN);
//						add(F,F,IN);
//
//					WHERE(R10);
//						add(F,F,IN);
//						add(F,F,IN);
//
//					WHERE(R11);
//						add(F,F,IN);
//					ALL();
//				scamp5_kernel_end();

//				MISC_FUNCTIONS::copy_F_into_areg(areg_to_scale);
			}


		}
	}
}

