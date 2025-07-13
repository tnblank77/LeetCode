// Overall approach: Once I understood the problem, just need to recursively explore the rooms based on where keys are found

// Literal constants
#define MAX_ROOM_CNT 1000

// Static variable - array for if we have a key for a room
static bool s_have_key[MAX_ROOM_CNT];

// Local function declarations
int searchRoom(
    int room_idx,
    int** rooms,
    int* roomsColSize
);

// Test function
bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize) {
    // Initialize variables
    memset(s_have_key, false, sizeof(bool) * MAX_ROOM_CNT);
    
    // We start by having the key for the first room
    s_have_key[0] = true;

    // Recursively go room-by-room and collect keys
    int visited_room_count = 0;
    visited_room_count = searchRoom(0, rooms, roomsColSize);

    // Check if we have all the keys
    return( visited_room_count == roomsSize );
}

// Recursive function to search a room
int searchRoom(
    int room_idx,
    int** rooms,
    int* roomsColSize
) {
    int room_count = 1;

    // Collect all the keys in this room and search unsearched rooms
    for( int i = 0; i < roomsColSize[room_idx]; i++ ) {
        int key = rooms[room_idx][i];

        if( !s_have_key[key] ) {
            s_have_key[key] = true;
            room_count += searchRoom(key, rooms, roomsColSize);
        }
    }

    return( room_count );
}