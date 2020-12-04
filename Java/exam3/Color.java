package exam3;

public class Color {
	private int red;
	private int blue;
	private int green;
	public Color(){
		this(0,0,0);
	}
	public Color(int r,int g,int b){
		if(r<0||r>255||g<0||b<0||g>255||b>255) {
			return;
		}
		this.red=r;
		this.green=g;
		this.blue=b;
	}
	public int getRed() {
		return red;
	}
	public void setRed(int red) {
		if(red>=0&&red<=255)
			this.red = red;
	}
	public int getBlue() {
		return blue;
	}
	public void setBlue(int blue) {
		if(blue>=0&&blue>=0)
			this.blue = blue;
	}
	public int getGreen() {
		return green;
	}
	public void setGreen(int green) {
		if(green>=0&&green<=255)
			this.green = green;
	}
}
