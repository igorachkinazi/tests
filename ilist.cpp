#include <boost/intrusive/list.hpp>
#include <iostream>

using namespace boost::intrusive;

class MyClass : public list_base_hook<>
{
   int val;

   public:

   MyClass(int i) :  val(i)  {}
   ~MyClass() { printf("Dtor is called\n");}
};

list<MyClass> baseList;

int main()
{
    MyClass a(1), b(2);

    baseList.insert(baseList.end(), a);
    baseList.insert(baseList.end(), b);
    std::cout << baseList.size() << std::endl;
   
    auto iter = baseList.begin();

    auto ptr = iter.pointed_node();

    MyClass& a1 = baseList.front();
    baseList.pop_front();

    iter = baseList.begin();
    ptr = iter.pointed_node();

    MyClass& b1 = baseList.front();
    baseList.pop_front();

    std::cout << baseList.size() << std::endl;

    return 0;
}

