#include "splashkit.h"
using namespace std;

int main()
{
    server_socket MainServer = create_server("Main", 6000);
    server_socket InformationServer = create_server("INFORMATION", 6345);
    write_line("Server started, waiting for connections...");

    while (true)
    {
        check_network_activity();

        while (has_messages(MainServer))
        {
            message msg = read_message(MainServer);
            string data = message_data(msg);
            // if (to_integer(data) != 30)
            // {
            write_line("Received: " + data);
            // }

            broadcast_message(data, MainServer);

            close_message(msg);
        };
        while (has_messages(InformationServer))
        {
            message msg_info = read_message(InformationServer);
            string data_info = message_data(msg_info);
            write_line("Received: " + data_info);

            broadcast_message(data_info, InformationServer);

            close_message(msg_info);
        }
    }

    close_all_servers();
    return 0;
}