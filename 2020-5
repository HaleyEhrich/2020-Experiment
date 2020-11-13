#include<iostream>

using namespace std;
template <class T>
class Tree_node {
public:
	Tree_node() {
		this->This_node = NULL;
		this->LChild = NULL;
		this->RChild = NULL;
	}
	Tree_node(T& Datain) {
		this->This_node = new T(Datain);
		this->LChild = NULL;
		this->RChild = NULL;
	}
	T& Backdata() {
		return *this->This_node;
	}
	int Tree_high(int floor=0) {
		if (this->This_node == NULL) {
			return floor;
		}
		int high = ++floor;
		int highL=0;
		int highR=0;
		if (this->LChild) {
			highL=this->LChild->Tree_high(floor);
			if (highL > high) {
				high = highL;
			}
		}
		if (this->RChild) {
			highR=this->RChild->Tree_high(floor);
			if (highR > high) {
				high = highR;
			}
		}
		return high;
	}
	bool Setnode() {
		T data;
		cin >> data;
		if (data == '#') {//If this node should't have data return value 1,to keep this node pointer be NULL;
			return 1;
		}
		else {//Have data set this node;
			this->This_node = new T;
			*(this->This_node) = data;
		}
		this->LChild = new Tree_node<T>;
		if (this->LChild->Setnode()) {//Keep node which not contain data pointer be NULL;
			delete this->LChild;
			this->LChild = NULL;
		}
		this->RChild = new Tree_node<T>;
		if (this->RChild->Setnode()) {//Keep node which not contain data pointer be NULL;
			delete this->RChild;
			this->RChild = NULL;
		}
		return 0;
	}
	bool PrintInFirst() {
		/*
		FOR LOOP EXPLANATION:
		ONE LOOP START:
		AT FIRST PRINT NODE DATA
		Next: If NODE RIGHT CHILD_NODE EXIST, STORE IT;
		Next: IF NODE LEFT CHILD_NODE EXIST, PRINT IT;
			  ELSE:
			        IF: NODE WHICH BEEN POINT HAS RIGHT CHILD_NODE:
					   PRINT ONE "#";
					ELSE: NODE DON'T HAS RIGHT CHILD_NODE
					   PRINT TWO "#"
					POINTER MOVE ELEMENT--"AdreesStore" LAST ELEM, WHICH MEANS THA LAST RIGHT_CHILD NEED TO BEPRINT
		ONE LOOP STOP;
		*/
		if (this->This_node == NULL) {//IN CASE TREE IS EMPTY;
			cout << "This tree is empty;" << endl;
			return 1;
		}
		Tree_node<char>* AdreesStore[100];
		AdreesStore[0] = NULL;
		Tree_node* PointerForScan = this;
		for (int i = 1; PointerForScan != NULL;) {
			cout << *(PointerForScan->This_node) << ' ';
			if (PointerForScan->RChild) {
				AdreesStore[i] = PointerForScan->RChild;
				++i;
			}
			if (PointerForScan->LChild!=NULL) {//If node left child exist pointer move to it
				PointerForScan = PointerForScan->LChild;
			}
			else {//Else move to lase pointer which is need to be print, and it's lase one which stored in element
				if (PointerForScan->RChild == NULL) {
					cout << '#' << ' ' << '#' << ' ';
				}
				else {
					cout << '#' << ' ';
				}
				PointerForScan = AdreesStore[i - 1];
				--i;				
			}
		}cout << endl;
		return 0;
	}
	bool PrintInMid() {
		if (this->This_node == NULL) {//IN CASE TREE IS EMPTY;
			cout << "This tree is empty;" << endl;
			return 1;
		}
		Tree_node<char>* AdreesStore[100];
		AdreesStore[0] = NULL;
		Tree_node* PointerForScan = this;
		for (int i = 1; PointerForScan != NULL;) {
			AdreesStore[i++] = PointerForScan;
			if (PointerForScan->LChild) {//LEFT CHILD EXIST STORE PAR_NODE
				PointerForScan = PointerForScan->LChild;
			}
			else {//LEFT CHILD_NODE DON'T EXIST
				cout << "# ";//PRINT ONE "#" TO FILL LEFT CHILD_NODE;
				cout << *(PointerForScan->This_node) << ' ';//PRINT POINTER WHICH ONE DON'T HAAS LEFT CHILD_NODE
				--i;//POP ONE POINTER ADRESS
				while (!PointerForScan->RChild) {//IF POINTER ALSO DON'T HAVE RIGHT CJILD_NODE, PRINT ONE "#" FILL BLANK
					cout << "# ";
					PointerForScan = AdreesStore[--i];//POINTEER MOVE TO LAST ONE ADRESS WHICH NEED PRINT
					if (PointerForScan == NULL)break;
					cout << *(PointerForScan->This_node) << ' ';
				}
				if (PointerForScan == NULL) {
					break;
				}
				PointerForScan = PointerForScan->RChild;
			}
		}cout << endl;
		return 0;
	}
	bool PrintInLast() {
	/*
	LOOP:
	LOOP START:
	FIRST:STORE NODE DATA;
	NEXT:
		IF NODE HAS LEFT CHILD_NODE:
			POINTER MEVE TO LEFT CHILD_NODE;
		ELSE:
			PRINT ONE # FILL THE BLANK CAUSED BY THE MISSING LEFT CHILD_NODE;
			IF NODE HAS RIGHT CHILD_NODE;
				MOVE TO RIGHT_CHILD;
			ELSE:
				PRINT ONE # FILL THE BLANK CAUSED BY THE MISSING RIGHT CHILD_NODE;
				POP LAST DATA, WHICH IS POINTER;
				WHILE(NOT THE ROOT OF THE TREE AND POINTER ADRESS WAS RIGHT CHILD_NODE OR PARENT DON'T HAVE RIGHT CHILD_NODE)
					PRINT PARENT NODE DATA
				POINTER MAVE LAST PARENT;
				IF(POINTER ISN'T NULL)MOVE RIGHT CHILD_NODE;
	LOOP END;
	MAIN IEAD:
	FIRST: VISIT LEFT CHILD_NODE;
	SECOND: VISIT RIGHT CHILD_NODE;
	LAST: VISIT PARENT;
	SO THERE WILL BE 3 SITUATION:
		1: HAVE LEFT CHILD_NODE
		2: DON'T HAVE LEFT CHILD_NODE, HAVE RIGHT CHILD_NODE;
		3: DON'T HAVE LEFT AND RIGHT CHILD_NODE
			A: NODE IS RIGHT CHILD_NODE OR ROOT NODE OF THIS NODE DON'T HAVE RIGHT_CHILD:
			B: NODE IS LEFT CHILD_NODE, AND ROOT NODE OF THIS NODE HAS RIGHT_CHILD;		
	*/
		if (this->This_node == NULL) {//IN CASE TREE IS EMPTY;
			cout << "This tree is empty;" << endl;
			return 1;
		}
		Tree_node<char>* AdreesStore[100];
		AdreesStore[0] = NULL;
		Tree_node* PointerForScan = this;
		for (int i = 1; PointerForScan != NULL;) {
			AdreesStore[i++] = PointerForScan;
			if (PointerForScan->LChild) {//NODE GET LEFT CHILD_NODE
				PointerForScan = PointerForScan->LChild;
			}
			else {//NODE DON'T HAVE LEFT CHILD_NODE
				cout << '#' << ' ';//FILL LEFT  BLANK
				if (PointerForScan->RChild) {//GET RIGHT CHILD_NODE, MOVE TO THAT
					PointerForScan = PointerForScan->RChild;
				}
				else {//DON'T HAVE RIGHT CHILD_NODE
					cout << '#' << ' ';//FILL BLANK FOR RIGHT CHILD_NODE
					cout << *(PointerForScan->This_node) << ' ';
					--i;
					while (i>1 && (AdreesStore[i - 1]->RChild == PointerForScan || AdreesStore[i - 1]->RChild == NULL)) {
						//VALUE I >1 ENSURE THAT POINTER WON'T POINT AN NULL ADRESS
						PointerForScan = AdreesStore[--i];
						if (PointerForScan == NULL) break;
						cout << *(PointerForScan->This_node) << ' ';
					}
					PointerForScan = AdreesStore[i-1];//BACK TO LAST ONE WHTCH SHOULD PRINT IT'S RIGHT CHILD
					if (PointerForScan == NULL)break;
					PointerForScan = PointerForScan->RChild;
				}
			}
		}cout << endl;
		return 0;
	}
	friend ostream& operator <<(ostream& out, Tree_node<T>* Treehead);//Print data in floor
private:
	T* This_node;
	Tree_node* LChild;
	Tree_node* RChild;
};
/*
template<class T>
ostream& operator << (ostream& out, Tree_node<T>* Treehead) {
	Tree_node<T>* AdreesStore[100];
	AdreesStore[0] = NULL;
	AdreesStore[1] = Treehead;
	for (int i = 0, j = 1;; ++i) {
		cout << "Floor " << i + 1 << endl;
		for (int k = 1; k <= j; ++k) {//Floor i data print
			if (AdreesStore[k] != NULL) {//Ensure poniter not null
				out << *(AdreesStore[k]->This_node) << ' ';
			}
			else {
				out << '#' << ' ';
			}
		}cout << endl;
		//Floor i data print end
		j = j * 2;
		int flag = 1;
		for (int q = j; q;) {//Adress fresh;
			if (AdreesStore[q / 2] == NULL || \
				(AdreesStore[q / 2]->LChild == NULL && AdreesStore[q / 2]->RChild == NULL)) {//Ensure poniter not null
				AdreesStore[q] = NULL;
				AdreesStore[q - 1] = NULL;
				q -= 2;
			}
			else {
				flag = 0;//Floor i+1 have data need to print
				AdreesStore[q] = AdreesStore[q / 2]->RChild;
				AdreesStore[q - 1] = AdreesStore[q / 2]->LChild;
				q -= 2;
			}
		}
		if (flag) {
			break;//End tree data print;
		}
	}
	return out;
}
*/
ostream& 
operator << (ostream& out, Tree_node<char>* Treehead) {
	if (Treehead->This_node == NULL) {//IN CASE TREE IS EMPTY
		cout << "This is an empty tree" << endl;
		return out;
	}
	Tree_node<char>* AdreesStore[100];
	AdreesStore[0] = NULL;
	AdreesStore[1] = Treehead;
	for (int i = 0,j=1;; ++i) {
		cout << "Floor " << i + 1 << endl;
		for (int k=1; k <= j; ++k) {//Floor i data print
			if (AdreesStore[k] != NULL) {//Ensure poniter not null
				out << *(AdreesStore[k]->This_node) << ' ';
			}else{
				out << '#' << ' ';
			}
		}cout << endl;
		//Floor i data print end
		j = j * 2;
		int flag = 1;
		for (int q = j; q;) {//Adress fresh;
			if (AdreesStore[q / 2] == NULL|| \
				(AdreesStore[q / 2]->LChild==NULL && AdreesStore[q / 2]->RChild==NULL) ) {//Ensure poniter not null
				AdreesStore[q] = NULL;
				AdreesStore[q-1] = NULL;
				q -= 2;
			}
			else {
				flag = 0;//Floor i+1 have data need to print
				AdreesStore[q] = AdreesStore[q / 2]->RChild;
				AdreesStore[q-1] = AdreesStore[q / 2]->LChild;
				q -= 2;
			}
		}
		if (flag) {
			break;//End tree data print;
		}
	}
	return out;
 }

