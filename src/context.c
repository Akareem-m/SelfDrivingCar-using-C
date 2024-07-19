#include <context.h>
#include <stdlib.h>

void initContext(Context *c)
{
  c->_window = sfRenderWindow_create((sfVideoMode){c->width, c->height, 32}, c->name, c->style, c->settings);
}

Context *generateContext(ContextConfig config)
{
  Context *context = (Context *)malloc(sizeof(Context));
  context->width = config.width;
  context->height = config.height;
  context->name = config.name;
  context->style = config.style;
  context->settings = config.settings;

  initContext(context);

  return context;
}

int isContextOpen(Context *c)
{
  return sfRenderWindow_isOpen(c->_window) ? 1 : 0;
}
void clearContext(Context *c)
{
  sfRenderWindow_clear(c->_window, sfBlack);
}
void updateContext(Context *c)
{
  sfRenderWindow_display(c->_window);
}
void destroyContext(Context *c)
{
  sfRenderWindow_destroy(c->_window);
}

int contextPollEvent(Context *c, sfEvent *e)
{
  return sfRenderWindow_pollEvent(c->_window, e) ? 1 : 0;
}

void closeContext(Context *c)
{
  sfRenderWindow_close(c->_window);
}