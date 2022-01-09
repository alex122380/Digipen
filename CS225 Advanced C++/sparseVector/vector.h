/*!*****************************************************************************
\file    vector.h
\author  Yi-Chun Chen
\par     DP email: yichun.chen\@digipen.edu
\par     DigiPen login: yichun.chen
\par     Course: CS225
\par     Assignment #6
\par     Section: A
\date    11/22/2019

\brief
  Header file of vector.cpp.

  - SparseVector::SparseVector
      Copy constructor of class SparseVector.

  - SparseVector::~SparseVector
      Destructor of class SparseVector, will clean up the linked list memory.
      
  - SparseVector::Get
      Get data value from the sparse vector.
      
  - SparseVector::Insert
      Insert an element into the sparse vector.
      
  - SparseVector::Delete
      Delete an element from the sparse vector.
      
  - SparseVector::operator[]
      overloaded operator[], there are two of them, one for non const v, one
      for const v.
      
  - SparseVector::operator+
      overloaded operator+, for v1 + v2.
      
  - SparseVector::operator*
      overloaded operator*, there are two of them, one for v * scalar,
      one for v1 * v2 (dot product).
      
  - SparseVector::operator=
      overloaded operator=, for v1 = v2.
      
  - operator*
      overloaded operator*, for scalar * v. Defined outside class SparseVector's
      scope.
      
  - operator<<
      friend function for cout << v .
      
  - ElementProxy::operator int()
      Overloaded Convert operator, for int i = v[pos].
      
  - ElementProxy::operator=
      Overloaded operator=, there are two of them, one for v[pos] = k, one for
      v1[pos1] = v2[pos2].
      
  - ElementProxy::operator+=
      Overloaded operator+=, for v[pos] += k.
      
  - ElementProxy::operator-=
      Overloaded operator-=, for v[pos] -= k.
*******************************************************************************/

#include <iostream>

/**************************************************************************/
/*!
  \struct ElementNode
  \brief  
    The linkded list structure for SparseVector class.
*/
/**************************************************************************/
template <typename T>
struct ElementNode
{
  T data;
  int pos;
  struct ElementNode<T> *next;
};

namespace CS225
{
  //forward declaration
  template <typename T>
  class ElementProxy;
  
  template <typename T>
  class SparseVector
  {
    public:
      SparseVector() : pHead(NULL), dimension(0) {}; // Implemented.
      SparseVector(const SparseVector &rhs);
      ~SparseVector();
      T Get(long pos) const;
      void Insert(T val, long pos);
      void Delete(long pos);
      ElementProxy<T> operator[](long pos);
      T operator[](long pos) const;
      SparseVector operator+(SparseVector v2) const;
      SparseVector operator*(T scalar) const; // vector * scalar
      T operator*(SparseVector v2) const; // dot product.
      SparseVector& operator=(SparseVector v2);
      void PrintRaw() const // Used for grading.
      {
        ElementNode<T> *curr = pHead;
        std::cout << "Raw vector: ";
        while (curr)
        {
          std::cout << "(" << curr->data << ", " << curr->pos << ")";
          curr = curr->next;
        }
        std::cout << std::endl;
      }
      template <typename S>
      friend std::ostream& operator<<(std::ostream &out, const SparseVector<S> &v); // Implemented.
    private:
      ElementNode<T> *pHead;
      long dimension;
  };
  
  template <typename T>
  SparseVector<T> operator*(T scalar, const SparseVector<T> &vector); // scalar * vector
  
  template <typename T>
  class ElementProxy
  {
    public:
      ElementProxy(SparseVector<T> &vector, long position) : v(vector), pos(position) {}; // Implemented.
      operator T() const;
      ElementProxy& operator=(T rval);
      ElementProxy& operator=(ElementProxy &rhs);
      ElementProxy& operator+=(T rval);
      ElementProxy& operator-=(T rval);
    private:
      SparseVector<T> &v;
      long pos;
  };
  
  /*********************************************************************************************/
  /*********************************************************************************************/
  /*********************************************************************************************/
  /*********************************************************************************************/
  /* Implementations.                                                                          */
  /*********************************************************************************************/
  /*********************************************************************************************/
  /*********************************************************************************************/
  /*********************************************************************************************/
  
  /*!*****************************************************************************
  \fn SparseVector::SparseVector(const SparseVector &rhs)

  \brief
    Copy constructor of class SparseVector.

  \param rhs
    The object to be copied.
  *******************************************************************************/
  template <typename T>
  SparseVector<T>::SparseVector(const SparseVector<T> &rhs) : pHead(NULL), dimension(0)
  {
    ElementNode<T> *pE = rhs.pHead;
    
    // Copy all elements.
    while (pE)
    {
      Insert(pE->data, pE->pos);
      pE = pE->next;
    }
  }
  
