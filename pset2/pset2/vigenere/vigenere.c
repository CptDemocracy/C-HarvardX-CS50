#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cs50.h"

#define ARGC_COUNT_INT				2
#define CHAR_BUFFER_LENGTH_INT		256
#define BUFFER_OVERFLOW_MSG_CSTR	"Character buffer encountered an overflow.\n"
#define INVALID_KEY_LEN_MSG_CSTR    "Your key's length exceeds the message's length which is illegal.\n"
#define INVALID_KEY_FORMAT_MSG_CSTR "The key should only contain ASCII alphabetical characters.\n"
#define INVALID_INPUT_MSG_CSTR		"The syntax of the command is incorrect. Please use ./vigenere /? for help\n"
#define OUTPUT_HELP_CMD_CSTR		"/?"


int  encrypt_ascii_vigenere (char*, char*, int, char*, int);
/**
 * -----------------/ Summary /------------------------
 * 
 * Provides a Vigenere's encryption mechanism. Unsafe.
 * Rotates each ASCII alphabetical character based on
 * the character key where its offset from the 1st 
 * letter in the alphabet serves as a number of steps
 * the character in the message should shifted.
 * 
 * -----------------/ Arguments /----------------------
 * 
 * msg : char*      - ASCII-encoded message to be encrypted.
 * 
 * buffer : char*   - buffer that will contain the result
 *                    of encryption.
 * 
 * msgLen : int     - the length of the message to be 
 *                    encrypted.
 * 
 * key : char*      - the ASCII-encoded key.
 * 
 * keyLen : int     - the length of the key.
 * 
 * -----------------/ Pre-condition /------------------
 * 
 * msg cannot be NULL or else an error code of 1 is
 * returned.
 * 
 * buffer cannot be NULL or else an error code of 1 is
 * returned.
 * 
 * msgLen cannot be negative or else an error code of 1
 * is returned.
 * 
 * key cannot be NULL or else an error code of 1 is
 * returned.
 * 
 * keyLen cannot be negative or else an error code of 1 
 * is returned.
 * 
 * keyLen can be greater than the msgLen, in that case
 * it will be considered equal to msgLen.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 * The result of the encryption is stored in the buffer
 * argument and a code of 0 is returned. Error code of 1
 * is returned on error.
 * 
 * -----------------/ Side-effects /-------------------
 * 
 * The buffer argument is mutated to contain the result
 * of encryption.
 *  
 */

char rotateAlphaChar        (char, int);
/**
 * -----------------/ Summary /------------------------
 * 
 * Rotates an ASCII alpha character the given number of steps.
 * 
 * -----------------/ Arguments /----------------------
 * 
 *  c : char    - character to be shifted.
 * 
 *  steps : int - a positive integer designates the number
 *                of steps to shift the character.
 * 
 * -----------------/ Pre-condition /------------------
 * 
 * For this implementation, the steps argument cannot be
 * negative or else the original character is returned.
 * 
 * -----------------/ Post-condition /-----------------
 * 
 * A new character is returned with a circular offset
 * to the original character equal to the number of steps.
 * 
 * -----------------/ Side-effects /-------------------
 * 
 * None.
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

bool isValidKey             (char*, int);
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Tests whether the key is valid for the encrypt_ascii_vigenere
 *  function.
 * 
 * -----------------/ Arguments /---------------------
 * 
 *  key : char*  - the ASCII key to be tested.
 * 
 *  count : int  - the length of the ASCII string to be
 *                 tested.
 * 
 * -----------------/ Pre-condition /-----------------
 * 
 *  The key argument cannot be NULL or else "false" is
 *  returned.
 * 
 *  The count argument cannot be negative or else "false"
 *  is returned.
 * 
 * -----------------/ Post-condition /----------------
 * 
 *  If the string is indeed a valid key, "true" is
 *  returned. Else, "false" is returned.
 * 
 * -----------------/ Side-effects /------------------
 * 
 *  None.
 * 
 */


