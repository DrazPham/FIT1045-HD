#include "splashkit.h"
#include "splashkit-arrays.h"
#include "house_data.h"

using message_handler = bool (*)(const string &, connection);

const string HOUSES_FILE = "houses.json";

dynamic_array<house> houses;

int next_id(const dynamic_array<house> &list)
{
    int max_id = 0;
    for (int i = 0; i < length(list); i++)
    {
        if (list[i].id > max_id)
        {
            max_id = list[i].id;
        }
    }
    return max_id + 1;
}

house add_house(dynamic_array<house> &list, house h)
{
    h.id = next_id(list);
    add(list, h);
    save_houses(HOUSES_FILE, list);
    return h;
}

bool remove_house(dynamic_array<house> &list, int id)
{
    for (int i = 0; i < length(list); i++)
    {
        if (list[i].id == id)
        {
            remove_at(list, i);
            save_houses(HOUSES_FILE, list);
            return true;
        }
    }
    return false;
}

bool house_update_handler(const string &data, connection sender)
{
    if (data == "GET_HOUSES")
    {
        send_message_to("HOUSES:" + houses_to_string(houses), sender);
        return true;
    }
    return false;
}

void server_handler(server_socket sv, bool should_broadcast, message_handler handler = nullptr)
{
    while (has_messages(sv))
    {
        message msg = read_message(sv);
        string data = message_data(msg);
        connection sender = message_connection(msg);
        close_message(msg);

        if (handler != nullptr && handler(data, sender))
        {
            continue;
        }
        if (should_broadcast)
        {
            broadcast_message(data, sv);
        }
    }
}

int main()
{
    server_socket MainServer = create_server("Main", 6000);
    server_socket TimeCountDownServer = create_server("TimeCountDown", 6123);
    server_socket InformationServer = create_server("INFORMATION", 6345);

    load_houses(HOUSES_FILE, houses);

    while (true)
    {
        check_network_activity();
        server_handler(TimeCountDownServer, true);
        server_handler(MainServer, true, house_update_handler);
        server_handler(InformationServer, false);
        delay(10);
    }

    close_all_servers();
    return 0;
}
