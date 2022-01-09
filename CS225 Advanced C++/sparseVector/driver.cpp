// Yi-Chun Chen, CS 225, Assignment #6, Fall 2019.
//

/*==========================================================================*/
/*       I N C L U D E S                                                    */
/*==========================================================================*/
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio> //For sscanf

#include "vector.h"

using namespace std;
//using namespace CS225;

/*==========================================================================*/
/*      G L O B A L   R E F E R E N C E S                                   */
/*      G L O B A L   D E F I N I T I O N S                                 */
/*==========================================================================*/

/*==========================================================================*/
/*      L O C A L   S Y M B O L   D E F I N I T I O N S                     */
/*==========================================================================*/

/*==========================================================================*/
/*      L O C A L   D A T A   D E F I N I T I O N S                         */
/*==========================================================================*/

/*==========================================================================*/
/*       L O C A L   F U N C T I O N S   P R O T O T Y P E S                */
/*==========================================================================*/
/* Test cases for Vector */

/* Test cases for templated Sparse Vector: The example of naming convention is: test101 is the templated class version of test01 */
static void test100(void);static void test101(void);static void test102(void);static void test103(void);static void test104(void);static void test105(void);
static void test106(void);static void test107(void);static void test108(void);static void test109(void);static void test110(void);
static void test111(void);static void test112(void);static void test113(void);static void test114(void);static void test115(void);
static void test116(void);static void test117(void);static void test118(void);static void test119(void);static void test120(void);
static void test121(void);

/*============================================================================*/
/* Test for Sparse Vector Begin                                               */
/*============================================================================*/

/*============================================================================*/
/* test30                                                                     */
/*============================================================================*/
static void test100()
{
  CS225::SparseVector<double> v1;

  for (int i=0; i < 10; ++i) v1.Insert(i+1.1, i);

  cout << "SparseVector v1:  " << v1 << endl;
}

/*============================================================================*/
/* test31                                                                     */
/*============================================================================*/
static void test101()
{
  CS225::SparseVector<double> v1;

  for (int i=0; i < 10; ++i) v1.Insert(i + 0.5, i);

  CS225::SparseVector<double> v2(v1);
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
}

/*============================================================================*/
/* test32                                                                     */
/*============================================================================*/
static void test102()
{
  CS225::SparseVector<long> v1;
  CS225::SparseVector<long> v2(v1);

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
}

/*============================================================================*/
/* test33                                                                     */
/*============================================================================*/
void test103()
{
  CS225::SparseVector<short> v1;

  for (int i=0; i < 10; ++i) v1.Insert(i + 1, i);

  CS225::SparseVector<short> v2(v1);

  for (int i=0; i < 5; ++i) v2.Insert(10, i + 10);

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;

  cout << "v1 = " << v1 << endl;
}

/*============================================================================*/
/* test104                                                                     */
/*============================================================================*/
static void test104()
{
  CS225::SparseVector<int> v1, v2;

  /* The v1[i] will use the overloading operation of "TNode& operator[](int index)" */
  for (int i=0; i < 10; ++i) v1[i] = i + 1;

  for (int i=0; i < 5; ++i) v2[i + 10] = i + 11;

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;

  CS225::SparseVector<int> v3(v1);

  cout << "v3 = " << v3 << endl;

  cout << "Delete every second element in v1\n";
  for (int i=0; i < 10; i += 2) 
    v1[i] = 0;

  cout << "v1 = " << v1 << endl;
}

/*============================================================================*/
/* test105                                                                     */
/*============================================================================*/
void test105()
{
  CS225::SparseVector<int> v1, v2, v3;

  for (int i=0; i < 10; ++i) v1[2 * i] = i + 1;

  for (int i=0; i < 5; ++i) v2[5 * i] = i + 10;

  for (int i=0; i < 15; ++i) v3[i] = i + 20;

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;

  CS225::SparseVector<int> v12;


  v12 = v1 + v2;
  cout << "v12 = " << v12 << endl;

  CS225::SparseVector<int> v13;

  v13 = v1 + v3;
  cout << "v13 = " << v13 << endl;

  CS225::SparseVector<int> v23;


  v23 = v2 + v3;
  cout << "v23 = " << v23 << endl;

  CS225::SparseVector<int> v21;

  v21 = v2 + v1;
  cout << "v21 = " << v21 << endl;

  CS225::SparseVector<int> v31;

  v31 = v3 + v1;
  cout << "v31 = " << v31 << endl;

  CS225::SparseVector<int> v32;

  v32 = v3 + v2;
  cout << "v32 = " << v32 << endl;
}

