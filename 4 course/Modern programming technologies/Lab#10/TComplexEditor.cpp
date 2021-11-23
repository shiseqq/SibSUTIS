#include "TComplexEditor.h"

const string TComplexEditor::imPart = "+i*";

TComplexEditor::TComplexEditor() : StrComplex("0"), currentPart(ComplexPart::Re) {}

bool TComplexEditor::isZero() {
    return StrComplex == "0";
}

string TComplexEditor::addSign() {
    if (currentPart == ComplexPart::Re) {
        if (StrComplex[0] == '-')
            StrComplex.erase(StrComplex.begin());
        else if (StrComplex[0] != '0')
            StrComplex = '-' + StrComplex;
    }
    else {
        auto pos = StrComplex.find('i');
        if (StrComplex[pos - 1] == '-')
            StrComplex[pos - 1] = '+';
        else
            StrComplex[pos - 1] = '-';
    }
    return StrComplex;
}

string TComplexEditor::addNumber(int a) {
    if (currentPart == ComplexPart::Im)
        StrComplex += to_string(a);
    else {
        auto pos = StrComplex.find('i');
        if (StrComplex[0] == '0')
            StrComplex.replace(0, 1, to_string(a));
        else if (pos != -1)
            StrComplex.insert(pos - 1, to_string(a));
        else if (StrComplex[0] == '-')
            StrComplex.insert(1, to_string(a));
        else
            StrComplex += to_string(a);
    }
    return StrComplex;
}

string TComplexEditor::addZero() {
    return addNumber(0);

}

string TComplexEditor::addIm() {
    if (StrComplex.find(imPart) == -1) {
        StrComplex = StrComplex + imPart;
        currentPart = ComplexPart::Im;
    }
    else {
        throw logic_error("Complex number already has a image part");
    }
    return StrComplex;
}

string TComplexEditor::removeLastDigit() {
    StrComplex.pop_back();
    if (currentPart == ComplexPart::Re) {
        if (StrComplex == "-" || StrComplex.empty())
            StrComplex = "0";
    }
    else {
        if (StrComplex[StrComplex.length() - 1] == '*') {
            StrComplex.erase(StrComplex.end() - 3, StrComplex.end());
            currentPart = ComplexPart::Re;
        }
        else if (StrComplex.find('i'))
            StrComplex.back();
    }
    return StrComplex;
}

string TComplexEditor::clear() {
    currentPart = ComplexPart::Re;
    return StrComplex = "0";
}

void TComplexEditor::editComplex(ComplexOperations operation) {
    switch (operation) {
    case ComplexOperations::ADD_SIGN:
        addSign();
        break;
    case ComplexOperations::ADD_DIGIT:
        int num;
        cout << "Enter number to add: ";
        cin >> num;
        addNumber(num);
        break;
    case ComplexOperations::ADD_ZERO:
        addZero();
        break;
    case ComplexOperations::ADD_IM:
        addIm();
        break;
    case ComplexOperations::REMOVE_LAST_DIGIT:
        removeLastDigit();
        break;
    case ComplexOperations::CLEAR:
        clear();
        break;
    default:
        break;
    }
}

string TComplexEditor::getComplexString() {
    return StrComplex;
}

bool TComplexEditor::isValid(string str) {
    bool res = false;
    if (!str.empty() && (str.find("+i*") != string::npos || str.find("-i*") != string::npos)) {
        auto pos = str.find('i');
        string tempRe = str;
        string tempIm = str;
        string rePart = tempRe.erase(pos - 1, str.length());
        string imPart = tempIm.erase(0, pos + 2);

        int digitCount = 0;
        for (auto i : rePart) {
            if (isdigit(i))
                digitCount++;
        }
        for (auto i : imPart) {
            if (isdigit(i))
                digitCount++;
        }

        if (digitCount) {
            if (str[0] == '-') {
                if (digitCount == str.length() - 4)
                    res = true;
            }
            else {
                if (digitCount == str.length() - 3)
                    res = true;
            }
        }
    }
    return res;
}

string TComplexEditor::setComplexString(string str) {
    if (isValid(str))
        StrComplex = str;
    else
        throw invalid_argument("Wrong complex number!");
    return string();
}
