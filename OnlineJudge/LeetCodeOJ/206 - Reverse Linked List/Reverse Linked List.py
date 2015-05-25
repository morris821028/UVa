# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    # @param {ListNode} head
    # @return {ListNode}
    def reverseList(self, head):
        if not head:
            return head
        
        curr = head
        prev = None
        next = None
        while curr:
            next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
            head = prev;
        
        return head