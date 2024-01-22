/*
  ==============================================================================

    Helper.h
    Created: 15 Apr 2015 5:36:11pm
    Author:  Cárthach Ó Nuanáin

  ==============================================================================
*/

#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

namespace Helper {
    
    /*convert to mono*/
    static float f_mono(float l, float r){
        return(l+r)/2.0f;
    }
    
    static float f_mag(float x, float y) {
	    return (float)sqrt(x*x+y*y);
    }
    
    static float win_multiplier(int n, int SIZE){
        return 0.5 * (1.0-cos(2.0*M_PI*(float)n/(float)SIZE));
    }    
}



#endif  // HELPER_H_INCLUDED
