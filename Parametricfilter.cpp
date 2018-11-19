/*
  ==============================================================================

    Parametricfilter.cpp
    Created: 5 Nov 2018 11:50:50pm
    Author:  Julian Esteban Nieto Diaz

  ==============================================================================
*/

#include "Parametricfilter.h"
#include <math.h>


float *Parametricfilter::proceso(const float* in, float* out, unsigned length) {
    
    float pi = 3.141592;float omega_0 = (2*pi*f/44100);
    //Coeficientes
    double b1 = 2* -2*r_z*cos(omega_0); double b2 = pow(r_z,2);
    double a1 = 2* -2*r_p*cos(omega_0); double a2 = pow(r_p,2);
    
    
    
    // static float y[512]; //definicion de y a 512 muestras
    
    switch (modo) {
 
            
        case Forma_Directa_II:
            m1 = 0; m2 = 0;
            for (unsigned i = 0; i < length; ++i)
            {   register float w = in[i] - a1*m1 - a2*m2;
                out[i] = b1*m1 + b2*m2 + w;
                m2 = m1; m1 = w;
                
                return out;
            }
    }
    
}

// w(n) = x(n) - a1 w(n-1) - a2 w(n-2)
// y(n) = w(n) + b1 w(n-1) + b2 w(n-2)

// x(n) = in[i], w = w(n)
// m1 = w(n-1), m2 = w(n-2)




