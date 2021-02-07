#pragma once
#include <iostream>
#include <stack>
#include <list>
#include <fstream>
#include <cstdlib>
#include <string>
#include <QApplication>
#include <QString>
#include <QMessageBox>

#define MaxSizeElem 100 //输入数据用的数组
#define MaxInt 36727
using namespace std;

//const int MaxInt=36727;

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
        if (this->Vertex == nullptr) {
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
        this->next = nullptr;
    }
    //获取路径信息
    int getWeight() {
        return this->weight;
    }
    VertexChain* getVerAdress() {
        return this->Vertex;
    }
    //
    void setWeight(int weight){
        this->weight=-weight;
    }
    //是否存在路径
    bool existsEdge(VertexChain* vertex) {
        LinkList* Find = this;
        while (Find != nullptr) {
            if (Find->Vertex == vertex) {
                return true;
            }
            Find = Find->next;
        }
        return false;
    }
    //添加路径
    bool addEdge(VertexChain* Vertex, int weight = 1) {
        LinkList* Last = this;
        while (Last->next != nullptr) {
            Last = Last->next;
        }
        Last->next = new LinkList(Vertex, weight);
        if (Last->next->Vertex == nullptr || Last->next->weight < 0) {
            delete Last->next;
            Last->next = nullptr;
            return false;
        }
        return true;
    }
    //求路径需求
    LinkList* getNext() {
        return this->next;
    }
};

