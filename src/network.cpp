#include "network.h"

connection connect_to_server()
{
    connection conn = open_connection(CLIENT_NAME, SERVER_IP, SERVER_PORT);
    if (!is_connection_open(conn))
    {
        write_line("WARNING: Could not connect to server!");
    }
    return conn;
}

static void handle_message(app_state &state, const string &data)
{
    if (is_integer(data))
    {
        state.auction.current_price = to_integer(data);
    }
    else if (contains(data, "TIME:"))
    {
        state.auction.time_left = data;
    }
    else
    {
        for (int i = 0; i < state.catalog.count; i++)
        {
            if (data == "ITEM:" + to_string(i))
            {
                state.auction.match_count++;
            }
        }
    }
}

void handle_server_messages(app_state &state)
{
    check_network_activity();
    while (has_messages(state.server))
    {
        message msg = read_message(state.server);
        handle_message(state, message_data(msg));
        close_message(msg);
    }
}

void send_price(app_state &state)
{
    send_message_to(to_string(state.auction.current_price), state.server);
}

void send_item_choice(app_state &state)
{
    send_message_to("ITEM:" + to_string(state.current_house), state.server);
}

void send_time_left(app_state &state, int seconds)
{
    send_message_to("TIME:" + to_string(seconds), state.server);
}
