#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "SkipListNode.h"
#include <ctime>
#include <cstdlib>

template<typename T>
class SkipList
{
    private:
    const int maxHeight=32;
    SkipListNode<T>* head;
    int currHeight;
    void deleteSL();
    public:
    class Iterator{
      private:
      SkipListNode<T>* currEl;
      public:
      Iterator(SkipListNode<T>* el);
      T operator*();
      void operator++();
      bool operator !=(Iterator it);
    };
    SkipList();
    SkipList(const SkipList<T>& other);
    SkipList& operator=(const SkipList<T>& other);
    ~SkipList();
    void add(T value);
    bool contains(T value);
    void remove(int value);
    Iterator begin()const;
    Iterator end()const;
};

template<typename T>
SkipList<T>::SkipList(){
  currHeight=0;
  head=new SkipListNode<T>(T(),maxHeight);
}

template<typename T>
SkipList<T>::SkipList(const SkipList<T>& other){
  currHeight=0;
  head=new SkipListNode<T>(T(),maxHeight);
  for(SkipList<T>::Iterator it=other.begin();it!=other.end();++it){
    this->add(*it);
  }
}

template<typename T>
SkipList<T>& SkipList<T>::operator=(const SkipList<T>& other){
  if(this!=&other){
    deleteSL();
    for(SkipList<int>::Iterator it=other.begin();it!=other.end();++it){
      this->add(*it);
    }
  }
  return *this;
}

template<typename T>
SkipList<T>::~SkipList(){
  this->deleteSL();
}

template<typename T>
void SkipList<T>::deleteSL(){
  std::vector<T> container;
  for(SkipList<T>::Iterator it=this->begin();it!=this->end();++it){
    container.push_back(*it);
  }
  for(typename std::vector<T>::iterator it=container.begin();it!=container.end();++it){
    this->remove(*it);
  }
}

template<typename T>
void SkipList<T>::add(T value){
  int level = 0;
  srand((unsigned)time( NULL ));
  for (; rand()%2==1&&currHeight<maxHeight; level++){
    if(level>currHeight){
      currHeight=level;
      break;
    }
  }
  SkipListNode<T>* newNode = new SkipListNode<T>(value, level + 1);
  SkipListNode<T>* currNode = head;
  for (int i = currHeight; i >= 0; i--){
    for (; currNode->next[i] != nullptr; currNode = currNode->next[i]){
      if (currNode->next[i]->value > value){
        break;
      }
      }
    if(i <= level){
      newNode->next[i] = currNode->next[i];
      currNode->next[i] = newNode;
      newNode->previous=currNode;
    }
  }
}

template<typename T>
bool SkipList<T>::contains(T value){
  SkipListNode<T>* currNode = head;
  for (int i = currHeight; i >= 0; i--){
    for (; currNode->next[i] != nullptr; currNode = currNode->next[i]){
      if (currNode->next[i]->value > value) break;
      if (currNode->next[i]->value == value) return true;
    }
  }
  return false;
}

template<typename T>
void SkipList<T>::remove(int value){
  SkipListNode<T>* currNode = head;
  for (int i = currHeight; i >= 0; i--){
    for (; currNode->next[i] != nullptr; currNode = currNode->next[i]){
      if (currNode->next[i]->value == value){
        SkipListNode<T>* tmp=currNode->next[i];
        currNode->next[i] = currNode->next[i]->next[i];
        if(currNode->next[i]!=nullptr&&currNode->next[i]->next[i]!=nullptr){
           currNode->next[i]->next[i]->previous=currNode->next[i];
        }
        delete tmp;
        break;
      }

      if (currNode->next[i]->value > value) break;
    }
  }
}

template<typename T>
typename SkipList<T>::Iterator SkipList<T>::begin()const{
  return Iterator(head->next[0]);
}

template<typename T>
typename SkipList<T>::Iterator SkipList<T>::end()const{
  return Iterator(nullptr);
}

template<typename T>
SkipList<T>::Iterator::Iterator(SkipListNode<T>* el){
  currEl=el;
}

template<typename T>
T SkipList<T>::Iterator::operator*(){
  return currEl->value;
}

template<typename T>
void SkipList<T>::Iterator::operator++(){
  if(currEl->next[0]!=nullptr){
    currEl=currEl->next[0];
  }else{
    currEl=nullptr;
  }
}

template<typename T>
bool SkipList<T>::Iterator::operator !=(Iterator it){
  if(currEl==nullptr&&it.currEl!=nullptr||currEl!=nullptr&&it.currEl==nullptr){
    return true;
  }else if(currEl==nullptr&&it.currEl==nullptr){
    return false;
  }else if(currEl->value!=it.currEl->value){
    return true;
  }else{
  return false;
  }
}

#endif // SKIPLIST_H