class VertexChain {
private:
    int Vertex;//顶点的编号
    string VertexName;//该顶点的名称
    string VertexInf;//地点的简介
    LinkList* FirstLink;//相通地点的链表的起始
    VertexChain* next;//下一节点的地址
public:
    //构造函数，参数包含地点编号，地点名称，地点简介，仅地点编号不可缺省
    VertexChain(int ver,string VertexName="Vertex",string VertexInf="There's no information about this loacte") {//构造
        this->VertexName = VertexName;
        this->VertexInf = VertexInf;
        this->Vertex = ver;
        this->FirstLink = nullptr;
        this->next = nullptr;
    }
    //析构函数
    ~VertexChain() {
        delete this->FirstLink;
        this->FirstLink = nullptr;
        this->Vertex = -1;
        this->VertexInf = "";
        this->VertexName = "";
    }
    //获取地点信息
    int getVertex() {//地点编号
        return this->Vertex;
    }
    string& getName() {//地点名称
        return this->VertexName;
    }
    string& getInf() {//地点简介
        return this->VertexInf;
    }
    LinkList* getLinklistAdr(){
        return this->FirstLink;
    }
    //set
    void setVertex(int data){
        this->Vertex=data;
    }
    void setName(string data){
        this->VertexName=data;
    }
    void setInf(string data){
        this->VertexInf=data;
    }
    void setWeight(VertexChain* End,int weight){
        LinkList* p=this->getLinklistAdr();
        while(p!=nullptr){
            if(p->getVerAdress()==End)break;
            p=p->getNext();
        }
        if(p!=nullptr){
            p->setWeight(weight);
        }
    }
    //获取下一地点的链表地址
    VertexChain* getNextVerAdress() {
        return this->next;
    }
    //该地点于参数地点是否存在路径
    bool existsEdge(VertexChain* vertex) {
        if (this->FirstLink == nullptr) {
            return false;
        }
        return this->FirstLink->existsEdge(vertex);
    }
    //添加下一地点于地点链表上
    bool addNextVertex(VertexChain* vertex) {
        if (vertex == nullptr) {
            return false;
        }
        this->next = vertex;
        return true;
    }
    //添加路径，默认该地点到参数地点的距离为1
    bool addEdge(VertexChain* vertex, int weight = 1) {
        if (this->existsEdge(vertex)) {//若可存在平行边删除判断
            return false;
        }else{
            if (this->FirstLink == nullptr) {
                this->FirstLink = new LinkList(vertex, weight);
                if (FirstLink->getVerAdress() == nullptr || FirstLink->getWeight()< 0) {
                    delete FirstLink;
                    FirstLink = nullptr;
                    return false;
                }
            }
            else {
                return this->FirstLink->addEdge(vertex, weight);
            }
        }
        return true;
    }
    //寻找该地点到参数地点的最短路径
    string findShortestRote(VertexChain* End) {//VertexChain* head,
        VertexChain* predecessor[100] = { nullptr };//存储某点的前驱节点
        int distanceFromThis[100] = { INT_MAX };//存储路径的权值
        list<VertexChain*> visitAble;//存储可访问的节点
        LinkList* p = this->FirstLink;
        for (; p != nullptr; p = p->getNext()) {
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
            //对于此处的NULL指针应用问题不予考虑，一般不会出现
            visitAble.remove(v);
            //更新最短路径
            for (p = v->FirstLink; p != nullptr; p = p->getNext()) {
                //v可达的的顶点j，如果j与起始点不可达或者j与起始点的权值大于先到v再由v到j的权值
                if ((predecessor[p->getVerAdress()->Vertex] == nullptr ||
                    distanceFromThis[p->getVerAdress()->Vertex] > distanceFromThis[v->Vertex] + p->getWeight())) {
                    distanceFromThis[p->getVerAdress()->Vertex] = p->getWeight() + distanceFromThis[v->Vertex];
                    if (predecessor[p->getVerAdress()->Vertex] == nullptr) {
                        visitAble.push_front(p->getVerAdress());
                    }
                    predecessor[p->getVerAdress()->Vertex] = v;
                }
            }
        }
        distanceFromThis[this->Vertex] = 0;//点到自己的距离为0;
        predecessor[this->Vertex] = nullptr;//保证在起点结束

        if (distanceFromThis[End->Vertex] == INT_MAX) {
            return "在"+this->VertexName+"~"+End->VertexName+"两点之间没有路径互通";
        }
        else {
            string shortestRoutine;
            stack<string> roteRe;
            VertexChain* rote = predecessor[End->Vertex];
            bool flagOfFirst=true;
            shortestRoutine="在"+this->VertexName+"~"+End->VertexName+"两点之间最短路径:\n\t最短路径长度:";
            shortestRoutine+=std::to_string(distanceFromThis[End->Vertex]);
            shortestRoutine+="\n\t具体路径:";
            while (rote!=nullptr) {
                roteRe.push(rote->VertexName);
                rote = predecessor[rote->Vertex];
            }
            while (!roteRe.empty()) {
                if(flagOfFirst==true){
                    shortestRoutine+=roteRe.top();
                    flagOfFirst=false;
                }else{
                     shortestRoutine += "->"+roteRe.top();
                }
                cout<<"AAA"<<endl;
                cout<<roteRe.top();
                roteRe.pop();
            }
            shortestRoutine += "->" + End->VertexName;
            return shortestRoutine;
        }
    }
    //输出地点信息
    string outVertex() {
        string back;
        back="Locate Information:\n\tNumber:";
        back+=to_string(this->Vertex);
        back+="\n\tName:"+this->VertexName+"\n\tInformation:"+this->VertexInf;
        if (this->FirstLink == nullptr) {
            back+="\n\t没有可达地点\n";
        }
        else {
            back+="\n\t临接顶点:";
            LinkList* p=this->FirstLink;
            while(p!=nullptr){
                back+="\n\t\tNumber:";
                back+=to_string(p->getVerAdress()->getVertex());
                back+="\n\t\tName:"+p->getVerAdress()->getName();
                back+="\n\t\tDistance:";
                back+=to_string(p->getWeight());
                p=p->getNext();
            }
            back+="\n";
        }
        return back;
    }
};

class Graph {
private:
    VertexChain* Vertex;
    VertexChain* lastVertex;
    int vertexNum;
    vector<vector<int> > path;
    vector<vector<int> > dist;

