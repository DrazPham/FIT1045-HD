#include "splashkit.h"

int main()
{
    string name = "unknown";
    string display_name = "";
    bool was_reading = false;
        rectangle input_rect = rectangle_from(230.0, 50.0, 200.0, 30.0);
    rectangle button_rect = rectangle_from(230.0, 100.0, 100.0, 40.0);

    open_window("Reading Input.", 800, 600);
    load_font("input", "arial.ttf");

    rectangle input_rect = rectangle_from(230.0, 50.0, 200.0, 30.0);
    rectangle button_rect = rectangle_from(230.0, 100.0, 100.0, 40.0);

    do
    {
        process_events();

        if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), input_rect) && !reading_text())
        {
            start_reading_text(input_rect);
        }

        was_reading = reading_text();

        if (was_reading && !reading_text())
        {
            if (text_entry_cancelled())
            {
                name = "unknown";
            }
            else
            {
                name = text_input();
            }
        }

        if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), button_rect))
        {
            display_name = name;
        }

        clear_screen(COLOR_WHITE);

        draw_rectangle(COLOR_BLACK, input_rect);
        if (reading_text())
        {
            draw_collected_text(COLOR_BLACK, font_named("input"), 18, option_defaults());
        }
        else
        {
            draw_text(name, COLOR_BLACK, font_named("input"), 18, input_rect.x + 5, input_rect.y + 5);
        }

        draw_rectangle(COLOR_GRAY, button_rect);
        draw_text("Submit", COLOR_BLACK, font_named("input"), 18, button_rect.x + 15, button_rect.y + 10);

        draw_text(display_name, COLOR_BLACK, font_named("input"), 18, 10, 10);

        refresh_screen(60);
    } while (!quit_requested());

    close_all_windows();
    return 0;
}