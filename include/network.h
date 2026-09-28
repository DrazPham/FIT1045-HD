#pragma once

#include "app_state.h"

connection connect_to_server();
void handle_server_messages(app_state &state);
void send_price(app_state &state);
void send_item_choice(app_state &state);
void send_time_left(app_state &state, int seconds);
