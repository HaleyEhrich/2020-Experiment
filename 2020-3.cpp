#include<iostream>

using namespace std;
/*
**************************************************************************
* ����1��                                                                *
* 1:����ѭ��������������ô����ڲ���ʱָ��ʹ�ø��ӱ�����������������   *
*	ѭ��������Ĳ���λ���ж���Ϊͷ�ڵ�ȱ���жϱ�־������鷳��           *
* 2:���캯�������뺯����ѭ��                                             *
*	A:�ڵ���һ�ڵ㲻��������Ϊ�գ���ʱֱ�Ӳ���ýڵ㣻                   *
*	B:��һ�ڵ���ڣ��½��ڵ����                                         *
* 3:����ɾ���ڵ�ļ������⣺                                             *
*	A:��Ϊthisָ�����������Ҫ����һ���ж����ڷ�ֹthis��ɾ����           *
*	B:����ǰ��ɾ�����Խ�����⣬������Ҫ���ؽڵ�ָ�룻                   *
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
	list1(list1<T>& datain) {//�����������򣬸���ָ����
		this->data = datain.data;
		this->next = datain.next;
	}
	//�ڵ�Ĳ���
	bool insert(list1<T>* datain) {//����ڵ�;�ڵ���ǰӦ�þ�������λ��;
		if (this->next == NULL) {
			this->data = datain->data;
			this->next = this;
		}
		else {
			list1<T>* temp = this->next;
			if (temp == this || (temp->data > datain->data && this->data <= datain->data) || this->data > temp->data) {//����ֻ��1��Ԫ�أ���һ��Ԫ�ش��ڲ���Ԫ��,������Ҳ�Ȳ���Ԫ��Сʱ����Ԫ��
				this->next = datain;
				this->next->next = temp;
			}
			else {
				for (;; temp = temp->next) {
					if ((temp->next->data > datain->data && temp->data <= datain->data) || temp->data > temp->next->data) {//��һ��Ԫ�ش��ڲ���Ԫ��,������Ҳ�Ȳ���Ԫ��Сʱ����Ԫ��
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
	bool insert(T datain) {//��������ΪT������
		if (this->next == NULL) {
			this->data = datain;
			this->next = this;
		}
		else {
			list1<T>* temp = this->next;
			if (temp == this || (temp->data > datain && this->data <= datain) || this->data > temp->data) {//����ֻ��1��Ԫ�أ���һ��Ԫ�ش��ڲ���Ԫ��,������Ҳ�Ȳ���Ԫ��Сʱ����Ԫ��
				this->next = new list1<T>(&datain);
				this->next->next = temp;
			}
			else {
				for (;; temp = temp->next) {
					if ((temp->next->data > datain && temp->data <= datain) || temp->data > temp->next->data) {//��һ��Ԫ�ش��ڲ���Ԫ��,������Ҳ�Ȳ���Ԫ��Сʱ����Ԫ��
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
	//�ڵ��ɾ��
	bool DelNood(list1<T>* NodeNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {//һ��Ԫ������
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
			//ʧ�ܵ�д��
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
	//ֱ��ǰ���ڵ��ɾ��
	bool DelPirNood(list1<T>* NodeNNeedDel) {
		if (this->next == NULL) {
			return 1;
		}
		if (this->next == this) {//һ��Ԫ������
			return 1;
		}
		else {
			list1<T>* temp = this;
			do {
				if (temp->next->next == NodeNNeedDel) {
					if (temp->next == this) {//ǰ���ڵ�Ϊͷ�ڵ�
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
		if (this->next == this) {//һ��Ԫ������
			return 1;
		}
		else {
			list1<T>* temp = this;
			do {
				//cout << temp->data << endl;
				if (temp->next->next->data == NodeNeedDel) {
					if (temp->next == this) {//ǰ���ڵ�Ϊͷ�ڵ�
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
//�����������
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
//ɾ���������д��!!!!!!
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
����2��
***************************************************************************
* 1:��������1����,�����Ľڵ�����Ϊlist1                                   *
* 2:���뺯����д�ˣ���list1�в����޹أ������뺯�����õ���list1�Ĳ��뺯��  *
* 3:���캯�������뺯����ѭ                                                *
*	 a:���ͷ�ڵ�ָ����������ͷ�ڵ��ַ��ͬ��ֱ�Ӳ���                     *
*	 b:�������������ʼѰ�Ҳ���λ                                         *
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
//����ķ���
list2<char>** DivList(list2<char>* datain) {//ģ�����ò��˵Ľ���취������֮��ν��C++��ģ������ʵ����֮ǰ����ʹ�ã�����
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
	cout <<"����:"<< *back[0]->firstnode;
	cout <<"��ĸ:" << *back[1]->firstnode;
	cout <<"��������:" << *back[2]->firstnode;
	return back;
}
/*
template <class T>
list2<T>** DivList(list2<T>* datain) {//ģ�����ò��˵Ľ���취������֮��ν��C++��ģ������ʵ����֮ǰ����ʹ�ã�����
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
����3
***************************************************************************
* 1:                       *
* 2:���뺯����д�ˣ���list1�в����޹أ������뺯�����õ���list1�Ĳ��뺯��  *
* 3:���캯�������뺯����ѭ                                                *
*	 a:���ͷ�ڵ�ָ����������ͷ�ڵ��ַ��ͬ��ֱ�Ӳ���                     *
*	 b:�������������ʼѰ�Ҳ���λ                                         *
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
		else {//�ձ�
			this->Next = this;//���
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
		if (this->Next != this) {//�ǿձ�
			list3* PointerTemp = this;
			for (; ; PointerTemp = PointerTemp->Next) {
				if ((PointerTemp->Freq==0 && PointerTemp->Data > Datain) || PointerTemp->Next == NULL) {
					if (PointerTemp == this && PointerTemp->Data > Datain) {//��������ͷ
						PointerTemp = this->Next;
						this->Next = new list3(this->Data);
						this->Next->Next = PointerTemp;
						if (PointerTemp) PointerTemp->Prior = this->Next;	//�ж���Ϊ��һ��Ԫ�����					
						this->Next->Prior = this;
						this->Data = Datain;
						break;
					}
					else if (PointerTemp->Next == NULL && PointerTemp->Data <= Datain) {//��������ĩβ
						PointerTemp->Next = new list3(Datain);
						PointerTemp->Next->Prior = PointerTemp;
						PointerTemp->Next->Next = NULL;
						break;
					}
					else {//��������ǰһ���
						list3* StorgePointer = PointerTemp->Prior;
						PointerTemp->Prior = new list3(Datain);
						PointerTemp->Prior->Next = PointerTemp;
						StorgePointer->Next = PointerTemp->Prior;
						PointerTemp->Prior->Prior = StorgePointer;
						break;
					}
				}
			} //�������ݵ�����С��������С��������
		}
		else {//�ձ�
			this->Data = Datain;
			this->Next = NULL;
		}
		return 0;
	}
	bool Insert(list3<T>* Datain) {
		if (this->Next != this) {//�ǿձ�
			list3* PointerTemp = this;
			for (; ; PointerTemp = PointerTemp->Next) {
				if (PointerTemp->Freq <= Datain->Freq) {//���ϵ�Ƶ�ʷ�Χ
					for (;; PointerTemp = PointerTemp->Next) {
						if (PointerTemp->Data > Datain->Data || PointerTemp->Next==NULL || PointerTemp->Freq < Datain->Freq) {//���ݴ��ڲ������ݣ�����ĩβ������Ƶ�ʴ��ڱȽ�Ԫ��
							if (PointerTemp==this && (PointerTemp->Data > Datain->Data || this->Freq < Datain->Freq)) {//��������ͷ�����ݴ��ڲ����Ԫ�أ�Ƶ��С�ڲ���Ƶ��
								//��һ�ڵ���滻
								Datain->Next = this->Next;
								if(this->Next) this->Next->Prior = Datain;//�ж���Ϊ��һ��Ԫ�����	
								//����Ԫ����ͷ�ڵ���һλ
								this->Next = Datain;
								Datain->Prior = this;
								//���ݵ��滻
								T temp = this->Data;
								int ftemp = this->Freq;
								this->Data = Datain->Data;
								this->Freq = Datain->Freq;
								Datain->Data = temp;
								Datain->Freq = ftemp;
								break;
							}
							else if (PointerTemp->Next == NULL && PointerTemp->Data <= Datain->Data) {//����ƨ��������С�ڲ����
								PointerTemp->Next = Datain;
								Datain->Prior = PointerTemp;
								Datain->Next = NULL;
								break;
							}
							else {//��������ǰһ���
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
			} //�������ݵ�����С��������С��������
		}
		else {//�ձ�
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
	cout << "1:ʵ��һ" << endl;
	cout << "2:ʵ���" << endl;
	cout << "3:ʵ����" << endl;
	cout << "4:EXIT" << endl;
}
int main() {

	int Choice = 0;
	while (Choice <= 3) {
		menu();
		cin >> Choice;
		switch (Choice){
		case 1: {
			cout << "�����ж���Ԫ��?" << endl;
			list1<int>* text = new list1<int>;
			int i; int data;
			cin >> i;
			cout << "����Ԫ��" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text->insert(data);
			}
			cout<<"����Ԫ��Ϊ:" << *text;
			cout << "����Ҫɾ���Ľڵ��ֱ�Ӻ����ڵ�����:" << endl;
			cin >> data;
			text->DelPirNood(data);
			cout << "����֮�������" << *text;
			system("PAUSE");
			break;
		}
		case 2: {
			cout << "�����ж���Ԫ��?" << endl;
			list2<char>* text1 = new list2<char>;
			int i; char data;
			cin >> i;
			cout << "����Ԫ��" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text1->insert(data);
			}
			cout << "����Ԫ��Ϊ:" << *text1->firstnode;
			DivList(text1);
			system("PAUSE");
			break;
		}
		case 3: {
			cout << "�����ж���Ԫ��?" << endl;
			list3<int>* text3 = new list3<int>;
			int i; int data;
			cin >> i;
			cout << "����Ԫ��" << endl;
			for (; i > 0; --i) {
				cin >> data;
				text3->Insert(data);
			}
			cout << "����Ԫ��Ϊ:" << *text3;
			int CHO = 1;
			while (CHO) {
				cout << "_________________" << endl;
				cout << "1:locateԪ��" << endl;
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