template <class T>
class Tree_my {
public:
	Tree_my(int floor) {
		this->num = (int)pow(2, floor)-1;
		this->Elem = new T[this->num];
	}
	bool set_tree() {
		T data;
		for (int i = 0; i < this->num; i++) {
			cin >> data;
			if (data == '$') {
				for (int j = i; j < this->num; ++j) {
					this->Elem[j] = '#';
				}
				if (i == 0) {
					return 1;
				}
				break;
			}
			else {
				this->Elem[i] = data;
			}
		}
		return 0;
	}
	bool PrintInFirst() {
		if (this->Elem[0] == '#') {
			cout << "Empty tree" << endl;
			return 1;
		}
		for (int i = 1; i != this->num;) {
			cout << this->Elem[i-1] << ' ';
			if (i * 2 < this->num) {
				i = i * 2;
			}
			else if (i * 2 > this->num && i % 2 != 0) {
				while (i % 2 != 0) {
					i /= 2;
				}
				i += 1;
			}
			else if(i*2 >= this->num && i % 2 == 0){
				i += 1;
			}
			
		}cout << this->Elem[this->num - 1] << endl;
		return 0;
	}

private:
	T* Elem;
	int num;
};

void menu() {
	cout << "1: Output the height of the binary tree" << endl;
	cout << "2: Preorder traversal of binary tree stored in array" << endl;
	cout << "3: Traversal of the binary tree stored in the linked list" << endl;
	cout << "4:Exit" << endl;
	cout << "Input your choice:";
}
void menu2() {
	cout << "1:Input data by floor;" << endl;
	cout << "2:Input data by preorder;" << endl;
	cout << "3:Input data by post sequence;" << endl;
	cout << "Input your choice:";
}
int main() {
	char choice='1';
	while (choice > '0' && choice < '4') {
		menu();
		cin >> choice;
		if (choice == '1') {
			Tree_node<char>* treehead = new Tree_node<char>;
			cout << "Input data:";
			if (treehead->Setnode()) {
				cout << "You bulid an empty tree" << endl;
			}
			else {
				cout << "The tree you bulid:" << endl;
				cout << treehead << endl;
			}
			cout << "The height of this tree:" << treehead->Tree_high() << endl;
			system("pause");
		}
		else if (choice == '2') {
			int floor;
			cout << "Input hoe many floor that it will be:" << endl;
			cin >> floor;
			cout << "Input data by floor,and end by '$':";
			Tree_my<char>* treehead = new Tree_my<char>(floor);
			if (treehead->set_tree()) {
				cout << "You bulid an empty tree" << endl;
			}
			else {
				cout << "Preorder traversal:" << endl;
				treehead->PrintInFirst();
			}
			system("pause");
		}
		else if (choice == '3') {
			Tree_node<char>* treehead = new Tree_node<char>;
			cout << "Input data:";
			if (treehead->Setnode()) {
				cout << "You bulid an empty tree" << endl;
			}
			else {
				cout << "The tree you bulid:" << endl;
				cout << treehead << endl;
				cout << "Preorder traversal:" << endl;
				treehead->PrintInFirst();
				cout << "Midorder traversal:" << endl;
				treehead->PrintInMid();
				cout << "Subsequent traversal:" << endl;
				treehead->PrintInLast();
			}
			system("pause");
		}
		system("cls");
	}
	return 0;
}

