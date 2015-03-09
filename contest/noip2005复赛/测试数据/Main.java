import java.io.FileInputStream;
import java.util.Arrays;
import java.util.Scanner;

public class Main {

	static Scanner scanner;
	static {
		scanner = new Scanner(System.in);
//		try{
//			scanner = new Scanner(new FileInputStream("2.in"));
//		}
//		catch (Exception e){}
	}

	static int[] stones = new int[105];

	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		assert false;
		int L;
		int S, T, M;
		L = scanner.nextInt();
		S = scanner.nextInt();
		T = scanner.nextInt();
		M = scanner.nextInt();

		assert 1 <= L && L <= 1000000000;
		assert 1 <= S && S <= T && T <= 10;
		assert 1 <= M && M <= 100;

		for (int i = 0; i < M; i++) {
			stones[i] = scanner.nextInt();
			assert 0 < stones[i] && stones[i] < L;
		}
//		for (int p : stones) System.out.println(p);

		assert !scanner.hasNext();

		Arrays.sort(stones, 0, M);

		for (int i = 0; i < M - 1; i++) {
			assert stones[i] != stones[i + 1];
		}

		if (S == T) {
			int result = 0;
			for (int i = 0; i < M; i++)
				if (stones[i] % S == 0) result++;
			System.out.println(result);
			return;
		}

		int dis = (T - 1 + (T - S - 1)) / (T - S) * T + 5 * T;

//		System.out.println("dis " + dis);

		stones[M] = L;
		for (int i = M; i >= 1; i--) {
			stones[i] = stones[i] - stones[i - 1];
		}
		for (int i = 0; i <= M; i++)
			if (stones[i] > dis) stones[i] = dis;
		for (int i = 1; i <= M; i++)
			stones[i] = stones[i] + stones[i - 1];
		L = stones[M];
//		for (int i = 0; i <= M; i++)
//			System.out.println(stones[i]);
//		System.out.println(L);

		int[] data = new int[L];
		boolean[] obt = new boolean[L];
		Arrays.fill(data, M + 1);
		Arrays.fill(obt, false);

		for (int i = 0; i < M; i++)
			obt[stones[i]] = true;

		data[0] = 0;
		int result = M + 1;
		for (int i = 0; i < L; i++) {
			if (data[i] == M + 1) continue;
			for (int j = S; j <= T; j++) {
				int now = i + j;
				if (now >= L) {
					if (data[i] < result)
						result = data[i];
				}
				else {
					int p = data[i];
					if (obt[now]) p++;
					if (p < data[now])
						data[now] = p;
				}
			}
		}

//		for (int i = 0; i < L; i++)
//			System.out.println(data[i]);

		System.out.println(result);
	}
}
