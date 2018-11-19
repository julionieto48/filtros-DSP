/*
  ==============================================================================

    Filter.cpp
    Created: 5 Nov 2018 12:10:35am
    Author:  Julian Esteban Nieto Diaz

  ==============================================================================
*/

#include "Filter.h"

double Filter::process(double inputValue) {
    buf0 += cutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
    buf1 += cutoff * (buf0 - buf1);
    switch (mode) {
        case FILTER_MODE_LOWPASS:
            return buf1;
        case FILTER_MODE_HIGHPASS:
            return inputValue - buf0;
        case FILTER_MODE_BANDPASS:
            return buf0 - buf1;
        default:
            return 0.0;
    }
}


