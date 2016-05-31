#ifndef _PRIMEHELPER_H_
#define _PRIMEHELPER_H_

/*

PrimeHelper provides services to work with primes. For this project, it serves as a helper class to the HashSet.

WORD OF NOTICE! Please note that this code has been ported/adapted from the .NET Framework library, in particular
the resource that you can find at the following link:

	http://referencesource.microsoft.com/#mscorlib/system/collections/hashtable.cs

I take no credit for the code below as if it was largely a port and maybe a couple of tweaks I did from 
the .NET Framework library.

Thank you.

*/

#define MAX_VALID_PRIME_NUMBER_INT	0x7FEFFFFD
#define PRIME_ARRAY_LENGTH_INT		72

int isPrime(int candidate);

int getMinPrime(void);

int getPrime(int min);

int expandPrime(int oldPrime);

#endif