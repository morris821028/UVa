import java.util.Scanner;
import java.math.BigDecimal;
import java.math.RoundingMode;

public class A204 {
	static BigDecimal order[] = new BigDecimal[500];
	
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		
		order[1] = new BigDecimal("1");
		for(int i = 2; i < 500; i++)
			order[i] = order[i-1].multiply(new BigDecimal(""+i));
		
		while(scanner.hasNext()) {
			String ans = sin(new BigDecimal(scanner.nextLine())).toString();
			
			if(ans.compareTo("0E-300") == 0)
				System.out.println("0.00000000000000000000000000000000000000000000000000");
			else
				System.out.println(ans.substring(0, ans.indexOf('.')+51));
		}
	}
	
	static BigDecimal sin(BigDecimal x) {
		BigDecimal ans = new BigDecimal(x.toString());
		
		for(int i = 3, flag = 0; i < 500; i += 2, flag = 1-flag) {
			if(flag == 0) {
				ans = ans.subtract(x.pow(i).divide(order[i], 300, RoundingMode.HALF_UP));
			} else {
				ans = ans.add(x.pow(i).divide(order[i], 300, RoundingMode.HALF_UP));
			}
		}
		
		return ans;
	}
}

