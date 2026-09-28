#include "layout.h"

screen_layout create_layout()
{
    double width = screen_width();
    double height = screen_height();

    screen_layout layout;
    layout.center = screen_center();
    layout.header = point_at(width * 0.03, height * 0.03);
    layout.title = point_at(width * 0.5, height * 0.15);
    layout.tag_line = point_at(width * 0.5, layout.title.y + 60);
    layout.start_button = point_at(width * 0.5, layout.title.y + 130);
    layout.footer = point_at(width * 0.5, height * 0.92);
    layout.house_price = point_at(300, 400);
    layout.house_description = point_at(300, 450);
    return layout;
}
