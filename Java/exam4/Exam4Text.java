package exam4;

public class Exam4Text {
	Exam4Circle text;
	Exam4Circle text1;
	public Exam4Text(){
		this.text=new Exam4Circle(1,2,3);
		this.text1=new Exam4Circle(1,2,3);
		if(text.equals(text1)) 
			System.out.println("��ͬ��Բ");
		else
			System.out.println("��ͬ��Բ");
		System.out.println(text.toString());
		System.out.println(text1.toString());
	}

}
