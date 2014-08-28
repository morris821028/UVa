import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		BigInteger[] f1 = new BigInteger[1024];
		BigInteger[] f2 = new BigInteger[1024];
		f1[1] = BigInteger.valueOf(2);
		f1[2] = BigInteger.valueOf(4);
		f2[0] = BigInteger.valueOf(0);
		f2[1] = BigInteger.valueOf(1);
		for (int i = 3; i < f1.length; i++)
			f1[i] = f1[i - 2].add(f1[i - 1]).add(BigInteger.ONE);
		for (int i = 2; i < f2.length; i++)
			f2[i] = f2[i - 1].add(f1[i - 1]);
		Scanner cin = new Scanner(System.in);
		int testcase = cin.nextInt();
		while (testcase-- != 0) {
			int n = cin.nextInt();
			if (n < 0)
				n = 0;
			System.out.println(f2[n]);
		}
	}
}
/*
 * 0 1 3 7 14 26 46 79 133 
 	 0 2 4 7 12 20 33 54
 */
