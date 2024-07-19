#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>

#include <dummy.h>
#include <core.h>

void initDummy(Dummy *d)
{
  d->alive = 1;
  d->startingTime = time(0);

  sfTexture *sprite = sfTexture_createFromFile(d->spritePath, NULL);
  d->sprite = sfSprite_create();
  sfSprite_setTexture(d->sprite, sprite, sfTrue);
  sfSprite_setPosition(d->sprite, (sfVector2f){d->position[0], d->position[1]});
  sfSprite_setRotation(d->sprite, -90);
  sfSprite_setOrigin(d->sprite, (sfVector2f){320 / 2, 613 / 2}); // This is missed up :)
  sfSprite_setScale(d->sprite, (sfVector2f){.03f, .03f});
}

Dummy *generateDummy(DummyConfig c)
{
  Dummy *d = (Dummy *)malloc(sizeof(Dummy));
  d->position[0] = c.position[0];
  d->position[1] = c.position[1];
  PhysicsBodyConfig bodyConfig = {1, 3};
  d->body = generatePhysicsBody(bodyConfig);

  d->spritePath = c.spritePath;

  initDummy(d);
  return d;
}

void updateDummy(Dummy *d)
{
  // Drawing updates
  d->position[0] += METER_TO_PIXEL(d->body->velocity.x);
  d->position[1] += METER_TO_PIXEL(d->body->velocity.y);
  sfSprite_setPosition(d->sprite, (sfVector2f){
                                      d->position[0],
                                      d->position[1]});
  sfSprite_setRotation(d->sprite, TO_DEGREES(d->body->rotation) + 90);
}

unsigned char dummyCheckCollision(Dummy *d)
{
  return hasCollided(d->radar);
}

void stopDummy(Dummy *d)
{
  stopPhysicsBody(d->body);

  d->alive = 0;

  d->endingTime = time(0);
  d->genume->fitness.timeTaken = d->endingTime - d->startingTime;
}

void restartDummy(Dummy *d, float x, float y)
{
  d->position[0] = x;
  d->position[1] = y;

  d->body->rotation = 0;
  d->body->acceleration = 1.0;
  d->body->deacceleration = 3.0;

  d->alive = 1;
  d->startingTime = time(0);
  d->endingTime = 0;

  d->radar->directions[0].position = (sfVector2f){0.f, 0.f};
  d->radar->directions[1].position = (sfVector2f){0.f, 0.f};
  d->radar->directions[2].position = (sfVector2f){0.f, 0.f};
  d->radar->directions[3].position = (sfVector2f){0.f, 0.f};
  d->radar->directions[4].position = (sfVector2f){0.f, 0.f};
  d->radar->power[0] = 0.0;
  d->radar->power[1] = 0.0;
  d->radar->power[2] = 0.0;
  d->radar->power[3] = 0.0;
  d->radar->power[4] = 0.0;
  d->radar->position[0] = d->position[0] / 1.3f;
  d->radar->position[1] = d->position[1] / 1.3f;
  d->radar->rotation = 0.0;

  sfSprite_setPosition(d->sprite, (sfVector2f){d->position[0], d->position[1]});
  sfSprite_setRotation(d->sprite, -90);
}