  /*!*****************************************************************************
  \fn SparseVector::~SparseVector()

  \brief
    Destructor of class SparseVector.
  *******************************************************************************/
  template <typename T>
  SparseVector<T>::~SparseVector()
  {
    ElementNode<T> *pE = pHead, *pTemp = pHead;
    
    while (pE)
    {
      pE = pE->next;
      pTemp->next = NULL;
      delete pTemp;
      pTemp = pE;
    }
  }
  
  /*!*****************************************************************************
  \fn int SparseVector::Get(long pos) const

  \brief
    Get an element's value.

  \param pos
    The position of the element.

  \return 
    Returns the value of the element.
  *******************************************************************************/
  template <typename T>
  T SparseVector<T>::Get(long pos) const
  {
    ElementNode<T> *pTemp = pHead;
  
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
  
  /*!*****************************************************************************
  \fn void SparseVector::Insert(int val, long pos)

  \brief
    Insert an element into the sparse vector.

  \param val
    The value to be inserted.

  \param pos
    The position of the element.
  *******************************************************************************/
  template <typename T>
  void SparseVector<T>::Insert(T val, long pos)
  {
    ElementNode<T> *pE, *pTemp;

    // Since we just update the node if it is already occupied, delete the node at pos no matter what.
    // This eliminate the possibility that pE->pos == pos.
    Delete(pos);
    
    pE = pHead;
    pTemp = pHead;
    
    if (val == 0) // If val == 0, no insert needed.
    {
      return;
    }
    
    if (pE == NULL) // If pHead is an empty list.
    {
      pTemp = new ElementNode<T>();
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
        pTemp = new ElementNode<T>();
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
        pTemp = new ElementNode<T>();
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
          pTemp = new ElementNode<T>();
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
  
  /*!*****************************************************************************
  \fn void SparseVector::Delete(long pos)

  \brief
    Delete an element from the sparse vector.

  \param pos
    The position of the element.
  *******************************************************************************/
  template <typename T>
  void SparseVector<T>::Delete(long pos)
  {
    ElementNode<T> *pPrev = pHead, *pE = pHead;
    
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
  
  /*!*****************************************************************************
  \fn ElementProxy SparseVector::operator[](long pos)

  \brief
    Overloaded operator[] for non-const v.

  \param pos
    The position of the element.

  \return 
    Returns a proxy to the element.
  *******************************************************************************/
  template <typename T>
  ElementProxy<T> SparseVector<T>::operator[](long pos)
  {
    ElementProxy<T> proxy(*this, pos);
    
    return proxy;
  }

  /*!*****************************************************************************
  \fn int SparseVector::operator[](long pos) const

  \brief
    Overloaded operator[] for const v.

  \param pos
    The position of the element.

  \return 
    Returns the value of the element.
  *******************************************************************************/
  template <typename T>
  T SparseVector<T>::operator[](long pos) const
  {
    return this->Get(pos);
  }
  
  /*!*****************************************************************************
  \fn SparseVector SparseVector::operator+(SparseVector v2) const

  \brief
    Overloaded operator+ for v1 + v2.

  \param v2
    The second operand.

  \return 
    Returns a sparse vector with elements of v1+v2 (component wise addition).
  *******************************************************************************/
  template <typename T>
  SparseVector<T> SparseVector<T>::operator+(SparseVector v2) const
  {
    SparseVector result(*this); // Copy v1 to result.
    int dim;
    
    if (result.dimension >= v2.dimension)
      dim = result.dimension;
    else
      dim = v2.dimension;
    
    for (int i = 0; i < dim; ++i)
    {
      int op1 = result[i], op2 = v2[i];
      result[i] = op1 + op2;
    }
    
    return result;
  }
  
  /*!*****************************************************************************
  \fn SparseVector SparseVector::operator*(int scalar) const

  \brief
    Overloaded operator* for v1 * scalar.

  \param scalar
    The scalar to be mutiplied.

  \return 
    Returns a sparse vector with elements of v1 * scalar.
  *******************************************************************************/
  template <typename T>
  SparseVector<T> SparseVector<T>::operator*(T scalar) const
  {
    SparseVector result(*this);
    
    for (int i = 0; i < dimension; ++i)
    {
      T op1 = result[i];
      result[i] = op1 * scalar;
    }
    
    return result;
  }
  
  /*!*****************************************************************************
  \fn int SparseVector::operator*(SparseVector v2) const

  \brief
    Returns the dot product of two sparse vector.

  \param v2
    The second operand.

  \return 
    Returns the dot product of two sparse vector.
  *******************************************************************************/
  template <typename T>
  T SparseVector<T>::operator*(SparseVector v2) const
  {
    SparseVector v1(*this);
    int dim;
    T result = 0;
    
    if (this->dimension >= v2.dimension)
      dim = this->dimension;
    else
      dim = v2.dimension;
    
    for (int i = 0; i < dim; ++i)
    {
      T op1 = v1[i], op2 = v2[i];
      result += op1 * op2;
    }
    
    return result;
  }
  
  /*!*****************************************************************************
  \fn SparseVector& SparseVector::operator=(SparseVector v2)

  \brief
    Overloaded operator= for v1 = v2;

  \param v2
    The second operand.

  \return 
    Returns the reference of v1 after assignment.
  *******************************************************************************/
  template <typename T>
  SparseVector<T>& SparseVector<T>::operator=(SparseVector v2)
  {
    ElementNode<T> *pE = pHead, *pE2 = v2.pHead;
    int tempPos;
    
    // Delete all elements from v1.
    while (pE)
    {
      tempPos = pE->pos;
      pE = pE->next;
      Delete(tempPos);
    }
    
    // Insert all elements from v2 to v1.
    while (pE2)
    {
      Insert(pE2->data, pE2->pos);
      pE2 = pE2->next;
    }
    
    return *this;
  }
  
  // For scalar * v, defined outside of class SparseVector's scope.
  /*!*****************************************************************************
  \fn SparseVector operator*(int scalar, const SparseVector &vector)

  \brief
    Overloaded operator* for scalar * v.

  \param scalar
    The scalar to be multiplied.
    
  \param vector
    The vector to be multiplied.

  \return 
    Returns the result of multiplication.
  *******************************************************************************/
  template <typename T>
  SparseVector<T> operator*(T scalar, const SparseVector<T> &vector)
  {
    return vector * scalar;
  }
  
  /*!*****************************************************************************
  \fn std::ostream& operator<<(std::ostream &out, const SparseVector &v)

  \brief
    Overloaded operator<< for cout << v.

  \param out
    The output stream.
    
  \param v
    The vector to be output.

  \return 
    Returns the output stream.
  *******************************************************************************/
  template <typename S>
  std::ostream& operator<<(std::ostream &out, const SparseVector<S> &v)
  {
    int i, last_pos = -1;
    ElementNode<S> *p_e = v.pHead;
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
  /*!*****************************************************************************
  \fn ElementProxy::operator int() const

  \brief
    Overloaded operator int() for int i = v[pos].
    
  \return 
    Returns the value of v[pos]
  *******************************************************************************/
  template <typename T>
  ElementProxy<T>::operator T() const
  {
    return this->v.Get(this->pos);
  }
  
  /*!*****************************************************************************
  \fn ElementProxy& ElementProxy::operator=(int rval)

  \brief
    Overloaded operator= for v[pos] = k.

  \param rval
    The value to be assigned.

  \return 
    Returns the reference of v after assignment.
  *******************************************************************************/
  template <typename T>
  ElementProxy<T>& ElementProxy<T>::operator=(T rval)
  {
    this->v.Insert(rval, this->pos);
    
    return *this;
  }
  
  /*!*****************************************************************************
  \fn ElementProxy& ElementProxy::operator=(ElementProxy &rhs)

  \brief
    Overloaded operator= for v1[pos1] = v2[pos].

  \param rhs
    The second operand.

  \return 
    Returns the reference of v1 after assignment.
  *******************************************************************************/
  template <typename T>
  ElementProxy<T>& ElementProxy<T>::operator=(ElementProxy<T> &rhs)
  {
    int rval = rhs.v.Get(rhs.pos);
    this->v.Insert(rval, this->pos);
    
    return *this;
  }
  
  /*!*****************************************************************************
  \fn ElementProxy& ElementProxy::operator+=(int rval)

  \brief
    Overloaded operator+= for v[pos] += k.

  \param rval
    The value to be added.

  \return 
    Returns the reference of v after addition.
  *******************************************************************************/
  template <typename T>
  ElementProxy<T>& ElementProxy<T>::operator+=(T rval)
  {
    T prevVal = this->v.Get(this->pos);
    T sum = prevVal + rval;
    this->v.Insert(sum, this->pos);
    
    return *this;
  }
  
  /*!*****************************************************************************
  \fn ElementProxy& ElementProxy::operator-=(int rval)

  \brief
    Overloaded operator-= for v[pos] -= k.

  \param rval
    The value to be substract.

  \return 
    Returns the reference of v after substraction.
  *******************************************************************************/
  template <typename T>
  ElementProxy<T>& ElementProxy<T>::operator-=(T rval)
  {
    T prevVal = this->v.Get(this->pos);
    T difference = prevVal - rval;
    this->v.Insert(difference, this->pos);
    
    return *this;
  }
}