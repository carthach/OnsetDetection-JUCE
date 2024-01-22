//
//  FFTW.h
//  spectrumAnalyser
//
//  Created by Cárthach Ó Nuanáin on 03/04/2015.
//
//

#ifndef __spectrumAnalyser__FFTW__
#define __spectrumAnalyser__FFTW__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "kiss_fftr.h"
#include <vector>
#include <complex>

class FFTK {
public:
    FFTK();
    ~FFTK();
    
    std::vector<std::complex<float> > processBlock (const std::vector<float> &block);
    void setup(int SIZE);
    
private:
    kiss_fftr_cfg cfg;
    kiss_fft_cpx *freqdata;

    int SIZE;
};

#endif /* defined(__spectrumAnalyser__FFTW__) */
