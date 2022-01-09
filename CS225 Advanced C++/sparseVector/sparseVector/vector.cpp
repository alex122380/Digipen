#include <iostream>
#include "vector.h"

using namespace std;

namespace CS225
{
  SparseVector::SparseVector(const SparseVector &rhs) : pHead(NULL), dimension(0)
  {
    ElementNode *pE = rhs.pHead;
    
    // Copy all elements.
    while (pE)
    {
      Insert(pE->data, pE->pos);
      pE = pE->next;
    }
  }
  
  int SparseVector::Get(long pos) const
  {
    ElementNode *pTemp = pHead;
  
    cout << pos << endl;
    while (pTemp)
    {
      if (pTemp->pos == pos)
      {
        return pTemp->data;
      }
      else
      {
        pTemp = pTemp->next;
      }
    }
    
    return 0;
  }
  
  void SparseVector::Insert(int val, long pos)
  {
    ElementNode *pE = pHead, *pTemp = pHead;

    // Since we just update the node if it is already occupied, delete the node at pos no matter what.
    // This eliminate the possibility that pE->pos == pos.
    Delete(pos);
    
    if (val == 0) // If val == 0, no insert needed.
    {
      return;
    }
    
    if (pE == NULL) // If pHead is an empty list.
    {
      pTemp = new ElementNode();
      pTemp->data = val;
      pTemp->pos = pos;
      pTemp->next = NULL;
      pHead = pTemp;
      if (pos >= dimension)
        dimension = pos + 1; // Automatically set dimension (it effects operator<< only)
      return;
    }
    
    // Insert
    while (pE)
    {
      if (pE->pos > pos) // Insert in front of the head.
      {
        pTemp = new ElementNode();
        pTemp->data = val;
        pTemp->pos = pos;
        pTemp->next = pE;
        pHead = pTemp;
        if (pos >= dimension)
          dimension = pos + 1; // Automatically set dimension (it effects operator<< only)
        break;
      }
      else if (pE->next == NULL) // Insert after the end.
      {
        pTemp = new ElementNode();
        pTemp->data = val;
        pTemp->pos = pos;
        pTemp->next = NULL;
        pE->next = pTemp;
        if (pos >= dimension)
          dimension = pos + 1; // Automatically set dimension (it effects operator<< only)
        break;
      }
      else // Insert in the middle.
      {
        if (pE->next->pos > pos)
        {
          // Found the insert point.
          pTemp = new ElementNode();
          pTemp->data = val;
          pTemp->pos = pos;
          pTemp->next = pE->next;
          pE->next = pTemp;
          if (pos >= dimension)
            dimension = pos + 1; // Automatically set dimension (it effects operator<< only)
          break;
        }
        else
        {
          pTemp = pE->next;
          pE = pE->next;
        }
      }
    }
  }
  
  void SparseVector::Delete(long pos)
  {
    ElementNode *pPrev = pHead, *pE = pHead;
    
    while (pE)
    {
      if (pE->pos == pos)
      {
        if (pE == pPrev) // The head is the pos.
        {
          pPrev = pE->next;
          pHead = pPrev;
          pE->next = NULL;
          delete pE;
          break;
        }
        else
        {
          pPrev->next = pE->next;
          pE->next = NULL;
          delete pE;
          break;
        }
      }
      else
      {
        pPrev = pE;
        pE = pE->next;
      }
    }
  }
  
  ElementProxy SparseVector::operator[](long pos)
  {
    ElementProxy proxy(*this, pos);
    
    return proxy;
  }
  
  SparseVector SparseVector::operator+(SparseVector &v2) const
  {
    SparseVector result(*this); // Copy v1 to result.
    int dim;
    
    if (result.dimension >= v2.dimension)
      dim = result.dimension;
    else
      dim = v2.dimension;
    
    for (int i = 0; i < dim; ++i)
    {
      cout << "check 0" << endl;
      int op1 = result[i], op2 = v2[i];
      cout << "check 1" << endl;
      result[i] = op1 + op2;
      cout << "check 2" << endl;
    }
    
    return result;
  }
  
  // friend function.
  std::ostream& operator<<(std::ostream &out, const SparseVector &v)
  {
    int i, last_pos = -1;
    ElementNode *p_e = v.pHead;
    while (p_e)
    {
      for (i = last_pos + 1; i < p_e->pos; ++i)
        out << " " << "0";
      out << " " << p_e->data;
      last_pos = p_e->pos;
      p_e = p_e->next;
    }
    for (i = last_pos + 1; i < v.dimension; ++i)
    {
      out << " " << "0";
    }
    return out;
  }
  
  // class ElementProxy definitions.
  ElementProxy::operator int() const
  {
    cout << "check 3" << endl;
    return this->v.Get(this->pos);
  }
  
  ElementProxy& ElementProxy::operator=(int rval)
  {
    this->v.Insert(rval, this->pos);
    
    return *this;
  }

#if 0
  int ElementProxy::operator+(ElementProxy &p2) const
  {
    cout << "check" << endl;
    return this->v.Get(this->pos) + p2.v.Get(p2.pos);
  }
#endif
}























