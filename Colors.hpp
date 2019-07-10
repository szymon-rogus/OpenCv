#ifndef OBJECT_DETECTION_COLORS_HPP
#define OBJECT_DETECTION_COLORS_HPP

/// enum of color range in hsv
enum colors {
    ORANGE_MIN = 11, ORANGE_MAX = 24,
    YELLOW_MIN = 25, YELLOW_MAX = 30,
    GREEN_MIN = 31, GREEN_MAX = 75,
    SEA_MIN = 76, SEA_MAX = 89,
    BLUE_MIN = 90, BLUE_MAX = 130,
    PURPLE_MIN = 129, PURPLE_MAX = 145,
    PINK_MIN = 146, PINK_MAX = 165,
    RED_MIN = 166, RED_MAX = 179,
    RED_MIN_2 = 1, RED_MAX_2 = 10
};

/// enum of colors in hsv
enum new_color {
    RED = 1,
    ORANGE = 10,
    YELLOW = 25,
    GREEN = 60,
    SEA = 80,
    BLUE = 105,
    PURPLE = 140,
    PINK = 170,
};

typedef struct Scale{
    int min_h;
    int max_h;
};

Scale convert_string_to_enum(const string &color);

int get_new_color(const string &color);

#endif //OBJECT_DETECTION_COLORS_HPP