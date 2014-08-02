import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		BigInteger[][] C = new BigInteger[128][128];
		for (int i = 0; i < 128; i++)
			for (int j = 0; j < 128; j++)
				C[i][j] = BigInteger.ZERO;
		for (int i = 1; i < 128; i++) {
			C[i][0] = BigInteger.ONE;
			for (int j = 1; j <= i; j++)
				C[i][j] = C[i - 1][j].add(C[i - 1][j - 1]);
		}

		Scanner cin = new Scanner(System.in);
		int n, m;
		int[] A = new int[128];
		while (cin.hasNext()) {
			n = cin.nextInt();
			m = cin.nextInt();
			if (n + m == 0)
				break;
			for (int i = 1; i <= m; i++)
				A[i] = cin.nextInt();
			BigInteger[][] dp = new BigInteger[128][128];
			for (int i = 0; i < 128; i++)
				for (int j = 0; j < 128; j++)
					dp[i][j] = BigInteger.ZERO;
			dp[0][0] = BigInteger.ONE;
			for (int i = 1; i <= m; i++) {
				for (int j = 0; j <= n; j++) {
					for (int k = 0; k <= A[i] && j + k <= n; k++)
						dp[i][j + k] = dp[i][j + k].add(dp[i - 1][j]
								.multiply(C[j + k + 1][k]));
				}
			}
			System.out.println(dp[m][n]);
		}
	}
}