#include "My_Exeption.hpp"

My_Exeption::My_Exeption(string message) : message(message) {}

void My_Exeption::throw_it(){
    cout << endl << this -> message << endl;
    throw *this;
}