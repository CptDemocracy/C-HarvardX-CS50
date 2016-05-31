#include <stdio.h>
#include "cs50.h"

#define OZ_PER_GAL_DOUBLE           128.0
#define GALS_PER_MIN_DOUBLE         1.5
#define OZ_IN_ONE_BOTTLE_DOUBLE     16.0


int GetPositiveInt(void) {
/**
 * -----------------/ Summary /-----------------
 * 
 * Gets a positive integer from user input. If a user fails
 * to provide one, he or she will be requested to enter it 
 * again until a positive integer has been entered by a user.
 * 
 * -----------------/ Arguments /-----------------
 * 
 *  None.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  None.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 *  The integer input by a user is returned.
 * 
 * -----------------/ Side-effects /-----------------
 * 
 *  Standard input buffer will be mutated and contain the 
 *  characters input by the user.  
 * 
 */
    int num;
    while ((num = GetInt()) < 0)
        ;
    return num;
}

int main(int argc, char** argv) {
/**
 * -----------------/ Summary /----------------------
 * 
 * Requests a user to enter the time in minutes it takes
 * him or her to shower. The program then converts the
 * amount of water expended into the number of 
 * OZ_IN_ONE_BOTTLE_DOUBLE ounce bottles.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  argc : int      - the number of arguments entered by a user.
 *                    Ignored for this program.
 * 
 *  argv : char**   - the array of commands entered by a user.
 *                    Ignored for this program.
 * 
 * -----------------/ Pre-condition /------------------
 * 
 *  None.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 *  The number of OZ_IN_ONE_BOTTLE_DOUBLE bottles is calculated 
 *  based on user input and output on the screen.
 * 
 * -----------------/ Side-effects /-------------------
 * 
 *  Standard input and output buffers will be mutated.
 *  
 * 
 */
 
    printf("For how long do you usually shower?\n");
    
    int mins = GetPositiveInt();
    printf("minutes: %i\n", mins);
    
    int bottles = 
        mins * GALS_PER_MIN_DOUBLE * OZ_PER_GAL_DOUBLE / OZ_IN_ONE_BOTTLE_DOUBLE;
    printf("bottles: %i\n", bottles);

    return 0;
}