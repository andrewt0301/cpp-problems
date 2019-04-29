//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "../Time.h"

#include "Multiplicator.h"
#include "Number.h"
#include "../Random.h"

using IntVector = std::vector<int>;

using Sample = IntVector;

void generateCsv(const std::vector<Sample>& samples)
{
    std::ofstream out{"test.csv", std::ofstream::out};

    for (const Sample& sample : samples)
    {
        std::copy(sample.cbegin(), sample.cend(), std::ostream_iterator<int>(out, ";"));
        out << std::endl;
    }

    out.close();
}

int main()
{

    std::vector<Sample> samples;

    samples.push_back({1, 2, 3});
    samples.push_back({2, 4, 5});
    samples.push_back({3, 6, 7});

    generateCsv(samples);

    return 0;
}