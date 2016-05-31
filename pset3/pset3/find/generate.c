/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the user dares enter less than 1 or 2 command line args,
    // the program will notify the user with a help message and 
    // return an error code of 1 to the OS.
    // 
    // The reason it says 2 and 3 in the test, is because a C
    // program always implicitly has one argument which is the
    // command that called the program. It resides at argv[0].
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Converts the first command line argument to an integer.
    // This will serve as a number of pseudo-random numbers
    // the user intents on generating.
    //
    // Error checking is advised, since on failure the atoi
    // function returns 0, which is safe for this implementation,
    // however the program will just fail silently.
    int n = atoi(argv[1]);

    // If there exist two command line arguments specified by
    // the user, that means the user intents to use a seed,
    // which resides at argv[2].
    //
    // If not, the system time (time_t) is used as a seed 
    // value which is an 8 byte value.
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // n pseudo-random numbers are generated [0.0, LIMIT)
    // We multiply the return value of the drand48 function
    // by the limit to obtain the number within [0.0, LIMIT).
    // The reason it works is because the drand48 function
    // returns a floating point number (a double) from 0.0 
    // to 1.0 [0.0, 1.0)
    // The number is then sent to the standard output buffer
    // and output on the screen.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}