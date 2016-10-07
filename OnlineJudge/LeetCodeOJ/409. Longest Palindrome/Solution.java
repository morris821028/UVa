public class Solution {
    public int longestPalindrome(String s) {
        int[] bin = new int[128];
        byte[] str = s.getBytes();
        for (int i = 0; i < str.length; i++) {
            bin[str[i]]++;
        }
        int odd = 0, even = 0;
        for (int i = 0; i < bin.length; i++) {
            even += bin[i] / 2 * 2;
            odd += bin[i] % 2;
        }
        return (odd > 0 ? 1 : 0) + even;
    }
}
