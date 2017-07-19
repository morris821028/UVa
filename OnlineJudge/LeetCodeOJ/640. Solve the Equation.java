public class Solution {
    private String coeff(String x) {    // +x -x +12x x -1230x
        if (x.length() > 1 && x.charAt(x.length()-2) >= '0' && x.charAt(x.length()-2) <= '9')
            return x.replace("x", "");
        return x.replace("x", "1");
    }
    public String solveEquation(String e) {
        int n = e.length();
        String[] s = e.split("=");
        // using Lookahead and Lookbehind
        int xval = 0, val = 0;
        for (String t: s[0].split("(?=\\+)|(?=-)")) {
            if (t.indexOf("x") >= 0)
                xval += Integer.parseInt(coeff(t));
            else
                val -= Integer.parseInt(t);
        }
        for (String t: s[1].split("(?=\\+)|(?=-)")) {
            if (t.indexOf("x") >= 0)
                xval -= Integer.parseInt(coeff(t));
            else
                val += Integer.parseInt(t);
        }
        if (xval == 0 && val == 0)
            return "Infinite solutions";
        else if (xval == 0 && val != 0)
            return "No solution";
        return "x=" + (val / xval);
    }
}