int main(int argc, char** argv) {
/**
 * -----------------/ Summary /-----------------------
 * 
 *  Provides a user interface to the unsafe vigenere
 *  encryption functionality.
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
	else if (isValidKey(argv[ARGC_COUNT_INT - 1], strlen(argv[ARGC_COUNT_INT - 1]))) {

        char  buffer[CHAR_BUFFER_LENGTH_INT];
        
		char* key      = argv[ARGC_COUNT_INT - 1];
		char* input    = GetString();
		int   inputLen = strlen(input);
		int   keyLen   = strlen(key);
		
		if (inputLen + 1 > CHAR_BUFFER_LENGTH_INT){
			printf(BUFFER_OVERFLOW_MSG_CSTR);
			return 1;
		}
		if (keyLen > inputLen) {
		    printf(INVALID_KEY_LEN_MSG_CSTR);
		    return 1;
		}
		encrypt_ascii_vigenere(input, buffer, inputLen, key, keyLen);
		printf("%s\n", buffer);
		free(input);
		
		return 0;
	} else {
	    printf(INVALID_KEY_FORMAT_MSG_CSTR);
		return 1;
	}

    return 0;
}

int encrypt_ascii_vigenere(char* msg, 
                           char* buffer, 
                           int   msgLen, 
                           char* key, 
                           int   keyLen) 
{
    if (msg == NULL) {
        return 1;
    } 
    if (buffer == NULL) {
        return 1;
    }
    if (msgLen < 0) {
        return 1;
    }
    if (key == NULL) {
        return 1;
    }
    if (keyLen < 0) {
        return 1;
    }
    
    // We will allow the user to pass the key length argument that is
    // greater than the message's length. However, since it's impossible
    // to map the keys directly to the message if the lengths are not
    // equal, we simply set the key's length to that of the message.
    // We will leave it up to the callers whether to enforce this constraint
    // or not.
    keyLen = keyLen > msgLen ? msgLen : keyLen;
    
    int i, j;
    for (i = 0, j = 0; i < msgLen; ++i) {
		char letter = msg[i];
        if (isalpha(letter)) {
			int offset = isupper(key[j]) ? 'A' : 'a';
            buffer[i] = rotateAlphaChar(letter, (int) (key[j] - offset));
			j = (j + 1) % keyLen;
        }
		else {
			buffer[i] = letter;
		}
    }
    buffer[i] = '\0';
    
    return 0;
}

char rotateAlphaChar(char c, int steps) {
    
    if (!isalpha(c)) {
        return c;
    }
    
    if (steps < 0) {
        return c;
    }
    
    int alphaLen;
    if ((alphaLen = 'z' - 'a') != 'Z' - 'A') {
        // Copied this straight from caesar.c
        // Same idea, same test.
        
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
        // in our program if it does change, we simply refuse to process a 
        // corrupt/mutated table.
        return c;
    }
    
    int offset = isupper(c) ? 'A' : 'a';
    
    return (c - offset + steps) % (alphaLen + 1) + offset;
}

void outputHelp(void) {
    printf("Shifts alphabetical ASCII characters based on a number of steps \n");
    printf("designated by each character of the key.\n\n");
    printf("For example \"./vigenere bacon\" followed by user input \n");
    printf("\"Meet me at the park at eleven am\" produces \n");
    printf("\"Negh zf av huf pcfx bt gzrwep oz\".\n");
    printf("\nArguments: \n");
    printf("key - any ASCII-encoded word of length less or equal to that of message's\n");
    printf("made up of alphabetical characters.\n");
}

bool isValidKey (char* key, int keyLen) {
    if (key == NULL) {
        return false;
    }
    if (keyLen < 0) {
        return false;
    }
    for (int i = 0; i < keyLen; ++i) {
        if (!isalpha(key[i])) {
            return false;
        }
    }
    return true;
}