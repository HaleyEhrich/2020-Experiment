#pragma once
#include<iostream>
#include<stack>
#include<list>

using namespace std;
class VertexChain;
class LinkList {
private:
	VertexChain* Vertex;
	int weight;
	LinkList* next;
public:
	LinkList(VertexChain* vertex, int weight=1) {
		this->Vertex = vertex;
		this->weight = -1;
		if (this->Vertex == NULL) {
			cout << "�ߵĵڶ������㲻����!!!" << endl;
		}
		else {
			if (weight <= 0) {
				cout << "Ȩֵ���Ϸ�������" << endl;
			}
			else {
				this->weight = weight;
			}
		}
		this->next = NULL;
	}
	int getWeight() {
		return this->weight;
	}
	VertexChain* getVerAdress() {
		return this->Vertex;
	}
	bool existsEdge(VertexChain* vertex) {
		LinkList* Find = this;
		while (Find != NULL) {
			if (Find->Vertex == vertex) {
				return true;
			}
			Find = Find->next;
		}
		return false;
	}
	bool addEdge(VertexChain* Vertex, int weight = 1) {
		LinkList* Last = this;
		while (Last->next != NULL) {
			Last = Last->next;
		}
		Last->next = new LinkList(Vertex, weight);
		if (Last->next->Vertex == NULL || Last->next->weight < 0) {
			delete Last->next;
			Last->next = NULL;
			return false;
		}
		return true;
	}
	void out();

	//��·������
	LinkList* getNext() {
		return this->next;
	}
};

class VertexChain {
private:
	int Vertex;
	string VertexName;
	LinkList* FirstLink;
	VertexChain* next;
public:
	VertexChain(int ver,string VertexName="Vertex") {
		this->VertexName = VertexName;
		this->Vertex = ver;
		this->FirstLink = NULL;
		this->next = NULL;
	}
	~VertexChain() { delete this->FirstLink; }
	int getVertex() {
		return this->Vertex;
	}
	string& getName() {
		return this->VertexName;
	}
	VertexChain* getNextVer() {
		return this->next;
	}
	bool existsEdge(VertexChain* vertex) {
		if (this->FirstLink == NULL) {
			return false;
		}
		return this->FirstLink->existsEdge(vertex);
	}
	bool addNextVertex(VertexChain* vertex) {
		if (vertex == NULL) {
			return false;
		}
		this->next = vertex;
		return true;
	}
	bool addEdge(VertexChain* vertex, int weight = 1) {
		if (this->existsEdge(vertex)) {
			cout << "�ñ��Ѿ�����!!!" << endl;
			return false;
		}
		if (this->FirstLink == NULL) {
			this->FirstLink = new LinkList(vertex, weight);
			if (FirstLink->getVerAdress() == NULL || FirstLink->getWeight()< 0) {
				delete FirstLink;
				FirstLink = NULL;
				return false;
			}
		}
		else {
			return this->FirstLink->addEdge(vertex, weight);
		}
		return true;
	}
	void out() {
		cout << "������Ϣ��\n\t���" << this->Vertex << " ���ƣ�" << this->VertexName << endl;
		if (this->FirstLink == NULL) {
			cout << "�ö���û���ڽӶ���" << endl;
		}
		else {
			cout << "�ٽӶ��㣺" << endl;
			this->FirstLink->out();
		}
	}
	string findSinpleRote(VertexChain* End) {
		string backRote;
		int visit[100] = { 0 };
		VertexChain* p;
		stack<VertexChain*> adress;
		adress.push(this);
		visit[this->Vertex] = 1;
		bool is_push = false;
		while (adress.empty() == false)
		{
			is_push = false;
			p = adress.top();
			for (LinkList* border=p->FirstLink; border !=NULL ; border= border->getNext())
			{
				if (border->getVerAdress() == End) {//�ҵ��˽ڵ�
					adress.push(border->getVerAdress());//��������Ҫ���ʵĶ���ѹ��ջ��
					goto dataprocessing;
				}
				if (!visit[border->getVerAdress()->Vertex])//�ҵ��ڽӶ���
				{
					visit[border->getVerAdress()->Vertex] = 1;//p���ű�Ϊ�Ѿ����ʹ�
					adress.push(border->getVerAdress());//���ɷ����ڽӶ���ѹ��ջ�ڣ�����
					is_push = true;
					break;
				}

			}
			if (!is_push)//��û���˿ɷ����ڽӶ��������£�����Ѿ����ʹ��ĵ�
			{
				adress.pop();
			}
		}
	dataprocessing:
		if (adress.empty() == true) {
			return "There's no rote";
		}
		else {

			stack<VertexChain*> adressback;
			while (adress.empty() == false) {
				adressback.push(adress.top());
				adress.pop();
			}
			while (adressback.empty() == false) {
				p=adressback.top();
				//backRote += "���:";
				//backRote += (char)(p->Vertex+"0");
				//backRote += "����:";
				backRote += "->";
				backRote += p->VertexName;
				adressback.pop();
			}
		}
		return backRote;
	}
	string findShortestRote(VertexChain* head, VertexChain* End) {
		VertexChain* predecessor[100] = { NULL };//�洢ĳ���ǰ���ڵ�
		int distanceFromThis[100] = { INT_MAX };//�洢·����Ȩֵ
		list<VertexChain*> visitAble;//�洢�ɷ��ʵĽڵ�
		LinkList* p = this->FirstLink;
		for (; p != NULL; p = p->getNext()) {
			distanceFromThis[p->getVerAdress()->getVertex()] = p->getWeight();
			predecessor[p->getVerAdress()->getVertex()] = this;
			visitAble.push_front(p->getVerAdress());
		}
		while (!visitAble.empty()) {
			//��������ʹ��ͬ��ָ��
			list<VertexChain*>::iterator iNewReachableVertices = visitAble.begin();
			list<VertexChain*>::iterator theEnd = visitAble.end();
			VertexChain* v = *iNewReachableVertices;
			iNewReachableVertices++;
			while (iNewReachableVertices != theEnd) {//�ڿɷ��ʵĵ���Ѱ�Ҿ�����СȨֵ�ĵ�
				VertexChain* w = *iNewReachableVertices;
				iNewReachableVertices++;
				if (distanceFromThis[v->Vertex] > distanceFromThis[w->Vertex]) {//����Ȩֵ��С�ĵĵ�
					v = w;
				}
			}
			visitAble.remove(v);
			//�������·��
			for (p = v->FirstLink; p != NULL; p = p->getNext()) {
				//v�ɴ�ĵĶ���j�����j����ʼ�㲻�ɴ����j����ʼ���Ȩֵ�����ȵ�v����v��j��Ȩֵ
				if ((predecessor[p->getVerAdress()->Vertex] == NULL ||
					distanceFromThis[p->getVerAdress()->Vertex] > distanceFromThis[v->Vertex] + p->getWeight())) {
					distanceFromThis[p->getVerAdress()->Vertex] = p->getWeight() + distanceFromThis[v->Vertex];
					if (predecessor[p->getVerAdress()->Vertex] == NULL) {
						visitAble.push_front(p->getVerAdress());
					}
					predecessor[p->getVerAdress()->Vertex] = v;
				}
			}
		}
		distanceFromThis[this->Vertex] = 0;//�㵽�Լ��ľ���Ϊ0;
		predecessor[this->Vertex] = NULL;//��֤��������

		if (distanceFromThis[End->Vertex] == INT_MAX) {
			return "There's no rote !";
		}
		else {
			string shortestRote;
			stack<string> roteRe;
			VertexChain* rote = predecessor[End->Vertex];
			//string weight = static_cast<ostringstream*>(&(ostringstream() << distanceFromThis[End->Vertex]))->str();
			cout << "���·������:" << distanceFromThis[End->Vertex] << endl;
			shortestRote += "����·��";
			while (rote!=NULL) {
				roteRe.push(rote->VertexName);
				rote = predecessor[rote->Vertex];
				
			}
			while (!roteRe.empty()) {
				shortestRote += "->"+roteRe.top();
				roteRe.pop();
			}
			shortestRote += "->" + End->VertexName;
			return shortestRote;
		}
		
	}
};

