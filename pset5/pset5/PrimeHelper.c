#include "PrimeHelper.h"

#include <limits.h>
#include <math.h>

/*

PrimeHelper provides services to work with primes. For this project, it serves as a helper class to the HashSet.

WORD OF NOTICE! Please note that this code has been ported/adapted from the .NET Framework library, in particular
the resource that you can find at the following link:

	http://referencesource.microsoft.com/#mscorlib/system/collections/hashtable.cs

I take no credit for the code below as if it was largely a port and maybe a couple of tweaks I did from 
the .NET Framework library.

Thank you.

*/


// 2 is a prime but it has been omitted. This is intentional since we don't want our hash table
// to resize so often due to expensive hashing.
const int PRIME_ARRAY[PRIME_ARRAY_LENGTH_INT] = {
	3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
	1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
	17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
	187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
	1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369
};

int isPrime(int candidate) {
	if ((candidate & 1) != 0) 
	{
		int lim = (int)sqrt(candidate);
		for (int div = 3; div <= lim; div += 2) 
		{
			if ((candidate % div) == 0) {
				return 0;
			}
		}
		return 1;
	}
	return (candidate == 2);
}

int getMinPrime(void) {
	return PRIME_ARRAY[0];
}

int getPrime(int min) {
	int minPrime = getMinPrime();

	if (min <= minPrime) {
		return minPrime;
	}

	// NOTE TO SELF: consider moving the for loop below to a bsearch algorithm
	/*for (int i = 0; i < PRIME_ARRAY_LENGTH_INT; i++) {
		int prime = PRIME_ARRAY[i];
		if (prime >= min) {
			return prime;
		}
	}*/

	int lo  = 0;
	int hi  = PRIME_ARRAY_LENGTH_INT;
	int mid = (lo + hi) / 2;
	while (lo < hi) {
		if (min > PRIME_ARRAY[mid]) {
			lo = mid + 1;
		} else if (min < PRIME_ARRAY[mid]) {
			hi = mid - 1;
		} else {
			return PRIME_ARRAY[mid];
		}
		mid = (lo + hi) / 2;
	}
 
	// outside of our predefined table. 
	// compute the hard way.
	min = (mid < (PRIME_ARRAY_LENGTH_INT - 1)) ? PRIME_ARRAY[mid + 1] : PRIME_ARRAY[mid];

	// guaranteed not to overflow since min is converted to an odd
	// number, odd + even == odd, and INT_MAX is an odd_number
	for (int i = (min | 1); i < INT_MAX; i += 2) {
		if (isPrime(i)) {
			return i;
		}
	}
	return MAX_VALID_PRIME_NUMBER_INT;
}

int expandPrime(int oldPrime) {
	int expandedValue = 2 * oldPrime;
	if (( (unsigned)expandedValue > MAX_VALID_PRIME_NUMBER_INT) && (MAX_VALID_PRIME_NUMBER_INT > oldPrime)) {
		return MAX_VALID_PRIME_NUMBER_INT;
	}
	return getPrime(expandedValue);
}