#include <stdlib.h>

#include <core.h>
#include <physicsBody.h>

void initPhysicsBody(PhysicsBody *b)
{
  b->rotation = 0.0;
  b->speed = 0.0;
  b->velocity = (sfVector2f){0.f, 0.f};
}

PhysicsBody *generatePhysicsBody(PhysicsBodyConfig c)
{
  PhysicsBody *body = (PhysicsBody *)malloc(sizeof(PhysicsBody));
  body->acceleration = c.acceleration;
  body->deacceleration = c.deacceleration;
  initPhysicsBody(body);
  return body;
}

void acceleratePhysicsBody(PhysicsBody *b)
{
  if (b->speed < 20.0)
  {
    b->speed += b->acceleration;
    updatePhysicsBody(b);
  }
}
void deacceleratePhysicsBody(PhysicsBody *b)
{
  if (b->speed > 0.0)
  {
    b->speed -= b->acceleration;
    updatePhysicsBody(b);
  }
}
void rotateLeftPhysicsBody(PhysicsBody *b)
{
  b->rotation -= TO_RAD(4);
  updatePhysicsBody(b);
}

void rotateRightPhysicsBody(PhysicsBody *b)
{
  b->rotation += TO_RAD(4);
  updatePhysicsBody(b);
}

void updatePhysicsBody(PhysicsBody *b)
{
  b->velocity.x = b->speed * cos(b->rotation);
  b->velocity.y = b->speed * sin(b->rotation);
}

void stopPhysicsBody(PhysicsBody *b)
{
  b->speed = 0;
  b->velocity.x = b->velocity.y = 0;
  b->acceleration = 0;
  b->deacceleration = 0;
  b->rotation = 0;
}