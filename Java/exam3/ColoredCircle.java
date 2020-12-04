package exam3;
import exam2.*;

public class ColoredCircle extends Circle{
	Color borderColor;
	Color centerColor;
	public ColoredCircle(){
		this(0,0,0,
				0,0,0,
				0,0,0);
	}
	public ColoredCircle(Point centerData,int radiousm){
		this(centerData.getX(),centerData.getY(),radiousm,
				0,0,0,
				0,0,0);
	}
	public ColoredCircle(Color centerColor,Color borderColor){
		this(0,0,0,
				centerColor.getRed(),centerColor.getGreen(),centerColor.getBlue(),
				borderColor.getRed(),borderColor.getGreen(),borderColor.getBlue());
	}
	public ColoredCircle(Point centerData,int radiousm,Color centerColor,Color borderColor){
		this(centerData.getX(),centerData.getY(),radiousm,
				centerColor.getRed(),centerColor.getGreen(),centerColor.getBlue(),
				borderColor.getRed(),borderColor.getGreen(),borderColor.getBlue());
	}
	public ColoredCircle(int x,int y,int radiousm,int r1,int g1,int b1,int r2,int g2,int b2){
		super(x,y,radiousm);
		this.borderColor=new Color(r1,g1,b1);
		this.centerColor=new Color(r2,g2,b2);
	}
	public Color getBorderColor() {
		return borderColor;
	}
	public void setBorderColor(Color borderColor) {
		this.borderColor = borderColor;
	}
	public Color getCenterColor() {
		return centerColor;
	}
	public void setCenterColor(Color centerColor) {
		this.centerColor = centerColor;
	}
	@Override
	public int circleRelation(Circle dataCircleIn) {
		int backData=super.circleRelation(dataCircleIn);
		if(backData==0&&(dataCircleIn instanceof ColoredCircle)) {
			if(((ColoredCircle)dataCircleIn).centerColor==this.centerColor) {
				return 0;
			}else {//Same value but has different color
				return 5;
			}
		}
		return backData;
	}
}
