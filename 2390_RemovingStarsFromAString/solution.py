#Overall approach:
#Use a stack to add/pop character as we find non-stars or stars in the input

class Solution:
    def removeStars(self, s: str) -> str:
        result = []

        for char in s:
            if(char == '*'):
                result.pop()
            else:
                result.append(char)

        return ''.join(result)

    # My initial thought was to operate on the string in-place, which is more memory efficient
    def removeStarsInPlace(self, s: str) -> str:
        i = 0

        # Go through string and look for stars
        while(i < len(s)):
            if(s[i] == '*'):
                # Found star, trim it and previous character from strin
                s = s[:(i-1)] + s[(i+1):]
                i -= 1
            else:
                i += 1
        
        return s