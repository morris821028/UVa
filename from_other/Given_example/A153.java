import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class A153 {
    public static void main(String[] args) {
        BufferedReader scanner = new BufferedReader(new InputStreamReader(System.in));
        char ch;
        
        int numbers[] = new int[500000];
        int index = 0;
        int flag = 0;
        
        try {
            while(true) {
                ch = (char)scanner.read();
				
                if(ch == ' ') {
                    flag = 0;
                    index++;
                } else if(Character.isDigit(ch)) {
                    flag = 1;
                    numbers[index] = numbers[index]*10+ch-'0';
                } else {
					index += flag;
					break;
				}
            }
        } catch(IOException e) {
            e.printStackTrace();
        }
        
        java.util.Arrays.sort(numbers);
        
        for(int i = numbers.length-index; i < numbers.length; i++)
            System.out.print(numbers[i]+" ");
    }
}

