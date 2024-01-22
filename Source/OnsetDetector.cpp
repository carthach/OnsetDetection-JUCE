//
//  OnsetDetector.cpp
//  onsetDetector
//
//  Created by Cárthach Ó Nuanáin on 17/04/2015.
//
//

#include "OnsetDetector.h"
#include "Helper.h"

OnsetDetector::OnsetDetector()
{
    onsetFunction = std::vector<float>(11, 0.0f);
    head = 0;
    indexOfLastOnset = 0;
    
    maxOnset = 0.0f;
}

OnsetDetector::~OnsetDetector()
{
    std::cout << "maxOnset: " << maxOnset << "\n";
}

bool isMax(std::vector<float> &onsetFunction, int index, int noOfFrames)
{
    int maxIndex = index;
    float maxValue = onsetFunction[index];
    
    int iterator = index;
    for(int i=0; i<noOfFrames; i++) {
        if(onsetFunction[iterator] > maxValue) {
            maxIndex = iterator;
            maxValue = onsetFunction[iterator];
        }
        iterator = (iterator + onsetFunction.size() - 1) % onsetFunction.size();
    }
    
    if (maxIndex == index)
        return true;
    
    return false;
}

float average(std::vector<float> &onsetFunction, int index, int noOfFrames)
{
    //Get average of the onsetFunction to get a threshold value
    float average = 0.0f;
    //    std::cout << "**************************\n";
    
    int iterator = index;
    for(int i=0; i<noOfFrames; i++) {
        average += onsetFunction[iterator];
        iterator = (iterator + onsetFunction.size() - 1) % onsetFunction.size();
    }
    
    return average / (float)noOfFrames;
}

/*Euclidean distance between frames*/
float difference(float *array0, float *array1, int array_size)
{
    float dist = 0.0f;
    int i;
    for(i=0; i<array_size; i++)
    {
        float val = array0[i]-array1[i];
        dist += val;
    }
    
    return dist;
}

void OnsetDetector::setup(int blockSize)
{
    fft.setup(blockSize);
    
    lastSpectrum = std::vector<float>(blockSize/2-1,0.0f);
}

bool OnsetDetector::hasOnset(std::vector<float>& block)
{
    for(int i=0; i<block.size();i++) {
        Helper::win_multiplier(i, block.size());
    }
    
    std::vector<std::complex<float> > fftData = fft.processBlock(block);
    
    std::vector<float> spectrum;
    for(int i=1; i<fftData.size()-1; i++) { //Omit dc/nyquist
        float binValue = Helper::f_mag(fftData[i].real(), fftData[i].imag());
        binValue /= fftData.size(); //Scale
        spectrum.push_back(binValue);
    }
    
    //Differentiate
    onsetFunction[head] = difference(&spectrum[0], &lastSpectrum[0], spectrum.size());
    lastSpectrum = spectrum;
    
    //Rectify
    if(onsetFunction[head] < 0.0f)
        onsetFunction[head] = 0.0f;
    
    //LP

/*
    1. ODF(n) = max(ODF(n − w1 : n + w2)
    2. ODF(n) ≥ mean(ODF(n − w3 : n + w4)) + δ
    3. n − nlast onset > w5
 */
    
    int w1 = 5;
    int w3 = 5;
    int w5 = 3;
    

    
    
//    bool criteria1 = isMax(onsetFunction, head, w1);
//
//    bool criteria2= false;
//    
//    float criteria2Val = average(onsetFunction, head, w3) + fixedThreshold;
//    
//    if(onsetFunction[head] >= criteria2Val)
//        criteria2 = true;
//    
//    bool criteria3 = true;
//
//    int onsetDistance = (head - indexOfLastOnset) % onsetFunction.size();
//    if (abs(onsetDistance) > w5)
//        criteria3 = true;
//
//    bool result = false;
//    if(criteria1 && criteria2 && criteria3) {
//        result = true;
//        indexOfLastOnset = head;
//    }
    
    bool result = false;
    if(onsetFunction[head] > fixedThreshold)
        result = true;
    
    if(onsetFunction[head] > maxOnset)
        maxOnset = onsetFunction[head];

    
    head++;
    head = head % onsetFunction.size();
    
    return result;
}

