// Overall approach:
//  - First thought could do this in place without the need of a buffer, but removing excess spaces would be annoying
//  - So going with output buffer, and just going to work backwards from input and add to output

//LITERAL CONSTANTS
#define DEBUG       false
#define SPACE_CHAR  ' '

//TYPES
typedef unsigned short uint16;

//VARIABLES
// Output buffer
static char s_output_buf[10000];

//Main test function
char* reverseWords(char* s) {
    // Local variables
    int     i;              /* input index      */
    uint16  input_len;      /* input length     */
    int     o;              /* output index     */
    int     word_end;       /* word end         */
    uint16  word_length;    /* word length      */

    // Initialize output
    memset(s_output_buf, SPACE_CHAR, sizeof(s_output_buf));
    o = -1;

    // Get the input length
    input_len = strlen(s);
    
    #ifdef DEBUG == true
        printf("Input length: %i\n", input_len);
    #endif

    // Work backwards and find words
    word_end = -1;

    for( i = (input_len - 1); i >= -1; i--) {
        if( word_end == -1 ) {
            if( i >= 0 && ( s[i] != SPACE_CHAR ) ) {
                // Found end of next word
                #ifdef DEBUG == true
                    printf("Found word end at index: %i\n", i);
                #endif

                word_end = i;
            }
        } else if( i == -1 || ( s[i] == SPACE_CHAR ) ) {
            // Found start of word
            word_length = (word_end - i);

            #ifdef DEBUG == true
                printf("Found word of length %i starting at index: %i\n", word_length, i + 1);
            #endif
            
            // Add space before word (we initialized "o" to -1 to prevent space at start), then copy word
            o++;
            memcpy(&s_output_buf[o], &s[i + 1], word_length);
            o += word_length;

            // Look for next word
            word_end = -1;
        }
    }

    // Null terminate the output and return it
    s_output_buf[o] = '\0';
    return( s_output_buf );
}
