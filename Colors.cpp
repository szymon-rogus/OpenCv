#include "My_Exeption.hpp"
#include "Colors.hpp"

Scale convert_string_to_enum(const string &color){
    Scale scale;
    scale.min_h = 0;
    scale.max_h = 0;

    if(color == "red"){
        scale.min_h = RED_MIN; scale.max_h = RED_MAX;
    }
    else
    if(color == "orange"){
        scale.min_h = ORANGE_MIN; scale.max_h = ORANGE_MAX;
    }
    else
    if(color == "yellow"){
        scale.min_h = YELLOW_MIN; scale.max_h = YELLOW_MAX;
    }
    else
    if(color == "green"){
        scale.min_h = GREEN_MIN; scale.max_h = GREEN_MAX;
    }
    else
    if(color == "sea"){
        scale.min_h = SEA_MIN; scale.max_h = SEA_MAX;
    }
    else
    if(color == "blue"){
        scale.min_h = BLUE_MIN; scale.max_h = BLUE_MAX;
    }
    else
    if(color == "purple"){
        scale.min_h = PURPLE_MIN; scale.max_h = PURPLE_MAX;
    }
    else
    if(color == "pink"){
        scale.min_h = PINK_MIN; scale.min_h = PINK_MAX;
    }
    else{
        My_Exeption ex = My_Exeption("Unknown color!");
        ex.throw_it();
    }

    return scale;
}

int get_new_color(const string &color){

    if(color == "red")      return RED;
    else
    if(color == "orange")   return ORANGE;
    else
    if(color == "yellow")   return YELLOW;
    else
    if(color == "green")    return GREEN;
    else
    if(color == "sea")      return SEA;
    else
    if(color == "blue")     return BLUE;
    else
    if(color == "purple")   return PURPLE;
    else
    if(color == "pink")     return PINK;
    else{
        My_Exeption ex = My_Exeption("Unknown color!");
        ex.throw_it();
        return -1;
    }
}