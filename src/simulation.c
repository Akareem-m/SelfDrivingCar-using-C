#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <simulation.h>

#define STARTING_POSITION_X 75.f
#define STARTING_POSITION_Y 550.f

void initSimulation(Simulation *s)
{
  ContextConfig contextConfig = {
      800, 600, "AI Car", sfResize | sfClose, NULL};
  s->context = generateContext(contextConfig);

  // generate world
  WorldConfig worldConfig = {
      "../../assets/stage.png",
      s->context};
  s->world = generateWorld(worldConfig);

  // generete ai agent
  AIConfig aiConfig = {s->numOfDummies};
  s->agent = generateAI(aiConfig);

  s->dummies = (Dummy **)malloc(sizeof(Dummy *) * s->numOfDummies);
  for (int i = 0; i < s->numOfDummies; i++)
  {
    s->dummies[i] = simulationSpawnDummy(s);
    s->dummies[i]->genume = *(s->agent->population + i);
  }

  s->dummiesLeft = s->numOfDummies;
}

Simulation *generateSimulation(SimulationConfig config)
{
  Simulation *simulation = (Simulation *)malloc(sizeof(Simulation));
  simulation->numOfDummies = config.numOfDummies;

  initSimulation(simulation);
  return simulation;
}

Dummy *simulationSpawnDummy(Simulation *s)
{
  DummyConfig d;
  d.position[0] = STARTING_POSITION_X;
  d.position[1] = STARTING_POSITION_Y;
  d.spritePath = "../../assets/car.png";

  Dummy *dummy;
  dummy = generateDummy(d);

  RadarConfig r;
  r.distance = 70;
  r.position[0] = dummy->position[0];
  r.position[1] = dummy->position[1];
  r.World = s->world;
  Radar *radar = generateRadar(r);

  dummy->radar = radar;

  return dummy;
}

void simulationMainLoop(Simulation *s)
{
  time_t t = time(NULL);
  while (isContextOpen(s->context))
  {
    if (time(NULL) - t > 10)
      return;

    if (s->dummiesLeft == 0)
      return;

    sfEvent e;
    while (contextPollEvent(s->context, &e))
    {
      switch (e.type)
      {
      case sfEvtClosed:
        closeContext(s->context);
        break;
      }
    }

    /* Clear the screen */
    clearContext(s->context);

    // Render world
    renderWorld(s->world, (void **)s->dummies, s->numOfDummies);

    // Update Dummies
    for (int i = 0; i < s->numOfDummies; i++)
    {
      if (!s->dummies[i]->alive)
        continue;
      updateDummy(s->dummies[i]);
      checkCollision(s, s->dummies[i]);
    }

    updateAI(s);

    moveDummies(s);

    /* Update the window */
    updateContext(s->context);
  }

  destroyContext(s->context);
}

void dummyInsideCheckpoint(Simulation *s, Dummy *d, int i)
{
  if (d->position[0] >= s->world->checkpointPosition[i][0].x &&
      d->position[0] <= s->world->checkpointPosition[i][0].x + s->world->checkpointPosition[i][1].x &&
      d->position[1] >= s->world->checkpointPosition[i][0].y &&
      d->position[1] <= s->world->checkpointPosition[i][0].y + abs(s->world->checkpointPosition[i][1].y))
  {
    d->genume->fitness.checkpointsReached++;
    printf("%d\n", s->dummies[0]->genume->fitness);
  }
}

void checkCollision(Simulation *s, Dummy *d)
{
  if (dummyCheckCollision(d) && d->alive)
  {
    stopDummy(d);
    s->dummiesLeft--;
  }
}

void moveDummies(Simulation *s)
{
  for (int i = 0; i < s->numOfDummies; i++)
  {
    switch (s->agent->actions[i])
    {
    case FRONT:
      acceleratePhysicsBody(s->dummies[i]->body);
      break;
    case LEFT:
      deacceleratePhysicsBody(s->dummies[i]->body);
      break;
    case RIGHT:
      rotateRightPhysicsBody(s->dummies[i]->body);
      break;
    case BRAKE:
      rotateLeftPhysicsBody(s->dummies[i]->body);
      break;
    }
  }
}

void updateAI(Simulation *s)
{
  float inputs[s->numOfDummies][5];
  for (int i = 0; i < s->numOfDummies; i++)
    for (int j = 0; j < 5; j++)
      inputs[i][j] = s->dummies[i]->radar->power[j];

  for (int i = 0; i < s->numOfDummies; i++)
    if (s->dummies[i]->alive)
      s->agent->actions[i] = trainAI(s->dummies[i]->genume, inputs[i]);
}

void restartPopulation(Simulation *s)
{
  // evolve genes
  evolveAI(s->agent);
  // restart...
  s->dummiesLeft = s->numOfDummies;
  for (int i = 0; i < s->numOfDummies; i++)
  {
    restartDummy(s->dummies[i], STARTING_POSITION_X, STARTING_POSITION_Y);
    s->dummies[i]->genume = s->agent->population[i];
  }
}