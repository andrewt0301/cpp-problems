//
// Created by Andrei Tatarnikov on 2019-04-14.
//

#ifndef TUTORIALS_RANDOM_H
#define TUTORIALS_RANDOM_H

#include <random>

<<<<<<< HEAD
class Random {
=======
class Random  {
>>>>>>> origin/master
private:
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis;;
public:
    explicit Random(int k);
    int next();
};

#endif //TUTORIALS_RANDOM_H
