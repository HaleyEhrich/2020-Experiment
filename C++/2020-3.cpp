#include<iostream>

using namespace std;
/*
**************************************************************************
* 链表1类                                                                *
* 1:对于循环单链表而言最大好处在于插入时指针使用更加便利，但是问题在于   *
*	循环单链表的插入位的判定因为头节点缺少判断标志而变得麻烦；           *
* 2:构造函数、插入函数遵循：                                             *
*	A:节点下一节点不存在链表为空，此时直接插入该节点；                   *
*	B:下一节点存在，新建节点接上                                         *
* 3:关于删除节点的几点问题：                                             *
*	A:因为this指针的特殊性需要加入一个判断用于防止this的删除；           *
*	B:类外前驱删除可以解决问题，但是需要返回节点指针；                   *
**************************************************************************
*/
template <class T>
class list1 {
public:
	T data;
	list1<T>* next;
	list1(T* datain=NULL) {
		if (datain) {
			this->data = *datain;
			this->next = this;
		}
		else {
			this->data = NULL;
			this->next = NULL;
		}
	}
	list1(list1<T>& datain) {//更改了数据域，更改指针域
		this->data = datain.data;
		this->next = datain.next;
	}
	//节点的插入
	bool insert(list1<T>* datain) {//传入节点;在调用前应该决定插入位置;
		if (this->next == NULL) {
			this->data = datain->data;
			this->next = this;
		}
		else {
			list1<T>* temp = this->next;
			if (temp == this || (temp->data > datain->data && this->data <= datain->data) || this->data > temp->data) {//链表只有1个元素，下一个元素大于插入元素,在最大的也比插入元素小时插入元素
				this->next = datain;
				this->next->next = temp;
			}
			else {
				for (;; temp = temp->next) {
					if ((temp->next->data > datain->data && temp->data <= datain->data) || temp->data > temp->next->data) {//下一个元素大于插入元素,在最大的也比插入元素小时插入元素
						list1<T>* p = temp->next;
						temp->next = datain;
						temp->next->next = p;
						break;
					}
				}
			}
			
		}
		return 0;
	}
	bool insert(T datain) {//传入数据为T型数据
		if (this->next == NULL) {
			this->data = datain;
			this->next = this;
		}
		else {
			list1<T>* temp = this->next;
			if (temp == this || (temp->data > datain && this->data <= datain) || this->data > temp->data) {//链表只有1个元素，下一个元素大于插入元素,在最大的也比插入元素小时插入元素
				this->next = new list1<T>(&datain);
				this->next->next = temp;
			}
			else {
				for (;; temp = temp->next) {
					if ((temp->next->data > datain && temp->data <= datain) || temp->data > temp->next->data) {//下一个元素大于插入元素,在最大的也比插入元素小时插入元素
						list1<T>* p = temp->next;
						temp->next = new list1<T>(&datain);
						temp->next->next = p;
						break;
					}
				}
			}
		}
		return 0;
	}
	//节点的删除
	bool DelNood(list1<T>* NodeNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {//一个元素链表
			if(this==NodeNeedDel)this->next = NULL;
		}
		else {
			list1<T>* temp = this;
			do {
				if (temp->next == NodeNeedDel) {
					temp->next       = temp->next->next;
					delete NodeNeedDel;
					break;
				}
				temp = temp->next;
			} while (temp != this);
			//失败的写法
			/*
			list1<T>* temp = this->next;
			for (; temp != this; temp = temp->next) {
				cout << temp->data << endl;
				if (temp->next == NodeNeedDel) {
					temp->next = temp->next->next;
					delete NodeNeedDel;
					break;
				}
			}
			*/
		}
		return 0;
	}
	bool DelNood(const T& NodeNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {
			if (this->data == NodeNeedDel)this->next = NULL;
		}
		else {
			list1<T>* temp = this;
			do {
				if (temp->next->data == NodeNeedDel) {
					list1<T>* TempNext = temp->next;
					temp->next = temp->next->next;
					delete TempNext;
					break;
				}
				temp = temp->next;
			} while (temp != this);
			
		}
		return 0;
	}
	//直接前驱节点的删除
	bool DelPirNood(list1<T>* NodeNNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {//一个元素链表
			return 1;
		}
		else {
			list1<T>* temp = this;
			do {
				if (temp->next->next == NodeNNeedDel) {
					if (temp->next == this) {//前驱节点为头节点
						temp = temp->next;
						temp->data = temp->next->data;
					}
					temp->next = temp->next->next;
					delete NodeNNeedDel;
					break;
				}
				temp = temp->next;
			} while (temp != this);
		}
		return 0;
	}
	bool DelPirNood(const T& NodeNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {//一个元素链表
			return 1;
		}
		else {
			list1<T>* temp = this;
			do {
				//cout << temp->data << endl;
				if (temp->next->next->data == NodeNeedDel) {
					if (temp->next == this) {//前驱节点为头节点
						temp->next->data = temp->next->next->data;
						temp = temp->next;
					}
					list1<T>* TempNext = temp->next;
					temp->next = temp->next->next;
					delete TempNext;
					break;
				}
				temp = temp->next;
			} while (temp != this);
		}
		return 0;
	}
};
//对输出的重载
template <class T>
bool operator << (ostream& out, list1<T>& datain) {
	list1<T>* temp = datain.next;
	out << datain.data << ' ';
	for (; temp != &datain; temp = temp->next) {
		out << temp->data << ' ';
	}
	out << endl;
	return 0;
}
//删除在类外的写法!!!!!!
template <class T>
list1<T>* DelPirNood(list1<T>* ListIn,const T& NodeNeedDel) {
	if (ListIn->next == NULL) {
		return ListIn;
	}
	if (ListIn->next == ListIn) {
		return ListIn;
	}
	else {
		list1<T>* temp = ListIn;
		do {
			if (temp->next->next->data == NodeNeedDel) {
				list1<T>* TempNext = temp->next;
				temp->next = temp->next->next;
				delete TempNext;
				break;
			}
			temp = temp->next;
		} while (temp != ListIn);
		return temp;
	}	
}
/*
链表2类
***************************************************************************
* 1:基于链表1构成,包含的节点类型为list1                                   *
* 2:插入函数重写了，于list1中插入无关，但分离函数中用到了list1的插入函数  *
* 3:构造函数、插入函数遵循                                                *
*	 a:如果头节点指针域数据与头节点地址相同，直接插入                     *
*	 b:非上述情况，开始寻找插入位                                         *
*                                                              10-18-2020 *
***************************************************************************
*/
template <class T>
class list2 {
public:
	list1<T>* firstnode;
	list2(T* datain=NULL) {
		this->firstnode = new list1<T>;
		this->firstnode->next = this->firstnode;
		if (datain) {
			this->firstnode->insert(*datain);
		}
	}
	list2(list2<T>& datain) {
		this->firstnode = datain->firstnode;
	}
	bool insert(T datain) {
		if (this->firstnode->next == this->firstnode) {
			this->firstnode->next = new list1<T>(&datain);
			this->firstnode->next->next = this->firstnode;
		}
		else {
			list1<T>* temp = this->firstnode;
			for (;; temp = temp->next) {
				if (datain < temp->next->data || temp->next==this->firstnode) {
					list1<T>* TempNode = temp->next;
					temp->next = new list1<T>(&datain);
					temp->next->next = TempNode;
					break;
				}
			}
		}
		return 0;
	}
	bool insert(list1<T>* datain) {
		if (this->firstnode->next == this->firstnode) {
			this->firstnode->next = datain;
			datain->next = this->firstnode;
		}
		else {
			list1<T>* temp = this->firstnode;
			for (;; temp = temp->next) {
				if (datain->data < temp->next->data || temp->next == this->firstnode) {
					list1<T>* TempNode = temp->next;
					temp->next = datain;
					datain->next = TempNode;
					break;
				}
			}
		}
		return 0;
	}
};
//链表的分离
list2<char>** DivList(list2<char>* datain) {//模板类用不了的解决办法，换言之如何解决C++中模板类在实例化之前就能使用！！！
	list2<char>** back = new list2<char>* [3];
	back[0] = new list2<char>;
	back[1] = new list2<char>;
	back[2] = new list2<char>;
	list1<char>* temp = datain->firstnode->next;
	for (list1<char>* p = temp->next; temp != datain->firstnode;temp=p ) {
		if ('0'<= temp->data && temp->data <= '9') {
			p = temp->next;
			back[0]->insert(temp);
		}
		else if (('a' <= temp->data && temp->data<= 'z')|| ('A' <= temp->data && temp->data <= 'Z')) {
			p = temp->next;
			back[1]->insert(temp);
		}
		else {
			p = temp->next;
			back[2]->insert(temp);
		}
	}
	cout <<"数字:"<< *back[0]->firstnode;
	cout <<"字母:" << *back[1]->firstnode;
	cout <<"其它符号:" << *back[2]->firstnode;
	return back;
}
/*
template <class T>
list2<T>** DivList(list2<T>* datain) {//模板类用不了的解决办法，换言之如何解决C++中模板类在实例化之前就能使用！！！
	list2<T>** back = new list2<T> * [3]{ NULL };
	list1<T>* temp = datain->firstnode->next;
	for (list1<T>* p = temp->next; temp != datain->firstnode; temp = p) {
		if ('0' <= temp->data && temp->data <= '9') {
			p = temp->next;
			if (back[0] == NULL) {
				back[0] = new list2<T>(temp);
			}
			else {
				back[0]->insert(temp);
			}
		}
		else if (('a' <= temp->data && temp->data <= 'z') || ('A' <= temp->data && temp->data <= 'Z')) {
			p = temp->next;
			if (back[1] == NULL) {
				back[1] = new list2<T>(temp);
			}
			else {
				back[1]->insert(temp);
			}
		}
		else {
			p = temp->next;
			if (back[2] == NULL) {
				back[2] = new list2<T>(temp);
			}
			else {
				back[2]->insert(temp);
			}
		}
	}
	return back;
}
*/


