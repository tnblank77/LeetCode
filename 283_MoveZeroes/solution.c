// Overall approach:
// Just some easy in-place list sort, go index by index and move nonzeroes left

void moveZeroes(int* nums, int numsSize) {
    int j = 0; // Index of next nonzero value

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            // Swap into next nonzero spot and iterate
            int nonzero = nums[i];
            nums[i] = nums[j];
            nums[j] = nonzero;
            j++;
        }
    }
}