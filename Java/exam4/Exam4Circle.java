package exam4;
import exam2.*;

public class Exam4Circle extends Circle{
	
	@Override
	public boolean equals(Object arg0) {
		if(arg0 instanceof Exam4Circle) {
			return ((Exam4Circle)arg0).getCenter().equals(((Exam4Circle)arg0).getCenter());
		}
		return super.equals(arg0);
	}
	@Override
	public String toString() {
		return this.getCenter().toString()+" "+this.getRadiousm();
	}
	public Exam4Circle(int x,int y,int r) {
		super(x,y,r);
	}

}
