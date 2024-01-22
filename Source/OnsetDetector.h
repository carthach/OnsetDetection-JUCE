//
//  OnsetDetector.h
//  onsetDetector
//
//  Created by Cárthach Ó Nuanáin on 17/04/2015.
//
//

#ifndef __onsetDetector__OnsetDetector__
#define __onsetDetector__OnsetDetector__

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "FFTK.h"

#endif /* defined(__onsetDetector__OnsetDetector__) */

class OnsetDetector {
public:
    OnsetDetector();
    ~OnsetDetector();
    
    bool hasOnset(std::vector<float>& block);
    void setup(int blockSize);
    
    FFTK fft;
    
    std::vector<float> lastSpectrum;
    std::vector<float> onsetFunction;
    
    int head;
    int indexOfLastOnset;
    
    float maxOnset;
    float fixedThreshold = 0.1;
};
