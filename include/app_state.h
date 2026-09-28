#pragma once

#include <set>
#include "splashkit.h"
#include "splashkit-arrays.h"
#include "house.h" // store everything related to house enum, structs,functions
#include "layout.h"

enum page_screen
{
    MAIN_MENU,
    USER_PAGE,
    HOUSE_SELECTION,
    WAITING_PAGE,
    AUCTION_PAGE,
    ADMIN_PAGE,
    USER_PURCHASE_FINAL,
    USER_FAIL
};

struct auction_state
{
    timer countdown;
    bool started;
    int extra_time;
    int current_price;
    int match_count;
    string time_left;
};

struct bid_input
{
    string text;
    rectangle input_rect;
    rectangle submit_rect;
};

struct user_filter
{
    std::set<string> properties;
    int property_count;
    dynamic_array<house_detail> matching_houses;
};

struct app_state
{
    page_screen screen;
    int current_house;
    bool info_open;
    window main_window;
    connection server;
    screen_layout layout;
    house_catalog catalog;
    auction_state auction;
    bid_input bid;
    user_filter filter;
};

void init_app(app_state &state);
void shutdown_app(app_state &state);
