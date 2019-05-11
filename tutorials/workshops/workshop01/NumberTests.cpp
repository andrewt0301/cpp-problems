//
// Created by Andrei Tatarnikov on 2019-05-10.
//

#include "Number.h"

#include <cassert>

/**
 * Checks whether this constructor works:
 *
 * Number(const std::initializer_list<Digit>& digits).
 */
void testConstructInit()
{
    assert((Number{1,0,0})   == (Number{1,0,0}));
    assert((Number{0,1,0,0}) == (Number{1,0,0}));
    assert((Number{0,0,1})   == (Number{1}));
    assert((Number{0,0,0})   == (Number{0}));
    assert((Number{0,0,0})   == (Number{}));
}

/**
 * Checks whether this constructor works:
 *
 * Number(Digits digits, bool negative).
 */
void testConstructVec()
{
    assert((Number{Number::Digits{1,0,0},   false}) == (Number{1}));
    assert((Number{Number::Digits{1,0,0},    true}) == (-Number{1}));

    assert((Number{Number::Digits{0,1,0,0}, false}) == (Number{1,0}));
    assert((Number{Number::Digits{0,1,0,0},  true}) == (-Number{1,0}));

    assert((Number{Number::Digits{0,0,1},   false}) == (Number{1,0,0}));
    assert((Number{Number::Digits{0,0,0},   false}) == (Number{}));
    assert((Number{Number::Digits{0,0,0},    true}) == (Number{}));
}

/**
 * Checks whether this constructor works:
 *
 * Number(const std::string &str).
 */
void testConstructString()
{
    assert(( Number{"001"})  == (Number{1}));
    assert((Number{"-001"})  == (-Number{1}));

    assert((Number{"0010"})  == (Number{1,0}));
    assert((Number{"-0010"}) == (-Number{1,0}));

    assert( (Number{"100"})  == (Number{1,0,0}));
    assert((Number{"-000"})  == (Number{}));
    assert((Number{"-000"})  == (Number{}));
}

/**
 * Tests whether this operation works:
 *
 * Number operator-() const;
 */
void testNegate()
{
    assert((   Number{1,2,3}) == (Number{Number::Digits{3,2,1}, false}));
    assert((  -Number{1,2,3}) == (Number{Number::Digits{3,2,1}, true}));
    assert((- -Number{1,2,3}) == (Number{Number::Digits{3,2,1}, false}));
    assert((  -Number{0,0,0}) == (Number{Number::Digits{},      false}));
    assert((   Number{0,0,0}) == (Number{Number::Digits{},      false}));
}

/**
 * Tests whether this method works:
 *
 * std::pair<Number, Number> split() const;
 */
void testSplit()
{
    assert((   Number{1,2,3,4}.split())   == (std::make_pair( Number{1,2},  Number{3,4})));
    assert(((-Number{1,2,3,4}).split())   == (std::make_pair(-Number{1,2}, -Number{3,4})));

    assert((   Number{1,2,3,4,5}.split()) == (std::make_pair( Number{1,2},  Number{3,4,5})));
    assert(((-Number{1,2,3,4,5}).split()) == (std::make_pair(-Number{1,2}, -Number{3,4,5})));

    assert((     Number{0,1,0,3}.split()) == (std::make_pair( Number{1},  Number{3})));
    assert(((-Number{0,1,0,0,0}).split()) == (std::make_pair(-Number{1,0},  Number{})));
}

/**
 * Tests whether these operators work:
 *
 * Number operator+(const Number& lhs, const Number& rhs)
 * Number operator-(const Number& lhs, const Number& rhs)
 */
void testAddSub()
{
    assert(( Number{1,0,0}) + (Number{9,9})   == ( Number{1,9,9}));
    assert(( Number{1,0,0}) - (Number{9,9})   == ( Number{1}));
    assert((-Number{1,0,0}) + (Number{9,9})   == (-Number{1}));
    assert((-Number{1,0,0}) - (Number{9,9})   == (-Number{1,9,9}));
    assert((   Number{9,9}) + (Number{1,0,0}) == ( Number{1,9,9}));
    assert(   (Number{9,9}) - (Number{1,0,0}) == (-Number{1}));
}

/**
 * Tests whether this operator work:
 *
 * Number operator*(const Number& lhs, const Number& rhs)
 */
void testMul()
{
    assert(( Number{1,2,3}) * ( Number{1,2}) == ( Number{1,4,7,6}));
    assert((-Number{1,2,3}) * ( Number{1,2}) == (-Number{1,4,7,6}));
    assert(( Number{1,2,3}) * (-Number{1,2}) == (-Number{1,4,7,6}));
    assert((-Number{1,2,3}) * (-Number{1,2}) == ( Number{1,4,7,6}));

    assert(( Number{1,2,3}) * ( Number{})       == ( Number{}));
    assert(( Number{})      * ( Number{1,2,3})  == ( Number{}));
    assert(( Number{2,0,0}) * ( Number{3,0})    == ( Number{6,0,0,0}));

    assert(( Number{9,9})     * ( Number{9,9})   == ( Number{9,8,0,1}));
    assert(( Number{9,9,9,9}) * ( Number{7,7,7}) == ( Number{7,7,6,9,2,2,3}));
}

/**
 * Checks the correctness of the Number implementation.
 */
void runNumberTests()
{
    testConstructInit();
    testConstructVec();
    testConstructString();
    testNegate();
    testSplit();
    testAddSub();
    testMul();
}
