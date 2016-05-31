/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"
#include "HashSet.h"

#define DICTIONARY          "dictionaries/large"

#define AVERAGE_WORD_LENGTH 10

// LENGTH is the length largest word in the English dictionary so far, but we need
// to provide for that extra null-terminating character.
// Those parenthesis are a must, since without them expressions like:
//      sizeof(char) * TERMINATED_LENGTH
// will compile to:
//      sizeof(char) * LENGTH + 1
// or given current LENGTH definition:
//      sizeof(char) * 45 + 1
// clearly not what we would want!
#define TERMINATED_LENGTH   (LENGTH + 1)

HashSet* DICTIONARY_SET;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char* const buffer = calloc(TERMINATED_LENGTH, sizeof(char));
    if (buffer == NULL) {
        
        // we want to return if calloc failed
        return false;
    }
    
    size_t wordLen = strlen(word);
    wordLen = (wordLen <= TERMINATED_LENGTH) ? wordLen : TERMINATED_LENGTH - 1;
    memcpy(buffer, word, wordLen);
    
    char* pntr = buffer;
    while (*pntr != '\0') {
        *pntr = tolower(*pntr);
        ++pntr;
    }
		
    bool contains = HashSetContainsItem(DICTIONARY_SET, buffer);
    free(buffer);
    return contains;
}

/**
 * Returns file size of a given file. Since ftell(...) returns a long int
 * which is on most implementations a WORD (4 bytes), I have provided that 
 * the function fails if a file size is over 2 TB and indicates that by 
 * returning a non-zero value. An -1L value is also returned if provided 
 * with a NULL file argument and/or fseek(...) fails.
 * 
 * The function has no side effect unless fsetpos(...) fails and we are stuck
 * at the end of the file. That is, the function has to get to the end of the 
 * file and calculate the size, and then goes back to its original position
 * which it had been at prior to the function call. If fsetpos(...) fails
 * to return to the original position, an -2L value is returned.
 * 
 * This function is used by the load function which tries to roughly estimate
 * the number of words it will have to hold in order to pre-allocate enough
 * memory and avoid future re-hashing.
 * 
 */
long fsize(FILE* file) {
    if (file == NULL) {
        return -1L;
    }
    
    fpos_t pos;
    
    // get original position.
    // report failure if failed.
    if ( fgetpos(file, &pos) != 0) {
        return -1L;
    }
    
    // this will change our position.
    // do not forget to go back to the original position
    // once we're done.
    // report failure if failed.
    if ( fseek(file, 0L, SEEK_END) != 0) {
        return -1L;
    }
    
    long fSize = ftell(file);
    
    // if long overflew and the file is thus greater than 2 TB
    // we want to report failure.
    
    // won't safeguard us from files of size (4TB + x) and greater
    // where 2 <= x < +Infinity.
    if (fSize < 0L) {
        return -1L;
    }
    
    // go back to the original position.
    // report failure if failed.
    if ( fsetpos(file, &pos) != 0) {
        return -2L;
    }
    
    return fSize;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL) {
        return false;
    } 

    char* buffer = calloc(TERMINATED_LENGTH, sizeof(char));
    if (buffer == NULL) {
        
        // if calloc failed, return false
        return false;
    }

	DICTIONARY_SET = HashSetNew(sizeof(char) * TERMINATED_LENGTH, NULL);
	if (DICTIONARY_SET == NULL) {
	    // report failure if HashSetNew failed
	    return false;
	}
	
    // Re-hashing is evil. Just think about it - every time we re-hash, we make
    // a puppy somewhere out there cry. Please keep re-hashing to a minimum.
    // And so to keep all our puppies are happy, we make a rough estimate of how
    // many bytes of memory we will need by a formula:
    //
    //      fileSize / AVERAGE_WORD_LENGTH
    //
    // and then call HashSetEnsureCapacity to save all the puppies.
    long fSize = fsize(dict);
    size_t capacity = (size_t)fSize / AVERAGE_WORD_LENGTH;
    HashSetEnsureCapacity(DICTIONARY_SET, capacity);
    
    int bufferIndex = 0;
    for (char c = fgetc(dict); c != EOF; c = fgetc(dict)) {
        if (isalpha(c) || c == '\'') 
        {
            ungetc(c, dict);
            while ((c = fgetc(dict)) != EOF 
                        && (isalpha(c) || c == '\'') 
                        && bufferIndex < TERMINATED_LENGTH - 1) 
            {
                buffer[bufferIndex] = c;
                ++bufferIndex;
            }
            buffer[bufferIndex] = '\0';
            HashSetAddItem(DICTIONARY_SET, buffer);
			memset(buffer, 0, sizeof(char) * TERMINATED_LENGTH);
			bufferIndex = 0;
        }
    }
    
    // free resources
    fclose(dict);
    free(buffer);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return HashSetGetCount(DICTIONARY_SET);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    if (HashSetDispose(DICTIONARY_SET) == 0) {
        return true;
    }
    return false;
}
