import java.util.*;
import java.io.*;

public class Main {
	static void solve(int n, char[][] g) {
		int[][] Q = new int[128*128][2];
		int[][] step = new int[128][128];
		int dx[] = {0, 0, 1, -1};
		int dy[] = {1, -1, 0, 0};
		int qidx = 0;
		Q[qidx][0] = 1;
		Q[qidx][1] = 1;
		step[1][1] = 1;
		for (int i = 0; i <= qidx; i++) {
			int x = Q[i][0], y = Q[i][1];
			int tx, ty;
			for (int j = 0; j < 4; j++) {
				tx = x + dx[j];
				ty = y + dy[j];
				if (tx < 0 || ty < 0 || tx >= n || ty >= n || g[tx][ty] == '#')
					continue;
				if (step[tx][ty] == 0) {
					step[tx][ty] = step[x][y] + 1;
					++qidx;
					Q[qidx][0] = tx;
					Q[qidx][1] = ty;
				}
			}
		}
		if (step[n-2][n-2] == 0)
			System.out.println("No solution!");
		else
			System.out.println(step[n-2][n-2]);
	}
	public static void main(String[] args) {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		try {
			int n = Integer.parseInt(in.readLine());
			char[][] g = new char[128][128];
			for (int i = 0; i < n; i++) {
				String t = in.readLine();
				for (int j = 0; j < n; j++)
					g[i][j] = t.charAt(j);
			}
			solve(n, g);
		} catch (Exception e) {
			System.err.println("Format Error");
		}
	}
}
