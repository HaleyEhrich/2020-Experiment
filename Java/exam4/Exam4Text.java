package exam4;

public class Exam4Text {
	Exam4Circle text;
	Exam4Circle text1;
	public Exam4Text(){
		this.text=new Exam4Circle(1,2,3);
		this.text1=new Exam4Circle(1,2,3);
		if(text.equals(text1)) 
			System.out.println("相同的圆");
		else
			System.out.println("不同的圆");
		System.out.println(text.toString());
		System.out.println(text1.toString());
	}

}
