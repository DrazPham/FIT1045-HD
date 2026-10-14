#pragma once

#include "splashkit.h"
#include "splashkit-arrays.h"

struct house
{
    int id;
    string owner;
    string house_name;
    int price;
    int bedrooms;
    int bathrooms;
    string location;
    double land_size;
    double floor_area;
    string house_type;
    int year_built;
    int garage_spaces;
    bool has_garden;
    bool has_pool;
    string orientation;
    string condition;
};

json house_to_json(const house &h);
house house_from_json(json j);

json houses_to_json(const dynamic_array<house> &list);
void houses_from_json(json root, dynamic_array<house> &list);

string houses_to_string(const dynamic_array<house> &list);
void houses_from_string(const string &text, dynamic_array<house> &list);

void load_houses(const string &filename, dynamic_array<house> &list);
void save_houses(const string &filename, const dynamic_array<house> &list);
