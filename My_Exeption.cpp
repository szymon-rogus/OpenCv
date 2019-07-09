#include "My_Exeption.hpp"

My_Exeption::My_Exeption(string message) : message(message) {}

void My_Exeption::throw_it(){
    /// in case of exception show message and throw an instance of it
    cout << endl << this -> message << endl;
    throw message;
}