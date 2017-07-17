public class Solution {
    public long dist(int p[], int q[]) {
        return (p[0] - q[0])*(p[0] - q[0]) + (p[1] - q[1])*(p[1] - q[1]);
    }
    public boolean validSquare(int[] p1, int[] p2, int[] p3, int[] p4) {
        int[][] pts = {p1, p2, p3, p4};
        Arrays.sort(pts, (p, q) -> p[0] == q[0] ? p[1] - q[1] : p[0] - q[0]);
        long d = dist(pts[0], pts[1]);
        return d > 0 &&
                d == dist(pts[0], pts[2]) &&
                d == dist(pts[2], pts[3]) &&
                d == dist(pts[1], pts[3]) &&
                dist(pts[0], pts[3]) == dist(pts[1], pts[2]);
    }
}
