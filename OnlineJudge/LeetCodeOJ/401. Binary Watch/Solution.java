public class Solution {
    public List<String> readBinaryWatch(int num) {
        List<String> ret = new ArrayList<String>();
        for (int i = 0; i < 1024; i++) {
            int mm = i&63;
            int hh = (i>>6);
            if (Integer.bitCount(mm) + Integer.bitCount(hh) == num) {
                if (mm < 60 && hh < 12)
                    ret.add(String.format("%d:%02d", hh, mm));
            }
        }
        return ret;
    }
}
