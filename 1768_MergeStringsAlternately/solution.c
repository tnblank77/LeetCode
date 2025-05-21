// Overall Approach:
// With C, I always felt it was most effecient to process strings until I reached a null teriminator. So will run two iterators through both words and add to buffer.

// Define type to represent an unsigned 8-bit integer clearly
typedef unsigned char uint8;

// Define constant for null; easier to read
const char NULL_CHAR = '\0';

// Create buffer for result, must be big enough to account for the maximum size of 100 characters in each word
char result[201];

// Declare local functions
bool tryToAddToResult(
    char * word,
    uint8 * word_idx,
    char * result,
    uint8 * result_idx
);

char * mergeAlternately(char * word1, char * word2){
    // Create indicies to go through each word
    uint8 i1 = 0;
    uint8 i2 = 0;
    uint8 ri = 0;

    // Loop while there's letters
    bool found1 = true;
    bool found2 = true;

    while( found1 || found2 ) {
        found1 = tryToAddToResult(word1, &i1, result, &ri);
        found2 = tryToAddToResult(word2, &i2, result, &ri);
    };

    // null terminate and return the result
    result[ri] = NULL_CHAR;
    return( result );
}

// Define function to try to add character to result to reduce code duplication
// Returns whether or not a character was added
bool tryToAddToResult(
    char * word,
    uint8 * word_idx,
    char * result,
    uint8 * result_idx
) {
    if( word[*word_idx] != NULL_CHAR ) {
        result[*result_idx] = word[*word_idx];
        *result_idx = *result_idx + 1;
        *word_idx = *word_idx + 1;
        return( true );
    } else {
        return( false );
    }
}