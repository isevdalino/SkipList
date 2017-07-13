#ifndef SKIPLISTNODE_H
#define SKIPLISTNODE_H
#include<vector>

template<typename T>
class SkipListNode
{
  public:
  T value;
  std::vector<SkipListNode*> next;
  SkipListNode* previous;
  SkipListNode(T value,int level);
};

template<typename T>
SkipListNode<T>::SkipListNode(T value,int level)
{
  this->value=value;
  next.assign(level,nullptr);
  previous=nullptr;
}

#endif // SKIPLISTNODE_H
