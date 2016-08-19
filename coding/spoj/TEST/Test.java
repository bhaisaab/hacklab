import java.util.*;
import java.lang.*;

class Test {
	public static void main (String[] args) throws java.lang.Exception {
		Scanner scan = new Scanner(System.in);
		while(scan.hasNext()) {
			int i = scan.nextInt();
			if (i == 42) {
				break;
			}
			System.out.println(i);
		}	
		scan.close();	
	}
}
