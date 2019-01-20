/*! \file       types.cpp
 *  \author     Andrei Tatarnikov
 *  \version    0.1
 *  \date       15.01.2019
 *
 *  This examples demonstrates how to work with built-in types of C++.
 */

// Printing facilities.
#include <iostream>

// Type limits.
#include <climits>

using std::cout;
using std::endl;

/**
 * Forward declarations of functions called from the 'main' function.
 * Needed because C++ does not see functions if they are defined below the point where they are called.
 */
void booleanDemo();
void characterDemo();
void wideCharacterDemo();
void integerDemo();
void floatingPointDemo();

/**
 * Demonstrates the use of built-in types of C++.
 * Types in C++ are machine-dependent: their size may be different on different machines.
 */
int main()
{
    // Here we run demos for specific data types.
    booleanDemo();
    characterDemo();
    wideCharacterDemo();
    integerDemo();
    floatingPointDemo();

    return 0;
}

/**
 * Demonstrates the use of the boolean type in C++.
 */
void booleanDemo()
{
    cout << "*****   Boolean demo  *****" << endl;

    // Boolean variables may be 'true' or 'false'.
    // Under the hood, 'false' is encoded as 0 and 'true' is an any non-zero value.

    // Proper way to give values to boolean variable.
    bool var01 = true;
    bool var02 = false;

    // Not a good way to give values to boolean variables.
    bool var03 = -1;
    bool var04 = 0;

    // Normally, boolean values have size of 1 byte.
    cout << "sizeof(bool) = " << sizeof(bool) << endl;

    // By default, boolean values are printed as integers.
    cout << "bool values (as ints):  ";
    cout << var01 << ", " << var02 << ", " << var03 << ", " << var04 << endl;

    // However, it is possible to print them as keywords:
    cout << std::boolalpha;
    cout << "bool values (as words): ";
    cout << var01 << ", " << var02 << ", " << var03 << ", " << var04 << endl;
}


/**
 * Demonstrates the use of the 'char' data type in C++.
 */
void characterDemo()
{
    cout << "*****  Character demo *****" << endl;

    // The 'char' type is used to store ASCII characters.
    // It has a size of 1 byte and encodes ASCII characters with values from 0 to 255.
    cout << "sizeof(char) = " << sizeof(char) << endl;

    // 'char' variables can be assigned character values.
    char var01 = 'A';

    // Also, they can be assigned integer values.
    char var02 = 65; // 'A' has the ASCII code of 65.

    // Or hexadecimal integer.
    char var03 = 0x41; // 65 in hex.

    // Character values are printed as letters.
    cout << "char values: ";
    cout << var01 << ", " << var02 << ", " << var03 << endl;
}

/**
 * Demonstrates the use of the 'wchar_t' data type in C++.
 */
void wideCharacterDemo()
{
    cout << "*** Wide character demo ***" << endl;

    // The 'wchar_t' type is used to store UNICODE characters.
    // Therefore, it has larger size than 'char':
    cout << "sizeof(wchar_t) = " << sizeof(wchar_t) << endl;

    // UNICODE values must have prefix 'L'.
    wchar_t var01 = L'Щ';

    // Wide characters are printed as integer values:
    cout << "wchar_t values: ";
    cout << var01 << endl;

    // To print them as character, a stream with UNICODE support is needed:
    std::wcout << L"wchar_t values: ";
    std::wcout << var01 << endl;

    cout << endl;
}


/**
 * Demonstrates the use of the integer data types in C++.
 */
void integerDemo()
{
    cout << "****** Integer demo ******" << endl;

    // C++ supports several integer types that have different size.
    // They are machine-dependent and their size depends in the machine.

    // Commonly, 16 bits.
    cout << "sizeof(short)     = " << sizeof(short) << endl;
    // Commonly, 32 bits.
    cout << "sizeof(int)       = " << sizeof(int) << endl;
    // Commonly, 32 or 64 bits.
    cout << "sizeof(long)      = " << sizeof(long) << endl;
    // Commonly, 64 bits.
    cout << "sizeof(long long) = " << sizeof(long long) << endl;

    // Limits on integer values are provided in the 'climits' library file.
    cout << "short     range: ["  << SHRT_MIN << ", " << SHRT_MAX << "]" << endl;
    cout << "int       range: ["  << INT_MIN  << ", " << INT_MAX << "]" << endl;
    cout << "long      range: ["  << LONG_MIN << ", " << LONG_MAX << "]" << endl;
    cout << "long long range: ["  << LONG_LONG_MIN << ", " << LONG_LONG_MAX << "]" << endl;

    // Integer values can be signed or unsigned (in the latter case they are prefixed with
    // 'unsigned'). Unsigned values have different limits:
    cout << "unsigned short     range: ["  << 0 << ", " << USHRT_MAX << "]" << endl;
    cout << "unsigned int       range: ["  << 0 << ", " << UINT_MAX << "]" << endl;
    cout << "unsigned long      range: ["  << 0 << ", " << ULONG_MAX << "]" << endl;
    cout << "unsigned long long range: ["  << 0 << ", " << ULONG_LONG_MAX << "]" << endl;

    // Integer values can be initialized with decimal constants:
    short     var01 = -123;
    int       var02 = -234;
    long      var03 = -345;
    long long var04 = -456;

    cout << "Signed integer values: ";
    cout << var01 << ", " << var02 << ", " << var03 << ", " << var04 << endl;

    // Signed values are automatically converted when assigned to unsigned variables:
    unsigned short     var05 = -123;
    unsigned int       var06 = -234;
    unsigned long      var07 = -345;
    unsigned long long var08 = -456;

    cout << "Unsigned integer values: ";
    cout << var05 << ", " << var06 << ", " << var07 << ", " << var08 << endl;

    // Integer variables can be initialized with hexadecimal constants:
    short     var09 = 0xDEAF;
    int       var10 = 0xCAFEBABE;
    long long var11 = 0xDEADBEEFBAADF00D;

    // By default, all integer values are printed in the decimal format:
    cout << "Integer values (dec): ";
    cout << var09 << ", " << var10 << ", " << var11 << endl;
    // To print them in hexadecimal, the std::hex marker needs to be used:
    cout << "Integer values (hex): " << std::hex;
    cout << var09 << ", " << var10 << ", " << var11 << endl;

}


/**
 * Demonstrates the use of the floating-point data types in C++.
 */
void floatingPointDemo()
{
    // TODO
}
