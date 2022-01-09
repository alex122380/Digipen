#include <iostream>

struct ElementNode
{
  int data;
  int pos;
  struct ElementNode *next;
};

namespace CS225
{
  //forward declaration
  class ElementProxy;
  
  class SparseVector
  {
    public:
      SparseVector() : pHead(NULL), dimension(0) {}; // Implemented.
      SparseVector(const SparseVector &rhs);
      int Get(long pos) const;
      void Insert(int val, long pos);
      void Delete(long pos);
      ElementProxy operator[](long pos);
      SparseVector operator+(SparseVector &v2) const;
      void PrintRaw() const // Used for grading.
      {
        ElementNode *curr = pHead;
        std::cout << "Raw vector: ";
        while (curr)
        {
          std::cout << "(" << curr->data << ", " << curr->pos << ")";
          curr = curr->next;
        }
        std::cout << std::endl;
      }
      friend std::ostream& operator<<(std::ostream &out, const SparseVector &v); // Implemented.
      // ...
    private:
      ElementNode *pHead;
      long dimension;
  };
  
  class ElementProxy
  {
    public:
      ElementProxy(SparseVector &vector, long position) : v(vector), pos(position) {}; // Implemented.
      operator int() const;
      ElementProxy& operator=(int rval);
      //int operator+(ElementProxy &p2) const;
      // .......
    private:
      SparseVector &v;
      long pos;
  };
}