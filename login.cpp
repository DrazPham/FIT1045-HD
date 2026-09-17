#include "splashkit.h"

string vigenere_cipher_encode(const string &input, const string &keyword)
{
    string encoded_string;

    for (size_t i = 0; i < input.size(); i++)
    {
        unsigned char character = input[i];
        unsigned char key = keyword[i % keyword.size()];
        unsigned char encoded_char = (character + key) % 127;
        encoded_string += encoded_char;
    }

    return encoded_string;
};

string vigenere_cipher_decode(const string &input, const string &keyword)
{
    string decoded_string;

    for (size_t i = 0; i < input.size(); i++)
    {
        unsigned char character = input[i];
        unsigned char key = keyword[i % keyword.size()];

        unsigned char decoded_char = (character - key + 127) % 127;
        decoded_string += decoded_char;
    }

    return decoded_string;
};
int main()
{
    connection server_info = open_connection("client1", "127.0.0.1", 6345);
    open_window("LOGIN!", 800, 600);
    load_font("input", "arial.ttf");

    string encoded_message;
    string keyword = "KEY";
    point_2d center_point_pos = screen_center();

    if (!is_connection_open(server_info))
    {
        write_line("WARNING: Could not connect to server!");
    };
    while (!quit_requested())
    {
        check_network_activity();
        bool is_entering_name;
        string name;
        while (has_messages(server_info))
        {
            message message_log = read_message(server_info);
            string data = message_data(message_log);
            close_message(message_log);
        }
        process_events();
        clear_screen(COLOR_WHITE);
        rectangle rect = rectangle_from(500.0, 550.0, 200.0, 30.0);
        draw_rectangle(COLOR_BLACK, rect);
        if (button("Open typing", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 200 - 12, 200, 24)))
        {
            start_reading_text(rect);
            is_entering_name = true;
        }

        if (is_entering_name)
        {
            if (reading_text())
            {
                draw_collected_text(COLOR_BLACK, font_named("input"), 18, option_defaults());
            }
            else
            {
                if (text_entry_cancelled())
                    name = "unknown";
                else
                {
                    name = text_input();
                    encoded_message = vigenere_cipher_encode(name, keyword);

                    is_entering_name = false;
                }
            }
        }
        if (button("CREATE", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 260 - 12, 200, 24)))
        {
            write_line(name);
            send_message_to(encoded_message, server_info);
            write_line(encoded_message);
        };

        draw_interface();
        refresh_screen();
    }
    // string message = "Hello, World!";
    // string encoded_message = vigenere_cipher_encode(message, keyword);
    // string decoded_message = vigenere_cipher_decode(encoded_message, keyword);
    // write_line(message);
    // write_line(encoded_message);
    // write_line(decoded_message);
    return 0;
}