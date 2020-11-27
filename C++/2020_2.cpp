#include<iostream>
using namespace std;

template<class T>
class node{//节点class，仅需要提供初始化以及复制构造,set
public:
	T data;
	node<T>* next;
	node(const T& datain = -23896549) {
		this->data = datain;
		this->next = NULL;
	}
	node(const node<T>& datain) {
		this->data = datain.data;
		this->next = datain.next;
	}
	bool set(const node<T>& datain) {
		this->data = datain.data;
		this->next = datain.next;
		return 0;
	}
	bool set(const T& datain) {
		this->data = datain;
		return 0;
	}
	bool setn(node<T>* datain) {
		node<T>* temp = this->next;
		this->next = datain;
		datain->next = temp;
		return 0;
	}
};
template <class T>
bool operator <= (const node<T>& first, const node<T>& sencond) {//operator <
	if (&sencond == NULL) {
		return true;
	}
	else if (&first == NULL) {
		return false;
	}
	else {
		return first.data <= sencond.data;
	}
}
template <class T>
bool operator == (const node<T>& first, const node<T>& sencond) {//operator <
	if (sencond == NULL|| first == NULL) {
		return false;
	}
	else {
		return first.data == sencond.data;
	}
}
template <class T>
bool operator < (const node<T>& first, const node<T>& sencond) {//operator <
	if (sencond == NULL) {
		return true;
	}
	else if (first == NULL) {
		return false;
	}
	else {
		return first.data < sencond.data;
	}
}

template <class T>
class stl_list {
public:
	node<T>* firstnode;
	stl_list(node<T>* datain=NULL) {
		this->firstnode = new node<T>;//First node
		if (datain) {//If get data input, set a new node;
			this->firstnode->setn(datain);
		}
	}
	stl_list(const stl_list& datain) {
		this->firstnode = datain.firstnode;
	}
	bool insert(node<T>* datain) {
		node<T>* ptemp = this->firstnode;
		while (ptemp) {
			if (*datain <= *(ptemp->next)) {
				ptemp->setn(datain);
				break;
			}
			else {
				ptemp = ptemp->next;
			}
		}
		return 0;
	}
	bool insert(T datain) {
		node<T>* ptemp = this->firstnode;
		node<T>* temp = new node<T>(datain);
		while (ptemp) {
			if (*temp <= *(ptemp->next)) {
				ptemp->setn(temp);
				break;
			}
			else {
				ptemp = ptemp->next;
			}
		}
		return 0;
	}
	node<T>* utd(node<T>* last, node<T>* head=NULL) {
		if (this->firstnode==NULL) {//链表为空
			return this->firstnode;
		}
		if (head == NULL) {//初始化
			head = this->firstnode;
			last = this->firstnode->next;
		}
		if (last == NULL) {//最后的节点到了
			return head;
		}
		head = this->utd(last->next, head);//接受逆置后最后的链表节点
		head->setn(last);
		head = head->next;
		if (head->next == head) {//应为head的next的指向为第一个节点的地址
			head->next = NULL;
		}
		return head;//第一层不要需要返回；
	}

	
	/*
	node<T>* reverse(node<T>* head)//传入头节点的next指针
	{
		if (head == NULL || head->next == NULL)
			return head;
		this->firstnode->next = reverse(head->next);
		//回溯：将当前表头结点链接到逆序链表的尾部
		head->next->next = head;
		head->next = NULL;
		return this->firstnode->next;
	}

	bool utd() {
		if (this->firstnode->next == NULL) {//链表为空
			return 1;
		}
		node<T>* PointerTemp = this->firstnode->next,Temp;
		this->firstnode->next = NULL;
		while (PointerTemp) {
			Temp = PointerTemp;
			PointerTemp = PointerTemp->next;

			Temp->next = this->firstnode->next;
			this->firstnode->next = Temp;
		}
		return 0;//第一层不要需要返回；
	}
	*/
	
};
template<class T>
stl_list<T>* gett(stl_list<T>* a, stl_list<T>* b) {//链表的合成；返回stl_list<T>*
	node<T>* pa = a->firstnode->next;
	node<T>* pb = b->firstnode->next;
	node<T>* pback = a->firstnode;
	if (pa) {//list a empty?
		while (pa && pb) {
			if (pa->data < pb->data) {//a链元素小于b链，插入a
				pback = pback->next;
				pa = pa->next;
			}else if (pa->data == pb->data) {//a链元素等于b链，插入a
				pback = pback->next;
				pa = pa->next;
				pb = pb->next;
			}
			else {//b链元素小于a链，插入b
				node<T>* temp = pb->next;
				pback->setn(pb);
				pback = pback->next;
				pb = temp;
			}
		}
		if (pb) {//b链表还没接完
			pback->next = pb;
		}
	}
	else {//a链表为空
		a->firstnode->next = b->firstnode->next;
	}
	delete b->firstnode;
	a->utd(NULL);
	return a;
}

int main() {
	node<int>* data1=new node<int>(10);
	node<int>* head;
	//插入
	stl_list<int> a(data1);
	a.insert(456);
	a.insert(235647);
	a.insert(215);
	a.insert(23);
	head = a.firstnode->next;
	cout << "a的数据" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}cout << endl;
	//构建b链表
	stl_list<int> b;
	b.insert(325);
	b.insert(4869);
	b.insert(26);
	b.insert(23678);
	b.insert(23);
	head = b.firstnode->next;
	cout << "b的数据" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}cout << endl;
	//a，b链表的合并
	stl_list<int>* back=gett(&a, &b);
	head = back->firstnode->next;
	cout << "a,b链表合并后数据" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}
	cout << endl;
	//back链表倒置
	back->utd(NULL);
	head = back->firstnode->next;
	cout << "a,b链表合并后数据倒置" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}
	cout << endl;
	return 0;
}

