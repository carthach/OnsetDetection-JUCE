//
//  FFTW.cpp
//  spectrumAnalyser
//
//  Created by Cárthach Ó Nuanáin on 03/04/2015.
//
//

#include "IFFTK.h"

IFFTK::IFFTK()
{
    cfg = NULL;
    timedata = NULL;
}

IFFTK::~IFFTK()
{
    free(cfg);
    free(timedata);
}

void IFFTK::allocate(int SIZE)
{
    free(timedata);
    free(cfg);
    cfg = kiss_fftr_alloc(SIZE, 1, 0, 0);
    timedata = (kiss_fft_scalar * ) malloc(sizeof(kiss_fft_scalar) * SIZE);
    
    this->SIZE = SIZE;
}

std::vector<float > IFFTK::processBlock (const std::vector<std::complex<float> > &freqdata)
{

    
    kiss_fftri(cfg,(const kiss_fft_cpx *) &freqdata[0],(kiss_fft_scalar *) timedata);
    
    std::vector<float> result(SIZE);

    for(int i=0; i<SIZE; i++)
        result[i] = timedata[i];
    
    return result;
}