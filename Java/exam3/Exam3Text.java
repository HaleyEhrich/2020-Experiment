package exam3;
import keyInput.*;

public class Exam3Text {
	private void menu() {
		System.out.println("1:Set X value;");
		System.out.println("2:Set Y value;");
		System.out.println("3:Set radiousm value;");
		System.out.println("4:Set boreder color value;");
		System.out.println("5:Set center color value;");

		System.out.println("6:Get X value;");
		System.out.println("7:Get Y value;");
		System.out.println("8:Get radiousm value;");
		System.out.println("9:Get border color value;");
		System.out.println("10:Get center color value;");
		System.out.println("11:Get perimeter value;");
		System.out.println("12:Get area value;");

		System.out.println("13:Exit;");
	}

	private void PrintAll(ColoredCircle textCircle) {
		System.out.println("X value: " + textCircle.getCenter().getX());
		System.out.println("Y value: " + textCircle.getCenter().getY());
		System.out.println("Radiousm value: " + textCircle.getRadiousm());
		System.out.println("Red: " + textCircle.getBorderColor().getRed() + " Green: "
				+ textCircle.getBorderColor().getGreen() + " Blue: " + textCircle.getBorderColor().getGreen());
		System.out.println("Red: " + textCircle.getCenterColor().getRed() + " Green: "
				+ textCircle.getCenterColor().getGreen() + " Blue: " + textCircle.getCenterColor().getGreen());
		System.out.println("This Cirlce Perimter: " + textCircle.perimeter());
		System.out.println("This Cirlce Area: " + textCircle.area());
	}

	public void Start() {
		ColoredCircle textCircle = new ColoredCircle();
		ColoredCircle textCircle2 = new ColoredCircle(12, 34, 3, 0, 0, 0, 0, 0, 0);
		int choice = 0;
		while (choice != 13) {
			menu();
			choice=Key_io.cin();
			switch (choice) {
			case 1: {
				textCircle.setX();
				break;
			}
			case 2: {
				textCircle.setY();
				break;
			}
			case 3: {
				textCircle.setR();
				break;
			}
			case 4: {
				System.out.print("Input red,green,blue value:");
				textCircle.setBorderColor(new Color(Key_io.cin(), Key_io.cin(), Key_io.cin()));
				break;
			}
			case 5: {
				System.out.print("Input red,green,blue value:");
				textCircle.setBorderColor(new Color(Key_io.cin(), Key_io.cin(), Key_io.cin()));
				break;
			}
			case 6: {
				System.out.println("X value: " + textCircle.getCenter().getX());
				break;
			}
			case 7: {
				System.out.println("Y value: " + textCircle.getCenter().getY());
				break;
			}
			case 8: {
				System.out.println("Radiousm value: " + textCircle.getRadiousm());
				break;
			}
			case 9: {
				System.out.println("Red: " + textCircle.getBorderColor().getRed() + " Green: "
						+ textCircle.getBorderColor().getGreen() + " Blue: " + textCircle.getBorderColor().getGreen());
				break;
			}
			case 10: {
				System.out.println("Red: " + textCircle.getCenterColor().getRed() + " Green: "
						+ textCircle.getCenterColor().getGreen() + " Blue: " + textCircle.getCenterColor().getGreen());
				break;
			}
			case 11: {
				System.out.println("This Cirlce Perimter: " + textCircle.perimeter());
				break;
			}
			case 12: {
				System.out.println("This Cirlce Area: " + textCircle.area());
				break;
			}
			}
		}
		this.PrintAll(textCircle);
		this.PrintAll(textCircle2);
		System.out.println("Relation bewteen circle and circle2: ");
		switch(textCircle.circleRelation(textCircle2)) {
		case 0:{
			System.out.println("相同的圆");
			break;
		}
		case 1:{
			System.out.println("同心圆");
			break;
		}
		case 2:{
			System.out.println("相交的圆");
			break;
		}
		case 3:{
			System.out.println("分离的圆");
			break;
		}
		case 4:{
			System.out.println("包含的圆");
			break;
		}
		case 5:{
			System.out.println("中心颜色不同");
			break;
		}
		}
	}
}
