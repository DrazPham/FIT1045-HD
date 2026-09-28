#include "app_state.h"
#include "network.h"

void init_app(app_state &state)
{
    state.main_window = open_window(MAIN_WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
    load_font(FONT_NAME, FONT_FILE);

    state.server = connect_to_server();
    state.layout = create_layout();
    load_house_catalog(state.catalog);

    state.screen = MAIN_MENU;
    state.current_house = 0;
    state.info_open = false;

    state.auction.countdown = create_timer("auction_countdown");
    state.auction.started = false;
    state.auction.extra_time = 0;
    state.auction.current_price = 0;
    state.auction.match_count = 0;
    state.auction.time_left = "";

    state.bid.text = "";
    state.bid.input_rect = rectangle_from(230, 50, 200, 30);
    state.bid.submit_rect = rectangle_from(230, 100, 100, 40);

    state.filter.property_count = 0;
}

void shutdown_app(app_state &state)
{
    if (state.server != nullptr && is_connection_open(state.server))
    {
        send_message_to("BYE", state.server);
    }
    stop_timer(state.auction.countdown);
    free_all_timers();
    close_all_connections();
    close_all_windows();
}
