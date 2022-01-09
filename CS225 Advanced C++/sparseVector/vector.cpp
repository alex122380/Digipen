/*!*****************************************************************************
\file    vector.cpp
\author  Yi-Chun Chen
\par     DP email: yichun.chen\@digipen.edu
\par     DigiPen login: yichun.chen
\par     Course: CS225
\par     Assignment #6
\par     Section: A
\date    11/22/2019

\brief
  This program implements sparse vector using c++.

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
#include "vector.h"























