//
// SNN_0_0_0_1.h
//
// programmed by George Andrews
//
// This library is the implementation of a spiking neural network
// (SNN). The algorithm used is the one specified in Path
// Planning using a Spiking Neuron Algorithm with Axonal Delays
// by Jeffrey L. Krichmar.
//

#ifndef SNN_0_0_0_1_h
#define SNN_0_0_0_1_h

#include "Arduino.h"

class Neuron
{
  public:
    //
    // variables
    //
    
    // membrane action potential of the neuron
    double v_i;
    
    // recovery variable of the neuron
    double u_i;
    
    // current input
    double I_i;
    
    // axonal delay
    double d_ij[8];
    
    // delay value
    double D_ij[8];
    
    // learning rate
    double delta;
    
    // value of environment at location (x,y)
    double map_xy;
    
    // list of connected neurons: order is clockwise starting
    // with North
    Neuron ConnectedNeurons[8];
    
    //
    // functions
    //
    
    // class constructor
    Neuron();
    
    // update parameters over one time step
    void Update();
  
    // simulate a spike
    void Spike();
};

#endif
