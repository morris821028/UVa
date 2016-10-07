/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */

public class Solution {
	private static ListNode splitHalf(ListNode head) {
		ListNode p = head, q = head.next;
		while (q != null && q.next != null && q.next.next != null) {
			p = p.next;
			q = q.next.next;
		}
		return p;
	}

	private static void reverseList(ListNode st, ListNode ed) {
		if (st == ed) {
			st.next = null;
			return;
		}
		ListNode nt = st.next, ntnt = st.next.next;
		st.next = null;
		while (true) {
			nt.next = st;
			st = nt;
			if (st == ed)
				return;
			nt = ntnt;
			ntnt = ntnt.next;
		}
	}

	private static boolean same(ListNode a, ListNode b) {
		while (a != null && b != null) {
			if (a.val != b.val)
				return false;
			a = a.next;
			b = b.next;
		}
		return a == b;
	}
	public boolean isPalindrome(ListNode head) {
		if (head == null || head.next == null)
			return true;
		ListNode mpos = splitHalf(head);
		ListNode tpos = mpos.next;
		reverseList(head, mpos);
		return same(mpos, tpos) || (tpos != null && same(mpos, tpos.next));
	}
}
