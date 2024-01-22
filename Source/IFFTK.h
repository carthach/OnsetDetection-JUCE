//
//  FFTW.h
//  spectrumAnalyser
//
//  Created by Cárthach Ó Nuanáin on 03/04/2015.
//
//

#ifndef __spectrumAnalyser__IIFFTK__
#define __spectrumAnalyser__IIFFTK__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "kiss_fftr.h"
#include <vector>
#include <complex>

class IFFTK {
public:
    IFFTK();
    ~IFFTK();
    
    std::vector<float > processBlock (const std::vector<std::complex<float> > &freqdata);
    void allocate(int SIZE);
    
private:
    kiss_fftr_cfg cfg;
    kiss_fft_scalar *timedata;
    int SIZE;
};

#endif /* defined(__spectrumAnalyser__FFTW__) */
