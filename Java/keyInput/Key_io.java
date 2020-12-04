package keyInput;
import java.util.Scanner;
public class Key_io {
	Scanner sc=new Scanner(System.in);
	public static int cin() {
		Scanner sc=new Scanner(System.in);
		return sc.nextInt();
	}
	public int nextInt() {
		//System.out.print("Please input an int type data:");
		return sc.nextInt();
	}
	public float nextFloat() {
		//System.out.print("Please input an float type data:");
		return sc.nextFloat();
	}
	public double nextDouble() {
		//System.out.print("Please input an double type data:");
		return sc.nextDouble();
	}
	public long nextLong() {
		//System.out.print("Please input an long type data:");
		return sc.nextLong();
	}
	public String nextString() {
		//System.out.print("Please input an string type data:");
		String backData;
		backData = sc.nextLine();
		if(backData.length()==0) {
			return sc.nextLine();
		}else {
			return backData;
		}
	}
}
