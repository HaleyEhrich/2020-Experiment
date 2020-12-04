package exam2;
import keyInput.*;

public class Circle {
	private Point center;
	private int radiousm;
	public Circle() {
		this(0,0,0);
	}
	public Circle(Point centerData) {
		this(centerData.getX(),centerData.getY(),0);
	}
	public Circle(Point centerData,int radiousm) {
		this(centerData.getX(),centerData.getY(),radiousm);
	}
	public Circle(int xInput,int yInpute,int rInput) {
		if(rInput<0) 
			return;
		this.center=new Point(xInput,yInpute);
		this.radiousm=rInput;
	}
	public void setR() {
		System.out.print("输入半径R:");
		Key_io cin=new Key_io();
		radiousm=cin.nextInt();
		if(radiousm>=0) {
			this.radiousm=radiousm;
		}
	}
	public void setX() {
		this.center.setX();
	}
	public void setY() {
		this.center.setY();
	}
		public Point getCenter() {
		return center;
	}
	public int getRadiousm() {
		return radiousm;
	}
	public double  perimeter() {
		return (double)this.radiousm*Math.PI*2;
	}
	public double area() {
		return (double)Math.pow(radiousm, 2)*Math.PI;
	}
	public int circleRelation(Circle dataCircleIn) {
		if(dataCircleIn.radiousm==this.radiousm && dataCircleIn.center.getX()==this.center.getX() 
				&& dataCircleIn.center.getY()==this.center.getY()) {//相同的圆
			return 0;
		}else if(dataCircleIn.radiousm!=this.radiousm && dataCircleIn.center.getX()==this.center.getX() 
				&& dataCircleIn.center.getY()==this.center.getY()) {//同心圆
			return 1;
		}else if(Math.sqrt(Math.pow(this.center.getX()-dataCircleIn.center.getX(), 2) + Math.pow(this.center.getY()-dataCircleIn.center.getY(), 2))
				< Math.max(this.radiousm/2, dataCircleIn.radiousm/2)) {
			return 4;
			
		}else if(Math.sqrt(Math.pow(this.center.getX()-dataCircleIn.center.getX(), 2) + Math.pow(this.center.getY()-dataCircleIn.center.getY(), 2)) 
				< this.radiousm+dataCircleIn.radiousm) {//相交的圆
			return 2;
		}else if(Math.sqrt(Math.pow(this.center.getX()-dataCircleIn.center.getX(), 2) + Math.pow(this.center.getY()-dataCircleIn.center.getY(), 2)) 
				> this.radiousm+dataCircleIn.radiousm) {//分离的圆
			return 3;
		}
		return -1;
	}
}
