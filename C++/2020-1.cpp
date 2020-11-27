#include<iostream>
#define Maxsize 100
using namespace std;
template <class T>
class examnation1 {
public:
	T list[Maxsize];
	int length;
	examnation1(const T *str=NULL,int len=0) {//链表构造函数，可提供数组、int型指针，并接受参数传入元素个数
		if (str == NULL) {
			this->length = 0;
			return;
		}
		for (int i = 0; i<len; ++i) {
			this->sert(str[i]);//this->length && this->list均在sert内初始化
		}
	}
	bool add(const T &addelem) {
		return this->sert(addelem);
	}
	bool sert(const T &sertelem) {//insert data for this list
		if (this->length == Maxsize) {
			return 1;
		}
		for (int i=this->length-1; i >= -1; --i) {//Important:The first data node insert should happened at firstnode;
			if (i==-1||this->list[i] <= sertelem) {
				this->list[i+1] = sertelem;
				++this->length;
				break;
			}
			this->list[i + 1] = this->list[i];
		}
		return 0;
	}
	bool utd() {//list up to down
		if (this->length == 0) {
			return 1;
		}
		T temp;
		for (int i = 0, j = this->length - 1; i < j; ++i, --j) {
			temp=this->list[i];
			this->list[i] = this->list[j];
			this->list[j] = temp;
		}
		return 0;
	}
	bool Cyclic_disaplacment(int k) {
		k %= this->length;
		if (!k) return 0;
		int i = 0;
		T temp = this->list[k];
		for (int j = k, lastj = 0;;) {
			++i;
			if (lastj == k) {
				this->list[j] = temp;
				break;
			}
			else {
				this->list[j] = this->list[lastj];
			}
			j = lastj;
			lastj = j - k;
			if (lastj < 0)lastj += this->length;
		}
		int num = this->length / i;
		for (i = 1; i < num; ++i) {
			temp = this->list[k + i];
			for (int j = k + i,lastj = i;;) {
				if (lastj == k+i) {
					this->list[j] = temp;
					break;
				}
				else {
					this->list[j] = this->list[lastj];
				}
				j = lastj;
				lastj = j - k;
				if (lastj < 0)lastj += this->length;
			}
		}
		return 0;
		
	}
	/*bool Cyclic_displacement(int k, T temp=0, int num=0) {
		if (num == 0) {
			k %= this->length;
			if (k == this->length / 2) {
				for (; num < this->length / 2; num++) {
					temp = this->list[num];
					this->list[num] = this->list[ num + this->length/2];
					this->list[this->length/2 + num] = temp;
				}
				return 0;
			}
			temp = this->list[k];		
			this->list[k] = this->list[num];
		}
		int lasti = num - k;
		if (lasti < 0) lasti += this->length;
		if (lasti == k) {
			this->list[num] = temp;
			return 0;
		}
		this->list[num] = this->list[lasti];//每层先替换再进入下一层
		this->Cyclic_displacement(k, temp, lasti);
		return 0;
	}*/
	//非递归
	/*bool Cyclic_displacement(int num) {
		if (num >= this->length)num %= this->length;//位移量k的处理
		if (!num) return 0;//num为0，结束
		T temp;
		if(num==this->length/2){//特殊情况，但此时时间复杂度为length/2;
			for (; num < this->length / 2; num++) {
				temp = this->list[num];
				this->list[num] = this->list[ num + this->length/2];
				this->list[this->length/2 + num] = temp;
			}
			return 0;
		}
		temp = this->list[num];
		this->list[num] = this->list[0];
		for (int i = 0,lasti; ;i=lasti) {
			lasti = i - num;
			if (lasti < 0) lasti += this->length;
			if (lasti == num) {
				this->list[i] = temp;
				break;
			}
			else {
				this->list[i] = this->list[lasti];
			}
		}
		return 0;
	}*/ 
	
};
int main() {
	examnation1<int> text1;
	text1.add(346);
	text1.add(36576);
	text1.sert(263);
	text1.sert(6753);
	text1.sert(34);
	text1.sert(4);
	text1.sert(56);
	text1.sert(456);
	text1.sert(78998);
	text1.sert(356);
	text1.sert(3);
	text1.sert(24536);
	text1.sert(711);
	cout << "插入后顺序表的数据" << endl;
	for (int i = 0; i < text1.length; i++) {
		cout << text1.list[i] << ' ';
	}cout << endl;
	/*
	text1.utd();
	cout << "顺序表逆置后的数据" << endl;
	for (int i = 0; i < text1.length; i++) {
		cout << text1.list[i] << ' ';
	}cout << endl;

	text1.utd();
	*/
	text1.Cyclic_disaplacment(8);
	cout << "顺序表右移3位的数据" << endl;
	for (int i = 0; i < text1.length; i++) {
		cout << text1.list[i] << ' ';
	}
	cout << endl;
	return 0;
}
