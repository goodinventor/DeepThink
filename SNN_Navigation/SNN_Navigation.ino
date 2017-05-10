//
// SNN_Navigation.ino
//
// programmed by George Andrews
//
// This program uses a spiking neural network (SNN) to plan
// paths in maps. This example uses sample maps (built-in to the
// program) and sends the output over serial (which will be
// processed using other software). The algorithm used is the one
// listed in Path Planning using a Spiking Neuron Algorithm with
// Axonal Delays by Jeffrey L. Krichmar.
//

#include "Timer.h"
#include "SNN_0_0_0_1.h"

// neurons
Neuron neuron1;
Neuron neuron2;
Neuron neuron3;
Neuron neuron4;
Neuron neuron5;
Neuron neuron6;
Neuron neuron7;
Neuron neuron8;
Neuron neuron9;
Neuron neuron10;
Neuron neuron11;
Neuron neuron12;
Neuron neuron13;
Neuron neuron14;
Neuron neuron15;
Neuron neuron16;

neuron1.ConnectedNeurons = {null, null, neuron2, neuron6, neuron5, null, null, null};
neuron2.ConnectedNeurons = {null, null, neuron3, neuron7, neuron6, neuron5, neuron1, null};
neuron3.ConnectedNeurons = {null, null, neuron4, neuron8, neuron7, neuron6, neuron2, null};
neuron4.ConnectedNeurons = {null, null, null, null, neuron8, neuron7, neuron3, null};
neuron5.ConnectedNeurons = {neuron1, neuron2, neuron6, neuron10, neuron9, null, null, null};
neuron6.ConnectedNeurons = {neuron2, neuron3, neuron7, neuron11, neuron10, neuron9, neuron5, neuron1};
neuron7.ConnectedNeurons = {neuron3, neuron4, neuron8, neuron12, neuron11, neuron10, neuron6, neuron2};
neuron8.ConnectedNeurons = {neuron4, null, null, null, neuron12, neuron11, neuron7, neuron3};
neuron9.ConnectedNeurons = {neuron5, neuron6, neuron10, neuron14, neuron13, null, null, null};
neuron10.ConnectedNeurons = {neuron6, neuron7, neuron11, neuron15, neuron14, neuron13, neuron9, neuron5};
neuron11.ConnectedNeurons = {neuron7, neuron8, neuron12, neuron16, neuron15, neuron14, neuron10, neuron6};
neuron12.ConnectedNeurons = {neuron8, null, null, null, neuron16, neuron15, neuron11, neuron7};
neuron13.ConnectedNeurons = {neuron9, neuron10, neuron14, null, null, null, null, null};
neuron14.ConnectedNeurons = {neuron10, neuron11, neuron15, null, null, null, neuron13, neuron9};
neuron15.ConnectedNeurons = {neuron11, neuron12, neuron16, null, null, null, neuron14, neuron10};
neuron16.ConnectedNeurons = {neuron12, null, null, null, null, null, neuron15, neuron11};

// Set environment: allocate values of map_xy for each neuron
// (each number indicates number of time steps until the
// associated neuron fires a spike to all 8 surrounding neurons).
// Roads have a cost of 1, minor obstacles have a cost of 5,
// and major obstacles have a cost of 25. Open spaces have a cost
// of 3.
void LoadEnvironment1()
{
  neuron1.map_xy = 1;
  neuron2.map_xy = 1;
  neuron3.map_xy = 1;
  neuron4.map_xy = 1;
  neuron5.map_xy = 1;
  neuron6.map_xy = 3;
  neuron7.map_xy = 3;
  neuron8.map_xy = 1;
  neuron9.map_xy = 1;
  neuron10.map_xy = 3;
  neuron11.map_xy = 3;
  neuron12.map_xy = 1;
  neuron13.map_xy = 1;
  neuron14.map_xy = 1;
  neuron15.map_xy = 1;
  neuron16.map_xy = 1;
}

// time associated with a time step (in milliseconds)
long time_step = 500;

void setup()
{
  // load the environment
  LoadEnvironment1();
  
  // keep track of program running time for measuring performance
  long run_time = millis();
  
  // start environment 1 at (1,1) (i.e. neuron1)
  neuron1.Update();
}

void loop()
{
}
