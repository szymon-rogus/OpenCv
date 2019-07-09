#include "My_Exeption.hpp"
#include "Colors.hpp"

int* convert_string_to_enum(const string &color){
    int *scale = new int[2];

    if(color == "red"){
        scale[0] = RED_MIN; scale[1] = RED_MAX;
    }
    else
    if(color == "orange"){
        scale[0] = ORANGE_MIN; scale[1] = ORANGE_MAX;
    }
    else
    if(color == "yellow"){
        scale[0] = YELLOW_MIN; scale[1] = YELLOW_MAX;
    }
    else
    if(color == "green"){
        scale[0] = GREEN_MIN; scale[1] = GREEN_MAX;
    }
    else
    if(color == "sea"){
        scale[0] = SEA_MIN; scale[1] = SEA_MAX;
    }
    else
    if(color == "blue"){
        scale[0] = BLUE_MIN; scale[1] = BLUE_MAX;
    }
    else
    if(color == "purple"){
        scale[0] = PURPLE_MIN; scale[1] = PURPLE_MAX;
    }
    else
    if(color == "pink"){
        scale[0] = PINK_MIN; scale[1] = PINK_MAX;
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