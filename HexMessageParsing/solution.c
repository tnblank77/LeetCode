// INCLUDES
#include <stdio.h>
#include <stdlib.h>

// LITERAL CONSTANTS
#define HEX_BASE_16     (16)    /* base-16 hex                  */
#define HEX_BYTE_STR_SZ (2)     /* string size of byte in hex   */
#define MSG_BUF_SZ      (5)     /* message buffer size          */

// TYPES
// Data types to clarify unsigned 8-bit and 16-bit integers
typedef unsigned char uint8;
typedef unsigned short uint16;

// Parsed message information type
typedef struct {
    uint16  timestamp;
    uint8   id;    
    uint8   payload_sz;
    uint8 * payload;
} msg_info_type;

// VARIABLES
static msg_info_type 	s_msg_buf[MSG_BUF_SZ];	/* message buffer				*/
static uint8 			s_msg_buf_cnt;			/* count of messages in buffer	*/

// PROCEDURES
static void debug_print_buf();
static void debug_print_message(char * msg, msg_info_type * info);
static void msg_add(char * msg_hex);
static msg_info_type * msg_get_oldest();
static uint16 parse_hex(char * msg_hex, int data_offset, int data_size);
static void parse_msg(char * msg_hex, msg_info_type * info);

int main() {
    // Local variables
    msg_info_type   parse_msg_test_result;  /* test result for parse_msg    */

    //Test parse_message
    parse_msg("0190280A0102030405060708090A", &parse_msg_test_result);
    debug_print_message("parse_msg_test_result", &parse_msg_test_result);
    printf("\n");

    //Test adding to buffer
    s_msg_buf_cnt = 0;

    printf("DEBUG adding 1\n");
    msg_add("23e8990b0b38e56fa24e55c1c628b35012");
    debug_print_buf();

    printf("DEBUG adding 4 more\n");
    msg_add("8894900c0c3237dc5e2d79f4217f976e5393");
    msg_add("bd9ae50d0d235efa639b329b53f4d40e4b5149");
    msg_add("306145oe0e5a4ba7b7ac622a92e570e4f58769a1");
    msg_add("03ba0b0f0ff1407457d97ffe7bb59e79f50a4ea6e5");
    debug_print_buf();

    printf("DEBUG adding 1 more\n");
    msg_add("c28a7e0a0a3fa00c17993665101d50fe");
    debug_print_buf();

    printf("DEBUG adding 1 more\n");
    msg_add("0dc9e50a0abd737ca2fe5ba23a2785f2");
    debug_print_buf();

    printf("DEBUG adding 1 more\n");
    msg_add("3894d40a0a947b5286fb11452260118f");
    debug_print_buf();

    printf("DEBUG adding 1 more\n");
    msg_add("f987970a0af69cf2fd6ce5e6406ffa35");
    debug_print_buf();
   
    return 0;
}

static void debug_print_buf() {
    int i;   /* loop index          */

    for( i = 0; i < MSG_BUF_SZ; i++ ) {
        debug_print_message("buffer", &s_msg_buf[i]);
    }

    printf("\n");
}

static void debug_print_message(char * msg, msg_info_type * info) {
    int i;   /* loop index  */

    printf(
        "DEBUG %s timestamp=%i, id=%i, payload_sz=%i, payload=",
        msg,
        info->timestamp,
        info->id,
        info->payload_sz
        );
    for( i = 0; i < info->payload_sz; i++ ) {
        printf("%i ", info->payload[i]);
    }
    printf("\n");
}

// Function to add a message to the buffer
static void msg_add(char * msg_hex) {
    // Local variables
    msg_info_type   info;       /* message info             */
    msg_info_type * info_ptr;   /* pointer to message info  */

    // If buffer isn't full, just add to it
    if( s_msg_buf_cnt < MSG_BUF_SZ ) {
        parse_msg(msg_hex, &s_msg_buf[s_msg_buf_cnt]);
        s_msg_buf_cnt++;
        return;
        }

    // Buffer is full, find oldest and replace it
    parse_msg(msg_hex, &info);
    info_ptr = msg_get_oldest();

    if(info.timestamp < info_ptr->timestamp) {
        // New message is older than oldest, so discard it
        printf("DEBUG: new message (%i) older than oldest message (%i)\n", info.timestamp, info_ptr->timestamp);
        return;
    }

    // NOTE: make sure to free the payload memory to prevent memory leaks!
    printf("DEBUG: new message (%i) replacing oldest message (%i)\n", info.timestamp, info_ptr->timestamp);
    free(info_ptr->payload);
    memcpy(info_ptr, &info, sizeof(info));
}

// Function to retrieve the oldest message
static msg_info_type * msg_get_oldest() {
    // Local variables
    uint8   i;      /* loop index               */
    uint8   i_min;  /* index of minimum entry   */

    // TODO: check that s_msg_buf_cnt is > 0

    // Initialize variables
    i_min = 0;

    // Find minimum timestamp to get oldest message
    for( i = 1; i < s_msg_buf_cnt; i++ ) {
        if( s_msg_buf[i].timestamp < s_msg_buf[i_min].timestamp ) {
            i_min = i;
        }
    }

    return( &s_msg_buf[i_min] );
}

// Function to parse a hex string into an integer
static uint16 parse_hex(char * msg_hex, int data_offset, int data_size) {
    char buf[4 + 1]; // Buffer large enough to get 2 bytes of hex data

    // Get buffer to convert to hex
    memcpy(buf, &msg_hex[data_offset], data_size);
    buf[data_size] = 0;

    // Return value from hex buffer
    return strtol(buf, NULL, HEX_BASE_16);
}

// Function to parse an input message as hex string into the data type
static void parse_msg(char * msg_hex, msg_info_type * info) {
    // Local variables
    int i;  /* loop index   */

    // Get timestamp
    info->timestamp = parse_hex(
        msg_hex,
        offsetof(msg_info_type, timestamp) * HEX_BYTE_STR_SZ,
        sizeof(info->timestamp) * HEX_BYTE_STR_SZ
    );

    // Get ID
    info->id = parse_hex(
        msg_hex,
        offsetof(msg_info_type, id) * HEX_BYTE_STR_SZ,
        sizeof(info->id) * HEX_BYTE_STR_SZ
    );

    // Get payload size
    info->payload_sz = parse_hex(
        msg_hex,
        offsetof(msg_info_type, payload_sz) * HEX_BYTE_STR_SZ,
        sizeof(info->payload_sz) * HEX_BYTE_STR_SZ
    );

    // Allocate and get payload
    // TODO: add protection against overflow in case payload_sz is corrupted
    info->payload = malloc(info->payload_sz);
    
    for(i = 0; i < info->payload_sz; i++) {
        info->payload[i] = parse_hex(
            msg_hex,
            offsetof(msg_info_type, payload) + (i * HEX_BYTE_STR_SZ),
            sizeof(uint8) * HEX_BYTE_STR_SZ
        );
    }
}
