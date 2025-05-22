# Overall approach:
# This one is super straight-forward to me, essentially converting array to another based on if a value meets a threshold
# I did have to remind myself how to do the array conversion in Python (been a while)

class Solution:
    def kidsWithCandies(self, candies: List[int], extraCandies: int) -> List[bool]:
        # Find the maximum value in the array
        maxCandies = max(candies)

        # Calculate the minimum value needed for any value to have the greatest number of candies if given all extra
        minCandiesNeeded = (maxCandies - extraCandies - 1)

        # Build result array (all values that are > min will have the greatest if given all extra)
        result = [count > minCandiesNeeded for count in candies]

        return result