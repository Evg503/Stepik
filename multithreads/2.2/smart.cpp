#include <string>
#include <iostream>


class StringPointer {
public:
    std::string *operator->() {return p;}
    operator std::string*() {return p;}
    StringPointer(std::string *Pointer)
    {
      if (Pointer == nullptr)
        p = &null;
      else
        p = Pointer;
    }
    StringPointer():p(&null) {}

  private:
    std::string* p;
    std::string null;
};


int main()
{
  std::string s1 = "Hello, world!";

  StringPointer sp1(&s1);
  StringPointer sp2(NULL);

  std::cout << sp1->length() << std::endl;
  std::cout << *sp1 << std::endl;
  std::cout << sp2->length() << std::endl;
  std::cout << *sp2 << std::endl;
}
