#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <ai/AI.h>

// PROTOTYPES
float sigmoid(float);
int getAction(Genome *g, float *input);

void initAI(AI *ai)
{
  generatePopulation(ai);
}

AI *generateAI(AIConfig c)
{
  AI *ai = (AI *)malloc(sizeof(AI));
  ai->populationSize = c.populationSize;
  ai->population = (Genome **)malloc(sizeof(Genome *) * ai->populationSize);
  ai->actions = (ACTION *)malloc(sizeof(ACTION) * ai->populationSize);

  initAI(ai);
  return ai;
}

void generatePopulation(AI *ai)
{
  GenomeConfig genomeConfig;
  genomeConfig.sensorsNum = 5;
  genomeConfig.hiddenNum = 4;
  genomeConfig.outputNum = 4;

  for (int i = 0; i < ai->populationSize; i++)
  {
    ai->population[i] = generateGenome(genomeConfig);
  }
}

int *selectParentsFromPopulation(AI *ai)
{
  int p1 = 0, p2 = 1;
  int *Ps = (int *)malloc(sizeof(int) * 2);

  for (int i = 0; i < ai->populationSize; i++)
  {
    float fitness = genomeFitness(ai->population[i]);
    if (fitness > genomeFitness(ai->population[p1]))
    {
      p2 = p1;
      p1 = i;
    }
    else if (fitness > genomeFitness(ai->population[p2]))
    {
      p2 = i;
    }
  }

  Ps[0] = p1;
  Ps[1] = p2;
  return Ps;
}

void crossover(Genome *offspring, Genome *p1, Genome *p2)
{
  offspring->fitness.checkpointsReached = (int)((p1->fitness.checkpointsReached + p2->fitness.checkpointsReached) / 2);
  offspring->fitness.timeTaken = (p1->fitness.timeTaken + p2->fitness.timeTaken) / 2.0f;
}

void mutate(Genome *g, float mutationRate)
{
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.checkpointsReached = (float)rand() / RAND_MAX * 45;
  }
  if ((float)rand() / RAND_MAX < mutationRate)
  {
    g->fitness.timeTaken += (float)rand() / RAND_MAX * 60;
  }
}

void evolveAI(AI *ai)
{
  Genome **newPopulation = (Genome **)malloc(sizeof(Genome *) * ai->populationSize);

  int *parentIndex = selectParentsFromPopulation(ai);

  for (int i = 2; i < ai->populationSize; i++)
  {
    Genome *offspring = (Genome *)malloc(sizeof(Genome));
    memcpy(offspring, ai->population[parentIndex[0]], sizeof(Genome));
    crossover(offspring, ai->population[parentIndex[0]], ai->population[parentIndex[1]]);

    mutate(offspring, 0.6);

    newPopulation[i] = offspring;
  }

  newPopulation[0] = (Genome *)malloc(sizeof(Genome));
  newPopulation[1] = (Genome *)malloc(sizeof(Genome));
  memcpy(newPopulation[0], ai->population[parentIndex[0]], sizeof(Genome));
  memcpy(newPopulation[1], ai->population[parentIndex[1]], sizeof(Genome));

  free(parentIndex);
  float *x = ai->population[0]->weights_ho[0];
  for (int i = 0; i < ai->populationSize; i++)
    free(ai->population[i]);
  free(ai->population);
  ai->population = newPopulation;
}

ACTION trainAI(Genome *g, float *inputs)
{
  return getAction(g, inputs);
}

float sigmoid(float x)
{
  // Sigmoid activation function
  return 1.0 / (1.0 + exp(-x));
}

int getAction(Genome *g, float *input)
{
  float *hidden = (float *)malloc(sizeof(float) * g->hiddenNum);
  float *output = (float *)malloc(sizeof(float) * g->outputNum);

  // Compute activations of hidden layer nodes
  for (int i = 0; i < g->hiddenNum; i++)
  {
    float sum = 0.0;
    for (int j = 0; j < g->sensorsNum; j++)
    {
      sum += input[j] * g->weights_ih[j][i];
    }
    sum += g->biases_h[i];
    hidden[i] = sigmoid(sum);
  }

  // Compute activations of output layer nodes
  for (int i = 0; i < g->outputNum; i++)
  {
    float sum = 0.0;
    for (int j = 0; j < g->hiddenNum; j++)
    {
      sum += hidden[j] * g->weights_ho[j][i];
    }
    sum += g->biases_o[i];
    output[i] = sigmoid(sum);
  }

  int action = 0;
  float maxOutput = output[0];

  for (int i = 1; i < g->outputNum; i++)
  {
    if (output[i] > maxOutput)
    {
      maxOutput = output[i];
      action = i;
    }
  }

  // Backpropagation
  // Generate targets

  /**
   * @brief OKAY.. now the target is just every possible senario that could happen.
   *        The input is just the radar reading and the given data is between  [0-1],
   *        also there are five radars in the following order:
   *        front, left, right, angled left, and angled right
   */
  float incrementation = 0.2;
  float *targets = (float *)malloc(sizeof(float) * g->outputNum);
  for (int i = 0; i < g->outputNum; i++)
    targets[i] = 0;

  if (input[0] <= 0.7 && input[1] >= 0.8)
  {

    targets[0] = 1;
    targets[1] = 1;
    // targets[3] = 1;
  }

  if (input[3] >= 0.9)
  {
    targets[0] = 0.5;
    targets[1] = 1;
    // targets[3] = 0.3;
  }

  float *hiddenErrors = (float *)malloc(sizeof(float) * g->hiddenNum);
  float *outputErrors = (float *)malloc(sizeof(float) * g->outputNum);
  float learningRate = 0.4;

  // Compute errors of output layer nodes
  for (int i = 0; i < g->outputNum; i++)
  {
    float error = targets[i] - output[i];
    outputErrors[i] = error * output[i] * (1.0 - output[i]);
  }

  // Compute errors of hidden layer nodes
  for (int i = 0; i < g->hiddenNum; i++)
  {
    float error = 0.0;
    for (int j = 0; j < g->outputNum; j++)
    {
      error += outputErrors[j] * g->weights_ho[i][j];
    }
    hiddenErrors[i] = error * hidden[i] * (1.0 - hidden[i]);
  }

  // Update weights and biases
  for (int i = 0; i < g->hiddenNum; i++)
  {
    for (int j = 0; j < g->outputNum; j++)
    {
      g->weights_ho[i][j] += learningRate * outputErrors[j] * hidden[i];
    }
  }

  for (int i = 0; i < g->sensorsNum; i++)
  {
    for (int j = 0; j < g->hiddenNum; j++)
    {
      g->weights_ih[i][j] += learningRate * hiddenErrors[j] * input[i];
    }
  }

  free(hidden);
  free(hiddenErrors);
  free(output);
  free(outputErrors);
  free(targets);

  return action;
}