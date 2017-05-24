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
Neuron neuron_grid[4][4];

// Set environment: allocate values of map_xy for each neuron
// (each number indicates number of time steps until the
// associated neuron fires a spike to all 8 surrounding neurons).
// Roads have a cost of 1, minor obstacles have a cost of 5,
// and major obstacles have a cost of 25. Open spaces have a cost
// of 3.
void LoadEnvironment1()
{
  for (int i = 0; i < 4; i++)
  {
    neuron_grid[0][i].map_xy = 1;
    neuron_grid[3][i].map_xy = 1;
  }
  for (int j = 1; j < 3; j++)
  {
    neuron_grid[j][0].map_xy = 1;
    neuron_grid[j][3].map_xy = 1;
    neuron_grid[j][1].map_xy = 3;
    neuron_grid[j][2].map_xy = 3;
  }
}

// time associated with a time step (in milliseconds)
long time_step = 500;

void setup()
{
  // load the environment
  LoadEnvironment1();
  
  // keep track of program running time for measuring performance
  long run_time = millis();
  
  // spike top leftmost neuron
  neuron_grid[0][0].Spike();
  
  // start environment 1 at (0,0)
  neuron_grid[0][0].Update();
}

void loop()
{
}
