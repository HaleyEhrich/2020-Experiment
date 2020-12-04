package exam1;
public class Exam1 {
	public void start() {
		this.func1();
		System.out.println();
		System.out.println("99乘法表");
		this.fuc2();
	}
	private void func1() {
		double j=1;
		for(int i=1;i<=20;++i) {
			j=j*i;
			System.out.println(i+"的阶乘为"+j);
		}
	}
	private void fuc2() {
		for(int i=1;i<10;++i) {
			for(int j=1;j<=i;++j) {
				System.out.print(j+"*"+i+"="+i*j+"\t");
			}System.out.println();
		}
	}
}
