#include "screens.h"
#include "ui.h"
#include "network.h"

void draw_waiting_page(app_state &state)
{
    state.auction.current_price = state.catalog.details[state.current_house].price;
    send_price(state);
    draw_label(TEXT_WAITING, 20, state.layout.header.x, state.layout.header.y);

    if (state.auction.match_count == PLAYERS_TO_MATCH)
    {
        state.screen = AUCTION_PAGE;
    }
}

static int remaining_seconds(auction_state &auction)
{
    if (!auction.started)
    {
        start_timer(auction.countdown);
        auction.started = true;
    }
    int elapsed = timer_ticks(auction.countdown) / 1000;
    return AUCTION_SECONDS - elapsed + auction.extra_time;
}

static void end_auction(app_state &state)
{
    remove_house(state.catalog, state.current_house);
    if (state.current_house >= state.catalog.count)
    {
        state.current_house = 0;
    }
    stop_timer(state.auction.countdown);
    reset_timer(state.auction.countdown);
    state.auction.started = false;
    state.auction.extra_time = 0;
    state.auction.match_count = 0;
    state.screen = USER_PAGE;
}

static void place_bid(app_state &state, int amount, int remaining)
{
    if (remaining > 0 && remaining < EXTRA_TIME_THRESHOLD)
    {
        state.auction.extra_time += EXTRA_TIME_SECONDS;
    }
    state.auction.current_price += amount;
    send_price(state);
}

static void draw_progress_bar(const app_state &state, int remaining)
{
    rectangle bar = rectangle_from(state.layout.center.x - 100, 0, 200, 30);
    double ratio = (double)remaining / AUCTION_SECONDS;
    if (ratio < 0)
        ratio = 0;
    if (ratio > 1)
        ratio = 1;
    fill_rectangle(COLOR_GRAY, bar);
    fill_rectangle(COLOR_GREEN, rectangle_from(bar.x, bar.y, bar.width * ratio, bar.height));
}

static void handle_custom_bid(app_state &state, int remaining)
{
    bid_input &bid = state.bid;

    if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), bid.input_rect) && !reading_text())
    {
        start_reading_text(bid.input_rect);
    }

    if (mouse_clicked(LEFT_BUTTON) && point_in_rectangle(mouse_position(), bid.submit_rect) && reading_text())
    {
        bid.text = text_entry_cancelled() ? "" : text_input();
        if (is_integer(bid.text))
        {
            place_bid(state, to_integer(bid.text), remaining);
        }
    }

    draw_rectangle(COLOR_BLACK, bid.input_rect);
    if (reading_text())
    {
        draw_collected_text(COLOR_BLACK, font_named(FONT_NAME), 18, option_defaults());
    }
    else
    {
        draw_label(bid.text, 18, bid.input_rect.x + 5, bid.input_rect.y + 5);
    }
    draw_rectangle(COLOR_GRAY, bid.submit_rect);
    draw_label("Submit", 18, bid.submit_rect.x + 15, bid.submit_rect.y + 10);
}

void draw_auction_page(app_state &state)
{
    point_2d c = state.layout.center;
    screen_layout &l = state.layout;
    int remaining = remaining_seconds(state.auction);

    if (remaining <= 0)
    {
        end_auction(state);
        return;
    }

    draw_progress_bar(state, remaining);
    send_time_left(state, remaining);
    draw_label("Remaining time:" + state.auction.time_left, 20, l.header.x + 200, l.header.y);
    draw_label("$" + to_string(state.auction.current_price), 20, l.house_price.x, l.house_price.y);
    draw_current_house_image(state);

    if (button("+100 AUD", rectangle_from(c.x - 300, c.y + 188, 200, 24)))
    {
        place_bid(state, 100, remaining);
    }
    if (button("+200 AUD", rectangle_from(c.x - 300, c.y + 218, 200, 24)))
    {
        place_bid(state, 200, remaining);
    }
    if (button("+300 AUD", rectangle_from(c.x - 300, c.y + 248, 200, 24)))
    {
        place_bid(state, 300, remaining);
    }

    handle_custom_bid(state, remaining);
}