/*
链表3
***************************************************************************
* 1:                       *
* 2:插入函数重写了，于list1中插入无关，但分离函数中用到了list1的插入函数  *
* 3:构造函数、插入函数遵循                                                *
*	 a:如果头节点指针域数据与头节点地址相同，直接插入                     *
*	 b:非上述情况，开始寻找插入位                                         *
*                                                              10-18-2020 *
***************************************************************************
*/
template <class T>
class list3 {
public:
	T Data;
	int Freq;
	list3* Next;
	list3* Prior;
	list3(T* Datain=NULL) {
		if (Datain) {
			this->Next = NULL;
			this->Prior = NULL;
			this->Data = *Datain;
			this->Freq = 0;
		}
		else {//空表
			this->Next = this;//辨别处
			this->Prior = NULL;
			this->Freq = 0;
		}
	}
	list3(T Datain) {
		this->Data = Datain;
		this->Next = NULL;
		this->Prior = NULL;
		this->Freq = 0;
	}
	list3(list3<T>& Datain) {
		this->Data = Datain.Data;
		this->Freq = Datain.Freq;
		this->Next = Datain.Next;
		this->Prior = Datain.Prior;
	}
	bool Insert(T Datain) {
		if (this->Next != this) {//非空表
			list3* PointerTemp = this;
			for (; ; PointerTemp = PointerTemp->Next) {
				if ((PointerTemp->Freq==0 && PointerTemp->Data > Datain) || PointerTemp->Next == NULL) {
					if (PointerTemp == this && PointerTemp->Data > Datain) {//插入链表头
						PointerTemp = this->Next;
						this->Next = new list3(this->Data);
						this->Next->Next = PointerTemp;
						if (PointerTemp) PointerTemp->Prior = this->Next;	//判定是为了一个元素情况					
						this->Next->Prior = this;
						this->Data = Datain;
						break;
					}
					else if (PointerTemp->Next == NULL && PointerTemp->Data <= Datain) {//插入链表末尾
						PointerTemp->Next = new list3(Datain);
						PointerTemp->Next->Prior = PointerTemp;
						PointerTemp->Next->Next = NULL;
						break;
					}
					else {//正常插入前一结点
						list3* StorgePointer = PointerTemp->Prior;
						PointerTemp->Prior = new list3(Datain);
						PointerTemp->Prior->Next = PointerTemp;
						StorgePointer->Next = PointerTemp->Prior;
						PointerTemp->Prior->Prior = StorgePointer;
						break;
					}
				}
			} //访问数据到了最小处，按照小到大排序
		}
		else {//空表
			this->Data = Datain;
			this->Next = NULL;
		}
		return 0;
	}
	bool Insert(list3<T>* Datain) {
		if (this->Next != this) {//非空表
			list3* PointerTemp = this;
			for (; ; PointerTemp = PointerTemp->Next) {
				if (PointerTemp->Freq <= Datain->Freq) {//符合的频率范围
					for (;; PointerTemp = PointerTemp->Next) {
						if (PointerTemp->Data > Datain->Data || PointerTemp->Next==NULL || PointerTemp->Freq < Datain->Freq) {//数据大于插入数据，链表末尾，插入频率大于比较元素
							if (PointerTemp==this && (PointerTemp->Data > Datain->Data || this->Freq < Datain->Freq)) {//插入链表头，数据大于插入的元素，频率小于插入频率
								//下一节点的替换
								Datain->Next = this->Next;
								if(this->Next) this->Next->Prior = Datain;//判定是为了一个元素情况	
								//插入元素于头节点下一位
								this->Next = Datain;
								Datain->Prior = this;
								//数据的替换
								T temp = this->Data;
								int ftemp = this->Freq;
								this->Data = Datain->Data;
								this->Freq = Datain->Freq;
								Datain->Data = temp;
								Datain->Freq = ftemp;
								break;
							}
							else if (PointerTemp->Next == NULL && PointerTemp->Data <= Datain->Data) {//到了屁股且数据小于插入的
								PointerTemp->Next = Datain;
								Datain->Prior = PointerTemp;
								Datain->Next = NULL;
								break;
							}
							else {//正常插入前一结点
								Datain->Next = PointerTemp;
								Datain->Prior = PointerTemp->Prior;
								PointerTemp->Prior->Next = Datain;
								PointerTemp->Prior = Datain;
								break;
							}
						}
					}
					break;
				}
			} //访问数据到了最小处，按照小到大排序
		}
		else {//空表
			*this = *Datain;
		}
		return 0;
	}
	bool locate(list3<T>* Datain) {
		list3<T>* PointerTemp = this;
		for (; PointerTemp; PointerTemp = PointerTemp->Next) {
			if (PointerTemp->Data == Datain->Data) {
				if (PointerTemp == this) {
					++(PointerTemp->Freq);
				}
				else {
					if (PointerTemp->Next != NULL) {
						PointerTemp->Prior->Next = PointerTemp->Next;
						PointerTemp->Next->Prior = PointerTemp->Prior;
					}
					else {
						PointerTemp->Prior->Next = NULL;
					}
					++(PointerTemp->Freq);
					this->Insert(PointerTemp);
				}
				cout << *this;
				return 0;
			}
		}
		return 1;
	}
	bool locate(T Datain) {
		list3<T>* PointerTemp = this;
		for (; PointerTemp; PointerTemp = PointerTemp->Next) {
			if (PointerTemp->Data == Datain) {
				if (PointerTemp == this) {
					++(PointerTemp->Freq);
				}
				else {
					if (PointerTemp->Next != NULL) {
						PointerTemp->Prior->Next = PointerTemp->Next;
						PointerTemp->Next->Prior = PointerTemp->Prior;
					}
					else {
						PointerTemp->Prior->Next = NULL;
					}
					++(PointerTemp->Freq);
					this->Insert(PointerTemp);
				}
				cout << *this;
				return 0;
			}
		}
		return 1;
	}
};
template <class T>
ostream& operator <<(ostream& out, list3<T>& Datain) {
	list3<T>* Pointer = &Datain;
	while (Pointer) {
		out << Pointer->Data << ' ';
		Pointer = Pointer->Next;
	}out << endl;
	return out;
}

