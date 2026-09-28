#include "app_state.h" // STORE EVERYTHING RELATED TO APP STATE
#include "network.h" // CONNECT BTW SERVER AND CLIENT
#include "screens.h" // ALL FUNCTIONS TO DRAW SCREENS

int main()
{
    app_state state;
    init_app(state);

    while (!quit_requested())
    {
        handle_server_messages(state);
        process_events();

        clear_screen(COLOR_WHITE);
        draw_current_screen(state);
        draw_interface();
        refresh_screen();

        update_info_window(state);
    }

    shutdown_app(state);
    return 0;
}
