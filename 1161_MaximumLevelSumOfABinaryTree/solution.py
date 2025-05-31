# Overall Approach
# Use recursion to navigate the tree, and a use a dictionary to sum the vales
# Then, return the level of the biggest vaue in the dictionary

# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    level_values = {}

    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        self.level_values = {}

        # Call recursive function to do the work
        self.sumValueAndChildren(root, 1)

        # Return the level which has the biggest value
        max_value = self.level_values[1]
        max_level = 1

        for key, value in self.level_values.items():
            if( value > max_value ):
                max_value = value
                max_level = key

        return max_level

    # Recursive function to add the value for the level and then process it's children
    def sumValueAndChildren(self, node: Optional[TreeNode], level: int):
        if node is None:
            return

        if level in self.level_values:
            self.level_values[level] += node.val
        else:
            self.level_values[level] = node.val

        self.sumValueAndChildren(node.left, (level + 1))
        self.sumValueAndChildren(node.right, (level + 1))
