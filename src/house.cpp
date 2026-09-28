#include "house.h"

static const house_detail HOUSE_DATA[TOTAL_HOUSES] = {
    {650000, "House A", 3, 2, "Clayton", 450.0, 180.0, "Single Storey", 2005, 2, true, false, "North", "Well Maintained"},
    {720000, "House B", 4, 2, "Glen Waverley", 520.0, 220.0, "Double Storey", 2012, 2, true, false, "East", "Excellent"},
    {800000, "House C", 4, 3, "Box Hill", 480.0, 240.0, "Double Storey", 2018, 2, true, true, "North", "Brand New"},
    {540000, "House D", 2, 1, "Springvale", 320.0, 110.0, "Townhouse", 1995, 1, false, false, "West", "Needs Renovation"},
    {910000, "House E", 5, 3, "Doncaster", 650.0, 310.0, "Double Storey", 2020, 3, true, true, "South", "Brand New"},
    {675000, "House F", 3, 2, "Mulgrave", 400.0, 175.0, "Single Storey", 2008, 2, true, false, "East", "Well Maintained"},
    {1050000, "House G", 5, 4, "Camberwell", 720.0, 350.0, "Double Storey", 2021, 3, true, true, "North", "Brand New"},
    {485000, "House H", 2, 1, "Noble Park", 280.0, 95.0, "Unit", 1988, 1, false, false, "West", "Needs Renovation"},
    {830000, "House I", 4, 2, "Blackburn", 500.0, 230.0, "Double Storey", 2015, 2, true, false, "South", "Excellent"},
    {760000, "House J", 3, 2, "Burwood", 430.0, 190.0, "Single Storey", 2010, 2, true, false, "East", "Well Maintained"},
    {995000, "House K", 5, 3, "Balwyn", 680.0, 320.0, "Double Storey", 2019, 3, true, true, "North", "Excellent"},
    {620000, "House L", 3, 2, "Oakleigh", 390.0, 165.0, "Townhouse", 2003, 2, false, false, "West", "Well Maintained"}};

static const string IMAGE_NAMES[TOTAL_HOUSES] = {
    "first", "second", "third", "fourth", "fifth", "sixth",
    "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth"};

void load_house_catalog(house_catalog &catalog)
{
    for (int i = 0; i < TOTAL_HOUSES; i++)
    {
        catalog.details[i] = HOUSE_DATA[i];
        catalog.images[i] = load_bitmap(IMAGE_NAMES[i] + "_house_image", IMAGE_NAMES[i] + "_house.jpg");
    }
    catalog.count = TOTAL_HOUSES;
}

void remove_house(house_catalog &catalog, int index)
{
    if (index < 0 || index >= catalog.count)
    {
        return;
    }
    for (int i = index; i < catalog.count - 1; i++)
    {
        catalog.details[i] = catalog.details[i + 1];
        catalog.images[i] = catalog.images[i + 1];
    }
    catalog.count--;
}

string house_summary(const house_detail &house)
{
    return house.house_name + " - " + to_string(house.bathrooms) + " bathrooms - " +
           to_string(house.bedrooms) + " bedrooms - " + house.location;
}

string house_full_description(const house_detail &house)
{
    return "This " + house.house_type + " home in " + house.location + " features " +
           to_string(house.bedrooms) + " spacious bedrooms and " +
           to_string(house.bathrooms) + " bathrooms, set on a generous " +
           to_string((int)house.land_size) + "m² block with a " +
           to_string((int)house.floor_area) + "m² floor plan. Built in " +
           to_string(house.year_built) + " and " + to_lowercase(house.condition) + ", this " +
           house.orientation + "-facing property comes with " +
           to_string(house.garage_spaces) + "-car garage space.";
}
