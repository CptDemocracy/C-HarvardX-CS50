#include <stdio.h>
#include "cs50.h"

#define PYRAMID_MIN_HEIGHT_INT      0
#define PYRAMID_MAX_HEIGHT_INT      23
#define DEFAULT_BLOCK_CHAR          '#'


void drawPyramid(char block, int height) {
/**
 * -----------------/ Summary /---------------------
 * 
 * Draws a pyramid using the standard output buffer of 
 * height specified by a user.
 * 
 * -----------------/ Arguments /-------------------
 * 
 *  block : char - the character a block should be 
 *                 represented with.
 *  
 *  height : int - the height of the pyramid to draw.
 * 
 * -----------------/ Pre-condition /----------------
 * 
 *  The height argument cannot be negative or else the 
 *  program will simply return. 
 * 
 * -----------------/ Post-condition /---------------
 * 
 *  The pyramid of requested height will be drawn using 
 *  the standard output buffer.
 * 
 * -----------------/ Side-effects /-----------------
 * 
 *  Standard output buffer will be mutated and contain 
 *  the characters representing the pyramid.
 * 
 */
    
    if (height < 0) {
        return;
    }
    
    int row, col, paddingIndex;
    for (row = 1; row <= height; ++row) {
        for (paddingIndex = 0; paddingIndex < height - row; ++paddingIndex) {
            printf(" ");
        }
        for (col = 0; col <= row; ++col) {
            printf("%c", block);
        }
        printf("\n");
    }
    
}

int main(int argc, char** argv) {
/**
 * -----------------/ Summary /---------------------
 * 
 * Prompts the user for input of a height of a pyramid
 * he intents to draw. On invalid input, the user is
 * prompted again. On valid output the pyramid of 
 * requested height is drawn using the standard output
 * buffer.
 * 
 * -----------------/ Arguments /-------------------
 * 
 *  argc : int      - contains the number of arguments passed.
 * 
 *  argv : char**   - contains the string of arguments to
 *                    the program.
 * 
 * -----------------/ Pre-condition /----------------
 * 
 *  None.
 * 
 * -----------------/ Post-condition /---------------
 * 
 *  The pyramid of requested height will be drawn using 
 *  the standard output buffer. A code of 0 is always
 *  guaranteed to be returned.
 * 
 * -----------------/ Side-effects /-----------------
 * 
 *  Standard output and input buffers will be mutated.
 * 
 */

    printf("Please input the height of the pyramid you'd like to draw (%i through %i): \n",
                PYRAMID_MIN_HEIGHT_INT,
                PYRAMID_MAX_HEIGHT_INT);
    
    int userInputHeight = GetInt();
    
    while ( !((userInputHeight <= PYRAMID_MAX_HEIGHT_INT) && (userInputHeight >= PYRAMID_MIN_HEIGHT_INT)) ) {
        
        printf("It looks like your input is not within limits. Please make sure you specify a value from %i through %i: \n",
                    PYRAMID_MIN_HEIGHT_INT,
                    PYRAMID_MAX_HEIGHT_INT);
 
        
        userInputHeight = GetInt();
    }
    
    drawPyramid(DEFAULT_BLOCK_CHAR, userInputHeight);
    
    return 0;
}