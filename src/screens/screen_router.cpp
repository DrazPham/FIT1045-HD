#include "screens.h"

void draw_current_screen(app_state &state)
{
    switch (state.screen)
    {
    case MAIN_MENU:
        draw_main_menu(state);
        break;
    case USER_PAGE:
        draw_user_page(state);
        break;
    case HOUSE_SELECTION:
        draw_house_selection(state);
        break;
    case WAITING_PAGE:
        draw_waiting_page(state);
        break;
    case AUCTION_PAGE:
        draw_auction_page(state);
        break;
    case ADMIN_PAGE:
        draw_admin_page(state);
        break;
    case USER_PURCHASE_FINAL:
        draw_purchase_final(state);
        break;
    case USER_FAIL:
        draw_user_fail(state);
        break;
    }
}
