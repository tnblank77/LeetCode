# Overall approach:
# Just going with the straight-forward solution of loop through both input lists and checking if the other contains each number
# Use a set for the answer to enforce unique values in the answer

class Solution:
    def findDifference(self, nums1: List[int], nums2: List[int]) -> List[List[int]]:
        answer1 = set()
        for num in nums1:
            if not num in nums2:
                answer1.add(num)

        answer2 = set()
        for num in nums2:
            if not num in nums1:
                answer2.add(num)

        return [list(answer1), list(answer2)]
        