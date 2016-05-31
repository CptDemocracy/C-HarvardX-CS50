#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cs50.h"

#define ARGC_COUNT_INT				2
#define CHAR_BUFFER_LENGTH_INT		256
#define BUFFER_OVERFLOW_MSG_CSTR	"Character buffer encountered an overflow.\n"
#define INVALID_INPUT_MSG_CSTR		"The syntax of the command is incorrect. Please use ./caesar /? for help\n"
#define OUTPUT_HELP_CMD_CSTR		"/?"

int  encrypt_ascii_caesar   (char*, char*, int, int);
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Provides ROT13 encryption which should only be used
 *  for scientific research and/or curiosity. Or in the
 *  Ist century B.C. It would fare just fine!
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  msg : char*     - the message to be encrypted.
 * 
 *  buffer : char*  - the buffer that will contain the
 *                    result.
 * 
 *  msgLen : int    - the length of the message.
 * 
 *  key : int       - the key which is the number of steps each
 *                    character in the message should be shifted.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  The msg argument cannot be NULL or else an error code 1
 *  is returned.
 * 
 *  The buffer argument cannot be NULL or else an error code 1
 *  is returned.
 * 
 *  The msgLen argument cannot be negative or else an error
 *  code 1 is returned.
 * 
 *  The key argument cannot be negative or an error code 1 is
 *  returned.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  On success, 0 is returned and the buffer now contains the
 *  result.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  The buffer passed as the second argument to this function
 *  is mutated and contains the result of character rotation.
 * 
 */


bool isLiteralInt           (char*, int);
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Checks whether a string represents an integer and
 *  can be successfully converted to the int type.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  cstr : char* - ASCII string to be tested.
 * 
 *  count : int  - the length of the ASCII string to be
 *                 tested.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  The cstr argument cannot be NULL or else "false" is
 *  returned.
 * 
 *  The count argument cannot be negative or else "false"
 *  is returned.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  If the string can indeed be successfully converted
 *  to an int, "true" is returned.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  None.
 * 
 */

void outputHelp             (void);
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Provides a help message for the program.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  None.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  None.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  Help message sent to standard output buffer and 
 *  output on the screen.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  Standard output buffer mutated to output help.
 * 
 */


int main(int argc, char** argv) {
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Provides a user interface to the ROT13 functionality.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  argc : int      - contains the number of arguments passed.
 * 
 *  argv : char**   - contains the string of arguments to
 *                    the program.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  argc must be equal to ARGC_COUNT_INT or else an error
 *  code of 1 will be returned by the program.
 * 
 *  argv at index 1 (ARGC_COUNT_INT - 1) should contain
 *  an integer number to represent the key or OUTPUT_HELP_CMD_CSTR
 *  to represent a user request for a help message. In case of
 *  failure to satisfy these requirements, an error code of 1
 *  is returned.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  An encrypted message is output on the screen. 0 returned
 *  to signify successful completion of the program.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  Standard input and output buffers mutated by the program.
 * 
 */

	if (argc != ARGC_COUNT_INT) {
		printf(INVALID_INPUT_MSG_CSTR);
		return 1;
	}

	if ( strcmp(argv[ARGC_COUNT_INT - 1], OUTPUT_HELP_CMD_CSTR) == 0) {
		outputHelp();
	}
	else if ( isLiteralInt(argv[ARGC_COUNT_INT - 1], strlen(argv[ARGC_COUNT_INT - 1])) ) {

		int key = atoi(argv[ARGC_COUNT_INT - 1]);
		char buffer[CHAR_BUFFER_LENGTH_INT];
		char* input = GetString();
		int inputLen = strlen(input);
		if (inputLen + 1 > CHAR_BUFFER_LENGTH_INT){
			printf(BUFFER_OVERFLOW_MSG_CSTR);
			return 1;
		}
		encrypt_ascii_caesar(input, buffer, inputLen, key);
		printf("%s\n", buffer);
		free(input);
		
		return 0;
	} 
	else {
		printf(INVALID_INPUT_MSG_CSTR);
		return 1;
	}

    return 0;
}

int encrypt_ascii_caesar(char* msg, char* buffer, int msgLen, int key) {
    if (msg == NULL) {
        return 1;
    }
    
    if (buffer == NULL) {
        return 1;
    }
    
    if (msgLen < 0) {
        return 1;
    }
    
    if (key < 0) {
        // the reason it's not: 
        //      "if (key <= 0 || 
        //           key % ('a' - 'z') == 0) { ..." 
        // is that we want to allow clients to have the ROT26 functionality.
        
        // Just kidding, we're simply leaving that because it's actually quite
        // logical - we may assume that all messages are initially encrypted
        // with a key of 0 or a key equal to the alphabet's length.
        
        // Not allowing clients to have a key of 0 would be quite alogical
        // and it should probably be up to client's code to impose constraints
        // on keys.
        
        return 1;
    }
    
    int alphaLen;
    if ((alphaLen = 'z' - 'a') != 'Z' - 'A') {
        // Okay, but you might ask, what's with all these ('z' - 'a') and 
        // ('Z' - 'A') tests?
        
        // Obviously we would be testing so that the key was not
        // producing the same character and ('z' - 'a') gives us the alphabet
        // length. ('Z' - 'A') does exactly the same, so what's the point?
        
        // Well, here's a basic idea. Let's assume that it's not an ascii table
        // we are dealing with but some other table that is subject to change,
        // and suppose that for some reason a certain letter only appears in 
        // uppercase.
        
        // We want to make sure that's not the case and, as unlikely as the 
        // ascii table is to change, rather than introduce a security hole
        // in our program if it does change (which has a chance of roughly 
        // 0E-100000), we simply refuse to process a corrupt/mutated table.
        return 1;
    }
    
    int i;
    for (i = 0; i < msgLen; ++i) {
		char encChar;
        if (isalpha(msg[i])) {
            int offset = isupper(msg[i]) ? 'A' : 'a';
            encChar = (msg[i] - offset + key) % (alphaLen + 1) + offset;
        }
		/*
		else {
            buffer[i] = msg[i] + key;   
            // we let it overflow if necessary, in this case it's okay,
            // since we can always retrace it back to its original index
            // in the ascii table.
        }
		*/
		else {
			encChar = msg[i];
		}
		buffer[i] = encChar;
    }
    buffer[i] = '\0';
    
    return 0;
}

bool isLiteralInt(char* cstr, int len) {
	if (cstr == NULL) {
		return false;
	}
	if (len <= 0) {
		return false;
	}
	for (int i = 0; i < len; ++i) {
		if (!isdigit(cstr[i])) {
			return false;
		}
	}
	return true;
}

void outputHelp(void) {
    printf("Shifts alphabetical ASCII characters in input a requested number of steps.\n\n");
    printf("For example \"./caesar 13\" followed by input \"Be sure to drink your Ovaltine!\"\n");
    printf("produces input of \"Or fher gb qevax lbhe Binygvar!\"\n");
    printf("\nArguments:\n");
    printf("key - a non-negative integer designating the number of steps letters should move to the right.\n");
}
