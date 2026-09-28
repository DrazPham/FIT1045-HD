#include "screens.h"
#include "ui.h"
#include "network.h"

static void add_property(user_filter &filter, const string &name, int flag)
{
    filter.properties.insert(name);
    filter.property_count += flag;
}

static void apply_filter(app_state &state)
{
    user_filter &filter = state.filter;
    if (filter.property_count == 4)
    {
        for (int i = 0; i < state.catalog.count; i++)
        {
            if (state.catalog.details[i].has_pool)
            {
                add(filter.matching_houses, state.catalog.details[i]);
            }
        }
    }
}

void draw_user_page(app_state &state)
{
    point_2d h = state.layout.header;
    bool unchecked = false;

    if (checkbox("<2 Bedrooms", unchecked, rectangle_from(200, 300, 180, 50)))
    {
        add_property(state.filter, "<2 Bedrooms", 1);
    }
    else if (checkbox("<2 Bathrooms", unchecked, rectangle_from(200, 360, 180, 50)))
    {
        add_property(state.filter, "<2 Bathrooms", 2);
    }
    else if (checkbox("Pool", unchecked, rectangle_from(200, 420, 180, 50)))
    {
        add_property(state.filter, "Pool", 4);
    }
    else if (checkbox("Garden", unchecked, rectangle_from(200, 480, 180, 50)))
    {
        add_property(state.filter, "Garden", 8);
    }

    draw_label(TEXT_DASHBOARD, 20, h.x, h.y);
    draw_label(TEXT_HOUSE_OWNED, 20, h.x, h.y + 30);
    draw_label("0", 20, h.x + 250, h.y + 30);
    draw_label(TEXT_HOUSE_AVAILABLE, 20, h.x, h.y + 60);
    draw_label(to_string(state.catalog.count), 20, h.x + 250, h.y + 60);

    if (button("START CHOOSING", rectangle_from(0, 300, 200, 24)))
    {
        apply_filter(state);
        state.screen = HOUSE_SELECTION;
    }
}

void draw_house_selection(app_state &state)
{
    point_2d c = state.layout.center;
    screen_layout &l = state.layout;
    const house_detail &house = state.catalog.details[state.current_house];

    draw_label(TEXT_HEADER, 20, l.header.x, l.header.y);

    if (button("Yes", rectangle_from(c.x - 300, c.y + 200 - 12, 200, 24)))
    {
        send_item_choice(state);
        state.screen = WAITING_PAGE;
        return;
    }
    if (button("MORE_INFO", rectangle_from(c.x, c.y + 100 - 12, 200, 24)))
    {
        state.info_open = true;
    }
    if (button("No", rectangle_from(c.x + 100, c.y + 200 - 12, 200, 24)))
    {
        state.current_house = rnd(0, state.catalog.count - 1);
    }

    draw_current_house_image(state);
    draw_label("$" + to_string(house.price), 20, l.house_price.x, l.house_price.y);
    draw_label(house_summary(house), 20, l.house_description.x, l.house_description.y);
}

void update_info_window(app_state &state)
{
    if (!state.info_open)
    {
        return;
    }
    if (!has_window(INFO_WINDOW_TITLE))
    {
        open_window(INFO_WINDOW_TITLE, INFO_WINDOW_WIDTH, INFO_WINDOW_HEIGHT);
    }
    window info_win = window_named(INFO_WINDOW_TITLE);
    bitmap bmp = state.catalog.images[state.current_house];

    set_current_window(info_win);
    clear_screen(COLOR_WHITE);
    draw_bitmap(bmp, 80, 20, option_scale_bmp(HOUSE_IMAGE_WIDTH / bitmap_width(bmp), HOUSE_IMAGE_HEIGHT / bitmap_height(bmp)));
    draw_wrapped_text(house_full_description(state.catalog.details[state.current_house]), 18, 30, 340, 640, 26);
    bool back_clicked = window_button(info_win, "BACK TO CHOOSING", rectangle_from(250, 550, 200, 30));
    refresh_screen();
    set_current_window(state.main_window);

    if (back_clicked || window_close_requested(info_win))
    {
        close_window(info_win);
        state.info_open = false;
    }
}
