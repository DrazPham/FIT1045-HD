#include <sstream>
#include "ui.h"

void draw_label(const string &text, int size, double x, double y)
{
    draw_text(text, COLOR_BLACK, font_named(FONT_NAME), size, x, y);
}

void draw_centered_label(const string &text, int size, double center_x, double y)
{
    double width = text_width(text, font_named(FONT_NAME), size);
    draw_label(text, size, center_x - width / 2.0, y);
}

void draw_wrapped_text(const string &text, int size, double x, double y, double max_width, double line_height)
{
    font fnt = font_named(FONT_NAME);
    std::stringstream ss(text);
    string word, line;
    while (ss >> word)
    {
        string test = line.empty() ? word : line + " " + word;
        if (!line.empty() && text_width(test, fnt, size) > max_width)
        {
            draw_label(line, size, x, y);
            y += line_height;
            line = word;
        }
        else
        {
            line = test;
        }
    }
    if (!line.empty())
    {
        draw_label(line, size, x, y);
    }
}

bool window_button(window win, const string &label, const rectangle &rect)
{
    font fnt = font_named(FONT_NAME);
    fill_rectangle(COLOR_LIGHT_GRAY, rect);
    draw_rectangle(COLOR_BLACK, rect);
    draw_label(label, 16,
               rect.x + (rect.width - text_width(label, fnt, 16)) / 2,
               rect.y + (rect.height - text_height(label, fnt, 16)) / 2);
    return window_has_focus(win) && mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), rect);
}

void draw_current_house_image(const app_state &state)
{
    bitmap bmp = state.catalog.images[state.current_house];
    double width = bitmap_width(bmp);
    double height = bitmap_height(bmp);
    drawing_options opt = option_scale_bmp(HOUSE_IMAGE_WIDTH / width, HOUSE_IMAGE_HEIGHT / height);
    draw_bitmap(bmp, state.layout.center.x - width / 2, state.layout.center.y - height / 2 - 80, opt);
}
