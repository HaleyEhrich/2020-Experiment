public class Exam1 {
	public void func1() {
		double j=1;
		for(int i=1;i<=20;++i) {
			j=j*i;
			System.out.println(i+"µÄ½×³ËÎª"+j);
		}
	}
	public void fuc2() {
		for(int i=1;i<10;++i) {
			for(int j=1;j<=i;++j) {
				System.out.print(j+"*"+i+"="+i*j+"\t");
			}System.out.println();
		}
	}
}
