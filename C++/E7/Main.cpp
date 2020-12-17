#include "graph.h"
using namespace std;
void findSimpleRote(int i, int j,Graph* Map) {
	if (!Map->existsVer(i) || !Map->existsVer(j)) {
		cout << "节点不存在" << endl;
		return;
	}
	VertexChain* Start = Map->getVerAdress(i);
	VertexChain* End = Map->getVerAdress(j);
	cout << "路径：" << Start->findSinpleRote(End) << endl;
}
void findShortestRote(int i, int j, Graph* Map) {
	if (!Map->existsVer(i) || !Map->existsVer(j)) {
		cout << "节点不存在" << endl;
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
		cout << "1:添加顶点" << endl;
		cout << "2:添加边" << endl;
		cout << "3:返回上一级" << endl;
		cout << "-------------------------" << endl;
		cout << "输入你的选择";
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
	cout << "1:建立图" << endl;
	cout << "2:输出图" << endl;
	cout << "3:寻找简单路径" << endl;
	cout << "4:寻找最短路径" << endl;
	cout << "5:退出" << endl;
	cout << "-------------------------" << endl;
	cout << "输入你的选择";
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
			cout << "输入两个顶点编号:";
			int i,j;
			cin >> i >> j;
			findSimpleRote(i, j, a);
			system("Pause");
			break;
		}
		case '4': {
			cout << "输入两个顶点编号:";
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