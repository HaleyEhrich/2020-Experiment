#include<iostream>
#define Maxsize 100
 using namespace std;
 template <class T>
 class StackList {
 public:
	 T* Data;
	 int StaLength;
	 int StaMaxsize;
	 StackList(const T &DataIn) {
		 this->StaMaxsize = Maxsize;
		 this->Data = new T(this->StaMaxsize);
		 this->Data[0] = DataIn;
		 this->StaLength = 1;
	 }
	 StackList() {
		 this->StaMaxsize = Maxsize;
		 this->Data = new T(this->StaMaxsize);
		 this->StaLength = 0;
	 }
	 bool pop() {
		 if (!this->StaLength) {
			 return 1;
		 }
		 --this->StaLength;
		 return 0;
	 }
	 bool push(T& DataIn) {
		 if (this->StaLength == this->StaMaxsize) {
			 return 1;
		 }
		 this->Data[this->StaLength] = DataIn;
		 ++this->StaLength;
		 return 0;
	 }
	 bool Sta_is_empty() {//1 No,0 Yes
		 return this->StaLength;
	 }
	 T& ReTop() {
		 return this->Data[this->StaLength-1];
	 }
 };
 template <class T>
 class DataList{
 public:
	 T* Data;
	 DataList* next;
	 DataList(T& Datain) {
		this->Data = new T(Datain);
		this->next = NULL;
	 }
	 DataList() {
		this->Data = NULL;
		this->next = NULL;
	 }
	 DataList(DataList& Datain) {
		 this->Data = Datain.Data;
		 this->next = Datain.next;
	 }
	 bool Addnext(T& Datain) {
		 this->next = new DataList<T>(Datain);
		 return 0;
	 }
	 
 };
 template <class T>
 class linernode {
 public:
	 T data;
	 linernode<T>* next;
	 linernode(T& Datain) {
		 this->data = Datain;
		 this->next = NULL;
	 }
	 linernode() {
		 this->next = NULL;
	 }
 };
 template <class T>
 class Liner {
 public:
//	 linernode<T>* head;
	 linernode<T>* tail;
	 Liner(T& Datain) {
		 this->tail = new linernode<T>(Datain);
		 this->tail->next = this->tail;
//		 this->head = new linernode<T>(Datain);
//		 this->tail = head;
	 }
	 Liner() {
		 this->tail = NULL;
//		 this->head = this->tail = NULL;
	 }
	 bool Liner_in(T& Datain) {
		 if (this->tail == NULL) {
			 this->tail = new linernode<T>(Datain);
			 this->tail->next = this->tail;
		 }
		 else {
			 linernode<T>* TempNode = this->tail->next;
			 this->tail->next = new linernode<T>(Datain);
			 this->tail = this->tail->next;
			 this->tail->next = TempNode;
		 }
//		 if (!this->head) {
//			 this->head = new linernode<T>(Datain);
//			 this->tail = head;
//		 }
//		 else {
//			 this->tail->next= new linernode<T>(Datain);
//			 this->tail = this->tail->next;
//		 }
		 return 0;
	 }
	 bool Liner_out() {
		 if (!this->tail) {
			 return 1;
		 }
		 else {
			 linernode<T>* TempNode = this->tail->next;
			 if (this->tail->next == this->tail) {
				 this->tail = NULL;
			 }
			 else {
				 this->tail->next = this->tail->next->next;
			 }
			 delete TempNode;
			 return 0;
		 }

//		 if (!this->head) {
//			 return 1;
//		 }
//		 else {
//			 linernode<T>* Nodedel = this->head;
//			 this->head = this->head->next;
//			 delete Nodedel;
//			 return 0;
//		 }
	 }
	 void out_data() {
		 if (this->tail == NULL) {//队空
			 return ;
		 }
		 linernode<T>* temp = this->tail->next;
		 if (temp) {
			 do {
				 cout << temp->data << ' ';
				 temp = temp->next;
			 } while (temp != this->tail->next);
			 cout << endl;
		 }
		 else {
			 cout << "No data" << endl;
		 }
//		 linernode<T>* temp = this->tail->next;
//		 if (temp) {
//			 while (temp!=NULL) {
//				 cout << temp->data << ' ';
//				 temp = temp->next;
//			 }
//			 cout << endl;
//		 }
//		 else {
//			 cout << "No data" << endl;
//		 }
	 }
 };

 void menu() {
	 cout << "_________________________" << endl;
	 cout << "1:回文串" << endl;
	 cout << "2:左右括号匹配" << endl;
	 cout << "3:队列" << endl;
	 cout << "4:Exit" << endl;
	 cout << "_________________________" << endl;
	 cout << "输入选择" << endl;
 }
 int main() {
	 int i = 0;
	 while (i < 4) {
		 menu();
		 cin >> i;
		 switch (i){
		 case 1: {
			 DataList<char>* firstnode = new DataList<char>;
			 StackList<char>* _Stack = new StackList<char>;
			 DataList<char>* tempnode = firstnode;
			 char data;
			 int count=0;
			 cout << "输入数据以 # 结束" << endl;
			 do {
				 cin >> data;
				 if (data != '#') {
					 tempnode->Addnext(data);
					 tempnode = tempnode->next;
					 ++count;
				 }
			 } while (data != '#');//数据录入、计数
			 tempnode = firstnode->next;
			 for (int j = 0; j < count / 2; ++j) {//入栈
				 _Stack->push(*(tempnode->Data));
				 tempnode = tempnode->next;
			 }
			 if (count % 2) {//中间量
				 tempnode = tempnode->next;
			 }
			 while (tempnode) {//出栈
				 if (*tempnode->Data == _Stack->ReTop()) {
					 _Stack->pop();
					 tempnode = tempnode->next;
				 }
				 else {
					 break;
				 }
			 }
			 if (_Stack->Sta_is_empty()) {
				 cout << "NO" << endl;
			 }
			 else {
				 cout << "Yes" << endl;
			 }
			 break;
		 }
		 case 2: {
			 StackList<char>* _Stack = new StackList<char>;
			 char data;
			 cout << "输入数据以 # 结束" << endl;
			 do {
				 cin >> data;
				 if (data != '#' && _Stack->ReTop()!=')') {
					 if (data == '(') {
						 _Stack->push(data);
					 }
					 else {
						 if (_Stack->pop()) {
							 _Stack->push(data);
						 }
					 }
				 }
			 } while (data != '#');
			 if (_Stack->Sta_is_empty()) {
				 cout << "NO" << endl;
			 }
			 else {
				 cout << "Yes" << endl;
			 }
			 break;
		 }
		 case 3: {
			 Liner<char> LinerText;
			 char data;
			 int j = 0;
			 cout << "1 Push data in liner,2 Pop data in liner,3 Pop all data" << endl;
			 do {
				 cin >> j;
				 fflush(stdin);
				 if (j == 1) {
					 cout << "输入数据以 # 结束" << endl;
					 do {
						 cin >> data;
						 if (data != '#') {
							 LinerText.Liner_in(data);
						 }
					 } while (data != '#');
					 cout << "Pushed \nLiner contain data:" << endl;
					 LinerText.out_data();
				 }else if(j==2){
					 if (LinerText.Liner_out()) {
						 cout << "No data in liner" << endl;
					 }
					 else {
						 cout << "Poped \nLiner contain data:" << endl;
						 LinerText.out_data();
					 }
				 }else if (j == 3) {
					 while(!LinerText.Liner_out());
					 cout << "Poped all data\n" << endl;
				 }
			 } while (j<=3 && j>=1);
			 break;
		 }
		 }
		 system("Pause");
		 system("cls");
	 }
	 return 0;
 }