/*============================================================================*/
/* test106                                                                     */
/*============================================================================*/
static void test106(void)
{
  CS225::SparseVector<long> v1, v2, v3;

  for (int i=0; i < 10; ++i) v1[2 * i] = i + 1;

  for (int i=0; i < 5; ++i) v2[5 * i] = i + 10;

  for (int i=0; i < 15; ++i) 
    v3[i] = i + 20;


  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
  cout << "v2+v2 = " << v2 + v2 << endl;
  cout << "v1+v2+v3 = " << v1 + v2 + v3 << endl;
  cout << "Check v1,v2,v3 are the same\n";
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
}

/*============================================================================*/
/* test107                                                                     */
/*============================================================================*/
static void test107(void)
{
  CS225::SparseVector<int> v1, v2, v3;

  for (int i=0; i < 10; ++i) v1[2 * i] = i + 1;

  for (int i=0; i < 5; ++i) v2[5 * i] = i + 10;

  for (int i=0; i < 15; ++i) v3[i] = i + 20;

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
  cout << "v1*10 = " << v1 * 10 << endl;
  cout << "10*v2 = " << v2 * 10 << endl;
  cout << "0*v3 = " << v3 * 0 << endl;
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
}

/*============================================================================*/
/* test108                                                                    */
/*============================================================================*/
static void test108(void)
{
  CS225::SparseVector<int> v1, v2, v3;

  for (int i=0; i < 10; ++i)  v1[2 * i] = i + 1;

  for (int i=0; i < 5; ++i)  v2[5 * i] = i + 10;

  for (int i=0; i < 15; ++i)  v3[i] = i + 20;

  cout << "v1*10+v3*(-1) = " << v1 * 10 + v3 * (-1) << endl;
  cout << "10*v1+(-1)*v3 = " << v1 * 10 + v3 * (-1) << endl;
}

/*============================================================================*/
/* test109                                                                    */
/*============================================================================*/
static void test109(void)
{
  CS225::SparseVector<int> v1, v2, v3;

  for (int i=0; i < 10; ++i)  v1[2 * i] = i + 1;

  for (int i=0; i < 5; ++i)  v2[5 * i] = i + 10;

  for (int i=0; i < 15; ++i)  v3[i] = i + 20;

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;

  cout << "v12 = " << v1 * v2 << endl;
  cout << "v13 = " << v1 * v3 << endl;
  cout << "v23 = " << v2 * v3 << endl;

  cout << "v21 = " << v2 * v1 << endl;
  cout << "v31 = " << v3 * v1 << endl;
  cout << "v32 = " << v3 * v2 << endl;
}

/*============================================================================*/
/* test110                                                                    */
/*============================================================================*/
static void test110(void)
{
  CS225::SparseVector<int> v;

  v[1] = 1;
  v[2] = 2;
  v[13] = 13;

  CS225::SparseVector<int>& vr = v;

  vr[1] = 0;
  vr[2] = 0;
  vr[6] = 6;
  vr[7] = 7;
  vr[15] = 15;
  v = vr;
  cout << "Should be equal\n";
  cout << "v  = " << v << endl;
  cout << "vr = " << vr << endl;
}

/*============================================================================*/
/* test111                                                                    */
/*============================================================================*/
static void test111(void)
{
  CS225::SparseVector<int> v;

  for (int i = 0; i < 10; ++i) v.Insert(i + 1, i);

  cout << "v = " << v << endl;

  cout << "Second element is v[2]=" << v[2] << endl;

  v[2] = 5;
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  int temp = v[5];
  cout << "v[5]=" << temp << endl;
  v.PrintRaw(); 
  cout << endl;

  v[6] += -5; v[5] -= 3;
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  v[2] = v[8];
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;
}

/*============================================================================*/
/* test112                                                                    */
/*============================================================================*/
static void test112(void)
{
  CS225::SparseVector<int> v;

  for (int i = 0; i < 10; ++i) v.Insert(i + 1, i);

  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  v[1] += v[5];
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  v[2] -= v[2];
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;
}

/*============================================================================*/
/* test113                                                                     */
/*============================================================================*/
static void test113(void)
{
  CS225::SparseVector<int> v;

  for (int i=0; i < 10; ++i) v[i] = i;

  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  v[1] = v[5] = v[2];
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;

  v[1] += v[5] += v[2];
  cout << "v = " << v << endl;
  v.PrintRaw(); 
  cout << endl;
}

/*============================================================================*/
/* test114                                                                     */
/*============================================================================*/
static void test114(void)
{
  // test for existance of nodes with 0 in them
  CS225::SparseVector<int> v;

  for (int i=0; i < 16; ++i) v[i] = i % 2;

  v.PrintRaw();

  CS225::SparseVector<int> v1, v2;
  for (int i=0; i < 20; ++i) 
  { 
    v1[i] = i % 2; 
    v2[i] = -v1[i]; 
  }

  CS225::SparseVector<int> v_sum = v1 + v2;

  v_sum.PrintRaw();

  CS225::SparseVector<int> v3;

  for (int i=0; i < 20; ++i)  v3[i] = i + 1;
  for (int i=0; i < 20; i+=2) v3[i] -= v3[i];
  v3.PrintRaw();
  cout << "v3 = " << v3 << endl;
}

