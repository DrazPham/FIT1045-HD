#include "splashkit.h"
#include "splashkit-arrays.h"
#include "common.hpp"
#include "string.h"
#include <set>

enum GameScreen
{
    MAIN_MENU,
    HOUSE_SELECTION,
    AUCTION_PAGE,
    WAITING_PAGE,
    HOUSE_MORE_INFORMATION,
    USER_PAGE,
    ADMIN_PAGE,
    USER_PURCHASE_FINAL,
    USER_FAIL
};
GameScreen current_screen = MAIN_MENU;

enum HOUSE
{
    first_house,
    second_house,
    third_house,
    fourth_house,
    fifth_house,
    sixth_house,
    seventh_house,
    eighth_house,
    ninth_house,
    tenth_house,
    eleventh_house,
    twelfth_house
};
HOUSE current_house = first_house;

struct house_detail
{
    int price;
    string house_name;
    int bedrooms;
    int bathrooms;
    string location;
    double land_size;
    double floor_area;
    string house_type;
    int year_built;
    int garage_spaces;
    bool has_garden;
    bool has_pool;
    string orientation;
    string condition;
};

int main()
{
    int extra_time_added = 0;
    int property_count = 0;
    string time_left = "";
    int total_house = 12;
    std::set<std::string> properties = {};
    dynamic_array<house_detail> house_list_more;
    const int total_house_const = 12;
    connection server_conn = open_connection("client1", "127.0.0.1", 6000);
    window main_win = open_window("HOUSEMATCH", 1280, 720);
    timer minute_countdown = create_timer("1 Minute");
    unsigned long current_time = 0;
    if (!is_connection_open(server_conn))
    {
        write_line("WARNING: Could not connect to server!");
    };

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

    point_2d house_price_pos;
    point_2d house_description_pos;

    bitmap first_house = load_bitmap("first_house_image", "first_house.jpg");
    bitmap second_house = load_bitmap("second_house_image", "second_house.jpg");
    bitmap third_house = load_bitmap("third_house_image", "third_house.jpg");
    bitmap fourth_house = load_bitmap("fourth_house_image", "fourth_house.jpg");
    bitmap fifth_house = load_bitmap("fifth_house_image", "fifth_house.jpg");
    bitmap sixth_house = load_bitmap("sixth_house_image", "sixth_house.jpg");
    bitmap seventh_house = load_bitmap("seventh_house_image", "seventh_house.jpg");
    bitmap eighth_house = load_bitmap("eighth_house_image", "eighth_house.jpg");
    bitmap ninth_house = load_bitmap("ninth_house_image", "ninth_house.jpg");
    bitmap tenth_house = load_bitmap("tenth_house_image", "tenth_house.jpg");
    bitmap eleventh_house = load_bitmap("eleventh_house_image", "eleventh_house.jpg");
    bitmap twelfth_house = load_bitmap("twelfth_house_image", "twelfth_house.jpg");

    bitmap bitmap_list[total_house_const] = {first_house, second_house, third_house, fourth_house, fifth_house, sixth_house, seventh_house, eighth_house, ninth_house, tenth_house, eleventh_house, twelfth_house};
    bool bitmap_list_check[total_house] = {true};
    house_detail house_list_detail[total_house_const] = {
        {650000, "House A", 3, 2, "Clayton", 450.0, 180.0, "Single Storey", 2005, 2, true, false, "North", "Well Maintained"},
        {720000, "House B", 4, 2, "Glen Waverley", 520.0, 220.0, "Double Storey", 2012, 2, true, false, "East", "Excellent"},
        {800000, "House C", 4, 3, "Box Hill", 480.0, 240.0, "Double Storey", 2018, 2, true, true, "North", "Brand New"},
        {540000, "House D", 2, 1, "Springvale", 320.0, 110.0, "Townhouse", 1995, 1, false, false, "West", "Needs Renovation"},
        {910000, "House E", 5, 3, "Doncaster", 650.0, 310.0, "Double Storey", 2020, 3, true, true, "South", "Brand New"},
        {675000, "House F", 3, 2, "Mulgrave", 400.0, 175.0, "Single Storey", 2008, 2, true, false, "East", "Well Maintained"},
        {1050000, "House G", 5, 4, "Camberwell", 720.0, 350.0, "Double Storey", 2021, 3, true, true, "North", "Brand New"},
        {485000, "House H", 2, 1, "Noble Park", 280.0, 95.0, "Unit", 1988, 1, false, false, "West", "Needs Renovation"},
        {830000, "House I", 4, 2, "Blackburn", 500.0, 230.0, "Double Storey", 2015, 2, true, false, "South", "Excellent"},
        {760000, "House J", 3, 2, "Burwood", 430.0, 190.0, "Single Storey", 2010, 2, true, false, "East", "Well Maintained"},
        {995000, "House K", 5, 3, "Balwyn", 680.0, 320.0, "Double Storey", 2019, 3, true, true, "North", "Excellent"},
        {620000, "House L", 3, 2, "Oakleigh", 390.0, 165.0, "Townhouse", 2003, 2, false, false, "West", "Well Maintained"}};
    double target_width = 400;
    double target_height = 300;

    string name = "unknown";
    string display_name = "";
    bool was_reading = false;
    rectangle input_rect = rectangle_from(230.0, 50.0, 200.0, 30.0);
    rectangle button_rect = rectangle_from(230.0, 100.0, 100.0, 40.0);

    int current_price = 100;
    // string name = "";
    string header = "HouseMatch";
    string title = "Swipe. Match. Win.";
    string tag_line = "Find a house you love, get matched with another buyer, and settle it with a live bid.";
    string footer = "A real-time house-buying game";
    string house_price = "$650,00";
    string house_description = "4 bed - 2 bath - Glen Waverley";
    string waiting_for_match = "Waiting for match";
    string waiting_for_match_description = "Whe might start the auction the moment another user clicks YES to this house";
    string HOUSE_MATCH_DASHBOARD = "HOUSEMATCH - DASHBOARD";
    string HOUSE_OWNED = "HOUSE OWNED:";
    string HOUSE_AVAILABLE = "HOUSE AVAILABLE:";
    string HOUSE_UNSOLD = "HOUSE_UNSOLD";
    string HOUSE_TOTAL = "HOUSE_TOTAL";
    string HOUSE_REMAINING = "HOUSE_REMAINING";
    int time_temp;
    int total_revenue = 100;
    int flag_count = 1;
    bool flag;
    bool is_entering_name = false;
    int flag1 = 0;
    while (!quit_requested())
    {
        check_network_activity();

        while (has_messages(server_conn))
        {
            message message_log = read_message(server_conn);
            string data = message_data(message_log);

            if (is_integer(data))
            {
                current_price = to_integer(data);
            }
            else if (contains(data, "TIME:"))
            {
                time_left = data;
            }
            else
            {
                for (int i = 0; i < total_house; i++)
                {
                    if (data == ("ITEM:" + to_string(i)))
                    {
                        flag1 += 1;
                    }
                }
            }

            close_message(message_log);
        }
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
                current_screen = USER_PAGE;
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
                send_message_to("ITEM:" + to_string(current_house), server_conn);
                current_screen = WAITING_PAGE;
                continue;
            }
            if (button("MORE_INFO", rectangle_from(center_point_pos.x, center_point_pos.y + 100 - 12, 200, 24)))
            // if (button("Yes", rectangle_from(start_btn_pos.x, start_btn_pos.y, 200, 24)))
            {
                current_screen = HOUSE_MORE_INFORMATION;
            }
            if (button("No", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 200 - 12, 200, 24)))
            {
                // if (flag_count == 12)
                // {
                //     for (int i = 0; i < total_house; i++)
                //     {
                //         bitmap_list_check[i] = false;
                //     }
                //     flag_count = 0;
                // }
                // do
                // {
                current_house = (HOUSE)rnd(0, 3);
                write_line(house_list_more[current_house].house_name);
                // } while (bitmap_list_check[current_house]);
                // bitmap_list_check[current_house] = true;
                // flag_count++;
                // write_line("Flag Count:" + to_string(flag_count));
                // write_line("Total House:" + to_string(total_house));
            }

            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);

            house_price_pos.x = 300;
            house_price_pos.y = 400;

            house_description_pos.x = 300;
            house_description_pos.y = 450;
            draw_text("$" + to_string(house_list_detail[current_house].price), COLOR_BLACK, font_named("input"), 20, house_price_pos.x, house_price_pos.y);
            draw_text(house_list_detail[current_house].house_name, COLOR_BLACK, font_named("input"), 20, house_description_pos.x, house_description_pos.y);

            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            house_price_pos.x = 300;
            house_price_pos.y = 400;

            house_description_pos.x = 300;
            house_description_pos.y = 450;
            // draw_text("$" + to_string(current_price), COLOR_BLACK, font_named("input"), 20, house_price_pos.x, house_price_pos.y);
            string detail = house_list_detail[current_house].house_name + " - " + to_string(house_list_detail[current_house].bathrooms) + " bathrooms - " + to_string(house_list_detail[current_house].bedrooms) + " bedrooms - " + house_list_detail[current_house].location;
            draw_text(detail, COLOR_BLACK, font_named("input"), 20, house_description_pos.x, house_description_pos.y);
            // };
        }
        else if (current_screen == WAITING_PAGE)
        {
            current_price = house_list_detail[current_house].price;
            send_message_to(to_string(current_price), server_conn);
            clear_screen(COLOR_WHITE);
            // draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            draw_text(waiting_for_match, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y);
            // if (button("AUCTION STARTED", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 200 - 12, 200, 24)))
            if (flag1 == 2)
            {
                current_screen = AUCTION_PAGE;
            };
        }
        else if (current_screen == AUCTION_PAGE)
        {
            int one_minute = 30;
            if (!flag)
            {
                start_timer(minute_countdown);
                flag = true;
            };
            current_time = timer_ticks(minute_countdown);
            int running_second = (int)current_time / 1000;
            int remaining_second = one_minute - running_second + extra_time_added;
            if (remaining_second == 0)
            {
                current_screen = USER_PAGE;
                for (int i = 0; i < total_house; i++)
                {
                    if (bitmap_list[i] == bitmap_list[current_house])
                    {
                        for (int j = i; j < total_house - 1; j++)
                        {
                            bitmap_list[j] = bitmap_list[j + 1];
                            house_list_detail[i] = house_list_detail[i + 1];
                        }
                        flag = false;
                        flag1 = 0;
                    }
                }
                total_house--;
            };
            double bar_x = center_point_pos.x - 100;
            double bar_y = 0;
            double bar_width = 200;
            double bar_height = 30;

            fill_rectangle(COLOR_GRAY, rectangle_from(bar_x, bar_y, bar_width, bar_height));

            double progress_ratio = (double)remaining_second / one_minute;
            if (progress_ratio < 0)
                progress_ratio = 0;
            if (progress_ratio > 1)
                progress_ratio = 1;

            double filled_width = bar_width * progress_ratio;
            fill_rectangle(COLOR_GREEN, rectangle_from(bar_x, bar_y, filled_width, bar_height));

            send_message_to("TIME:" + to_string(remaining_second), server_conn);
            draw_text("Remaining time:" + time_left, COLOR_BLACK, font_named("input"), 20, header_pos.x + 200, header_pos.y);
            draw_text("$" + to_string(current_price), COLOR_BLACK, font_named("input"), 20, house_price_pos.x, house_price_pos.y);

            draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);

            if (button("+100 AUD", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 200 - 12, 200, 24)))
            {
                if (remaining_second > 0 && remaining_second < 15)
                {
                    extra_time_added += 15;
                }
                current_price += 100;
                send_message_to(to_string(current_price), server_conn);
            };
            if (button("+200 AUD", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 230 - 12, 200, 24)))
            {
                if (remaining_second > 0 && remaining_second < 15)
                {
                    extra_time_added += 15;
                };
                current_price += 200;
                send_message_to(to_string(current_price), server_conn);
            };
            if (button("+300 AUD", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 260 - 12, 200, 24)))
            {
                if (remaining_second > 0 && remaining_second < 15)
                {
                    extra_time_added += 15;
                };
                current_price += 300;
                send_message_to(to_string(current_price), server_conn);
            };

            if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), input_rect) && !reading_text())
            {
                start_reading_text(input_rect);
            }

            if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), button_rect))
            {
                if (reading_text())
                {
                    if (text_entry_cancelled())
                    {
                        name = "unknown";
                    }
                    else
                    {
                        name = text_input();
                    }
                    if (is_integer(name))
                    {
                        if (remaining_second > 0 && remaining_second < 15)
                        {
                            extra_time_added += 15;
                        };
                        current_price += to_integer(name);
                        send_message_to(to_string(current_price), server_conn);
                    }
                }
                display_name = name;
            }

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
            // draw_text(display_name, COLOR_BLACK, font_named("input"), 18, 10, 10);
        }
        else if (current_screen == USER_PAGE)
        {
            clear_screen(COLOR_WHITE);
            bool my_bool = false;

            rectangle checkbox1_container = rectangle_from(200, 300, 180, 50);
            rectangle checkbox2_container = rectangle_from(200, 360, 180, 50);
            rectangle checkbox3_container = rectangle_from(200, 420, 180, 50);
            rectangle checkbox4_container = rectangle_from(200, 480, 180, 50);
            if (checkbox("<2 Bedrooms", my_bool, checkbox1_container))
            {
                properties.insert("<2 Bedrooms");
                property_count += 1;
            }
            else if (checkbox("<2 Bathrooms", my_bool, checkbox2_container))
            {
                properties.insert("<2 Bathrooms");
                property_count += 2;
            }
            else if (checkbox("Pool", my_bool, checkbox3_container))
            {
                properties.insert("Pool");
                property_count += 4;
            }
            else if (checkbox("Garden", my_bool, checkbox4_container))
            {
                properties.insert("Garden");
                property_count += 8;
            };
            // draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            draw_text(HOUSE_MATCH_DASHBOARD, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y);
            ///
            draw_text(HOUSE_OWNED, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y + 30);
            draw_text("0", COLOR_BLACK, font_named("input"), 20, header_pos.x + 250, header_pos.y + 30);

            // a
            draw_text(HOUSE_AVAILABLE, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y + 60);
            draw_text(to_string(total_house), COLOR_BLACK, font_named("input"), 20, header_pos.x + 250, header_pos.y + 60);

            if (button("START CHOOSING", rectangle_from(0, 300, 200, 24)))
            {
                switch (property_count)
                {
                case 4:
                {
                    for (int i = 0; i < total_house; i++)
                        if (house_list_detail[i].has_pool)
                            add(house_list_more, house_list_detail[i]);
                    break;
                }
                // case 2:
                //     break;
                // case 4:
                //     break;
                // case 8:
                //     break;
                default:
                    break;
                }
                current_screen = HOUSE_SELECTION;
            };
        }
        else if (current_screen == HOUSE_MORE_INFORMATION)
        {
            if (!has_window("HOUSE INFORMATION"))
            {
                open_window("HOUSE INFORMATION", 700, 500);
            }
            window info_win = window_named("HOUSE INFORMATION");

            string detail_house_txt = "This " + house_list_detail[current_house].house_type + " home in " +
                                      house_list_detail[current_house].location + " features " +
                                      to_string(house_list_detail[current_house].bedrooms) + " spacious bedrooms and " +
                                      to_string(house_list_detail[current_house].bathrooms) + " bathrooms, set on a generous " +
                                      to_string(house_list_detail[current_house].land_size) + "m² block with a " +
                                      to_string(house_list_detail[current_house].floor_area) + "m² floor plan. Built in " +
                                      to_string(house_list_detail[current_house].year_built) + " and " +
                                      to_lowercase(house_list_detail[current_house].condition) + ", this " +
                                      house_list_detail[current_house].orientation + "-facing property comes with " +
                                      to_string(house_list_detail[current_house].garage_spaces) + "-car garage space.";

            set_current_window(info_win);
            clear_screen(COLOR_WHITE);
            paragraph(detail_house_txt);
            draw_bitmap_on_window(info_win, bitmap_list[current_house], 80, 50, opt);

            bool back_clicked = button("BACK TO CHOOSING", rectangle_from(250, 450, 200, 24));
            draw_interface();
            refresh_screen();

            if (back_clicked || window_close_requested(info_win))
            {
                close_window(info_win);
                current_screen = HOUSE_SELECTION;
            }

            set_current_window(main_win);
        }
        else if (current_screen == ADMIN_PAGE)
        {
            clear_screen(COLOR_WHITE);
            // draw_bitmap(bitmap_list[current_house], center_point_pos.x - bmp_width / 2, (center_point_pos.y - bmp_height / 2) - 80, opt);
            draw_text(HOUSE_MATCH_DASHBOARD, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y);
            //
            draw_text(HOUSE_TOTAL, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y + 30);
            draw_text(to_string(total_house_const), COLOR_BLACK, font_named("input"), 20, header_pos.x + 250, header_pos.y + 30);
            //
            draw_text(HOUSE_UNSOLD, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y + 60);
            draw_text(to_string(total_house), COLOR_BLACK, font_named("input"), 20, header_pos.x + 250, header_pos.y + 30);
            //
            draw_text(HOUSE_REMAINING, COLOR_BLACK, font_named("input"), 20, header_pos.x, header_pos.y + 90);
            draw_text(to_string(total_house_const - total_house), COLOR_BLACK, font_named("input"), 20, header_pos.x + 250, header_pos.y + 120);
        }
        else if (current_screen == USER_PURCHASE_FINAL)
        {
            clear_screen(COLOR_WHITE);
            draw_text("WAITING FOR OWNER CONFIRMATION", COLOR_BLACK, font_named("input"), 20, center_point_pos.x - 100, center_point_pos.y);
            if (button("Back to user page", rectangle_from(center_point_pos.x - 100, center_point_pos.y + 50, 200, 24)))
            {
                current_screen = USER_PAGE;
            };
        }
        else if (current_screen == USER_FAIL)
        {
            clear_screen(COLOR_WHITE);
            draw_text("THANK YOU FOR TRYING", COLOR_BLACK, font_named("input"), 20, center_point_pos.x - 100, center_point_pos.y);
            if (button("Back to user page", rectangle_from(center_point_pos.x - 100, center_point_pos.y + 50, 200, 24)))
            {
                current_screen = USER_PAGE;
            };
        }
        draw_interface();
        refresh_screen();
    };
    stop_timer(minute_countdown);
    free_all_timers();
    close_all_windows();
    return 0;
}