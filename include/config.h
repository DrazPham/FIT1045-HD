#pragma once

#include <string>

const int TOTAL_HOUSES = 12;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int INFO_WINDOW_WIDTH = 700;
const int INFO_WINDOW_HEIGHT = 600;
const int AUCTION_SECONDS = 30;
const int EXTRA_TIME_SECONDS = 15;
const int EXTRA_TIME_THRESHOLD = 15;
const int PLAYERS_TO_MATCH = 2;
const double HOUSE_IMAGE_WIDTH = 400;
const double HOUSE_IMAGE_HEIGHT = 300;
const int SERVER_PORT = 6000;

inline const std::string SERVER_IP = "127.0.0.1";
inline const std::string CLIENT_NAME = "client1";
inline const std::string MAIN_WINDOW_TITLE = "HOUSEMATCH";
inline const std::string INFO_WINDOW_TITLE = "HOUSE INFORMATION";
inline const std::string FONT_NAME = "input";
inline const std::string FONT_FILE = "arial.ttf";

inline const std::string TEXT_HEADER = "HouseMatch";
inline const std::string TEXT_TITLE = "Swipe. Match. Win.";
inline const std::string TEXT_TAG_LINE = "Find a house you love, get matched with another buyer, and settle it with a live bid.";
inline const std::string TEXT_FOOTER = "A real-time house-buying game";
inline const std::string TEXT_WAITING = "Waiting for match";
inline const std::string TEXT_DASHBOARD = "HOUSEMATCH - DASHBOARD";
inline const std::string TEXT_HOUSE_OWNED = "HOUSE OWNED:";
inline const std::string TEXT_HOUSE_AVAILABLE = "HOUSE AVAILABLE:";
inline const std::string TEXT_HOUSE_TOTAL = "HOUSE TOTAL:";
inline const std::string TEXT_HOUSE_UNSOLD = "HOUSE UNSOLD:";
inline const std::string TEXT_HOUSE_SOLD = "HOUSE SOLD:";
