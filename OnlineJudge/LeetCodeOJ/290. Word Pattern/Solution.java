public class Solution {
    public boolean wordPattern(String pattern, String str) {
        String[] tokens = str.split(" ");
        if (pattern.length() != tokens.length)
            return false;
        Map<String, Character> sR = new TreeMap<String, Character>();
        Map<Character, String> cR = new TreeMap<Character, String>();
        for (int i = 0; i < pattern.length(); i++) {
            char c = pattern.charAt(i);
            if (sR.get(tokens[i]) == null)
                sR.put(tokens[i], c);
            if (cR.get(c) == null)
                cR.put(c, tokens[i]);
            if (sR.get(tokens[i]) != c || !cR.get(c).equals(tokens[i]))
                return false;
        }
        return true;
    }
}
