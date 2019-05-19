#include "gameconfig.h"

#define PLAYGROUND_WIDTH 800
#define PLAYGROUND_HEIGHT 800
#define PLAYGROUND_BORDER_WIDTH 50
#define PLAYGROUND_BORDER_HEIGHT 50
#define PLAYGROUND_VIEW_EXTRA_WIDTH 100
#define PLAYGROUND_VIEW_EXTRA_HEIGHT 100
#define PLAYGROUND_VIEW_WIDTH PLAYGROUND_WIDTH + PLAYGROUND_VIEW_EXTRA_WIDTH
#define PLAYGROUND_VIEW_HEIGHT PLAYGROUND_HEIGHT + PLAYGROUND_VIEW_EXTRA_HEIGHT


double GameConfig::playground_width = PLAYGROUND_WIDTH;
double GameConfig::playground_height = PLAYGROUND_HEIGHT;
double GameConfig::playground_border_width = PLAYGROUND_BORDER_WIDTH;
double GameConfig::playground_border_height = PLAYGROUND_BORDER_HEIGHT;
double GameConfig::playground_view_extra_width = PLAYGROUND_VIEW_EXTRA_WIDTH;
double GameConfig::playground_view_extra_height = PLAYGROUND_VIEW_EXTRA_HEIGHT;
double GameConfig::playground_view_width = GameConfig::playground_width
        + GameConfig::playground_view_extra_width;
double GameConfig::playground_view_height = GameConfig::playground_height
        + GameConfig::playground_view_extra_height;
