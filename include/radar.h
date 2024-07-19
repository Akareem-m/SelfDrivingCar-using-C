/**
 * @file radar.h
 * @brief Radar object to detect walls
 * @version 0.1
 * @date 2023-05-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __RADAR_H__
#define __RADAR_H__

#include <SFML/Graphics.h>

#include <world.h>

typedef struct Radar
{
  sfVertex directions[5];
  double power[5];
  World *World;
  float distance;
  float position[2];
  double rotation;
} Radar;

typedef struct RadarConfig
{
  World *World;
  float distance;
  float position[2];
} RadarConfig;

/**
 * @brief Generate the radar object and allocate it to heap
 *
 * @param c : Configuration
 * @return Radar*
 */
Radar *generateRadar(RadarConfig c);

/**
 * @brief Initialize the radar
 *
 * @param r : Radar
 */
void initRadar(Radar *r);

/**
 * @brief Get the Wall Coords
 *
 * @param r : Radar
 */
void updateWallCoords(Radar *r);

/**
 * @brief Checks if owner object has collided
 *
 * @param r : Radar
 * @return unsigned char
 */
unsigned char hasCollided(Radar *r);

/**
 * @brief Update the radar
 *
 * @param r : radar
 * @param x : x position
 * @param y : y position
 * @param rotation :  rotation
 */
void updateRadar(Radar *r, float x, float y, float rotation);

#endif // __RADAR_H__