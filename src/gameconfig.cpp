/*
 *	Monster Chase: a testing playground for behaviors trees
 *
 *	Copyright 2021 Andrea Ravalli <anravalli @ gmail.com>
 *
 *	This file is part of Monster Chase.
 *
 *	Monster Chase is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	Monster Chase is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with Monster Chase.  If not, see <http://www.gnu.org/licenses/>.
*/


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
