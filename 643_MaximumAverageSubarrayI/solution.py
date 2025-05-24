#Overall Approach:
# Straight-forward with these constraints which require less input checking
# The greatest average will have the greatest sum, so we just need to find the greatest sum in the list before returning it as an average
# Start with sum at index 0, then slide through the list subtracting the old value and adding the new one, keeping track of the max sum

import sys

class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        # Start with sum at index 0 as maximum
        max_sum = sum(nums[0:k])
        last_sum = max_sum
        nums_sz = len(nums)

        # Slide through the list removing old values and adding new ones to find the max sum
        if(nums_sz > 0):
            for i in range(1, nums_sz + 1 - k):
                last_sum = last_sum - nums[i - 1] + nums[i + k - 1]
                max_sum = max(last_sum, max_sum)  
        
        # Return the average of the maximum sum
        return float(max_sum / k)