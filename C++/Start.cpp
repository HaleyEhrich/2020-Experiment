#include <iostream>
#include<Windows.h>
#include "Stack_chara.h"
using namespace std;

void menu() {
	cout << "--------------------------------" << endl;
	cout << "\t表达式求值" << endl;
	cout << "1: 中缀表达式到后缀表达式的转换" << endl;
	cout << "2: 后缀表达式的求解" << endl;
	cout << "3: 中缀表达式的计算" << endl;
	cout << "4: 退出" << endl;
	cout << "--------------------------------" << endl;
	cout << "输入你的选择:";
}
double CharToNum(string& Data,int& i) {
	double LeftNum = 0, RightNum = 0, j = 0.1;
	while (Data[i] <= '9' && Data[i] >= '0') {
		LeftNum = LeftNum * 10 + (double)Data[i++] - '0';
	}
	if (Data[i] == '.') {
		++i;
		while (i<Data.length() && Data[i] <= '9' && Data[i] >= '0') {
			RightNum += ((double)Data[i++] - '0') * j;
			j *= 0.1;
		}
	}
	return LeftNum + RightNum;
}

StackChara* MidLastCon() {
	string Data;
	cout << "输入数据:";
	cin >> Data;
	StackChara* BackData = new StackChara();
	StackChara* StoreTempData = new StackChara();
	double PriorityBase=0;
	char Chara=(char)0;
	int StateNum=0;//0 means don't have left number, 1 means has left number
	double Num=0;
	int flag=0;
	for (int i = 0; i < Data.length();) {
		//7+8*(9-2)/((5-2)/(6-3))+(((-1)/2+3)/5+6)/7
		if (Data[i] >= '0' && Data[i] <= '9') {//Number situaion
			if ((int)Chara) {
				//cout << "AAA" << endl;
				Num = CharToNum(Data, i);
				if (Chara == '/' && Num == 0) {
					cout << "0不可作为除数:";
					for (int j = 0; j <= i; ++j) {
						cout << Data[j];
					}cout << endl;
					for (int j = 0; j < i + 13; ++j)cout << ' ';
					cout << '^' << '$' << endl;
					return NULL;
				}
				BackData->AddData(Num);
				BackData->AddData(Chara);
				if (StoreTempData->GetTopNumData() == PriorityBase) {
					StoreTempData->PopTopData();
					BackData->AddData(StoreTempData->GetTOP());
					StoreTempData->PopTopData();
				}
				if (flag)flag = 0;
				Chara = (char)0;
			}
			else {
				//cout << "BBB" << endl;
				Num = CharToNum(Data, i);
				BackData->AddData(Num);
				StateNum = 1;
			}
		}
		else {//Chara situation
			//cout << Data[i] << endl;
			if (Data[i] == '-' || Data[i] == '+' || Data[i] == '/' || Data[i] == '*') {
				if ((Data[i] == '-' || Data[i] == '+') && StateNum == 0) {//Negative or clear positive
					//cout << "CCC" << endl;
					if (Data[i++] == '-') {
						if (Data[i] <= '9' && Data[i] >= '0') {
							Num = CharToNum(Data, i);
							Num *= -1;
							BackData->AddData(Num);
							StateNum = 1;
						}
						else {
							cout << Data[i] << "左边缺失操作数：";
							for (int j = 0; j <= i; ++j) {
								cout << Data[j];
							}cout << endl;
							for (int j = 0; j < i + 17; ++j)cout << ' ';
							cout << '^' << '$' << endl;
							return NULL;
						}
					}
				}
				else {
					//cout << "DDD" << endl;
					if ((int)Chara) {
						cout << Data[i] << "左边缺失操作数：";
						for (int j = 0; j <= i; ++j) {
							cout << Data[j];
						}cout << endl;
						for (int j = 0; j < i + 17; ++j)cout << ' ';
						cout << '^' << '$' << endl;
						return NULL;
					}
					Chara = Data[i++];//Store the chara first
					if (BackData->GetTopPriority() == 1 && (Chara == '/' || Chara == '*') && !flag ) {//The chara store in print stack priority is small than this , and it should pop
						StoreTempData->AddData(BackData->GetTOP());
						StoreTempData->AddData(PriorityBase);
						BackData->PopTopData();
					}
				}
			}
			else if (Data[i] == '(') {
				//cout << "EEE" << endl;
				++i;
				if ((int)Chara) {
					StoreTempData->AddData(Chara);
					StoreTempData->AddData(PriorityBase);
					Chara = (char)0;
				}
				else {
					if (BackData->StackEmpty() && Data[i - 2] != '(') {//必为头
						cout << "缺失运算符:";
						for (int j = 0; j < i; ++j) {
							cout << Data[j];
						}cout << endl;
						for (int j = 0; j < i + 10; ++j)cout << ' ';
						cout << '^' << '$' << endl;
						return NULL;
					}
				}
				PriorityBase += 1;
				StateNum = 0;
				Num = 0;
			}
			else if (Data[i] == ')') {
				//cout << "FFF" << endl;
				++i;
				flag = 1;
				if ((int)Chara) {
					cout << "缺失操作数:";
					for (int j = 0; j < i; ++j) {
						cout << Data[j];
					}cout << endl;
					for (int j = 0; j < i + 10; ++j)cout << ' ';
					cout << '^' << '$' << endl;
					return NULL;
				}
				while (StoreTempData->GetTopNumData() > PriorityBase) {
					StoreTempData->PopTopData();
					BackData->AddData(StoreTempData->GetTOP());
					StoreTempData->PopTopData();
				}--PriorityBase;
				while (StoreTempData->GetTopNumData() >= PriorityBase) {
					StoreTempData->PopTopData();
					BackData->AddData(StoreTempData->GetTOP());
					StoreTempData->PopTopData();
					flag = 0;
				}
				StateNum = 1;
			}
		}
		//处理括号后的优先级
		cout << "剩余待处理:";
		for (int j = i; j < Data.length(); ++j) {
			cout << Data[j];
		}//cout << endl;
		cout << "输出内容: ";
		BackData->out();
		cout << "临时内容: ";
		StoreTempData->out();
		cout << endl;
		//cout << "Chara  " << Chara << endl;
		//cout << "Pri  " << PriorityBase << endl;
		//cout << "Num  " << Num << endl;
		//cout << "State " << StateNum << endl;
	}
	if (PriorityBase != 0) {
		cout << Data << endl;
		cout << "括号不匹配" << endl;
	}
	else {
		cout << endl;
		cout << "原始中缀数据:" << Data << endl;
		cout << "转换后数据:";
		BackData->out();
		cout << endl;
	}
	return BackData;
	//for (int i=0; i < Data.length();) {
	//	if (Data[i] >= '0' && Data[i] <= '9') {//Num
	//		if ((int)Chara > 0) {//左操作数存在，换言之此时键入的是右操作数，需要将符号压入栈
	//			Num = CharToNum(Data, i);//操作数读取，转换到DOUBLE
	//			if (Chara == '/' && Num == 0) {
	//				cout << "0不可作为除数:";
	//				for (int j = 0; j <= i; ++j) {
	//					cout << Data[j];
	//				}cout << endl;
	//				for (int j = 0; j < i + 13; ++j)cout << ' ';
	//				cout << '^' << '$' << endl;
	//				return NULL;
	//			}
	//			Last->AddData(Num);//压入右操作数
	//			Last->AddData(Chara);//压入运算符号
	//			if (StoreTempData->TopPriority() ==1 && Data[i] != ')' ) {//优先级补足，若存在1优先级的操作符，存入1优先级符号
	//				Last->AddData(StoreTempData->GetTOP());
	//				StoreTempData->PopTopData();
	//			}
	//			if (Flag)Flag = 0;
	//			Chara = (char)0;
	//		}
	//		else {//此时输入的为左操作数
	//			Num = CharToNum(Data, i);
	//			Last->AddData(Num);//压入左操作数
	//		}
	//	}
	//	else {//Chara
	//		if (Data[i] == '-' || Data[i] == '*' || Data[i] == '/' || Data[i] == '+' ) {
	//			if ((Data[i] == '-'|| Data[i]=='+') && (Last->GetType() == CHARATYPE || Num == 0 )) {//|| (int)Chara > 0 这个判定条件可考虑，主要是添加后如何处理
	//				if (Data[i] == '-') {
	//					Num = CharToNum(Data, ++i);
	//					Num *= -1;
	//					Last->AddData(Num);//Note double type value
	//				}
	//				else {
	//					++i;
	//				}
	//			}else {//正常符号的出现
	//				if ((int)Chara>0) {//判断正确与否
	//					cout << Data[i] << "左边缺失操作数：";
	//					for (int j = 0; j <= i;++j) {
	//						cout << Data[j];
	//					}cout << endl;
	//					for (int j = 0; j < i + 17; ++j)cout << ' ';
	//					cout << '^' << '$' << endl;
	//					return NULL;
	//				}
	//				Chara = Data[i++];//存储
	//				if (Last->TopPriority() == 1 && (Chara == '/' || Chara == '*') && Flag == 0) {//判断优先级
	//					StoreTempData->AddData(Last->GetTOP());
	//					Last->PopTopData();
	//				}
	//			}
	//		}
	//		else if (Data[i] == '(') {
	//			++i;
	//			++Flag_Left;
	//			if ((int)Chara > 0) {//存在符号，存储于临时栈内
	//				StoreTempData->AddData(Chara);
	//				Chara = (char)0;
	//			}
	//			else {//不含有符号未存储
	//				if (Last->StackEmpty() && Data[i-2]!='(' ) {//必为头
	//					cout << "缺失运算符:";
	//					for (int j = 0; j < i;++j) {
	//						cout << Data[j];
	//					}cout << endl;
	//					for (int j = 0; j < i + 10; ++j)cout << ' ';
	//					cout << '^' << '$' << endl;
	//					return NULL;
	//				}
	//				else {
	//					StoreTempData->AddData('(');
	//				}
	//			}
	//			Num = 0;//Means a new term, Num data will store when it be scnnaed
	//		}
	//		else if(Data[i]==')'){
	//			--Flag_Left;
	//			if (Chara) {
	//				cout << "缺失运算符:";
	//				for (int j = 0; j < i; ++j) {
	//					cout << Data[j];
	//				}cout << endl;
	//				for (int j = 0; j < i + 10; ++j)cout << ' ';
	//				cout << '^' << '$' << endl;
	//				return NULL;
	//			}
	//			++i; Num = 1;//恢复含有左操作数
	//			Flag = 1;
	//			if (StoreTempData->StackEmpty()) {//避免出空栈
	//				StackCharaNode ttt= StoreTempData->GetTOP();
	//				if (ttt.PopChara() != '(') {
	//					Last->AddData(StoreTempData->GetTOP());
	//				}
	//				StoreTempData->PopTopData();
	//				Flag = 0;
	//			}
	//			if (StoreTempData->TopPriority() == 1) {//此处需要是因为（默认压出一个操作符，在上面出栈后，若还存在1级优先级符号则需要出栈
	//				Last->AddData(StoreTempData->GetTOP());
	//				StoreTempData->PopTopData();
	//				Flag = 0;
	//			}
	//		}
	//	}
	//	cout << "输出内容: " ;
	//	Last->out();
	//	cout << "临时内容: ";
	//	StoreTempData->out();
	//	//cout << Flag << endl;
	//	//cout << Chara << "Chara" << endl;
	//	//cout << Num << "Num" << endl;
	//}                                 
	//if (StoreTempData->StackEmpty() || Flag_Left) {
	//	cout << Data << endl;
	//	cout << "表达式错误" << endl;
	//	return NULL;
	//}
	//else {
	//	cout << Data << endl;
	//	Last->out();
	//}
}