/*
					if (i>1 && AdreesStore[i - 1]->RChild == PointerForScan) {//POINTER POINT A RIGHT CHILD_NODE
						while (i>1 && AdreesStore[i - 1]->RChild == PointerForScan) {//IF THIS NODE IS LAST PARENT RIGHT CHILD_NODE
							PointerForScan = AdreesStore[--i];
							if (PointerForScan == NULL) {
								break;
							}
							cout << *(PointerForScan->This_node) << ' ';
						}
					}
					PointerForScan = AdreesStore[i-1];
					if (PointerForScan == NULL) break;
				    while(AdreesStore[i-1]->RChild == NULL) {//IF NODE RIGHT CHILD_NODE NOT EXIST, PRINT THIS NODE DATA
						PointerForScan = AdreesStore[--i];
						//IN FACT THE POINT OF POINTERFORSCAN DON'T GET CHANGE, JUST BECAUSE LAST STEP DIDN'T MAKE I-1, SO THERE WILL BE ON MORE DATA EXIST IN ELEMENT
						//在上一步替换后，不能确定右节点是否存在，故没有对数组内地址进行减去，所以在此处确认了右节点的不存在，先进行了数组的数据删除，再来输出数据
						if (PointerForScan == NULL)break;
						cout << *(PointerForScan->This_node) << ' ';
					}
*/
