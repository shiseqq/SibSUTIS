#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <exception>

using namespace std;

enum class ComplexOperations {
    ADD_SIGN,
    ADD_DIGIT,
    ADD_ZERO,
    ADD_IM,
    REMOVE_LAST_DIGIT,
    CLEAR
};

enum class ComplexPart {
    Re,
    Im
};

class TComplexEditor {
private:
    string StrComplex;
    ComplexPart currentPart;
public:
    static const string imPart;

    TComplexEditor();
    bool isZero();
    string addSign();
    string addNumber(int a);
    string addZero();
    string addIm();
    string removeLastDigit();
    string clear();
    void editComplex(ComplexOperations operation);
    string getComplexString();
    string setComplexString(std::string str);
    bool isValid(std::string);
};