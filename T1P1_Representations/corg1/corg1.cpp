#include <iostream>
#include <limits>
#include "corg1.h"

using namespace std;

/*
*   Функция для ввода данных в терминал
*   При вызове функции нужно указать получаемые данные в скобках, т.е. readValue<int>() - получить число
*/
template <typename T>
T readValue() {
    T value{};
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cout << "\nIncorrect input. Enter new value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int main()
{
    while (true) {
        system("cls");
        cout <<
            "Choose a category from below:\n"
            "0. Exit\n"
            "1. 'long' Representation\n"
            "2. 'double' Representation\n\n";
        cout << "Type a number to continue: ";
        int choice = readValue<int>();
        system("cls");
        switch (choice) {
        case 0:
            return 0;
        case 1:
            longTask();
            break;
        case 2:
            doubleTask();
            break;
        default:
            cout << "\nCategory with number " << choice << " does not exist." << endl;
        }
        system("pause");
    }
}

void printLong(long number) {
    unsigned int order = sizeof(number) * 8;
    unsigned long mask = 1ul << (order - 1);

    cout << "\x1B[33m"; // Bit Sign
    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(number & mask);
        mask >>= 1;
        if (bit == 1)
            cout << "\x1B[32m "; // Other Bits
        else if (bit % 8 == 0)
            cout << ' ';
    }
    cout << "\x1B[0m"; // Reset colors
}

void varyLong(long& number, char side, int amount, int begin, int length) {
    amount = amount % length;
    unsigned long mask = (~0ul >> begin) ^ (~0ul >> (begin + length)); // Mask to make row of ones in specified sector
    long n = number & mask;
    printLong(mask);
    cout << "Shift mask" << endl;
    if (side == 'r') // Cycling Shift
        n = (n >> amount) | (n << (length - amount)); 
    else
        n = (n << amount) | (n >> (length - amount));
    number = (number & ~mask) | (n & mask); // Applying changes
}

void longTask() {
    long number = 0;
    cout << "Input an integer: ";
    number = readValue<int>();

    printLong(number);
    cout << "(" << number << ")" << endl;

    while (true) {
        char side;
        int amount;
        int begin;
        int length;
        do {
            cout << "Enter shift side, (l)eft, (r)ight or (n)one: ";
            side = readValue<char>();
        } while (side != 'l' && side != 'r' && side != 'n');
        if (side == 'n') return;
        do {
            cout << "Enter shift amount (0 to cancel): ";
            amount = readValue<int>();
        } while (amount < 0);
        if (amount == 0) return;
        do {
            cout << "Enter segment begin (0 to cancel): ";
            begin = readValue<int>();
        } while (begin < 0);
        if (begin == 0) return;
        do {
            cout << "Enter segment length (0 to cancel): ";
            length = readValue<int>();
        } while (length < 0);
        if (length == 0) return;
        varyLong(number, side, amount, begin, length);
        printLong(number);
        cout << "(" << number << ")" << endl;
    }
}

void printDouble(long long number) {
    unsigned int order = sizeof(number) * 8;
    unsigned long long mask = 1ull << (order - 1);

    cout << "\x1B[33m"; // Bit Sign
    for (unsigned int bit = 1; bit <= order; bit++) {
        cout << (bool)(number & mask);
        mask >>= 1;
        if (bit == 1)
            cout << "\x1B[36m "; // Mantissa
        if (bit == 12)
            cout << "\x1B[32m "; // Exponent
    }
    cout << "\x1B[0m "; // Reset colors
}

void varyDouble(unsigned long long& number, char side, int amount, int begin, int length) {
    amount = amount % length;
    unsigned long long mask = (~0ull >> begin) ^ (~0ull >> (begin + length)); // Mask to make row of ones in specified sector
    long long n = number & mask;
    printDouble(mask);
    cout << "Shift mask" << endl;
    if (side == 'r') // Cycling Shift
        n = (n >> amount) | (n << (length - amount)); 
    else
        n = (n << amount) | (n >> (length - amount));
    number = (number & ~mask) | (n & mask); // Applying changes
}

void doubleTask() {
    union {
        double number = 0.0;
        unsigned long long repr;
    };

    cout << "Input a double: ";
    number = readValue<double>();

    printDouble(repr);
    cout << " (" << number << ")" << endl;

    while (true) {
        char side;
        int amount;
        int begin;
        int length;
        do {
            cout << "Enter shift side, (l)eft, (r)ight or (n)one: ";
            side = readValue<char>();
        } while (side != 'l' && side != 'r' && side != 'n');
        if (side == 'n') return;
        do {
            cout << "Enter shift amount (0 to cancel): ";
            amount = readValue<int>();
        } while (amount < 0);
        if (amount == 0) return;
        do {
            cout << "Enter segment begin (0 to cancel): ";
            begin = readValue<int>();
        } while (begin < 0);
        if (begin == 0) return;
        do {
            cout << "Enter segment length (0 to cancel): ";
            length = readValue<int>();
        } while (length < 0);
        if (length == 0) return;
        varyDouble(repr, side, amount, begin, length);
        printDouble(repr);
        cout << "(" << number << ")" << endl;
    }
}
