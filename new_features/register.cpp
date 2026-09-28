#include "splashkit.h"

struct account_detail
{
    string username;
    string pwd;
};
bool flaglogin = true;
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
    open_window("REGISTER!", 800, 600);
    load_font("input", "arial.ttf");

    string encoded_message;
    string keyword = "KEY";
    point_2d center_point_pos = screen_center();
    string fetch_data;
    account_detail user1;

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
            write_line("DATA" + data);
            fetch_data = data;
            close_message(message_log);
        }
        draw_text("NAME", COLOR_BLACK, font_named("input"), 20, center_point_pos.x - 100, center_point_pos.y - 130);
        draw_text("NAME", COLOR_BLACK, font_named("input"), 20, center_point_pos.x - 100, center_point_pos.y - 40);
        process_events();
        clear_screen(COLOR_WHITE);
        rectangle username_rect = rectangle_from(center_point_pos.x - 100, center_point_pos.y - 100, 200, 30);
        rectangle password_rect = rectangle_from(center_point_pos.x - 100, center_point_pos.y - 10, 200, 30);
        draw_rectangle(COLOR_BLACK, username_rect);
        draw_rectangle(COLOR_BLACK, password_rect);
        if (button("Open typing", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 200 - 12, 200, 24)))
        {
            start_reading_text(username_rect);
            is_entering_name = true;
            flaglogin = true;
        };
        if (button("Open typing pwd ", rectangle_from(center_point_pos.x + 100, center_point_pos.y + 230 - 12, 200, 24)))
        {
            start_reading_text(password_rect);
            is_entering_name = true;
            flaglogin = false;
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
                    if (flaglogin)
                    {
                        user1.username = name;
                        write_line("USERNAME: " + user1.username);
                    }
                    else
                    {
                        user1.pwd = name;
                        write_line("pwd:" + user1.pwd);
                    }
                    is_entering_name = false;
                }
            }
        }
        // if (button("CREATE", rectangle_from(center_point_pos.x - 100, center_point_pos.y + 60, 200, 30)))
        // {
        //     // write_line("USERNAME: " + user1.username);
        //     // write_line("PWD:  " + user1.pwd);
        //     encoded_message = vigenere_cipher_encode(password_detail, keyword);
        //     send_message_to(encoded_message, server_info);
        //     write_line("ENCODED" + encoded_message);
        // };

        if (button("FETCH", rectangle_from(center_point_pos.x - 300, center_point_pos.y + 120, 200, 30)))
        {
            string decrypted_msg = vigenere_cipher_decode(fetch_data, keyword);
            string password_detail = "Username: " + user1.username + ", Pwd: " + user1.pwd;
            write_line(decrypted_msg);
            if (decrypted_msg == password_detail)
                write_line("VALID");
            else
            {
                write_line("INVALID");
                // string password_detail = "Username: " + user1.username + ", Pwd: " + user1.pwd;
            }
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