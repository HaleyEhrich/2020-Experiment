#include<iostream>
using namespace std;

template<class T>
class node{//�ڵ�class������Ҫ�ṩ��ʼ���Լ����ƹ���,set
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
		if (this->firstnode==NULL) {//����Ϊ��
			return this->firstnode;
		}
		if (head == NULL) {//��ʼ��
			head = this->firstnode;
			last = this->firstnode->next;
		}
		if (last == NULL) {//���Ľڵ㵽��
			return head;
		}
		head = this->utd(last->next, head);//�������ú���������ڵ�
		head->setn(last);
		head = head->next;
		if (head->next == head) {//ӦΪhead��next��ָ��Ϊ��һ���ڵ�ĵ�ַ
			head->next = NULL;
		}
		return head;//��һ�㲻Ҫ��Ҫ���أ�
	}

	
	/*
	node<T>* reverse(node<T>* head)//����ͷ�ڵ��nextָ��
	{
		if (head == NULL || head->next == NULL)
			return head;
		this->firstnode->next = reverse(head->next);
		//���ݣ�����ǰ��ͷ������ӵ����������β��
		head->next->next = head;
		head->next = NULL;
		return this->firstnode->next;
	}

	bool utd() {
		if (this->firstnode->next == NULL) {//����Ϊ��
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
		return 0;//��һ�㲻Ҫ��Ҫ���أ�
	}
	*/
	
};
template<class T>
stl_list<T>* gett(stl_list<T>* a, stl_list<T>* b) {//����ĺϳɣ�����stl_list<T>*
	node<T>* pa = a->firstnode->next;
	node<T>* pb = b->firstnode->next;
	node<T>* pback = a->firstnode;
	if (pa) {//list a empty?
		while (pa && pb) {
			if (pa->data < pb->data) {//a��Ԫ��С��b��������a
				pback = pback->next;
				pa = pa->next;
			}else if (pa->data == pb->data) {//a��Ԫ�ص���b��������a
				pback = pback->next;
				pa = pa->next;
				pb = pb->next;
			}
			else {//b��Ԫ��С��a��������b
				node<T>* temp = pb->next;
				pback->setn(pb);
				pback = pback->next;
				pb = temp;
			}
		}
		if (pb) {//b����û����
			pback->next = pb;
		}
	}
	else {//a����Ϊ��
		a->firstnode->next = b->firstnode->next;
	}
	delete b->firstnode;
	a->utd(NULL);
	return a;
}

int main() {
	node<int>* data1=new node<int>(10);
	node<int>* head;
	//����
	stl_list<int> a(data1);
	a.insert(456);
	a.insert(235647);
	a.insert(215);
	a.insert(23);
	head = a.firstnode->next;
	cout << "a������" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}cout << endl;
	//����b����
	stl_list<int> b;
	b.insert(325);
	b.insert(4869);
	b.insert(26);
	b.insert(23678);
	b.insert(23);
	head = b.firstnode->next;
	cout << "b������" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}cout << endl;
	//a��b����ĺϲ�
	stl_list<int>* back=gett(&a, &b);
	head = back->firstnode->next;
	cout << "a,b����ϲ�������" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}
	cout << endl;
	//back������
	back->utd(NULL);
	head = back->firstnode->next;
	cout << "a,b����ϲ������ݵ���" << endl;
	for (; head; head = head->next) {
		cout << head->data << " ";
	}
	cout << endl;
	return 0;
}

