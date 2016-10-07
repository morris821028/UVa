public class Solution {
    public String getHint(String src, String tar) {
        int[] cntS = new int[128];
        int A = 0, B = 0;
        for (int i = 0; i < src.length(); i++)
            cntS[src.charAt(i)]++;
        for (int i = 0; i < tar.length(); i++) {
            char c = tar.charAt(i);
            if (cntS[c] > 0) {
                cntS[c]--;
                B++;
            }
            if (c == src.charAt(i))
                A++;
        }
        B -= A;
        return String.format("%dA%dB", A, B);
    }
}