/*============================================================================*/
/* test115                                                                     */
/*============================================================================*/
static void test115(void)
{
  CS225::SparseVector<int> v;

  for (int i=0; i < 6; ++i)  v[i] = i + 1;

  const CS225::SparseVector<int> v_copy(v);

  cout << "v_copy = " << v_copy << endl;
  cout << "v_copy*v_copy = " << v_copy * v_copy << endl;

  cout << "10*v_copy = " << v_copy * 10 << endl;
}

/*============================================================================*/
/* test116                                                                     */
/*============================================================================*/
static void test116(void)
{
  CS225::SparseVector<int> v;

  for (int i=0; i < 6; ++i)  v[i] = i + 1;
  cout << "v = " << v << endl;

  CS225::SparseVector<int> v_1(v * 0);

  cout << "Vector v_1(0*v);\n";
  v_1.PrintRaw();
}

/*============================================================================*/
/* test117                                                                     */
/*============================================================================*/
static void test117(void)
{
  CS225::SparseVector<int> v;

  for (int i=0; i < 6; ++i)  v[i] = i + 1;

  const CS225::SparseVector<int> v_copy(v);
  //SparseVector<int> v_copy(v);

  cout << "v_copy = " << v_copy << endl;
  cout << "v_copy[4] = " << v_copy[4] << endl;

  const CS225::SparseVector<int> v_1(v_copy * 0);

  cout << "const Vector v_1(0*v_copy);\n";
  v_1.PrintRaw();
}

/*============================================================================*/
/* test118                                                                     */
/*============================================================================*/
static void test118(void)
{
  CS225::SparseVector<int> v;

  for (int i=0; i < 10; ++i) v.Insert(i + 1, i);

  const CS225::SparseVector<int> cv(v);
  //SparseVector<int> cv(v);

  int i = cv[3] + cv[4];
  cout << "cv[3] + cv[4] = " << i << endl;
}

/*============================================================================*/
/* test119                                                                     */
/*============================================================================*/
static void test119(void)
{
  CS225::SparseVector<int> v1, v2;

  for (int i = 0; i < 20; ++i) 
  {
    v1[i] = i % 2;
    v2[i] = -v1[i];
  }
  std::cout << "v1 = " << v1 << endl;
  std::cout << "v2 = " << v2 << endl;

  v2 = v1;
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;

  // modify v1, make sure v2 is not effected
  for (int i = 0; i < 20; ++i) 
  {
    v1[i] = 1;
  }

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  v1.PrintRaw();
  v2.PrintRaw();
}

/*============================================================================*/
/* test120                                                                     */
/*============================================================================*/
static void test120(void)
{
  CS225::SparseVector<int> v1, v2;

  for (int i = 0; i < 20; ++i) 
  {
    v1[i] = i % 2;
    v2[i] = -v1[i];
  }
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;

  v2 = v1;
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;

  // modify v2, make sure v1 is not effected
  for (int i = 0; i < 20; ++i) 
  {
    v2[i] = 1;
  }

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  v1.PrintRaw();
  v2.PrintRaw();
}

/*============================================================================*/
/* test121                                                                     */
/*============================================================================*/
static void test121(void)
{
  CS225::SparseVector<int> v1, v2;

  for (int i = 0; i < 20; ++i) 
  {
    v1[i] = i % 2;
    v2[i] = -v1[i];
  }

  CS225::SparseVector<int> const v3(v1); // constant

  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;

  // try to assign from constant 

  v2 = v3;
  cout << "v1 = " << v1 << endl;
  cout << "v2 = " << v2 << endl;
  cout << "v3 = " << v3 << endl;
  v1.PrintRaw();
  v2.PrintRaw();
  v3.PrintRaw();
}

static void (*pSparseVectorTests[])() =
{
  test100,test101,test102,test103,test104,test105,
  test106,test107,test108,test109,test110,
  test111,test112,test113,test114,test115,
  test116,test117,test118,test119,test120,
  test121
};

/*============================================================================*/
/*
 * FUNCTION     : main
 *   Input      :
 *   Output     :
 *   Return     :
 * DESCRIPTION  : Main entry of program
 *   Pre cond.  :
 *   Post cond. :
 */
 /*============================================================================*/
int main(int argc, char** argv) 
{
  if (argc > 1) 
  {
    //if (atoi(argv[1]) < 23)
      //pTests[atoi(argv[1])]();
      //;
    //else if ((atoi(argv[1]) >= 200) && (atoi(argv[1]) <= 205))
      //p200Tests[atoi(argv[1]) - 200]();
      //;
    //else if ((atoi(argv[1]) >= 100) && (atoi(argv[1]) <= 121))
    if (atoi(argv[1]) < 23)
      pSparseVectorTests[atoi(argv[1])]();
  }
  return 0;
}