#Overall Approach:
# Build a dictionary of the numbers to the characters they can be
# Go digit by digit and recursively follow the tree down to every combination
# When we reach the end, add it to a result that is returned

class Solution:
    # Number to letter dictionary
    letterDict = {
        '2': ['a', 'b', 'c'],
        '3': ['d', 'e', 'f'],
        '4': ['g', 'h', 'i'],
        '5': ['j', 'k', 'l'],
        '6': ['m', 'n', 'o'],
        '7': ['p', 'q', 'r', 's'],
        '8': ['t', 'u', 'v'],
        '9': ['w', 'x', 'y', 'z']
    }

    # Result that is returned
    result = []

    def letterCombinations(self, digits: str) -> List[str]:
        # Initialize result to nothing
        self.result = []

        # If there's digits, processs them recursively
        digits_len = len(digits)

        if digits_len > 0:
            self.getCombosRecursive(digits, digits_len, 0, "")
            
        # Return the result
        return self.result       

    def getCombosRecursive(self, digits: str, digits_len: int, i: int, input: str):
        # Go through each possible character for the current digit
        chars = self.letterDict[digits[i]]

        for char in chars:
            # Add this character to a possible output
            output = input + char

            if( i == (digits_len - 1)):
                # We've reached the end of the digits, add this output to the result
                self.result.append(output)
            else:
                # There's more digits, keep going recursively
                self.getCombosRecursive(digits, digits_len, (i + 1), output)