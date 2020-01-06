// main.cpp

// from https://www.earlevel.com/main/2012/11/26/biquad-c-source-code/

#include <stdio.h>

#include "biquad.h"


// When we need a biquad, we just instantiate the Biquad object, request its initial setting, 
// then call the process function for every sample we want to filter.

void test_biquad1(void)
{
	Biquad *lpFilter = new Biquad();	// create a Biquad, lpFilter;

	lpFilter->setBiquad(bq_type_lowpass, Fc / sampleRate, 0.707, 0);

	// filter a buffer of input samples, in-place
	for (int idx = 0; idx < bufSize; idx++) 
	{
		in[idx] = lpFilter->process(in[idx]);
	}
}

// Here’s an example of cascading two peak filters to yield a 3 dB dip at 200 Hz and a 6 dB bump at 6 kHz:
void test_biquad2(void)
{

	Biquad *filter1 = new Biquad(bq_type_peak, 200.0 / sampleRate, 1.0, -3.0);
	Biquad *filter2 = new Biquad(bq_type_peak, 6000.0 / sampleRate, 5.0, 6.0);

	// filter a buffer of input samples, in-place
	for (int idx = 0; idx < bufSize; idx++) 
	{
		in[idx] = filter2->process(filter1->process(in[idx]));
	}
}

int main(void)
{
	test_biquad2();
	return 0;
	
}
