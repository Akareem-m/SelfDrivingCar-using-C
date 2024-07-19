#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <simulation.h>

#define NUM_OF_GENERATION 1000

int main()
{
  srand(time(NULL)); // Seed the generator

  SimulationConfig simulationConfig = {10};
  Simulation *simulation = generateSimulation(simulationConfig);

  for (int i = 0; i < NUM_OF_GENERATION; i++)
  {
    printf("\n Starting generation (%d)\n", i);
    simulationMainLoop(simulation);
    restartPopulation(simulation);
  }

  return 0;
}