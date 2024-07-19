/**
 * @file physicsBody.h
 * @brief Specific physics module for mechanical handling for a simple car
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __PHYSICSBODY_H__
#define __PHYSICSBODY_H__

#include <SFML/Graphics.h>

/**
 * @brief Configuration structure
 *
 */
typedef struct PhysicsBodyConfig
{
  double acceleration;
  double deacceleration;
} PhysicsBodyConfig;

/**
 * @brief Physics body which defines physical properties
 *
 */
typedef struct PhysicsBody
{
  double rotation;
  double speed;
  sfVector2f velocity;
  double acceleration;
  double deacceleration;
} PhysicsBody;

/**
 * @brief Generate PhysicsBody object and allocate it to heap
 *
 * @param c : Configuration object
 * @return PhysicsBody*
 */
PhysicsBody *generatePhysicsBody(PhysicsBodyConfig c);

/**
 * @brief Initialize the strucutre
 *
 * @param b : PhysicsBody
 */
void initPhysicsBody(PhysicsBody *b);

/**
 * @brief Accelerate the body
 *
 * @param b : PhysicsBody
 */
void acceleratePhysicsBody(PhysicsBody *b);

/**
 * @brief Deaccelerate the body
 *
 * @param b : PhysicsBody
 */
void deacceleratePhysicsBody(PhysicsBody *b);

/**
 * @brief Rotate body to left with a fixed angle
 *
 * @param b : PhysicsBody
 */
void rotateLeftPhysicsBody(PhysicsBody *b);

/**
 * @brief Rotate body to right with a fixed angle
 *
 * @param b : PhysicsBody
 */
void rotateRightPhysicsBody(PhysicsBody *b);

/**
 * @brief Update body velocity after a change in body properties
 * Should be called last.
 *
 * @param b : PhysicsBody
 */
void updatePhysicsBody(PhysicsBody *b);

/**
 * @brief Stop physics body from moving
 *
 * @param b : PhysicsBody
 */
void stopPhysicsBody(PhysicsBody *b);

#endif //__PHYSICSBODY_H__