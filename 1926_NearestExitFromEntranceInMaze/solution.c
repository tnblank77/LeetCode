// General approach: - Recursively explore every viable path and return the shortest one
//                   - Use a queue to ensure shallowest path is explored next

// Includes
#include <limits.h>

// Literal constants
#define DEBUG false

#define MAX_ROW_SZ  (100) // maximum row size per constraints
#define MAX_COL_SZ  (100) // maximum column size per constraints

// TYPES
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef signed long sint32;

// Enumeration for direction to go
typedef uint8 dir_t8;
enum {
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT,

    DIR_CNT
};

// Position information type
typedef struct {
    int step_cnt;
    int pos_x;
    int pos_y;
    dir_t8 dir_from;
} pos_info_type;

// Memory constants
static const dir_t8 s_dir_backwards[] = 
    {
    /* DIR_UP    */ DIR_DOWN,
    /* DIR_RIGHT */ DIR_LEFT,
    /* DIR_DOWN  */ DIR_UP,
    /* DIR_LEFT  */ DIR_RIGHT,

    /* DIR_CNT   */ DIR_CNT
    };
//TODO: add compiler assert that this table is of size DIR_CNT

// Static variables
static bool             s_to_explore[MAX_ROW_SZ + 1][MAX_COL_SZ];               // matrix of whether or not we are to explore a cell in the queue
static pos_info_type    s_explore_queue[(MAX_ROW_SZ + 1) * (MAX_COL_SZ + 1)];   // queue of positions to explore
static uint16           s_explore_queue_next_idx;   // next index to add to queue of positions to explore
static uint16           s_explore_idx;              // index of queue we are exploring at

// PROCEDURES
// function which explores the specified cell, adding any possible future paths to the queue
// returns whether or not exploration should end
static bool explore(int step_cnt, int pos_x, int pos_y, char** maze, int max_x, int max_y, dir_t8 dir_from);

// Main function
int nearestExit(char** maze, int mazeSize, int* mazeColSize, int* entrance, int entranceSize) {
    #if (DEBUG == true)
    printf("nearestExit: mazeSize=%i, mazeColSize=%i,\n", mazeSize,  mazeColSize[0]);
    #endif

    // Initialize variables
    memset(s_to_explore, false, sizeof(s_to_explore));
    memset(s_explore_queue, -1, sizeof(s_explore_queue));
    s_explore_idx = 0;
    s_explore_queue_next_idx = 0;

    // Explore the starting cell
    bool exit_found = explore(0, entrance[0], entrance[1], maze, mazeSize, mazeColSize[0], DIR_CNT);

    // Keep exploring until we're done
    while(!exit_found && (s_explore_idx < s_explore_queue_next_idx)) {
        pos_info_type *info = &s_explore_queue[s_explore_idx];
        s_explore_idx++;

        exit_found = explore(info->step_cnt, info->pos_x, info->pos_y, maze, mazeSize, mazeColSize[0], info->dir_from);
    }

    // Return result
    return( s_explore_queue[s_explore_idx].step_cnt );
}

// Exploration function which checks surrounding cells and:
//  1) Adds them to queue if they should be explored
//  2) Ignores them if they are a wall or already explored
//  3) Returns result when an exit is found
static bool explore(int step_cnt, int pos_x, int pos_y, char** maze, int max_x, int max_y, dir_t8 dir_from) {
    #if (DEBUG == true)
        printf("explore: step_cnt=%i, pos=%i,%i\n", step_cnt, pos_x, pos_y);
    #endif

    for( dir_t8 dir = 0; dir < DIR_CNT; dir++) {
        if( dir == s_dir_backwards[dir_from] ) {
            // Don't go backwards
            continue;
        }

        // Calculate position based on direction
        int pos_x_new = pos_x;
        int pos_y_new = pos_y;

        switch(dir) {
            case DIR_UP:
                pos_y_new--;
                break;
            
            case DIR_RIGHT:
                pos_x_new++;
                break;

            case DIR_DOWN:
                pos_y_new++;
                break;

            case DIR_LEFT:
                pos_x_new--;
                break;

            default:
                //TODO: Throw a developer exception
                break;
        }

        // Check if we've exited the maze
        if( pos_x_new < 0 
         || pos_y_new < 0
         || pos_x_new >= max_x
         || pos_y_new >= max_y )
            {
            if( step_cnt > 0 ) {
                #if (DEBUG == true)
                    printf("explore result: maze exit, dir=%i (%i, %i)\n", dir, pos_x_new, pos_y_new);
                #endif
                s_explore_idx--;
                return( true );
            }
            else {
                #if (DEBUG == true)
                printf("explore result: maze limit, dir=%i (%i, %i)\n", dir, pos_x_new, pos_y_new);
                #endif
                continue;
            }
        }

         // Abort if we've already queued the exploration of this cell
        if( s_to_explore[pos_x_new][pos_y_new] ) {
            #if (DEBUG == true)
                printf("explore result: already queued, dir=%i (%i, %i)\n", dir, pos_x_new, pos_y_new);
            #endif
            continue;
        }

        // Check if we've hit a wall
        if( maze[pos_x_new][pos_y_new] == '+') {
            #if (DEBUG == true)
                printf("explore result: hit a wall, dir=%i (%i, %i)\n", dir, pos_x_new, pos_y_new);
            #endif
            continue;
        }

        // Otherwise add to the queue
        #if (DEBUG == true)
            printf("explore result: adding to queue, dir=%i (%i, %i)\n", dir, pos_x_new, pos_y_new);
        #endif
        s_to_explore[pos_x_new][pos_y_new] = true;
        pos_info_type *info = &s_explore_queue[s_explore_queue_next_idx];
        info->step_cnt = (step_cnt + 1);
        info->pos_x = pos_x_new;
        info->pos_y = pos_y_new;
        info->dir_from = dir;

        s_explore_queue_next_idx++;
    }

    return( false );
}