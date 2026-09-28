#pragma once

#include "app_state.h"

void draw_label(const string &text, int size, double x, double y);
void draw_centered_label(const string &text, int size, double center_x, double y);
void draw_wrapped_text(const string &text, int size, double x, double y, double max_width, double line_height);
bool window_button(window win, const string &label, const rectangle &rect);
void draw_current_house_image(const app_state &state);
