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
			cout << "边的第二个顶点不存在!!!" << endl;
		}
		else {
			if (weight <= 0) {
				cout << "权值不合法！！！" << endl;
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

	//求路径需求
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
			cout << "该边已经存在!!!" << endl;
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
		cout << "顶点信息：\n\t编号" << this->Vertex << " 名称：" << this->VertexName << endl;
		if (this->FirstLink == NULL) {
			cout << "该顶点没有邻接顶点" << endl;
		}
		else {
			cout << "临接顶点：" << endl;
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
				if (border->getVerAdress() == End) {//找到了节点
					adress.push(border->getVerAdress());//将最终需要访问的顶点压入栈内
					goto dataprocessing;
				}
				if (!visit[border->getVerAdress()->Vertex])//找到邻接顶点
				{
					visit[border->getVerAdress()->Vertex] = 1;//p点编号标为已经访问过
					adress.push(border->getVerAdress());//将可访问邻接顶点压入栈内，结束
					is_push = true;
					break;
				}

			}
			if (!is_push)//在没有了可访问邻接顶点的情况下，输出已经访问过的点
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
				//backRote += "编号:";
				//backRote += (char)(p->Vertex+"0");
				//backRote += "名称:";
				backRote += "->";
				backRote += p->VertexName;
				adressback.pop();
			}
		}
		return backRote;
	}
	string findShortestRote(VertexChain* head, VertexChain* End) {
		VertexChain* predecessor[100] = { NULL };//存储某点的前驱节点
		int distanceFromThis[100] = { INT_MAX };//存储路径的权值
		list<VertexChain*> visitAble;//存储可访问的节点
		LinkList* p = this->FirstLink;
		for (; p != NULL; p = p->getNext()) {
			distanceFromThis[p->getVerAdress()->getVertex()] = p->getWeight();
			predecessor[p->getVerAdress()->getVertex()] = this;
			visitAble.push_front(p->getVerAdress());
		}
		while (!visitAble.empty()) {
			//迭代器的使用同于指针
			list<VertexChain*>::iterator iNewReachableVertices = visitAble.begin();
			list<VertexChain*>::iterator theEnd = visitAble.end();
			VertexChain* v = *iNewReachableVertices;
			iNewReachableVertices++;
			while (iNewReachableVertices != theEnd) {//在可访问的点中寻找具有最小权值的点
				VertexChain* w = *iNewReachableVertices;
				iNewReachableVertices++;
				if (distanceFromThis[v->Vertex] > distanceFromThis[w->Vertex]) {//出现权值更小的的点
					v = w;
				}
			}
			visitAble.remove(v);
			//更新最短路径
			for (p = v->FirstLink; p != NULL; p = p->getNext()) {
				//v可达的的顶点j，如果j与起始点不可达或者j与起始点的权值大于先到v再由v到j的权值
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
		distanceFromThis[this->Vertex] = 0;//点到自己的距离为0;
		predecessor[this->Vertex] = NULL;//保证在起点结束

		if (distanceFromThis[End->Vertex] == INT_MAX) {
			return "There's no rote !";
		}
		else {
			string shortestRote;
			stack<string> roteRe;
			VertexChain* rote = predecessor[End->Vertex];
			//string weight = static_cast<ostringstream*>(&(ostringstream() << distanceFromThis[End->Vertex]))->str();
			cout << "最短路径长度:" << distanceFromThis[End->Vertex] << endl;
			shortestRote += "具体路径";
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
		cout << "\t编号" << p->Vertex->getVertex() << " 名称：" << p->Vertex->getName() << " 权重" << p->weight << endl;
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
		cout << "输入\"-1\"结束顶点添加!" << endl;
		while (vertex != -1) {
			cout << "\t输入顶点编号：";
			cin >> vertex;
			if (vertex >= 0) {
				if (this->existsVer(vertex)) {
					cout << "Eorro: 该编号节点已存在!!!" << endl;
				}
				else {
					cout << "\t输入顶点的名称:";
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
		cout << "输入\"-1\"结束边添加!" << endl;
		while (ver1 != -1) {
			cout << "\t输入第一个边的顶点的编号：";
			cin >> ver1;
			if (ver1 >= 0) {
				vertex1 = getVerAdress(ver1);
				if (vertex1 == NULL) {
					cout << "该编号顶点不存在!!!" << endl;
				}
				else {
					cout << "\t输入第二个边的顶点的编号：";
					cin >> ver2;
					vertex2 = getVerAdress(ver2);
					int weight;
					cout << "\t输入该边的权重：";
					cin >> weight;
					if (!vertex1->addEdge(vertex2, weight)) {
						cout << "Eorro:添加失败" << endl;
					}
				}
			}
		}
		return true;
	}
	void outGraph() {
		if (this->Vertex == NULL) {
			cout << "空图表" << endl;
		}
		else {
			VertexChain* p = this->Vertex;
			while (p != NULL) {
				p->out();
				p = p->getNextVer();
			}
		}
	}

	//最短路径函数
	VertexChain* getFirstVerAdrsss() {
		return this->Vertex;
	}
};