    int Whether;
public:
    //图的基本构造默认为空图
    Graph() {
        this->Vertex = nullptr;
        this->lastVertex = nullptr;
        this->vertexNum=0;
        this->Whether=0;
    }
    //获取某顶点的地址，依据顶点的编号查找
    VertexChain* getVerAdress(int vertex) {//编号查找
        VertexChain* Find = this->Vertex;
        while (Find != nullptr) {
            if (Find->getVertex() == vertex) break;
            Find = Find->getNextVerAdress();
        }
        return Find;
    }
    VertexChain* getVerAdress(string vertexName) {//名称查找
        VertexChain* Find = this->Vertex;
        while (Find != nullptr) {
            if (Find->getName() == vertexName) break;
            Find=Find->getNextVerAdress();
        }
        return Find;
    }
    VertexChain* getFirAdress(){
        return this->Vertex;
    }
    VertexChain* getEndAiress(){
        return this->lastVertex;
    }
    int getVerNum(){
        return this->vertexNum;
    }
    //添加顶点数据
    bool addVertex() {
        int vertex=0;
        //输入全部用char数组输入，但是处理全为string
        char vertexName[MaxSizeElem]= { "vertex\0" },\
            vertexInf[MaxSizeElem]= { "There's no information about this loacte\0" };
        cout << "输入\"-1\"结束地点添加!" << endl;
        while (vertex >=0 ) {
            //输入数据
            cout << "\t输入地点编号：";
            cin >> vertex;
            if (vertex >= 0) {
                if (this->getVerAdress(vertex) != nullptr) {
                    cout << "Eorro: 编号已存在!!!" << endl;
                }
                else {
                    cout << "\t输入地点的名称:";
                    cin.get();
                    cin.getline(vertexName, MaxSizeElem);
                    fflush(stdin);//注意数据过多的溢出问题
                    cout << "\t输入该地点的简介";
                    cin.getline(vertexInf,MaxSizeElem);
                    fflush(stdin);
                    //顶点建立
                    if (this->Vertex == nullptr) {
                        this->Vertex = new VertexChain(vertex, vertexName, vertexInf);
                        this->lastVertex = this->Vertex;
                    }
                    else {
                        this->lastVertex->addNextVertex(new VertexChain(vertex, vertexName, vertexInf));
                        this->lastVertex = this->lastVertex->getNextVerAdress();
                    }
                }
            }
        }
        return true;
    }
    bool addVertex(int ver, string vertexName = "Vertex", string vertexInf = "There's no information about this loacte") {//文件读取中建立地点
        if (ver >= 0) {
            if (this->getVerAdress(ver) != nullptr) {
                //冲突的地点编号直接删去。
            }
            else {
                //顶点建立
                if (this->Vertex == nullptr) {
                    this->Vertex = new VertexChain(ver, vertexName, vertexInf);
                    this->lastVertex = this->Vertex;
                }
                else {
                    this->lastVertex->addNextVertex(new VertexChain(ver, vertexName, vertexInf));
                    this->lastVertex = this->lastVertex->getNextVerAdress();
                }
            }
        }
        return true;
    }
    bool addvertex(VertexChain* verNode){//节点地址添加
        if(verNode!=nullptr){
            if(this->getVerAdress(verNode->getVertex())!=nullptr){
                return false;
            }
            if (this->Vertex == nullptr) {
                this->Vertex = verNode;
                this->lastVertex = this->Vertex;
            }
            else {
                this->lastVertex->addNextVertex(verNode);
                this->lastVertex = this->lastVertex->getNextVerAdress();
            }
        }
        this->vertexNum++;
        this->Whether++;
        return true;
    }
    //添加路径
    bool addEdge(int ver1,int ver2,int weight) {
        VertexChain* vertex1, * vertex2;
        if (ver1 >= 0 && ver2 >=0 ) {
            vertex1 = getVerAdress(ver1);
            vertex2 = getVerAdress(ver2);
            if (vertex1 && vertex2) {
                return vertex1->addEdge(vertex2, weight);
            }
        }
        //不符合编号的地点直接删去不予处理。
        //this->Floyd();
        return false;
    }
    //数据输出
    QString outGraph(){
        QString back;
        VertexChain* p=this->Vertex;
        while(p!=nullptr){
            back.append(QString::fromStdString(p->outVertex()));
            p=p->getNextVerAdress();
        }
        if(back.isEmpty()==true){
            return "空地图";
        }
        else{
            return back;
        }

    }
    //isEmpty
    bool graphIsEmpty(){
        if(this->Vertex==nullptr){
            return  true;
        }
        return false;
    }
    //Floyd
    void Floyd(){
      if (this->Whether)this->capacity();
      int i, j, k;
      for (i = 0; i < this->getVerNum(); ++i) {
          for (j = 0; j < this->getVerNum(); ++j) {
            dist[i][j] = this->getWeigth(i+1, j+1);
            if(dist[i][j]<MaxInt&&i!=j) path[i][j] = j;
            else path[i][j] = -1; // "顶点i"到"顶点j"的最短路径是经过顶点j。
          }
      }
      for(k = 0; k < this->getVerNum(); ++k)
       for(i = 0; i < this->getVerNum(); ++i)
        for(j = 0; j < this->getVerNum(); ++j)
            if (dist[i][k] + dist[k][j] < dist[i][j]) {
                dist[i][j] = dist[i][k] + dist[k][j];
                path[i][j] = path[i][k];  //将i的后继更改为k
            }
    }
    //
    void capacity() {
      this->path.resize(this->getVerNum());
      this->dist.resize(this->getVerNum());
      for (int i = 0; i < this->getVerNum(); ++i) {
       this->path[i].resize(this->getVerNum());
       this->dist[i].resize(this->getVerNum());
      }
      this->Whether = 0;
     }
    //最短路径
    string findShortestRote_Floyd(int i, int j) {
         if(!this->getVerAdress(i) && !this->getVerAdress(j) && this->dist[--i][--j]==MaxInt){
             return "无法到达";
         }else{
             string backRoutiune;
             backRoutiune="路径长度";
             backRoutiune+=to_string(this->dist[i][j]);
             backRoutiune+="m";
             backRoutiune+="\n路线编号：";
             backRoutiune+=std::to_string(i+1)+"->";
             int k=this->path[i][j];
             while (k != j) {
                 backRoutiune+=std::to_string(k+1)+"->";
                 k = this->path[k][j];
             }
             backRoutiune+=std::to_string(k+1);
             return backRoutiune;
         }
    }
    //file process
    bool saveMapData(string filePath){
        ofstream outdata(filePath,ios::out);// | ios::binary
        if(outdata.is_open()==true){
            VertexChain* vertexPointer=this->Vertex;
            string vertexInf="#\n";
            string linklistInf="#\n";
            while(vertexPointer!=nullptr){
                vertexInf+=to_string(vertexPointer->getVertex())+'\n';
                vertexInf+=vertexPointer->getName()+'\n'+vertexPointer->getInf()+'\n';
                LinkList* p=vertexPointer->getLinklistAdr();
                while(p!=nullptr){
                    linklistInf+=to_string(vertexPointer->getVertex())+" "+to_string(p->getVerAdress()->getVertex())+" "+to_string(p->getWeight())+"\n";
                    p=p->getNext();
                }
                vertexPointer=vertexPointer->getNextVerAdress();
            }
            outdata<<vertexInf<<linklistInf;
            return true;
        }else{
            return false;
        }
    }
    bool openMap(string filePath){
        ifstream readData(filePath,ios::in);// | ios::binary
        string vertextNum,vertextName,vertextInf;
        int ver1,ver2,weight;
        if(readData.is_open()==true){
            getline(readData,vertextNum);
            while(1){
                getline(readData,vertextNum);
                if(vertextNum=="#"){
                    break;
                }
                getline(readData,vertextName);
                getline(readData,vertextInf);
                this->addvertex(new VertexChain(stoi(vertextNum),vertextName,vertextInf));
            }
            while(!readData.eof()){
                getline(readData,vertextNum);
                this->getWeight(vertextNum,ver1,ver2,weight);
                this->addEdge(ver1,ver2,weight);
            }
            this->capacity();
        }else{
            return false;
        }
        return true;
    }
    void getWeight(string line, int& v1, int& v2, int& weight) {
        const char* str = line.c_str();
        v1 = atoi(str);
        v2 = atoi(&str[line.find(' ') + 1]);
        weight = atoi(&str[line.find_last_of(' ') + 1]);
    }
    int getWeigth(int i, int j) {
      VertexChain* former = this->getVerAdress(i);
      VertexChain* latter = this->getVerAdress(j);
      if (!former||!latter)return MaxInt;
      else {
       LinkList* first = former->getLinklistAdr();
       while (first) {
        if (first->getVerAdress() == latter)
         return first->getWeight();
        first = first->getNext();
       }
       return MaxInt;
      }
     }
    void freeMap(){
        delete this->Vertex;
        this->Vertex=nullptr;
        this->lastVertex=nullptr;
    }
};

