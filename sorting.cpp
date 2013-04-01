#include <boost/test/unit_test.hpp>

#include <iostream>
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

////////////////////////////////
// Bubble Sort
////////////////////////////////

// Average case performance: O( n^2 )
void bubble_sort( vector<int>& v )
{
    if( v.size() == 0 )
        return;

    bool swap = false;

    do 
    {
        swap = false;

        for( std::size_t i = 0; i < v.size() - 1; ++i )
        {
            if( v[i] > v[i+1] )
            {
                int t  = v[i];
                v[i]   = v[i+1];
                v[i+1] = t;

                swap = true;
            }
        }
    }
    while( swap == true );
}

////////////////////////////////
// median sort
////////////////////////////////

void swap( vector<int>& v, int i, int j )
{
    int t = v[i];
    v[i] = v[j];
    v[j] = t;
}

// when this function finishes all elements left to pivor_index are smaller
// then pivot. But they are not ordered!
// Right to pivot index are all elements that are larger then the pivot.
// e.g.
int partition( vector<int>& v, int left, int right, int pivot_index )
{
    assert( pivot_index <= right );
    assert( pivot_index >= left );

    int pivot = v[pivot_index];

    // move pivot to end of array
    swap( v, right, pivot_index );

    int store = left;

    for( int i = left; i < right; ++i )
    {
        if( v[i] <= pivot )
        {
            swap( v, i, store );

            ++store;
        }
    }

    swap( v, right, store );

    return store;
}

int select_kth( vector<int>& v, int k, int left, int right )
{
    int pivot_index = 0;

    if( left < right )
    {
        // choose a random index between left and right.
        pivot_index = partition( v, left, right
                                , left + rand() % ( right - left )); 
    }
    else
    {
        pivot_index = right;
    }

    if( left + k - 1 == pivot_index )
    {
        return pivot_index;
    }

    if( left + k - 1 < pivot_index )
    {
        return select_kth( v, k, left, pivot_index - 1 );
    }
    else
    {
        return select_kth( v, k - ( pivot_index - left + 1 ), pivot_index + 1, right );
    }

    return 0;
}

// The median sort algorithm only does sorting in partition function.
// Average performance: O( n log n )
void median_sort( vector<int>& v, int left, int right )
{
    if( right <= left )
        return;

    int mid = ( right - left + 1 ) / 2;
    int median = select_kth( v, mid + 1, left, right );

    median_sort( v,           left, left + mid - 1 );
    median_sort( v, left + mid + 1,          right );
}

BOOST_AUTO_TEST_CASE( sorting )
{
    // Bubble Sort
    {
        vector<int> v;
        generate_n( back_inserter( v ), 10, [&] () { return rand() % 100; } );

        bubble_sort( v );
    }

    // Median Sort
    {
        vector<int> v;
        generate_n( back_inserter( v ), 10, [&] () { return rand() % 100; } );

        median_sort( v, 0, v.size() - 1 );
    }

    // Another very simple and bad algorithm would be to:
    // 1. Create a binary tree ( which could be very unbalanced )
    // 2. Override the elements by traversing inorder through the tree.
}
