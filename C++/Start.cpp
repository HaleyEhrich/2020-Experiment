#include <iostream>
#include<Windows.h>
#include "Stack_chara.h"
using namespace std;

void menu() {
	cout << "--------------------------------" << endl;
	cout << "\t���ʽ��ֵ" << endl;
	cout << "1: ��׺���ʽ����׺���ʽ��ת��" << endl;
	cout << "2: ��׺���ʽ�����" << endl;
	cout << "3: ��׺���ʽ�ļ���" << endl;
	cout << "4: �˳�" << endl;
	cout << "--------------------------------" << endl;
	cout << "�������ѡ��:";
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
	cout << "��������:";
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
					cout << "0������Ϊ����:";
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
							cout << Data[i] << "���ȱʧ��������";
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
						cout << Data[i] << "���ȱʧ��������";
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
					if (BackData->StackEmpty() && Data[i - 2] != '(') {//��Ϊͷ
						cout << "ȱʧ�����:";
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
					cout << "ȱʧ������:";
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
		//�������ź�����ȼ�
		cout << "ʣ�������:";
		for (int j = i; j < Data.length(); ++j) {
			cout << Data[j];
		}//cout << endl;
		cout << "�������: ";
		BackData->out();
		cout << "��ʱ����: ";
		StoreTempData->out();
		cout << endl;
		//cout << "Chara  " << Chara << endl;
		//cout << "Pri  " << PriorityBase << endl;
		//cout << "Num  " << Num << endl;
		//cout << "State " << StateNum << endl;
	}
	if (PriorityBase != 0) {
		cout << Data << endl;
		cout << "���Ų�ƥ��" << endl;
	}
	else {
		cout << endl;
		cout << "ԭʼ��׺����:" << Data << endl;
		cout << "ת��������:";
		BackData->out();
		cout << endl;
	}
	return BackData;
	//for (int i=0; i < Data.length();) {
	//	if (Data[i] >= '0' && Data[i] <= '9') {//Num
	//		if ((int)Chara > 0) {//����������ڣ�����֮��ʱ��������Ҳ���������Ҫ������ѹ��ջ
	//			Num = CharToNum(Data, i);//��������ȡ��ת����DOUBLE
	//			if (Chara == '/' && Num == 0) {
	//				cout << "0������Ϊ����:";
	//				for (int j = 0; j <= i; ++j) {
	//					cout << Data[j];
	//				}cout << endl;
	//				for (int j = 0; j < i + 13; ++j)cout << ' ';
	//				cout << '^' << '$' << endl;
	//				return NULL;
	//			}
	//			Last->AddData(Num);//ѹ���Ҳ�����
	//			Last->AddData(Chara);//ѹ���������
	//			if (StoreTempData->TopPriority() ==1 && Data[i] != ')' ) {//���ȼ����㣬������1���ȼ��Ĳ�����������1���ȼ�����
	//				Last->AddData(StoreTempData->GetTOP());
	//				StoreTempData->PopTopData();
	//			}
	//			if (Flag)Flag = 0;
	//			Chara = (char)0;
	//		}
	//		else {//��ʱ�����Ϊ�������
	//			Num = CharToNum(Data, i);
	//			Last->AddData(Num);//ѹ���������
	//		}
	//	}
	//	else {//Chara
	//		if (Data[i] == '-' || Data[i] == '*' || Data[i] == '/' || Data[i] == '+' ) {
	//			if ((Data[i] == '-'|| Data[i]=='+') && (Last->GetType() == CHARATYPE || Num == 0 )) {//|| (int)Chara > 0 ����ж������ɿ��ǣ���Ҫ����Ӻ���δ���
	//				if (Data[i] == '-') {
	//					Num = CharToNum(Data, ++i);
	//					Num *= -1;
	//					Last->AddData(Num);//Note double type value
	//				}
	//				else {
	//					++i;
	//				}
	//			}else {//�������ŵĳ���
	//				if ((int)Chara>0) {//�ж���ȷ���
	//					cout << Data[i] << "���ȱʧ��������";
	//					for (int j = 0; j <= i;++j) {
	//						cout << Data[j];
	//					}cout << endl;
	//					for (int j = 0; j < i + 17; ++j)cout << ' ';
	//					cout << '^' << '$' << endl;
	//					return NULL;
	//				}
	//				Chara = Data[i++];//�洢
	//				if (Last->TopPriority() == 1 && (Chara == '/' || Chara == '*') && Flag == 0) {//�ж����ȼ�
	//					StoreTempData->AddData(Last->GetTOP());
	//					Last->PopTopData();
	//				}
	//			}
	//		}
	//		else if (Data[i] == '(') {
	//			++i;
	//			++Flag_Left;
	//			if ((int)Chara > 0) {//���ڷ��ţ��洢����ʱջ��
	//				StoreTempData->AddData(Chara);
	//				Chara = (char)0;
	//			}
	//			else {//�����з���δ�洢
	//				if (Last->StackEmpty() && Data[i-2]!='(' ) {//��Ϊͷ
	//					cout << "ȱʧ�����:";
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
	//				cout << "ȱʧ�����:";
	//				for (int j = 0; j < i; ++j) {
	//					cout << Data[j];
	//				}cout << endl;
	//				for (int j = 0; j < i + 10; ++j)cout << ' ';
	//				cout << '^' << '$' << endl;
	//				return NULL;
	//			}
	//			++i; Num = 1;//�ָ������������
	//			Flag = 1;
	//			if (StoreTempData->StackEmpty()) {//�������ջ
	//				StackCharaNode ttt= StoreTempData->GetTOP();
	//				if (ttt.PopChara() != '(') {
	//					Last->AddData(StoreTempData->GetTOP());
	//				}
	//				StoreTempData->PopTopData();
	//				Flag = 0;
	//			}
	//			if (StoreTempData->TopPriority() == 1) {//�˴���Ҫ����Ϊ��Ĭ��ѹ��һ�����������������ջ����������1�����ȼ���������Ҫ��ջ
	//				Last->AddData(StoreTempData->GetTOP());
	//				StoreTempData->PopTopData();
	//				Flag = 0;
	//			}
	//		}
	//	}
	//	cout << "�������: " ;
	//	Last->out();
	//	cout << "��ʱ����: ";
	//	StoreTempData->out();
	//	//cout << Flag << endl;
	//	//cout << Chara << "Chara" << endl;
	//	//cout << Num << "Num" << endl;
	//}                                 
	//if (StoreTempData->StackEmpty() || Flag_Left) {
	//	cout << Data << endl;
	//	cout << "���ʽ����" << endl;
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
			cout << "0������Ϊ������" << endl;
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
	cout << "�����: " << Back << endl;
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
					if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//���ȼ�
						RightNum = RightSolve(RightNum, Data, i);
					}
				}
				Back = Equaltion(Back, RightNum, Chara);
				//Chara = (char)0;
			}
			else {
				Chara = Data[i++];
				if (Chara == '-' && Back == 0.0) {//����
					Back = CharToNum(Data, i);
					Back *= -1;
					Chara = (char)0;
				}
				else {
					if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
						i - 2 >= 0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//ǰһ��ҲΪ����
						cout << "ȱʧ������:";
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
								cout << "ȱʧ�����:";
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
				if (Back) {//�����������
					RightNum = CharToNum(Data, i);
					if (i < Data.length()) {
						if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//���ȼ�
							RightNum = RightSolve(RightNum, Data, i);
						}
					}
					Back = Equaltion(Back, RightNum, Chara);
					Chara = (char)0;
				}
				else {//�������������
					Back = CharToNum(Data, i);
				}
			}
			else {
				Chara = Data[i++];
				if (Chara == '-' && Back == 0.0) {//����
					Back = CharToNum(Data, i);
					Back *= -1;
					Chara = (char)0;
				}
				else {
					if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
						i - 2 >= 0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//ǰһ��ҲΪ����
						cout << "ȱʧ������:";
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
								cout << "ȱʧ�����:";
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
	cout << "��������:";
	cin >> Data;
	if (BracketMatching(Data)) {
		cout << "���Ų�ƥ��" << endl;
		exit(1);
	}
	double RightNum = 0.0;
	double Back=0.0;
	char Chara = (char)0, Chara2 = (char)0;
	for (int i = 0; i < Data.length();) {
		if (Data[i] <= '9' && Data[i] >= '0') {
			if (Back) {//�����������
				RightNum = CharToNum(Data, i);
				if (i < Data.length()) {
					//Chara2 = Data[i];
					if ((Data[i] == '*' || Data[i] == '/') && (Chara == '-' || Chara == '+')) {//���ȼ�
						RightNum = RightSolve(RightNum, Data, i);
					}
				}
				Back = Equaltion(Back, RightNum, Chara);
				//Chara = (char)0;
			}
			else {//�������������
				Back= CharToNum(Data, i);
			}
		}
		else {
			Chara = Data[i++];
			if (Chara == '-' && Back == 0.0) {//����
				Back = CharToNum(Data, i);
				Back *= -1;
				Chara = (char)0;
			}
			else {
				if (i == 1 && (Chara == '*' || Chara == '/')) {
					cout << "ȱʧ������:";
					for (int j = 0; j < i; ++j) {
						cout << Data[j];
					}cout << endl;
					for (int j = 0; j < i + 10; ++j)cout << ' ';
					cout << '^' << '$' << endl;
					exit(1);
				}
				if ((Chara == '-' || Chara == '+' || Chara == '*' || Chara == '/') && \
					i-2>=0 && (Data[i - 2] == '-' || Data[i - 2] == '+' || Data[i - 2] == '*' || Data[i - 2] == '/')) {//ǰһ��ҲΪ����
					cout << "ȱʧ������:";
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
							cout << "ȱʧ�����:";
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
			cout << "лл����ʹ��" << endl;
			break;
		}
		default: {
			cout << "ѡ������" << endl;
			system("Pause");
			system("cls");
			break;
		}
		}
	}
	return 0;
	
}