double Equaltion(double& LeftNum, double& RightNum,char& Chara) {
	double Back=0.0;
	switch (Chara)
	{
	case '-':
		Back = LeftNum - RightNum;
		break;
	case'+':
		Back = LeftNum + RightNum;
		break;
	case '/':
		if (RightNum == 0) {
			cout << "0不可作为被除数" << endl;
			exit(1);
		}else{
			Back = LeftNum / RightNum;
		}
		break;
	case '*':
		Back = LeftNum * RightNum;
		break;
	}
	//cout << LeftNum << ' ' << RightNum << ' ' << Chara << ' ' << Back << endl;
	RightNum = 0.0;
	return Back;
}
double RightSolve(double& LeftNum, StackChara* Data) {
	double RightNum;
	char Chara;
	double Back=0.0;
	if (Data->GetFirstType() == NUMTYPE) {
		RightNum = Data->GetFirstNumData();
		Data->PopFirstData();
	}
	if (Data->GetFirstType() == NUMTYPE) {
		RightNum = RightSolve(RightNum, Data);
	}
	if (Data->GetFirstType() == CHARATYPE) {
		Chara = Data->GetFirstChara();
		Data->PopFirstData();
		Back = Equaltion(LeftNum, RightNum, Chara);
	}
	return Back;
}
double LastCau(StackChara* Data) {
	if (Data == NULL) {
		return 0;
	}
	//cout << "Lastcau" << endl;
	double Back=0.0;
	double LeftNum=0.0, RightNum=0.0;
	char Chara;
	while (Data->StackEmpty()) {
		if (Data->GetFirstType()==NUMTYPE) {
			if (Back == 0) {
				Back = Data->GetFirstNumData();
				Data->PopFirstData();
			}
			else {
				if (RightNum) {
					RightNum=RightSolve(RightNum, Data);
				}
				else {
					RightNum = Data->GetFirstNumData();
					Data->PopFirstData();
				}
			}
		}
		else if (Data->GetFirstType() == CHARATYPE) {
			Chara = Data->GetFirstChara();
			Data->PopFirstData();
			Back=Equaltion(Back, RightNum, Chara);
		}
	}
	cout << "求解结果: " << Back << endl;
	return Back;
}

