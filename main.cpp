#include <iostream>
#include "SkipList.h"

template<typename T>
SkipList<T> mergeSLS(SkipList<T> firstSl,SkipList<T> secondSl){
   SkipList<T> resultSL;
   for(SkipList<int>::Iterator it=firstSl.begin();it!=firstSl.end();++it){
     resultSL.add(*it);
   }
   for(SkipList<int>::Iterator it=secondSl.begin();it!=secondSl.end();++it){
     if(!resultSL.contains(*it)){
       resultSL.add(*it);
     }
   }
   return resultSL;
}

template<typename T>
SkipList<T> intersectSLS(SkipList<T> firstSl,SkipList<T> secondSl){
   SkipList<T> resultSL;
   for(SkipList<int>::Iterator it=firstSl.begin();it!=firstSl.end();++it){
     if(secondSl.contains(*it)){
        resultSL.add(*it);
     }
   }
   return resultSL;
}

int main()
{
    SkipList<int> mySl;
    mySl.add(1);
    mySl.add(2);
    mySl.add(3);
    mySl.add(4);
    mySl.add(5);
    std::cout<<"Printing mySL using iterator:"<<std::endl;
    for(SkipList<int>::Iterator it=mySl.begin();it!=mySl.end();++it){
      std::cout<<*it<<std::endl;
    }
    std::cout<<"Does mySl contain the integer 5?";
    mySl.contains(5)?std::cout<<"Yes"<<std::endl:std::cout<<"No"<<std::endl;
    mySl.remove(5);
    std::cout<<"Does mySl contain the integer 5 now?";
    mySl.contains(5)?std::cout<<"Yes"<<std::endl:std::cout<<"No"<<std::endl;
    SkipList<int> mySl2(mySl);
    std::cout<<"Printing mySL2 after building it with copy constructor:"<<std::endl;
    for(SkipList<int>::Iterator it=mySl2.begin();it!=mySl2.end();++it){
      std::cout<<*it<<std::endl;
    }
    mySl2.add(6);
    mySl2.add(7);
    mySl2.add(8);
    mySl=mySl2;
    std::cout<<"Printing mySL after assigning it mySL2:"<<std::endl;
    for(SkipList<int>::Iterator it=mySl.begin();it!=mySl.end();++it){
      std::cout<<*it<<std::endl;
    }
    mySl.remove(6);
    mySl.remove(7);
    mySl.remove(8);
    SkipList<int> mySl3=mergeSLS(mySl2,mySl);
    std::cout<<"Printing merge of mySL and mySL2:"<<std::endl;
    for(SkipList<int>::Iterator it=mySl3.begin();it!=mySl3.end();++it){
      std::cout<<*it<<std::endl;
    }
    SkipList<int> mySl4=intersectSLS(mySl2,mySl);
    std::cout<<"Printing intersect of mySL and mySL2:"<<std::endl;
    for(SkipList<int>::Iterator it=mySl4.begin();it!=mySl4.end();++it){
      std::cout<<*it<<std::endl;
    }
    return 0;
}
