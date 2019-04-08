import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class Solution {
	public static BigInteger sqrt(BigInteger x) {
		BigInteger div = BigInteger.ZERO.setBit(x.bitLength() / 2);
		BigInteger div2 = div;
		// Loop until we hit the same value twice in a row, or wind
		// up alternating.
		for (;;) {
			BigInteger y = div.add(x.divide(div)).shiftRight(1);
			if (y.equals(div) || y.equals(div2))
				return y;
			div2 = div;
			div = y;
		}
	}

	public static void main(String[] args) {
		Scanner cin = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
		int testcase = cin.nextInt();
		int cases = 0;
		while (testcase-- > 0) {
			String N = cin.next();
			int L = cin.nextInt();
			ArrayList<BigInteger> text = new ArrayList<>();
			for (int i = 0; i < L; i++) {
				String t = cin.next();
				text.add(new BigInteger(t));
			}
			System.out.printf("Case #%d: ", ++cases);

			TreeSet<BigInteger> S = new TreeSet<>();
			for (int i = 1; i < L; i++) {
				BigInteger a = text.get(i);
				BigInteger b = text.get(i - 1);
				BigInteger t = a.gcd(b);
				if (!t.equals(a) && !t.equals(b)) {
					S.add(t);
					S.add(b.divide(t));
					S.add(a.divide(t));
				}
			}
			for (int i = 0; i < L; i++) {
				BigInteger a = text.get(i);
				BigInteger t = sqrt(a);
				if (t.multiply(t).equals(a))
					S.add(t);
			}
			if (S.size() != 26) {
				System.err.printf("Failed %d\n", cases);
				throw new RuntimeException("");
			}

			Map<BigInteger, Integer> table = new HashMap<>();
			for (BigInteger key : S) {
				int v = table.size();
				table.put(key, v);
			}
			
			BigInteger[] plain = new BigInteger[L+1]; 
			
			for (int i = 1; i < L; i++) {
				BigInteger a = text.get(i);
				BigInteger b = text.get(i - 1);
				BigInteger t = a.gcd(b);
				if (!t.equals(a) && !t.equals(b)) {
					plain[i] = t;
					for (int j = i-1; j >= 0; j--)
						plain[j] = text.get(j).divide(plain[j+1]);
					for (int j = i+1; j <= L; j++)
						plain[j] = text.get(j-1).divide(plain[j-1]);
				}
			}

			for (int i = 0; i <= L; i++) {
				Integer c = table.get(plain[i]);
				System.out.printf("%c", (char) (c + 'A'));

			}
			System.out.println();
		}
	}
}

