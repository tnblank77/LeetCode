# Overall Approach:
# NOTE: I didn't spend a ton of time thinking about this, just wanted something quick that works
# Take the largest string that both string starts with, then see if it divides both. If not, trim off the end until a match is found.
# Regular expressions seems to like a good way to check the "division", and I had to do a quick Google search to remind myself on how to do that in Python

import re

class Solution:
    def gcdOfStrings(self, str1: str, str2: str) -> str:
        # Determine largest string that both strings start with
        size = 0
        for char in str1:
            if(size >= len(str2) or char != str2[size]):
                break
            size += 1

        # Step back on string until there's a match
        for i in range(size, -1, -1):
            x = str1[:i]
            pattern = r"(" + x + ")+"
            
            match1 = re.fullmatch(pattern, str1)
            if match1 is None:
                continue

            match2 = re.fullmatch(pattern, str2)
            if match2:
                return x
            
        return ""