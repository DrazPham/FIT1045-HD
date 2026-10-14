#include "house_data.h"

json house_to_json(const house &h)
{
    json j = create_json();
    json_set_number(j, "id", h.id);
    json_set_string(j, "owner", h.owner);
    json_set_string(j, "house_name", h.house_name);
    json_set_number(j, "price", h.price);
    json_set_number(j, "bedrooms", h.bedrooms);
    json_set_number(j, "bathrooms", h.bathrooms);
    json_set_string(j, "location", h.location);
    json_set_number(j, "land_size", h.land_size);
    json_set_number(j, "floor_area", h.floor_area);
    json_set_string(j, "house_type", h.house_type);
    json_set_number(j, "year_built", h.year_built);
    json_set_number(j, "garage_spaces", h.garage_spaces);
    json_set_bool(j, "has_garden", h.has_garden);
    json_set_bool(j, "has_pool", h.has_pool);
    json_set_string(j, "orientation", h.orientation);
    json_set_string(j, "condition", h.condition);
    return j;
}

house house_from_json(json j)
{
    house h;
    h.id = json_read_number_as_int(j, "id");
    h.owner = json_read_string(j, "owner");
    h.house_name = json_read_string(j, "house_name");
    h.price = json_read_number_as_int(j, "price");
    h.bedrooms = json_read_number_as_int(j, "bedrooms");
    h.bathrooms = json_read_number_as_int(j, "bathrooms");
    h.location = json_read_string(j, "location");
    h.land_size = json_read_number_as_double(j, "land_size");
    h.floor_area = json_read_number_as_double(j, "floor_area");
    h.house_type = json_read_string(j, "house_type");
    h.year_built = json_read_number_as_int(j, "year_built");
    h.garage_spaces = json_read_number_as_int(j, "garage_spaces");
    h.has_garden = json_read_bool(j, "has_garden");
    h.has_pool = json_read_bool(j, "has_pool");
    h.orientation = json_read_string(j, "orientation");
    h.condition = json_read_string(j, "condition");
    return h;
}

json houses_to_json(const dynamic_array<house> &list)
{
    std::vector<json> items;
    for (int i = 0; i < length(list); i++)
    {
        items.push_back(house_to_json(list[i]));
    }

    json root = create_json();
    json_set_array(root, "houses", items);

    for (json item : items)
    {
        free_json(item);
    }
    return root;
}

void houses_from_json(json root, dynamic_array<house> &list)
{
    clear(list);
    if (!json_has_key(root, "houses"))
    {
        return;
    }

    std::vector<json> items;
    json_read_array(root, "houses", items);
    for (json item : items)
    {
        add(list, house_from_json(item));
        free_json(item);
    }
}

string houses_to_string(const dynamic_array<house> &list)
{
    json root = houses_to_json(list);
    string text = json_to_string(root);
    free_json(root);
    return text;
}

void houses_from_string(const string &text, dynamic_array<house> &list)
{
    json root = json_from_string(text);
    houses_from_json(root, list);
    free_json(root);
}

void load_houses(const string &filename, dynamic_array<house> &list)
{
    json root = json_from_file(filename);
    houses_from_json(root, list);
    free_json(root);
}

void save_houses(const string &filename, const dynamic_array<house> &list)
{
    json root = houses_to_json(list);
    json_to_file(root, filename);
    free_json(root);
}
