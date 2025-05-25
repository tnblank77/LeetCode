#Overall approach:
# Doesn't seem hard at all? Just running through the list adding in altitute change and tracking the highest altitude

class Solution:
    def largestAltitude(self, gain: List[int]) -> int:
        alt = 0
        alt_max = 0

        for val in gain:
            alt += val
            alt_max = max(alt_max, alt)
        
        return alt_max