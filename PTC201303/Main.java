import java.util.Scanner;
import java.math.BigInteger;

public class Main {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);

		int t = scanner.nextInt();

		while (t-- > 0) {
			BigInteger a = new BigInteger(scanner.next());
			BigInteger b = new BigInteger(scanner.next());
			BigInteger c = new BigInteger(scanner.next());

			System.out.println(a.modPow(c, b));
		}
	}
}