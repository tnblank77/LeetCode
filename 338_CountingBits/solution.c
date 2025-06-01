// Overall approach:
// Count bits in return array by adding one for if it's odd, and summing with previous bit result

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* result;

int* countBits(int n, int* returnSize) {
    // Determine and malloc the result array
    *returnSize = (n + 1);
    result = malloc(*returnSize * sizeof(int));

    // Count bits
    result[0] = 0;

    for( int i = 1; i < *returnSize; i++ ) {
        result[i] = (i & 1) + result[i >> 1];
    }

    // Return result
    return result;
}