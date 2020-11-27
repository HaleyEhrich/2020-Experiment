#pragma once
#include <iostream>
#define NUMTYPE 1
#define CHARATYPE 2
#define EMPTYNODE 3

class StackCharaNode {
public:
	StackCharaNode() {
		this->Chara = 0;
		this->CharaNum = '0';
		this->Type = EMPTYNODE;
		this->Next = NULL;
	}
	double GetNum() {
		if (this->Type == EMPTYNODE) {
			return -1;
		}
		return this->CharaNum;
	}
	char GetChara() {
		return this->Chara;
	}
	int GetType() {
		return this->Type;
	}
	bool SetThisNode(const double& _charaNum) {
		this->CharaNum = _charaNum;
		this->Type = NUMTYPE;
		return 0;
	}
	bool SetThisNode(const char& _chara) {
		this->Chara = _chara;
		this->Type = CHARATYPE;
		return 0;
	}
	bool SetThisNode(const StackCharaNode& _stackNode) {
		if (_stackNode.Type == NUMTYPE) {
			this->CharaNum = _stackNode.CharaNum;
			this->Type = NUMTYPE;
		}
		else if (_stackNode.Type == CHARATYPE) {
			this->Chara = _stackNode.Chara;
			this->Type = CHARATYPE;
		}
		else {
			using namespace std;
			cout << "This is an empty data" << endl;
			return 1;
		}
		return 0;
	}
	bool SetNextNodeAdress(StackCharaNode* _Next) {
		this->Next = _Next;
		return 0;
	}
	bool SetType(int _Type) {
		this->Type = _Type;
		return 0;
	}//Only use at head element pop;
	bool PopNext() {
      	delete this->Next;
		this->Next = NULL;
		return 0;
	}
	int ThisPriority() {
		if (this->Type == NUMTYPE) {
			return 0;
		}
		else if (this->Type == CHARATYPE) {
			if (this->Chara == '+' || this->Chara == '-') {
				return 1;
			}
			else if (this->Chara == '*' || this->Chara == '/') {
				return 2;
			}
			else if (this->Chara == '(' || this->Chara == ')') {
				return 3;
			}
		}
		else {
			return -1;//Empty
		}
	}
	StackCharaNode* GetNext() {
		return this->Next;
	}
	//const StackCharaNode& GetNextQ() {
	//	return (const StackCharaNode&) * this->Next;
	//}
private:
	double CharaNum;//NUmber store
	char Chara;//Chara store
	int Type;//1-store number,2-store chara,3-din't containg data
	StackCharaNode* Next;
};

class StackChara {
private:
	StackCharaNode* Data;
	StackCharaNode* Top;
	//int Length;
public:
	StackChara() {
		this->Data = new StackCharaNode();
		this->Top = Data;
		//this->Length = 0;
	}
	bool AddData(const double& _charaNum) {
		if (this->Data->GetType() == EMPTYNODE) {
			this->Data->SetThisNode(_charaNum);
		}
		else {
			this->Top->SetNextNodeAdress(new StackCharaNode());
			this->Top = this->Top->GetNext();
			this->Top->SetThisNode(_charaNum);
		}
		return 0;
	}
	bool AddData(const char& _chara) {
		if (this->Data->GetType() == EMPTYNODE) {
			this->Data->SetThisNode(_chara);
		}
		else {
			this->Top->SetNextNodeAdress(new StackCharaNode());
			this->Top = this->Top->GetNext();
			this->Top->SetThisNode(_chara);
		}
		return 0;
	}
	bool AddData(const StackCharaNode& _stackNode) {
		if (this->Data->GetType() == EMPTYNODE) {
			this->Data->SetThisNode(_stackNode);
		}
		else {
			this->Top->SetNextNodeAdress(new StackCharaNode());
			this->Top = this->Top->GetNext();
			this->Top->SetThisNode(_stackNode);
		}
		return 0;
	}
	bool StackEmpty() {//1-Containg data
		return this->Data->GetType() != EMPTYNODE;//1==ture
	}
	bool PopTopData() {
		StackCharaNode* Pointer = this->Data;
		if (this->Data->GetType() == EMPTYNODE || this->Data->GetNext()==NULL ) {
			this->Data->SetType(EMPTYNODE);
			return 0;
		}
		for (; Pointer->GetNext() != this->Top;) {
			Pointer = Pointer->GetNext();
		}
		Pointer->PopNext();
		this->Top = Pointer;
		return 0;
	}
	bool PopFirstData() {
		
		if (this->Data->GetNext() == NULL) {
			this->Data->SetType(EMPTYNODE);
		}
		else {
			StackCharaNode* Pointer = this->Data;
			this->Data = this->Data->GetNext();
			delete Pointer;
		}

		return 0;
	}
	int GetTopPriority() {
		if (this->Data->GetType() == EMPTYNODE) {
			return -1;
		}
		else {
			return this->Top->ThisPriority();
		}
	}
	int GetFirstType() {
		return this->Data->GetType();
	}
	double GetTopNumData() {
		return this->Top->GetNum();
	}
	double GetFirstNumData() {
		return this->Data->GetNum();
	}
	char GetFirstChara() {
		return this->Data->GetChara();
	}
	const StackCharaNode& GetTOP() {//Before get top data should text stack empty!!!!
		return (const StackCharaNode&)*this->Top;
	}
	void out() {
		StackCharaNode* Pointer = this->Data;
		while (Pointer) {
			if (Pointer->GetType() == NUMTYPE) {
				std::cout << Pointer->GetNum() << ' ';
				//std::cout << '$' << Pointer->PopNum() << '$';
			}
			else if (Pointer->GetType() == CHARATYPE) {
				std::cout << Pointer->GetChara() << ' ';
				//std::cout << '#' << Pointer->PopChara() << '#';
			}
			else if (Pointer->GetType() == EMPTYNODE) {
				break;
			}
			Pointer = Pointer->GetNext();
		}//std::cout << std::endl;
	}
};
/*
	StackCharaNode(class):{
		Containg double CharaNum, int Type, char Chara, StackCharaNode* Next;
			Charanum: Store number data, when using this type value equal to CHARARNUM
			Type: Store which type data this node is, '1' means double, '2' means char, '3' means nonthing
			Chara: Store the caculator chara, and type equal to CHARA
			Next: Store the adress of the next chara;
		Function:
			
	}
	StackChara(class):{
		
	}
*/
