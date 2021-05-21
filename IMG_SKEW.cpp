#include "IMG_SKEW.hpp"
using namespace SCAMP5_PE;

namespace IMGTF
{
	namespace SKEW
	{
		namespace ANALOG
		{
			void SKEWX(areg_t reg,int skew_mag, bool skew_anti_clockwise,double offset)
			{
				if(skew_mag == 0)
				{
					return;
				}

				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();

				const int scalar_hack = 1000;
				int step_size = (int)(scalar_hack*127.0/skew_mag);
				if(!skew_anti_clockwise)
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;
						scamp5_load_rect(R1,0,0,in,255);
						scamp5_load_rect(R2,255-in,0,255,255);

						scamp5_kernel_begin();
							mov(E,F);

							WHERE(R1);
								mov(F,E,west);
							WHERE(R2);
								mov(F,E,east);
							all();
						 scamp5_kernel_end();
					}
				}
				else
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;
						scamp5_load_rect(R1,0,0,in,255);
						scamp5_load_rect(R2,255-in,0,255,255);

						scamp5_kernel_begin();
							mov(E,F);

							WHERE(R1);
								mov(F,E,east);
							WHERE(R2);
								mov(F,E,west);
							all();
						 scamp5_kernel_end();
					}
				}

				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}

			void SKEWX_TAN_RAD(areg_t reg,double tan_of_angle,double offset)
			{
				double skew_mag = 127.0*tan_of_angle;
				SKEWX(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWX_RAD(areg_t reg,double angle,double offset)
			{
				double skew_mag = 127*tan_approx3(angle);
				SKEWX(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWX_DEG(areg_t reg,double angle,double offset)
			{
				double angle_in_radians = M_PI*angle/180.0;
				SKEWX_RAD(reg,angle_in_radians, offset);
			}

			/////////////////////////////////////////////////////////////////////////

			void SKEWY(areg_t reg,int skew_mag, bool skew_anti_clockwise,double offset)
			{
				if(skew_mag == 0)
				{
					return;
				}

				scamp5_dynamic_kernel_begin();
					mov(F,reg);
				scamp5_dynamic_kernel_end();

				const int scalar_hack = 1000;
				int step_size = (int)(scalar_hack*127.0/skew_mag);

				if(!skew_anti_clockwise)
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;
						scamp5_load_rect(R1,0,0,255,in);
						scamp5_load_rect(R2,0,255-in,255,255);

						scamp5_kernel_begin();
							mov(E,F);

							WHERE(R1);
								mov(F,E,north);
							WHERE(R2);
								mov(F,E,south);
							all();
						scamp5_kernel_end();
					}
				}
				else
				{
					for(int n = offset*step_size  ; n < 127*scalar_hack ; n+= step_size)
					{
						int in = n/scalar_hack;
						scamp5_load_rect(R1,0,0,255,in);
						scamp5_load_rect(R2,0,255-in,255,255);

						scamp5_kernel_begin();
							mov(E,F);

							WHERE(R1);
								mov(F,E,south);
							WHERE(R2);
								mov(F,E,north);
							all();
						scamp5_kernel_end();
					}
				}

				scamp5_dynamic_kernel_begin();
					mov(reg,F);
				scamp5_dynamic_kernel_end();
			}

			void SKEWY_TAN_RAD(areg_t reg,double tan_of_angle,double offset)
			{
				double skew_mag = 127.0*tan_of_angle;
				SKEWY(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWY_RAD(areg_t reg,double angle,double offset)
			{
				double skew_mag = 127.0*tan_approx3(angle);
				SKEWY(reg,(int)fabs(skew_mag),skew_mag > 0 ? true : false, offset);
			}

			void SKEWY_DEG(areg_t reg,double angle,double offset)
			{
				double angle_in_radians = M_PI*angle/180.0;
				SKEWY_RAD(reg,angle_in_radians,offset);
			}

			/////////////////////////////////////////////////////////////////////////

			void STEP_SKEWX_CW_F(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R1,0,0,i,255);
				scamp5_load_rect(R2,255-i,0,255,255);

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

			void STEP_SKEWX_ACW_F(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R1,0,0,i,255);
				scamp5_load_rect(R2,255-i,0,255,255);

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

			void STEP_SKEWY_CW_F(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R1,0,0,255,i);
				scamp5_load_rect(R2,0,255-i,255,255);

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

			void STEP_SKEWY_ACW_F(int step_number)
			{
				unsigned char i = reverse_byte(step_number)/2;

				scamp5_load_rect(R1,0,0,255,i);
				scamp5_load_rect(R2,0,255-i,255,255);

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

		}
	}
}

