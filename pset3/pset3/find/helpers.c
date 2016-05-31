/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

#include <stdlib.h> 
// it's already included in cs50.h, but to maintain consistency
// we also include it here (to no effect).

/**
 * Returns true if value is in array of n values, else false.
 * 
 * Algorithm: Binary search. Non-recursive implementation.
 * 
 */
bool search(int value, int values[], int n)
{
    if (values == NULL) {
        return false;
    }
    if (n <= 0) {
        return false;
    }
    int lo  = 0;
    int hi  = n;
    int mid = (lo + hi) / 2;
    while (lo <= hi) {
        if (value > values[mid]) {
            lo = mid + 1;
        } else if (value < values[mid]) {
            hi = mid - 1;
        } else {
            return true;
        }
        mid = (lo + hi) / 2;
    }
    return false;
}

/**
 * Sorts array of n values.
 * 
 * Warning: time complexity O(n^2) !!!
 * 
 * Algorithm: Shell sort.
 *
 * Uses Sedgewick's implementation to calculate steps 
 * but in no way are we copying the code. This code
 * was written from memory and memory only!
 * 
 * Feedback requested if possible.
 * Thank you.
 */
void sort(int values[], int n)
{
    if (values == NULL) {
        return;
    }
    
    int h = 0;
    int multiplier = 3;
    while (n / multiplier > h) {
        h = multiplier * h + 1;
    }
    
	while (h > 0) {
	    
		for (int i = h; i < n; i += h) {
			for (int j = i; j - h >= 0 && values[j] < values[j - h]; j -= h) {
				int temp      = values[j];
				values[j]     = values[j - h];
				values[j - h] = temp;
			}			
		}
		
		h /= multiplier;
	}
}