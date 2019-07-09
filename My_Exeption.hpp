#ifndef OBJECT_DETECTION_MY_EXEPTION_HPP
#define OBJECT_DETECTION_MY_EXEPTION_HPP

#include <iostream>

using namespace std;

/// small class of Exception in using Picture class
class My_Exeption{
private:
    string message;
public:
    explicit My_Exeption(string message);

    void throw_it();
};

#endif //OBJECT_DETECTION_MY_EXEPTION_HPP