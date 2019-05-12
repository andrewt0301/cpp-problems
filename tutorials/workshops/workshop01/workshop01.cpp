//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "../Random.h"
#include "../Time.h"

#include "Number.h"
#include "NumberTests.h"

#include "Multiplicator.h"
#include "MultiplicatorTests.h"

using std::cout;
using std::endl;

int main()
{
    runNumberTests();
    runMultiplicatorTests();

    Number x{"6666"};
    Number y{"6666"};

    cout << Multiplicator::karatsuba(x,y) << endl;

    return 0;
}
