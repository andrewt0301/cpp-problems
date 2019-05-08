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

    std::cout << -n << std::endl;
    std::cout << Number{0,0,0} << std::endl;


    Number x{9,1};
    Number mx = -x;

    x  += Number{1};
    mx += Number{1};

    std::cout <<  x << std::endl;
    std::cout << mx << std::endl;

    return 0;
}
