//
// Created by Andrei Tatarnikov on 2019-05-12.
//

#include "MultiplicatorTests.h"

#include <cassert>

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

void runMultiplicatorTests()
{
    testFixedData([](const Number& lhs, const Number& rhs) {return Multiplicator::divideAndConquer(lhs, rhs);});
    testFixedData([](const Number& lhs, const Number& rhs) {return Multiplicator::karatsuba(lhs, rhs);});
}
