#include "screens.h"
#include "ui.h"

void draw_admin_page(app_state &state)
{
    point_2d h = state.layout.header;
    int unsold = state.catalog.count;

    draw_label(TEXT_DASHBOARD, 20, h.x, h.y);
    draw_label(TEXT_HOUSE_TOTAL, 20, h.x, h.y + 30);
    draw_label(to_string(TOTAL_HOUSES), 20, h.x + 250, h.y + 30);
    draw_label(TEXT_HOUSE_UNSOLD, 20, h.x, h.y + 60);
    draw_label(to_string(unsold), 20, h.x + 250, h.y + 60);
    draw_label(TEXT_HOUSE_SOLD, 20, h.x, h.y + 90);
    draw_label(to_string(TOTAL_HOUSES - unsold), 20, h.x + 250, h.y + 90);
}
