/**
 * @file context.h
 * @brief This file is responsible for window generation and status
 * @version 0.1
 * @date 2023-05-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

/**
 * @brief Context structure holdes the context
 *
 */
typedef struct Context
{
  sfRenderWindow *_window;
  unsigned width;
  unsigned height;
  char *name;
  sfWindowStyle style;
  const sfContextSettings *settings;
} Context;

/**
 * @brief Configuration strucure
 *
 */
typedef struct ContextConfig
{
  unsigned width;
  unsigned height;
  char *name;
  sfWindowStyle style;
  const sfContextSettings *settings;
} ContextConfig;

/**
 * @brief Generate context object and allocate it to heap
 *
 * @param config : Configuration obj
 * @return Context*
 */
Context *generateContext(ContextConfig config);

/**
 * @brief Initialize the window
 *
 * @param c : Context
 */
void initContext(Context *c);

/**
 * @brief Checks if context is still open
 *
 * @param c : Context
 * @return int
 */
int isContextOpen(Context *c);

/**
 * @brief Clear the buffer for next draw
 *
 * @param c : Context
 */
void clearContext(Context *c);

/**
 * @brief Draw to window
 *
 * @param c : Context
 */
void updateContext(Context *c);

/**
 * @brief Free heap after closing the window
 *
 * @param c : Context
 */
void destroyContext(Context *c);

/**
 * @brief Checks for events like keyboard, mouse, joystick, and window buttons
 *
 * @param c Context
 * @param e Event pointer to store unhandled event
 * @return int
 */
int contextPollEvent(Context *c, sfEvent *e);

/**
 * @brief Close the window
 *
 * @param c : Context
 */
void closeContext(Context *c);

#endif //__CONTEXT_H__