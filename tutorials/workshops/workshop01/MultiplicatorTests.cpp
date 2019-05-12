//
// Created by Andrei Tatarnikov on 2019-05-12.
//

#include "MultiplicatorTests.h"

#include <cassert>

#include "../Random.h"
#include "Multiplicator.h"

template <typename TMulOp>
void testFixedData(TMulOp mulOp)
{
    assert(mulOp(Number{1,0,0}, Number{1,0,0}) == ( Number{1,0,0,0,0}));
    assert(mulOp(Number{1,2,3}, Number{1,2})   == ( Number{1,4,7,6}));

    assert(mulOp(-Number{1,2,3},  Number{1,2}) == (-Number{1,4,7,6}));
    assert(mulOp( Number{1,2,3}, -Number{1,2}) == (-Number{1,4,7,6}));
    assert(mulOp(-Number{1,2,3}, -Number{1,2}) == ( Number{1,4,7,6}));

    assert(mulOp( Number{1,2,3},  Number{})       == ( Number{}));
    assert(mulOp( Number{},       Number{1,2,3})  == ( Number{}));
    assert(mulOp( Number{2,0,0},  Number{3,0})    == ( Number{6,0,0,0}));

    assert(mulOp( Number{9,9},     Number{9,9})   == ( Number{9,8,0,1}));
    assert(mulOp( Number{9,9,0},   Number{9,9})   == ( Number{9,8,0,1,0}));
    assert(mulOp( Number{9,9,9,9}, Number{7,7,7}) == ( Number{7,7,6,9,2,2,3}));
}

template <typename TMulOp>
void testRandomData(TMulOp mulOp)
{
    Random random{1};

    for (size_t lenLhs = 1; lenLhs <= 16; ++lenLhs)
    {
        for (size_t lenRhs = 1; lenRhs <= 16; ++lenRhs)
        {
            for (size_t count = 0; count < 10; ++count)
            {
                std::vector<int> lhsData = randomVector(random, lenLhs);
                std::vector<int> rhsData = randomVector(random, lenRhs);

                Number::Digits digitsLhs(lhsData.size());
                for (size_t i = 0; i < lhsData.size(); ++i)
                    digitsLhs[i] = lhsData[i];

                Number::Digits digitsRhs(rhsData.size());
                for (size_t i = 0; i < rhsData.size(); ++i)
                    digitsRhs[i] = rhsData[i];

                Number lhs{digitsLhs, random.next() % 2 == 0};
                Number rhs{digitsRhs, random.next() % 2 == 0};

                Number etalon = lhs * rhs;
                Number result = mulOp(lhs, rhs);

                assert(result == etalon);
            }
        }
    }
}

void runMultiplicatorTests()
{
    testFixedData([](const Number& lhs, const Number& rhs) {return Multiplicator::divideAndConquer(lhs, rhs);});
    testFixedData([](const Number& lhs, const Number& rhs) {return Multiplicator::karatsuba(lhs, rhs);});

    testRandomData([](const Number& lhs, const Number& rhs) {return Multiplicator::divideAndConquer(lhs, rhs);});
    testRandomData([](const Number& lhs, const Number& rhs) {return Multiplicator::karatsuba(lhs, rhs);});
}
