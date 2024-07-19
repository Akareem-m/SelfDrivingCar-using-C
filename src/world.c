#include <world.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <SFML/Graphics.h>

#include <dummy.h>

void initWorld(World *w)
{
  sfTexture *backgroundSprite = sfTexture_createFromFile(w->level, NULL);

  w->backgroundSprite = sfSprite_create();
  sfSprite_setTexture(w->backgroundSprite, backgroundSprite, sfTrue);
  sfSprite_setScale(w->backgroundSprite, (sfVector2f){1.3f, 1.3f});

  w->backgroundImage = sfImage_createFromFile(w->level);

  generateSectors(w);
}

World *generateWorld(WorldConfig c)
{
  World *world = (World *)malloc(sizeof(World));
  world->level = (char *)malloc(sizeof(c.level));
  world->level = c.level;

  world->context = c.context;
  world->numOfCheckpoints = 45;

  initWorld(world);

  return world;
}

// function of shame
void generateSectors(World *w)
{
  sfVector2f vRect = {30.f, 80.f};
  sfVector2f hRect = {80.f, -30.f};
  // first road
  for (int i = 0; i < 10; i++)
  {
    w->checkpointPosition[i][0].x = 80.f + 60.f * i;
    w->checkpointPosition[i][0].y = 505.f;
    w->checkpointPosition[i][1] = vRect;
  }

  // second road
  for (int i = 0; i < 7; i++)
  {
    w->checkpointPosition[i + 10][0].x = 680.f;
    w->checkpointPosition[i + 10][0].y = 500.f - 60.f * i;
    w->checkpointPosition[i + 10][1] = hRect;
  }

  w->checkpointPosition[17][0].x = 670.f;
  w->checkpointPosition[17][0].y = 25.f;
  w->checkpointPosition[17][1] = vRect;

  w->checkpointPosition[18][0].x = 450.f;
  w->checkpointPosition[18][0].y = 25.f;
  w->checkpointPosition[18][1] = vRect;

  w->checkpointPosition[19][0].x = 240.f;
  w->checkpointPosition[19][0].y = 25.f;
  w->checkpointPosition[19][1] = vRect;

  w->checkpointPosition[20][0].x = 590.f;
  w->checkpointPosition[20][0].y = 150.f;
  w->checkpointPosition[20][1] = hRect;

  w->checkpointPosition[21][0].x = 494.f;
  w->checkpointPosition[21][0].y = 150.f;
  w->checkpointPosition[21][1] = hRect;

  w->checkpointPosition[22][0].x = 144.f;
  w->checkpointPosition[22][0].y = 150.f;
  w->checkpointPosition[22][1] = hRect;

  w->checkpointPosition[23][0].x = 270.f;
  w->checkpointPosition[23][0].y = 150.f;
  w->checkpointPosition[23][1] = hRect;

  w->checkpointPosition[24][0].x = 144.f;
  w->checkpointPosition[24][0].y = 240.f;
  w->checkpointPosition[24][1] = hRect;

  w->checkpointPosition[25][0].x = 570.f;
  w->checkpointPosition[25][0].y = 190.f;
  w->checkpointPosition[25][1] = vRect;

  w->checkpointPosition[26][0].x = 345.f;
  w->checkpointPosition[26][0].y = 190.f;
  w->checkpointPosition[26][1] = vRect;

  for (int i = 0; i < 5; i++)
  {
    w->checkpointPosition[i + 27][0].x = 240.f + 60.f * i;
    w->checkpointPosition[i + 27][0].y = 260.f;
    w->checkpointPosition[i + 27][1] = vRect;
  }

  for (int i = 0; i < 5; i++)
  {
    w->checkpointPosition[i + 32][0].x = 240.f + 60.f * i;
    w->checkpointPosition[i + 32][0].y = 355.f;
    w->checkpointPosition[i + 32][1] = vRect;
  }

  w->checkpointPosition[37][0].x = 50.f;
  w->checkpointPosition[37][0].y = 70.f;
  w->checkpointPosition[37][1] = vRect;

  w->checkpointPosition[38][0].x = 73.f;
  w->checkpointPosition[38][0].y = 240.f;
  w->checkpointPosition[38][1] = hRect;

  // second road
  for (int i = 0; i < 6; i++)
  {
    w->checkpointPosition[i + 39][0].x = 5.f;
    w->checkpointPosition[i + 39][0].y = 500.f - 60.f * i;
    w->checkpointPosition[i + 39][1] = hRect;
    w->checkpointPosition[i + 39][1].x -= 30.f;
  }
}

void drawSectors(World *w)
{
  for (int i = 0; i < w->numOfCheckpoints; i++)
  {
    sfRectangleShape *obj = sfRectangleShape_create();
    sfRectangleShape_setPosition(obj, w->checkpointPosition[i][0]);
    sfRectangleShape_setSize(obj, w->checkpointPosition[i][1]);
    sfRectangleShape_setFillColor(obj, sfTransparent);
    sfRectangleShape_setOutlineColor(obj, sfGreen);
    sfRectangleShape_setOutlineThickness(obj, 1.f);
    sfRenderWindow_drawRectangleShape(w->context->_window, obj, NULL);
  }
}

void drawLine(World *w, sfVector2f p1, sfVector2f p2)
{
  sfVertex line[] =
      {{p1, {0, 0, 0, 0}, {0.f, 0.f}},
       {p2, {0, 0, 0, 0}, {0.f, 0.f}}};
  line[0].color = sfRed;
  line[1].color = sfRed;
  sfRenderWindow_drawPrimitives(w->context->_window, line, 2, sfLines, NULL);
}

void renderWorld(World *w, void **obj, unsigned int count)
{
  sfRenderWindow_drawSprite(w->context->_window, w->backgroundSprite, NULL); // TODO: factor low-level api out
  drawSectors(w);

  for (int i = 0; i < count; i++)
  {
    Dummy *d = (Dummy *)obj[i];
    if (!d->alive)
      continue;
    sfRenderWindow_drawSprite(w->context->_window, d->sprite, NULL); // TODO: factor low-level api out

    sfVector2f dummyPos = sfSprite_getPosition(d->sprite);
    dummyPos.x /= 1.3f;
    dummyPos.y /= 1.3f;
    updateRadar(d->radar, dummyPos.x, dummyPos.y, d->body->rotation);
    updateWallCoords(d->radar);

    for (int i = 0; i < 5; i++)
    {
      drawLine(w,
               (sfVector2f){dummyPos.x * 1.3f, dummyPos.y * 1.3f},
               (sfVector2f){d->radar->directions[i].position.x * 1.3f, d->radar->directions[i].position.y * 1.3f});
    }
  }
}
