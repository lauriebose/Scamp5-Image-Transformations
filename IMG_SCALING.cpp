#include "IMG_SCALING.hpp"

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





			void SCALE_Y(areg_t reg,int scaling_mag, bool scale_down)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();
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
				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}


			void SCALE_X(areg_t reg,int scaling_mag, bool scale_down)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();
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
				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}


			void SCALE(areg_t reg,int scaling_mag, bool scale_down)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();
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
				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}



			int STEP_SCALE(areg_t reg,int current_scaling_value, bool scale_DOWN)
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();
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
				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
				return current_scaling_value;
			}


			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			void HALF_SCALE(areg_t reg) //USE R11
			{
				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();

				uint8_t x = 128;
				uint8_t y = 0;
				uint8_t w = 127;
				uint8_t h = 255;
				scamp5_load_rect(R11,y,x,y+h,x+w);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XW);
						all();
					scamp5_kernel_end();
					scamp5_shift(R11,-1,0);
				}

				x = 0;
				y = 0;
				w = 127;
				h = 255;
				scamp5_load_rect(R11,y,x,y+h,x+w);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XE);
						all();
					scamp5_kernel_end();
					scamp5_shift(R11,1,0);
				}

				x = 0;
				y = 128;
				w = 255;
				h = 127;
				scamp5_load_rect(R11,y,x,y+h,x+w);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XS);
						all();
					scamp5_kernel_end();
					scamp5_shift(R11,0,-1);
				}

				x = 0;
				y = 0;
				w = 255;
				h = 127;
				scamp5_load_rect(R11,y,x,y+h,x+w);
				for(int n = 0; n < 64 ; n++)
				{
					scamp5_kernel_begin();
						bus(NEWS,F);
						WHERE(R11);
							bus(F,XN);
						all();
					scamp5_kernel_end();
					scamp5_shift(R11,0,1);
				}

				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}
		}
	}
}

