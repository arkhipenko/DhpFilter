//
// Integer math only implementation of the high-pass filter
//


#include <Arduino.h>

#ifndef _DHPFILTER_H
#define _DHPFILTER_H



class dhpFilter {

	public: 
		dhpFilter(long aInitValue=0);
	
		void	initialize(long aInitValue);
		long value(long aSample);

	private:
		long	iLastSample;
		long	iShiftedFilter;
};

dhpFilter::dhpFilter(long aInitValue) {
	initialize(aInitValue);
}

void dhpFilter::initialize(long aInitValue) {
	iLastSample = aInitValue;
	iShiftedFilter = aInitValue << 8;
}


long dhpFilter::value(long aSample) {

	long shiftedFCL = iShiftedFilter + ((aSample-iLastSample)<<8);

	iLastSample = aSample;
	iShiftedFilter = shiftedFCL - 5*(shiftedFCL>>7);
	return (iShiftedFilter+128)>>8;
}

#endif  // _DHPFILTER_H