void LinkList::out() {
	LinkList* p = this;
	while (p != NULL) {
		cout << "\t���" << p->Vertex->getVertex() << " ���ƣ�" << p->Vertex->getName() << " Ȩ��" << p->weight << endl;
		p = p->next;
	}
}

class Graph {
private:
	VertexChain* Vertex;
public:
	Graph() {
		this->Vertex = NULL;
	}
	VertexChain* getVerAdress(int vertex) {
		VertexChain* Find = this->Vertex;
		while (Find != NULL) {
			if (Find->getVertex() == vertex) break;
			Find = Find->getNextVer();
		}
		return Find;
	}
	bool existsVer(int& vertex) {
		VertexChain* Find = this->Vertex;
		while (Find != NULL) {
			if (Find->getVertex() == vertex) return true;
			Find = Find->getNextVer();
		}
		return false;
	}
	bool addVertex() {
		int vertex=0;
		string vertexName = "vertex";
		cout << "����\"-1\"�����������!" << endl;
		while (vertex != -1) {
			cout << "\t���붥���ţ�";
			cin >> vertex;
			if (vertex >= 0) {
				if (this->existsVer(vertex)) {
					cout << "Eorro: �ñ�Žڵ��Ѵ���!!!" << endl;
				}
				else {
					cout << "\t���붥�������:";
					cin >> vertexName;
					if (this->Vertex == NULL) {
						this->Vertex = new VertexChain(vertex, vertexName);
					}
					else {
						VertexChain* last = this->Vertex;
						while (last->getNextVer() != NULL) {
							last = last->getNextVer();
						}
						last->addNextVertex(new VertexChain(vertex, vertexName));
					}
				}
			}
		}
		return true;
	}
	bool addEdge() {
		int ver1 = 0,ver2=0;
		VertexChain* vertex1,*vertex2;
		cout << "����\"-1\"���������!" << endl;
		while (ver1 != -1) {
			cout << "\t�����һ���ߵĶ���ı�ţ�";
			cin >> ver1;
			if (ver1 >= 0) {
				vertex1 = getVerAdress(ver1);
				if (vertex1 == NULL) {
					cout << "�ñ�Ŷ��㲻����!!!" << endl;
				}
				else {
					cout << "\t����ڶ����ߵĶ���ı�ţ�";
					cin >> ver2;
					vertex2 = getVerAdress(ver2);
					int weight;
					cout << "\t����ñߵ�Ȩ�أ�";
					cin >> weight;
					if (!vertex1->addEdge(vertex2, weight)) {
						cout << "Eorro:���ʧ��" << endl;
					}
				}
			}
		}
		return true;
	}
	void outGraph() {
		if (this->Vertex == NULL) {
			cout << "��ͼ��" << endl;
		}
		else {
			VertexChain* p = this->Vertex;
			while (p != NULL) {
				p->out();
				p = p->getNextVer();
			}
		}
	}

	//���·������
	VertexChain* getFirstVerAdrsss() {
		return this->Vertex;
	}
};