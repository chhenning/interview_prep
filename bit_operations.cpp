#include <boost/test/unit_test.hpp>


//////////////////////////
// XOR
//////////////////////////

// 0 ^ 0 -> 0
// 1 ^ 0 -> 1
// 0 ^ 1 -> 1
// 1 ^ 1 -> 0

// some xor magic. Swapping without a temp variable.
// e.g a = 255 -- 1111 1111
// e.g b =  56 -- 0011 1000
// first assignment: 
//      1111 1111
//      0011 1000
//      ---------
//      1100 0111
//
// second assignment: 
//      1100 0111
//      0011 1000
//      ---------
//      1111 1111 --> b == a
//
// second assignment: 
//      1100 0111
//      1111 1111
//      ---------
//      0011 1000 --> a == b
void swap( unsigned char& a, unsigned char& b )
{
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

BOOST_AUTO_TEST_CASE( bit_operations )
{
    // xor sample
    unsigned char a = 255;
    unsigned char b = 56;

    swap( a, b );

    // extracting green values from argb value
    unsigned int color = 0xAABBCCDD;
    unsigned int green_filter = 0x0000FF00;
    unsigned char green = ( color & green_filter ) >> 8;

    assert( green == 0xCC );

    // clearing red channel in argb
    color = 0xAABBCCDD;
    unsigned int no_red = color & 0xFF00FFFF;
    unsigned int color_without_red = color & no_red;

    assert( color_without_red == 0xAA00CCDD );

    // adding red channel in argb
    color = 0xAA00CCDD;
    unsigned char r = 0xFF;
    unsigned int red = r << 16;

    color |= red;
    assert( color == 0xAAFFCCDD );
}
