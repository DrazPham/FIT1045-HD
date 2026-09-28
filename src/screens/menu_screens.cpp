#include "screens.h"
#include "ui.h"

void draw_main_menu(app_state &state)
{
    screen_layout &l = state.layout;
    draw_label(TEXT_HEADER, 20, l.header.x, l.header.y);
    draw_centered_label(TEXT_TITLE, 32, l.title.x, l.title.y);
    draw_centered_label(TEXT_TAG_LINE, 16, l.tag_line.x, l.tag_line.y);
    draw_centered_label(TEXT_FOOTER, 14, l.footer.x, l.footer.y);

    if (button("Let's Start", rectangle_from(l.start_button.x - 100, l.start_button.y - 12, 200, 24)))
    {
        state.screen = USER_PAGE;
    }
}

static void draw_message_with_back(app_state &state, const string &text)
{
    point_2d c = state.layout.center;
    draw_label(text, 20, c.x - 100, c.y);
    if (button("Back to user page", rectangle_from(c.x - 100, c.y + 50, 200, 24)))
    {
        state.screen = USER_PAGE;
    }
}

void draw_purchase_final(app_state &state)
{
    draw_message_with_back(state, "WAITING FOR OWNER CONFIRMATION");
}

void draw_user_fail(app_state &state)
{
    draw_message_with_back(state, "THANK YOU FOR TRYING");
}
