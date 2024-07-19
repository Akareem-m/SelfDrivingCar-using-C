#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include <ai/genome.h>

void initGenome(Genome *g)
{
  g->fitness.checkpointsReached = 0;
  g->fitness.timeTaken = 0.f;

  for (int i = 0; i < g->sensorsNum; i++)
    for (int j = 0; j < g->hiddenNum; j++)
      g->weights_ih[i][j] = (float)rand() / (float)RAND_MAX;

  for (int i = 0; i < g->hiddenNum; i++)
  {
    g->biases_h[i] = (float)rand() / (float)RAND_MAX;
    for (int j = 0; j < g->outputNum; j++)
    {
      g->biases_o[j] = (float)rand() / (float)RAND_MAX;
      g->weights_ho[i][j] = (float)rand() / (float)RAND_MAX;
    }
  }
}

Genome *generateGenome(GenomeConfig c)
{
  Genome *g = (Genome *)malloc(sizeof(Genome));
  g->weights_ih = (float **)malloc(sizeof(float *) * c.sensorsNum);
  for (int i = 0; i < c.sensorsNum; i++)
    g->weights_ih[i] = (float *)malloc(sizeof(float) * c.hiddenNum);

  g->weights_ho = (float **)malloc(sizeof(float *) * c.hiddenNum);
  for (int i = 0; i < c.hiddenNum; i++)
    g->weights_ho[i] = (float *)malloc(sizeof(float) * c.outputNum);

  g->biases_h = (float *)malloc(sizeof(float) * c.hiddenNum);
  g->biases_o = (float *)malloc(sizeof(float) * c.outputNum);

  g->sensorsNum = c.sensorsNum;
  g->hiddenNum = c.hiddenNum;
  g->outputNum = c.outputNum;

  initGenome(g);

  return g;
}

float genomeFitness(Genome *g)
{
  float fitnesss = 0.f;
  fitnesss += g->fitness.checkpointsReached * 3;
  fitnesss += g->fitness.timeTaken;
  return fitnesss;
}