bool BracketMatching(string& Data) {
	int Count = 0;
	for (int i = 0; i < Data.length(); ++i) {
		if (Data[i] == '(') {
			++Count;
		}
		else if(Data[i]==')'){
			if (Count) {
				--Count;
			}
			else {
				return 1;
			}
		}
	}
	if (Count) {
		return 1;
	}
	return 0;
}

double RightSolve(double Back,string& Data, int& i) {
	char Chara;
	double RightNum=0.0;
	if (Back) {
		while (i < Data.length() && (Data[i] != '+' && Data[i] != '-' && Data[i] != ')')) {
			if (Data[i] <= '9' && Data[i] >= '0') {
				RightNum = CharToNum(Data, i);
				if (i < Data.length()) {
					if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//优先级
						RightNum = RightSolve(RightNum, Data, i);
					}
				}
				Back = Equaltion(Back, RightNum, Chara);
				//Chara = (char)0;
			}
			else {
				Chara = Data[i++];
				if (Chara == '-' && Back == 0.0) {//负数
					Back = CharToNum(Data, i);
					Back *= -1;
					Chara = (char)0;
				}
				else {
					if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
						i - 2 >= 0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//前一个也为符号
						cout << "缺失操作数:";
						for (int j = 0; j < i; ++j) {
							cout << Data[j];
						}cout << endl;
						for (int j = 0; j < i + 10; ++j)cout << ' ';
						cout << '^' << '$' << endl;
						exit(1);
					}
					if (Chara == '(') {
						if (Back) {
							if (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/') {
								Chara = Data[i - 2];
								RightNum = RightSolve(0.0, Data, i);
								Back = Equaltion(Back, RightNum, Chara);
							}
							else {
								cout << "缺失运算符:";
								for (int j = 0; j < i; ++j) {
									cout << Data[j];
								}cout << endl;
								for (int j = 0; j < i + 10; ++j)cout << ' ';
								cout << '^' << '$' << endl;
								exit(1);
							}
						}
						else {
							Back = RightSolve(0.0, Data, i);
						}
					}
				}
			}
		}
	}
	else {
		while (i < Data.length() && Data[i] != ')') {
			if (Data[i] <= '9' && Data[i] >= '0') {
				if (Back) {//左操作数存在
					RightNum = CharToNum(Data, i);
					if (i < Data.length()) {
						if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//优先级
							RightNum = RightSolve(RightNum, Data, i);
						}
					}
					Back = Equaltion(Back, RightNum, Chara);
					Chara = (char)0;
				}
				else {//左操作数不存在
					Back = CharToNum(Data, i);
				}
			}
			else {
				Chara = Data[i++];
				if (Chara == '-' && Back == 0.0) {//负数
					Back = CharToNum(Data, i);
					Back *= -1;
					Chara = (char)0;
				}
				else {
					if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
						i - 2 >= 0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//前一个也为符号
						cout << "缺失操作数:";
						for (int j = 0; j < i; ++j) {
							cout << Data[j];
						}cout << endl;
						for (int j = 0; j < i + 10; ++j)cout << ' ';
						cout << '^' << '$' << endl;
						exit(1);
					}
					if (Chara == '(') {
						if (Back) {
							if (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/') {
								Chara = Data[i - 2];
								RightNum = RightSolve(0.0, Data, i);
								Back = Equaltion(Back, RightNum, Chara);
							}
							else {
								cout << "缺失运算符:";
								for (int j = 0; j < i; ++j) {
									cout << Data[j];
								}cout << endl;
								for (int j = 0; j < i + 10; ++j)cout << ' ';
								cout << '^' << '$' << endl;
								exit(1);
							}
						}
						else {
							Back = RightSolve(0.0, Data, i);
						}
					}
				}
			}
		}
	}
	return Back;
}
double MidCau() {
	string Data;
	cout << "输入数据:";
	cin >> Data;
	if (BracketMatching(Data)) {
		cout << "括号不匹配" << endl;
		exit(1);
	}
	double RightNum = 0.0;
	double Back=0.0;
	char Chara = (char)0, Chara2 = (char)0;
	for (int i = 0; i < Data.length();) {
		if (Data[i] <= '9' && Data[i] >= '0') {
			if (Back) {//左操作数存在
				RightNum = CharToNum(Data, i);
				if (i < Data.length()) {
					//Chara2 = Data[i];
					if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//优先级
						RightNum = RightSolve(RightNum, Data, i);
					}
				}
				Back = Equaltion(Back, RightNum, Chara);
				//Chara = (char)0;
			}
			else {//左操作数不存在
				Back= CharToNum(Data, i);
			}
		}
		else {
			Chara = Data[i++];
			if (Chara == '-' && Back == 0.0) {//负数
				Back = CharToNum(Data, i);
				Back *= -1;
				Chara = (char)0;
			}
			else {
				if (i == 1 && (Chara == '*' || Chara == '/')) {
					cout << "缺失操作数:";
					for (int j = 0; j < i; ++j) {
						cout << Data[j];
					}cout << endl;
					for (int j = 0; j < i + 10; ++j)cout << ' ';
					cout << '^' << '$' << endl;
					exit(1);
				}
				if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
					i-2>=0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//前一个也为符号
					cout << "缺失操作数:";
					for (int j = 0; j < i; ++j) {
						cout << Data[j];
					}cout << endl;
					for (int j = 0; j < i + 10; ++j)cout << ' ';
					cout << '^' << '$' << endl;
					exit(1);
				}
				if (Chara == '(') {
					if (Back) {
						if (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/') {
							Chara = Data[i - 2];
							RightNum = RightSolve(0.0, Data, i);
							Back = Equaltion(Back, RightNum, Chara);
						}
						else {
							cout << "缺失运算符:";
							for (int j = 0; j < i; ++j) {
								cout << Data[j];
							}cout << endl;
							for (int j = 0; j < i + 10; ++j)cout << ' ';
							cout << '^' << '$' << endl;
							exit(1);
						}
					}
					else {
						Back = RightSolve(0.0, Data, i);
					}
				}
			}
			
		}
	}
	return Back;
}

int main() {
	char Choice='1';
	while (Choice!='4') {
		menu();
		cin >> Choice;
		switch (Choice)
		{
		case '1': {
			MidLastCon();
			system("Pause");
			system("cls");
			break;
		}
		case '2': {
			LastCau(MidLastCon());
			system("Pause");
			system("cls");
			break;
		}
		case '3': {
			cout << MidCau() << endl;
			system("Pause");
			system("cls");
			break;
		}
		case '4': {
			cout << "谢谢您的使用" << endl;
			break;
		}
		default: {
			cout << "选择有误" << endl;
			system("Pause");
			system("cls");
			break;
		}
		}
	}
	return 0;
	
}