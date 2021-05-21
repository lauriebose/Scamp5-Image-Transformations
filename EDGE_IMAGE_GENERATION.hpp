#include <scamp5.hpp>

scamp5_kernel sobel_edge_R5([]{

    using namespace scamp5_kernel_api;

    // vertical edge
    mov(A,C,north);
    mov(B,C,south);
    add(A,A,B);
    add(A,A,C);
    add(A,A,C);

    mov(B,A,east);
    mov(A,A,west);

    sub(B,B,A);// B = B - A
    abs(D,B);// D is the vertical edge

    // horizontal edge
    mov(A,C,east);
    mov(B,C,west);
    add(A,A,B);
    add(A,A,C);
    add(A,A,C);

    mov(B,A,south);
    mov(A,A,north);

    sub(B,B,A);// B = B - A
    abs(A,B);// A is the horizontal edge

    add(A,A,D);// merge both result

    // digitize
    sub(A,A,IN);
    where(A);
    	MOV(R9,FLAG);
    all();

    // filter stand-alone points
    DNEWS(R8,R9,east|west|north|south);
    NOT(R7,R8);
    CLR_IF(R9,R7);

    // merge result into R5
    MOV(R8,R5);
	OR(R5,R8,R9);

    res(A);

});


scamp5_kernel gain_x2_C([]{
	using namespace scamp5_kernel_api;
	where(C);
		mov(A,C);
		mov(B,C);
		add(C,A,B);
	all();
});


void acquire_edge_image(int gain,int edge_threshold, int edge_expansion,int HDR_iterations, int HDR_exposure_time)
{
	//first exposure
	scamp5_kernel_begin();
		get_image(C);
		CLR(R5);
		respix(F);// store reset level of PIX in F
	scamp5_kernel_end();

	// apply gain and get edge map
	scamp5_load_in(edge_threshold);
	scamp5_launch_kernel(sobel_edge_R5);

	for(int n = 0 ; n < gain ; n++)
	{
		scamp5_launch_kernel(gain_x2_C);
		scamp5_load_in(edge_threshold);
		scamp5_launch_kernel(sobel_edge_R5);
	}

	scamp5_kernel_begin();
		mov(D,C);
		respix(C);// store reset level of PIX in F
	scamp5_kernel_end();

	// short exposure iterations to deal with high light part
	for(int i=0;i<HDR_iterations;i++){
		vs_wait(HDR_exposure_time);

		scamp5_kernel_begin();
			getpix(C,F);
		scamp5_kernel_end();

		scamp5_load_in(edge_threshold);
		scamp5_launch_kernel(sobel_edge_R5);

		scamp5_kernel_begin();
			mov(E,C);
			add(C,C,D);
		scamp5_kernel_end();

		scamp5_load_in(edge_threshold);
		scamp5_launch_kernel(sobel_edge_R5);

		scamp5_kernel_begin();
			mov(C,E);
		scamp5_kernel_end();
	}

	for(int n = 0 ; n < edge_expansion ; n++)
	{
		scamp5_kernel_begin();
			DNEWS(R11,R5,east | west | south | north);
			MOV(R1,R5);
			OR(R5,R1,R11);
		scamp5_kernel_end();
	}
}
