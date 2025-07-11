// Overall approach: Just a simple binary search for the number
#define DEBUG true

// Headers
int guess(int num);

int searchRecursively(int num, int max);

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 */

int guessNumber(int n) {
    // First handle edge cases (e.g. n == 1) by checking if n is the number
    if( guess(n) == 0 ) {
        return n;
    }
 
    #ifdef DEBUG
        printf("%i\n", n);
    #endif

    // Otherwise find it recurisvely via binary search
    return searchRecursively(0, n);
}

// Recusive binary search
int searchRecursively(int min, int max) {
    int mid = min + (max - min) / 2;

    int result = guess(mid);

    #ifdef DEBUG
        printf("%i %i\n", mid, result);
    #endif
    
    switch(result) {
        case -1:
            return searchRecursively(min, mid);

        case 1:
            return searchRecursively(mid, max);

        default:
            return mid;
    }
}