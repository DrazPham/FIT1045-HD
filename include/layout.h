#pragma once

#include "splashkit.h"

struct screen_layout
{
    point_2d center;
    point_2d header;
    point_2d title;
    point_2d tag_line;
    point_2d start_button;
    point_2d footer;
    point_2d house_price;
    point_2d house_description;
};

screen_layout create_layout();
