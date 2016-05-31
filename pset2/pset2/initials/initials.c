#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cs50.h"

int outputInitials(const char*, const int);
/**
 * -----------------/ Summary /-----------------
 * 
 * Requests a user to enter a full name and then outputs
 * the initials in uppercase.
 * 
 * -----------------/ Arguments /-----------------
 * 
 *  name : const char* - the full name containing alphabetic characters,
 *                       however alphanumeric entries will be accepted 
 *                       as well.
 * 
 *  count : const int  - the number of characters in the name.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  The name argument cannot be NULL or else the program returns an
 *  error code of 1.
 * 
 *  The count argument cannot be negative or else the program returns
 *  an error code of 1.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 *  The initials of the full name entered by a user are output
 *  on the screen.
 * 
 * -----------------/ Side-effects /-----------------
 * 
 *  Standard input and output buffers will be mutated.
 *  
 */


int main(int argc, char** argv) {
/**
 * -----------------/ Summary /-----------------
 * 
 * Requests a user to enter a full name and then outputs
 * the initials in uppercase.
 * 
 * -----------------/ Arguments /-----------------
 * 
 *  argc : int         - the number of arguments entered by a user.
 *                     Ignored for this program.
 * 
 *  argv : char**     - the array of commands entered by a user.
 *                     Ignored for this program.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  None.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 *  The initials of the full name entered by a user are output
 *  on the screen.
 * 
 * -----------------/ Side-effects /-----------------
 * 
 *  Standard input and output buffers will be mutated.
 *  
 */
    char* name = GetString();
    outputInitials(name, strlen(name));
    free(name);
    
    return 0;
}


int outputInitials(const char* name, const int count) {
    if (name == NULL) {
        return 1;
    }
    if (count < 0) {
        return 1;
    }
    
    bool isWhitespaceFound = true;
    
    for (int i = 0; i < count; ++i) {
        char letter = name[i];
        if (isWhitespaceFound) {
            printf("%c", toupper(letter));
            isWhitespaceFound = false;
        }
        if (isblank(letter)) {
            isWhitespaceFound = true;
        }
    }
    printf("\n");
    return 0;
}
