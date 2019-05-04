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

#include "Multiplicator.h"
#include "Number.h"

int main()
{

    Number n{3,2,3};
    Number n1{9,1};

    std::cout << n << std::endl;
    std::cout << n1 << std::endl;

    n += n1;

    std::cout << n << std::endl;
    std::cout << n + n << std::endl;

    return 0;
}
