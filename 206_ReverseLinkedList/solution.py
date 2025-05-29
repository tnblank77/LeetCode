#Overall Approach:
# Just need to run the linked list and swap the order by:
#  1) Remembering the next node temporarily
#  2) Setting the next node to the last node (starting with None for the last)
#  3) Setting the last node to the current node
#  4) Process the next temporarily remembered node

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head is None:
            return head

        last = None

        while head:
            next_head = head.next 
            head.next = last 
            last = head 
            head = next_head 

        return last