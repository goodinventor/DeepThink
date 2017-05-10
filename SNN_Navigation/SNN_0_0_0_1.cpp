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

#include "Arduino.h"
#include "SNN_0_0_0_1.h"

Neuron::Neuron()
{
  // note: one neuron will have to be re-initialized later (since
  // one neuron must start with a charge; for this problem the
  // neuron that starts out with a charge will represent the
  // starting location for the navigation task)
  this->v_i = 0;
  this->u_i = 0;
  this->I_i = 0;
  
  for (int i = 0; i < 8; i++)
  {
    this->d_ij[i] = 0;
  }
  
  for (int j = 0; j < 8; j++)
  {
    this->D_ij = 5;
  }
  
  this->delta = 1.0;
  this->map_xy = 0;
}

void Neuron::Update()
{
  // copy old values of time step t
  double old_v_i = this->v_i;
  double old_u_i = this->u_i;
  double old_I_i = this->I_i;
  
  double old_d_ij[8];
  for (int i = 0; i < 8; i++)
  {
    old_d_ij[i] = this->d_ij[i];
  }
  
  double old_D_ij[8];
  for (int j = 0; j < 8; j++)
  {
    old_D_ij[j] = this->D_ij[j];
  }
  
  // update
  this->v_i = old_u_i + old_I_i;
  this->u_i = min(old_u_i + 1, 0);
  
  // add up inputs from connected neurons
  for (int k = 0; k < 8; k++)
  {
    if (old_d_ij[k] == 1)
    {
      this->I_i += 1;
    }
  }
  
  for (int l = 0; l < 8; l++)
  {
    this->d_ij[l] = max(old_d_ij[l] - 1, 0);
  }
  
  for (int m = 0; m < 8; m++)
  {
    this->D_ij[m] = old_D_ij[m] + this->delta * (this->map_xy - old_D_ij[m]);
  }
}
