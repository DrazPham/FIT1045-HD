#include "splashkit.h"
#include "splashkit-arrays.h"
#include "common.hpp"

enum GameScreen
{
    MAIN_MENU,
    HOUSE_SELECTION,
    AUCTION_PAGE
};
GameScreen current_screen = MAIN_MENU;

enum HOUSE
{
    first_house,
    second_house,
    third_house
};
HOUSE current_house = first_house;

int main()
{
    open_window("My Interface!", 800, 600);

    load_font("input", "arial.ttf");
    point_2d center_point_pos = screen_center();

    bitmap first_house = load_bitmap("first_house_image", "first_house.jpg");
    bitmap second_house = load_bitmap("second_house_image", "second_house.jpg");
    bitmap third_house = load_bitmap("third_house_image", "third_house.jpg");
    sprite first_house_sprite = create_sprite(first_house);
    sprite second_house_sprite = create_sprite(second_house);
    sprite third_house_sprite = create_sprite(third_house);

    sprite sprite_list[3] = {first_house_sprite, second_house_sprite, third_house_sprite};

    sprite_set_x(first_house_sprite, center_point_pos.x - sprite_width(first_house_sprite) / 2);
    sprite_set_y(first_house_sprite, center_point_pos.y - sprite_height(first_house_sprite) / 2);
    sprite_set_x(second_house_sprite, center_point_pos.x - sprite_width(second_house_sprite) / 2);
    sprite_set_y(second_house_sprite, center_point_pos.y - sprite_height(second_house_sprite) / 2);
    sprite_set_x(third_house_sprite, center_point_pos.x - sprite_width(third_house_sprite) / 2);
    sprite_set_y(third_house_sprite, center_point_pos.y - sprite_height(third_house_sprite) / 2);

    bool flag;
    int current_price = 100;
    string name = "";
    bool is_entering_name = false;
    while (!quit_requested())
    {
        process_events();
        clear_screen(COLOR_WHITE);

        if (current_screen == MAIN_MENU)
        {
            if (button("Let's Start", rectangle_from(center_point_pos.x - 100, center_point_pos.y - 12, 200, 24)))
            {
                current_screen = HOUSE_SELECTION;
                flag = true;
            }
        }
        else if (current_screen == HOUSE_SELECTION)
        {
            // draw_sprite(first_house_sprite);
            if (button("Yes", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 200 - 12, 200, 24)))
            {
                current_screen = AUCTION_PAGE;
                flag = false;
                continue;
            }
            if (button("No", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 200 - 12, 200, 24)))
            {
                int temp = current_house;
                do
                {
                    current_house = (HOUSE)rnd(0, 2);
                } while (current_house == temp);
            }
        }
        clear_screen(COLOR_WHITE);
        if (flag)
            draw_sprite(sprite_list[current_house]);
        if (current_screen == AUCTION_PAGE)
        {
            draw_sprite(sprite_list[current_house]);
            draw_text(to_string(current_price), COLOR_BLACK, font_named("input"), 18, 10, 10);

            if (button("+100 AUD", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 200 - 12, 200, 24)))
            {
                current_price += 100;
            };

            rectangle rect = rectangle_from(500.0, 550.0, 200.0, 30.0);
            draw_rectangle(COLOR_BLACK, rect);
            if (button("Add customized amount", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 200 - 12, 200, 24)))
            {
                start_reading_text(rect);
                is_entering_name = true;
            }

            if (is_entering_name)
            {
                if (reading_text())
                {
                    draw_collected_text(COLOR_BLACK, font_named("input"), 18, option_defaults());
                }
                else
                {
                    if (text_entry_cancelled())
                        name = "unknown";
                    else
                    {
                        name = text_input();

                        if (is_integer(name))
                        {
                            current_price += to_integer(name);
                        }
                        else
                        {
                            write_line("Invalid number entered: " + name);
                        }
                    }
                    is_entering_name = false;
                }
            }
        }
        draw_interface();
        refresh_screen();
    }
    close_all_windows();
    return 0;
}