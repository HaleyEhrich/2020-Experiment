package exam2;
import keyInput.Key_io;

public class Point {
	private int x;
	private int y;
	public Point(){
		this(0,0);
	}
	public Point(Point centerPoint) {
		this(centerPoint.x,centerPoint.y);
	}
	public Point(int _x,int _y){
		this.x=_x;
		this.y=_y;
	}
	public int getX() {
		return this.x;
	}
	public int getY() {
		return this.y;
	}
	public void setX(int _x) {
		this.x=_x;
	}
	public void setX() {
		System.out.print("请输入X坐标的值:");
		Key_io a=new Key_io();
		System.out.println();
		this.x=a.nextInt();
	}
	public void setY(int _y) {
		this.y=_y;
	}
	public void setY() {
		System.out.print("请输入Y坐标的值:");
		Key_io a=new Key_io();
		System.out.println();
		this.y=a.nextInt();
	}
	public void setPoint(Point DataIn) {
		this.x=DataIn.x;
		this.y=DataIn.y;
	}
	public double distanceXY() {
		return Math.sqrt((double)(this.x*this.x+y*y));
	}
	public double distance(Point Datain) {
		return Math.sqrt(Math.pow(this.x-Datain.x, 2)+Math.pow(this.y-Datain.y, 2));
	}
	public void print() {
		System.out.println("X's value "+this.x+" Y's value "+this.y);
		System.out.println("Distance from (0,0): "+this.distanceXY());
	}
}