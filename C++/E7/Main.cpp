#include "graph.h"
using namespace std;
void findSimpleRote(int i, int j,Graph* Map) {
	if (!Map->existsVer(i) || !Map->existsVer(j)) {
		cout << "�ڵ㲻����" << endl;
		return;
	}
	VertexChain* Start = Map->getVerAdress(i);
	VertexChain* End = Map->getVerAdress(j);
	cout << "·����" << Start->findSinpleRote(End) << endl;
}
void findShortestRote(int i, int j, Graph* Map) {
	if (!Map->existsVer(i) || !Map->existsVer(j)) {
		cout << "�ڵ㲻����" << endl;
		return;
	}
	VertexChain* Start = Map->getVerAdress(i);
	VertexChain* End = Map->getVerAdress(j);
	cout << Start->findShortestRote(Map->getFirstVerAdrsss(), End) << endl;
}
void graphSet(Graph* a) {
	char choice = '0';
	while (choice != '3') {
		fflush(stdin);
		system("cls");
		cout << "-------------------------" << endl;
		cout << "1:��Ӷ���" << endl;
		cout << "2:��ӱ�" << endl;
		cout << "3:������һ��" << endl;
		cout << "-------------------------" << endl;
		cout << "�������ѡ��";
		cin >> choice;
		switch (choice) {
		case '1': {
			a->addVertex();
			system("Pause");
			break;
		}
		case '2': {
			a->addEdge();
			system("Pause");
			break;
		}
		}
	}
}
void menu() {
	system("cls");
	cout << "-------------------------" << endl;
	cout << "1:����ͼ" << endl;
	cout << "2:���ͼ" << endl;
	cout << "3:Ѱ�Ҽ�·��" << endl;
	cout << "4:Ѱ�����·��" << endl;
	cout << "5:�˳�" << endl;
	cout << "-------------------------" << endl;
	cout << "�������ѡ��";
}
int main() {
	Graph* a = new Graph();
	char choice = '0';
	while (choice != '5') {
		fflush(stdin);
		menu();
		cin >> choice;
		switch (choice){
		case '1': {
			graphSet(a);
			a->outGraph();
			system("Pause");
			break;
		}
		case '2': {
			a->outGraph();
			system("Pause");
			break;
		}
		case '3': {
			cout << "��������������:";
			int i,j;
			cin >> i >> j;
			findSimpleRote(i, j, a);
			system("Pause");
			break;
		}
		case '4': {
			cout << "��������������:";
			int i, j;
			cin >> i >> j;
			findShortestRote(i, j, a);
			system("Pause");
			break;
		}
		}
	}
	return 0;
}