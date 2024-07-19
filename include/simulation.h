/**
 * @file simulation.h
 * @brief This file is responsible for simulating AI, it connects the context, world, dummies, and AI together
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <context.h>
#include <world.h>
#include <dummy.h>
#include <ai/AI.h>

/**
 * @brief Simulation main structure holds everything
 *
 */
typedef struct Simulation
{
  Context *context;
  World *world;
  unsigned int numOfDummies;
  Dummy **dummies;
  AI *agent;
  unsigned int dummiesLeft;
} Simulation;

/**
 * @brief Configuration structure
 *
 */
typedef struct SimulationConfig
{
  unsigned int numOfDummies;
} SimulationConfig;

/**
 * @brief Initialize the structure and generate the context, world, and dummies
 *
 * @param s : Simulation to be initialized
 */
void initSimulation(Simulation *s);

/**
 * @brief Generate simulation object and allocate it to heap
 *
 * @param config : configuration object for the simulation
 * @return Simulation*
 */
Simulation *generateSimulation(SimulationConfig config);

/**
 * @brief Start the simulation main loop
 *
 * @param s : Simulation to start
 */
void simulationMainLoop(Simulation *s);

/**
 * @brief Spawn dummy to world
 *
 * @param s : Simulation
 * @return Dummy*
 */
Dummy *simulationSpawnDummy(Simulation *s);

/**
 * @brief
 *
 */
void dummyInsideCheckpoint(Simulation *s, Dummy *d, int i);

void checkCollision(Simulation *s, Dummy *d);

void moveDummies(Simulation *s);

void updateAI(Simulation *s);

void restartPopulation(Simulation *s);

#endif // __SIMULATION_H__