void menu() {
	cout << "1:实验一" << endl;
	cout << "2:实验二" << endl;
	cout << "3:实验三" << endl;
	cout << "4:EXIT" << endl;
}
int main() {

	int Choice = 0;
	while (Choice <= 3) {
		menu();
		cin >> Choice;
		switch (Choice){
		case 1: {
			cout << "链表含有多少元素?" << endl;
			list1<int>* text = new list1<int>;
			int i; int data;
			cin >> i;
			cout << "输入元素" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text->insert(data);
			}
			cout<<"链表元素为:" << *text;
			cout << "你想要删除的节点的直接后驱节点数据:" << endl;
			cin >> data;
			text->DelPirNood(data);
			cout << "操作之后的链表" << *text;
			system("PAUSE");
			break;
		}
		case 2: {
			cout << "链表含有多少元素?" << endl;
			list2<char>* text1 = new list2<char>;
			int i; char data;
			cin >> i;
			cout << "输入元素" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text1->insert(data);
			}
			cout << "链表元素为:" << *text1->firstnode;
			DivList(text1);
			system("PAUSE");
			break;
		}
		case 3: {
			cout << "链表含有多少元素?" << endl;
			list3<int>* text3 = new list3<int>;
			int i; int data;
			cin >> i;
			cout << "输入元素" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text3->Insert(data);
			}
			cout << "链表元素为:" << *text3;
			int CHO = 1;
			while (CHO) {
				cout << "_________________" << endl;
				cout << "1:locate元素" << endl;
				cout << "2:EXIT" << endl;
				cout << "_________________" << endl;
				cin >> CHO;
				if (CHO==1) {
					cin >> data;
					text3->locate(data);
				}
				else {
					CHO = 0;
				}
			}
			system("PAUSE");
			break;
		}
		}
		system("cls");
	}

	return 0;
}
