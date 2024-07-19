/**
 * @file world.h
 * @brief This file is responsible for rendering world and it's contents
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __WORLD_H__
#define __WORLD_H__

#include <Context.h>

/**
 * @brief World configuration object
 *
 */
typedef struct WorldConfig
{
  char *level;
  Context *context;
} WorldConfig;

/**
 * @brief World main structure, holds levels, context reference and background
 *
 */
typedef struct World
{
  char *level;
  Context *context;
  sfSprite *backgroundSprite;
  sfImage *backgroundImage;
  sfVector2f checkpointPosition[45][2];
  int numOfCheckpoints;
} World;

/**
 * @brief Generate world object and allocate it to heap
 *
 * @param config : configuration object for the world
 * @return World*
 */
World *generateWorld(WorldConfig config);

/**
 * @brief Initialize the structure and generate the world
 *
 * @param w : World to initialize
 */
void initWorld(World *w);

/**
 * @brief Initialize map sectors
 *
 * @param w : World
 */
void generateSectors(World *w);

/**
 * @brief Helper function to draw sectors
 *
 * @param w : World
 */
void drawSectors(World *w);

/**
 * @brief drawing helper function
 *
 * @param w World
 * @param p1 point1
 * @param p2 point2
 */
void drawLine(World *w, sfVector2f p1, sfVector2f p2);

/**
 * @brief Render to screen
 *
 * @param w : World
 * @param obj : void pointer pointing to list of objects to render
 * @param count : number of elements pointed by @param obj
 */
void renderWorld(World *w, void **obj, unsigned int count);

#endif //__WORLD_H__