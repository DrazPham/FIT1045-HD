#pragma once

#include "splashkit.h"
#include "config.h"

struct house_detail
{
    int price;
    string house_name;
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

struct house_catalog
{
    house_detail details[TOTAL_HOUSES];
    bitmap images[TOTAL_HOUSES];
    int count;
};

void load_house_catalog(house_catalog &catalog);
void remove_house(house_catalog &catalog, int index);
string house_summary(const house_detail &house);
string house_full_description(const house_detail &house);
