#include "splashkit.h"
using namespace std;

int main()
{
    server_socket MainServer = create_server("Main", 6000);
    write_line("Server started, waiting for connections...");

    while (true)
    {
        check_network_activity();

        // if (has_new_connections())
        // {
        //      write_line("New client connected! Total: " + to_string(connection_count(MainServer)));
        // }

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
        }
    }

    close_server(MainServer);
    return 0;
}