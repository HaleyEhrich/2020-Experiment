#pragma once
#include<string>
#include <stdio.h>  // ?????????
#include <conio.h>  // ??????????
#include <iostream>
#include"graph.h"
using namespace std;

class _hashNode {
private:
    int key;
    VertexChain* value;
    _hashNode* next;
public:
    _hashNode() {
        this->key = 0;
        this->value = nullptr;
        this->next = nullptr;
    }
    _hashNode( VertexChain* value,int key=0):key(key),value(value),next(nullptr){}
    void setKey(string valueName) {
        const char* str = valueName.c_str();
        this->key = str[strlen(str) / 2];
    }
    VertexChain* getvalue() { return this->value; }
    _hashNode* getNext() { return this->next; }
    int getKey() { return key; }
    void setKey(int key) { this->key = key; }
    void setNext(_hashNode* next) { this->next = next; }

};
class _hashTable {
private:
    _hashNode* _number;
    //_hashNode* _name;
    int  length;
    int p;
public:
    int _hash(int key) { return key % p; }
    _hashTable(Graph* graph) {
        this->_number = nullptr;
        this->length = 0;
        this->p = 2;
        if (!graph)return;
        int temp1 = 0,time=0;
        length = graph->getVerNum();
        p = findP(graph->getVerNum());
        this->_number = new _hashNode[length];
        VertexChain* ptr = graph->getFirAdress();
        _hashNode* p1, * p = nullptr;
        cout<<"ZZZZ"<<endl;
        while (true){
            if (ptr == graph->getEndAiress())time++;
            temp1 = this->_hash(ptr->getVertex());
            p1 = &_number[temp1];
            //p2 = &_name[temp2];
            while (true) {
                if (!p1) {
                    p1 = new _hashNode(ptr, ptr->getVertex());
                    p->setNext(p1);
                    break;
                }
                else {
                    p = p1;
                    p1 = p1->getNext();
                }
            }
            ptr = ptr->getNextVerAdress();
            if (time == 1)break;
            cout<<"ZZdsfhZZ"<<endl;
        }
    }
    void setLength(int length) { this->length = length; }
    int getLength() { return this->length; }
    VertexChain* findVertexChain(int key) {
        int k = _hash(key);
        _hashNode* ptr = _number[k].getNext();
        while (ptr) {
            cout<<"AAAA"<<endl;
            if (ptr->getKey() == key)
                return ptr->getvalue();
            ptr = ptr->getNext();
        }
        cout<<"CCCC"<<endl;
        return nullptr;
    }
    bool _isPrimMothed(int n) {
        if (n == 2 || n == 3) return true;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    }
    int findP(int l) {
        int k = 1;
        for (int i = 2; i < l; ++i)
            if (_isPrimMothed(i))k = i;
        return k;
    }
};
