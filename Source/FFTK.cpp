//
//  FFTW.cpp
//  spectrumAnalyser
//
//  Created by Cárthach Ó Nuanáin on 03/04/2015.
//
//

#include "FFTK.h"

FFTK::FFTK()
{
    cfg = NULL;
    freqdata = NULL;
}

FFTK::~FFTK()
{
    free(cfg);
    free(freqdata);
}

void FFTK::setup(int SIZE)
{
    free(freqdata);
    free(cfg);
    cfg = kiss_fftr_alloc(SIZE, 0, 0, 0);
    freqdata = (kiss_fft_cpx * ) malloc(sizeof(kiss_fft_cpx) * SIZE/2+1);
    
    this->SIZE = SIZE;
}

std::vector<std::complex<float> > FFTK::processBlock (const std::vector<float> &block)
{
    kiss_fftr(cfg,(const kiss_fft_scalar *) &block[0], freqdata);
    
    std::vector<std::complex<float> > result(SIZE/2+1);
    
    for(int i=0; i<result.size(); i++) {
        result[i] = std::complex<float>((float)freqdata[i].r, (float)freqdata[i].i);
    }
    
    return result;
}