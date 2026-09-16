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

struct house_detail
{
    int price;
    string house_name;
};

int main()
{
    open_window("My Interface!", 800, 600);

    load_font("input", "arial.ttf");
    double screen_max_width_postion = screen_width();
    double screen_max_height_postion = screen_height();
    point_2d center_point_pos = screen_center();

    point_2d header_pos;
    header_pos.x = screen_max_width_postion * 0.03;
    header_pos.y = screen_max_height_postion * 0.03;

    point_2d title_pos;
    title_pos.x = screen_max_width_postion * 0.5;
    title_pos.y = screen_max_height_postion * 0.15;

    point_2d tag_line_pos;
    tag_line_pos.x = screen_max_width_postion * 0.5;
    tag_line_pos.y = title_pos.y + 60;

    point_2d start_btn_pos;
    start_btn_pos.x = screen_max_width_postion * 0.5;
    start_btn_pos.y = title_pos.y + 130;

    point_2d footer_pos;
    footer_pos.x = screen_max_width_postion * 0.5;
    footer_pos.y = screen_max_height_postion * 0.92;

    bitmap first_house = load_bitmap("first_house_image", "first_house.jpg");
    bitmap second_house = load_bitmap("second_house_image", "second_house.jpg");
    bitmap third_house = load_bitmap("third_house_image", "third_house.jpg");
    // sprite first_house_sprite = create_sprite(first_house);
    // sprite second_house_sprite = create_sprite(second_house);
    // sprite third_house_sprite = create_sprite(third_house);

    // sprite sprite_list[3] = {first_house_sprite, second_house_sprite, third_house_sprite};

    // sprite_set_x(first_house_sprite, center_point_pos.x - sprite_width(first_house_sprite) / 2);
    // sprite_set_y(first_house_sprite, center_point_pos.y - sprite_height(first_house_sprite) / 2);
    // sprite_set_x(second_house_sprite, center_point_pos.x - sprite_width(second_house_sprite) / 2);
    // sprite_set_y(second_house_sprite, center_point_pos.y - sprite_height(second_house_sprite) / 2);
    // sprite_set_x(third_house_sprite, center_point_pos.x - sprite_width(third_house_sprite) / 2);
    // sprite_set_y(third_house_sprite, center_point_pos.y - sprite_height(third_house_sprite) / 2);

    bitmap bitmap_list[3] = {first_house, second_house, third_house};
    house_detail house_list_detail[3] = {
        {30, "House A"},
        {650000, "House B"},
        {800000, "House C"}};
    double target_width = 400;
    double target_height = 300;

    bool flag;
    int current_price = 100;
    string name = "";
    string header = "HouseMatch";
    string title = "Swipe. Match. Win.";
    string tag_line = "Find a house you love, get matched with another buyer, and settle it with a live bid.";
    string footer = "A real-time house-buying game";
    string house_price = "$650,00";
    string house_description = "4 bed - 2 bath - Glen Waverley";

    bool is_entering_name = false;
    while (!quit_requested())
    {
        process_events();
        clear_screen(COLOR_WHITE);
        double bmp_width = bitmap_width(bitmap_list[current_house]);
        double bmp_height = bitmap_height(bitmap_list[current_house]);
        double scale_x = target_width / bmp_width;
        double scale_y = target_height / bmp_height;
        drawing_options opt = option_scale_bmp(scale_x, scale_y);

        if (current_screen == MAIN_MENU)
        {
            draw_text(header, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y);
            double title_w = text_width(title, font_named("input"), 32);
            draw_text(title, COLOR_BLACK, font_named("input"), 32,
                      title_pos.x - title_w / 2.0, title_pos.y);

            double tagline_w = text_width(tag_line, font_named("input"), 16);
            draw_text(tag_line, COLOR_BLACK, font_named("input"), 16,
                      tag_line_pos.x - tagline_w / 2.0, tag_line_pos.y);

            double footer_w = text_width(footer, font_named("input"), 14);
            draw_text(footer, COLOR_BLACK, font_named("input"), 14,
                      footer_pos.x - footer_w / 2.0, footer_pos.y);
            if (button("Let's Start", rectangle_from(start_btn_pos.x - 100, start_btn_pos.y - 12, 200, 24)))
            {
                current_screen = HOUSE_SELECTION;
                flag = true;
            };
        }
        else if (current_screen == HOUSE_SELECTION)
        {
            draw_text(header, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y);

            bmp_width = bitmap_width(bitmap_list[current_house]);
            bmp_height = bitmap_height(bitmap_list[current_house]);
            scale_x = target_width / bmp_width;
            scale_y = target_height / bmp_height;

            if (button("Yes", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 200 - 12, 200, 24)))
            // if (button("Yes", rectangle_from(start_btn_pos.x, start_btn_pos.y, 200, 24)))
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
        // clear_screen(COLOR_WHITE);
        if (flag)
        {
            // draw_sprite(sprite_list[current_house]);
            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            point_2d house_price_pos;
            house_price_pos.x = 300;
            house_price_pos.y = 400;

            point_2d house_description_pos;
            house_description_pos.x = 300;
            house_description_pos.y = 450;
            draw_text("$" + to_string(house_list_detail[current_house].price), COLOR_BLACK, font_named("input"), 20, house_price_pos.x, house_price_pos.y);
            draw_text(house_list_detail[current_house].house_name, COLOR_BLACK, font_named("input"), 20, house_description_pos.x, house_description_pos.y);
            current_price = house_list_detail[current_house].price;
        };
        if (current_screen == AUCTION_PAGE)
        {
            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            point_2d house_price_pos;
            house_price_pos.x = 300;
            house_price_pos.y = 400;

            point_2d house_description_pos;
            house_description_pos.x = 300;
            house_description_pos.y = 450;
            draw_text("$" + to_string(current_price), COLOR_BLACK, font_named("input"), 20, house_price_pos.x, house_price_pos.y);
            draw_text(house_list_detail[current_house].house_name, COLOR_BLACK, font_named("input"), 20, house_description_pos.x, house_description_pos.y);

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