//Graph() {
//    this->Vertex = NULL;
//    this->lastVertex = NULL;
//    ifstream rvertex(vertex_informantion, ios::in | ios::binary);
//    if (!rvertex)return;
//    else{
//        string vertex, vertexname, vertexinf;
//        getline(rvertex, vertex);
//        getline(rvertex, vertexname);
//        getline(rvertex, vertexinf);
//        while (!rvertex.eof()) {
//            this->addVertex(atoi(vertex.c_str()), vertexname, vertexinf);
//            getline(rvertex, vertex);
//            getline(rvertex, vertexname);
//            getline(rvertex, vertexinf);
//        }
//    }
//    ifstream redge(edge_informantion, ios::in | ios::binary);
//    if (!redge)return;
//    else{
//        int v1=0, v2=0, wegith=0;
//        string line;
//        while (!redge.eof()) {
//            getline(redge, line);
//            getWeight(line, v1, v2, wegith);
//            this->addEdge(v1, v2, wegith);
//        }
//    }
//}
//del
/*
Graph::
    //最短路径函数
    string findShortestRote(VertexChain* Start,VertexChain* End) {
        VertexChain* Start = this->getVerAdress(i);
        VertexChain* End = this->getVerAdress(j);
        if (!Start || !End) {
            cout << "地点不存在" << endl;
            return;
        }
        if(Start&&End){
            return Start->findShortestRote(End);
        }else{
            return "";
        }
    }
    //
    void findSimpleRote(int i, int j) {
        VertexChain* Start = this->getVerAdress(i);
        VertexChain* End = this->getVerAdress(j);
        if (!Start || !End) {
            cout << "地点不存在" << endl;
            return;
        }
        cout << "路径：" << Start->findSinpleRote(End) << endl;
    }
    //查找地点存在与否,删掉，与上面有部分重复
    bool existsVer(int& vertex) {//编号查找
        VertexChain* Find = this->Vertex;
        while (Find != nullptr) {
            if (Find->getVertex() == vertex) return true;
            Find = Find->getNextVerAdress();
        }
        return false;
    }
    bool existVer(string& vertexName) {//名称查找
        VertexChain* Find = this->Vertex;
        while (Find != nullptr) {
            if (Find->getName() == vertexName) return true;
            Find = Find->getNextVerAdress();
        }
        return false;
    }
    //
    bool addEdge() {
        int ver1 = 0,ver2=0;
        VertexChain* vertex1,*vertex2;
        cout << "输入\"-1\"结束边=路径添加!" << endl;
        while (ver1 != -1) {
            cout << "\t输入该路径的起点编号:";
            cin >> ver1;
            if (ver1 >= 0) {
                vertex1 = getVerAdress(ver1);
                if (vertex1 == nullptr) {
                    cout << "该地点不存在!!!" << endl;
                }
                else {
                    cout << "\t输入该路径的起终点编号:";
                    cin >> ver2;
                    vertex2 = getVerAdress(ver2);
                    int weight;
                    cout << "\t输入该段路径的长度:";
                    cin >> weight;
                    if (!vertex1->addEdge(vertex2, weight)) {
                        cout << "Eorro:添加失败" << endl;
                    }
                }
            }
        }
        return true;
    }

VertexChain::
    //寻找该地点到参数地点的一条路径
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
            for (LinkList* border=p->FirstLink; border !=nullptr ; border= border->getNext())
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
    */
