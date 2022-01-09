#include <iostream>
#include <sstream>
#include <cstdlib>
#include "vector.h"

void test0() {
    CS225::SparseVector v1;
    for (int i=0;i<10;++i) v1.Insert(i+1,i);
    std::cout << "v1 = " << v1 << std::endl;
}

void test1() {
    CS225::SparseVector v1;
    for (int i=0;i<10;++i) v1.Insert(i+1,i);
    CS225::SparseVector v2(v1);
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
}

void test2() {
    CS225::SparseVector v1;
    CS225::SparseVector v2(v1);
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
}

void test3() {
    CS225::SparseVector v1;
    for (int i=0;i<10;++i) v1.Insert(i+1,i);
    {
        CS225::SparseVector v2(v1);
        for (int i=0;i<5;++i) v2.Insert(10,i+10);
        std::cout << "v1 = " << v1 << std::endl;
        std::cout << "v2 = " << v2 << std::endl;
    }
    std::cout << "v1 = " << v1 << std::endl;
}

void test4() {
    CS225::SparseVector v1,v2;
    for (int i=0;i<10;++i) v1[i]=i+1;
    for (int i=0;i<5;++i) v2[i+10]=i+11;
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;

    CS225::SparseVector v3(v1);
    std::cout << "v3 = " << v3 << std::endl;

    std::cout << "Delete every second element in v1\n"; 
    for (int i=0;i<10;i+=2) v1[i]=0;
    std::cout << "v1 = " << v1 << std::endl;
}

void test5() {
    CS225::SparseVector v1,v2,v3;
    for (int i=0;i<10;++i) v1[2*i]=i+1;
    for (int i=0;i<5;++i) v2[5*i]=i+10;
    for (int i=0;i<15;++i) v3[i]=i+20;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
    CS225::SparseVector v12 = v1+v2;
    std::cout << "v12 = "  << v12 << std::endl;
    CS225::SparseVector v13 = v1+v3;
    std::cout << "v13 = "  << v13 << std::endl;
    CS225::SparseVector v23 = v2+v3;
    std::cout << "v23 = "  << v23 << std::endl;

    CS225::SparseVector v21 = v2+v1;
    std::cout << "v21 = "  << v21 << std::endl;
    CS225::SparseVector v31 = v3+v1;
    std::cout << "v31 = "  << v31 << std::endl;
    CS225::SparseVector v32 = v3+v2;
    std::cout << "v32 = "  << v32 << std::endl;
}
#if 0
void test6() {
    CS225::SparseVector v1,v2,v3;
    for (int i=0;i<10;++i) v1[2*i]=i+1;
    for (int i=0;i<5;++i) v2[5*i]=i+10;
    for (int i=0;i<15;++i) v3[i]=i+20;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
    std::cout << "v2+v2 = " << v2+v2 << std::endl;
    std::cout << "v1+v2+v3 = " << v1+v2+v3 << std::endl;
    std::cout << "Check v1,v2,v3 are the same\n";
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
}

void test7() {
    CS225::SparseVector v1,v2,v3;
    for (int i=0;i<10;++i) v1[2*i]=i+1;
    for (int i=0;i<5;++i) v2[5*i]=i+10;
    for (int i=0;i<15;++i) v3[i]=i+20;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
    std::cout << "v1*10 = " << v1*10 << std::endl;
    std::cout << "10*v2 = " << 10*v2 << std::endl;
    std::cout << "0*v3 = "; 
    CS225::SparseVector v4 = 0*v3;
    v4.PrintRaw();
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
}

void test8() {
    CS225::SparseVector v1,v2,v3;
    for (int i=0;i<10;++i) v1[2*i]=i+1;
    for (int i=0;i<5;++i) v2[5*i]=i+10;
    for (int i=0;i<15;++i) v3[i]=i+20;

    std::cout << "v1*10+v3*(-1) = " << v1*10+v3*(-1) << std::endl;

    std::cout << "10*v1+(-1)*v3 = " << 10*v1+(-1)*v3 << std::endl;
}

void test9() {
    CS225::SparseVector v1,v2,v3;
    for (int i=0;i<10;++i) v1[2*i]=i+1;
    for (int i=0;i<5;++i) v2[5*i]=i+10;
    for (int i=0;i<15;++i) v3[i]=i+20;

    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;

    std::cout << "v12 = "  << v1*v2 << std::endl;
    std::cout << "v13 = "  << v1*v3 << std::endl;
    std::cout << "v23 = "  << v2*v3 << std::endl;

    std::cout << "v21 = "  << v2*v1 << std::endl;
    std::cout << "v31 = "  << v3*v1 << std::endl;
    std::cout << "v32 = "  << v3*v2 << std::endl;
}

void test10 () {
    CS225::SparseVector v;
    v[1]=1;
    v[2]=2;
    v[13]=13;
    CS225::SparseVector & vr=v;
    vr[1]=0;
    vr[2]=0;
    vr[6]=6;
    vr[7]=7;
    vr[15]=15;
    v=vr;
    std::cout << "Should be equal\n";
    std::cout << "v  = ";
    v.PrintRaw();
    std::cout << std::endl;
    std::cout << "vr = ";
    vr.PrintRaw();
    std::cout << std::endl;
}

void test11() {
    CS225::SparseVector v;
    for (int i=0;i<10;++i) v.Insert(i+1,i);
    std::cout << "v = " << v << std::endl;

    std::cout << "Second element is v[2]=" << v[2] << std::endl;

    v[2]=5;
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    int temp=v[5];
    std::cout << "v[5]=" << temp << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[6] += -5; v[5] -= 3;
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[2] = v[8];
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;
}

void test12() {
    CS225::SparseVector v;
    for (int i=0;i<10;++i) v.Insert(i+1,i);

    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[1] += v[5];
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[2] -= v[2];
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;
}

void test13() {
    CS225::SparseVector v;
    for (int i=0;i<10;++i) v[i]=i;

    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[1] = v[5] = v[2];
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;

    v[1] += v[5] += v[2];
    std::cout << "v = " << v << std::endl;
    v.PrintRaw(); std::cout << std::endl;
}

void test14() { // test for existance of nodes with 0 in them
    CS225::SparseVector v;
    for (int i=0;i<16;++i) v[i] = i%2;

    v.PrintRaw();

    CS225::SparseVector v1,v2;
    for (int i=0;i<20;++i) { v1[i] = i%2; v2[i] = -v1[i]; }
    CS225::SparseVector v_sum=v1+v2;
    v_sum.PrintRaw();

    CS225::SparseVector v3;
    for (int i=0;i<20;++i)  v3[i]=i+1;
    for (int i=0;i<20;i+=2) v3[i] -= v3[i];
    v3.PrintRaw();
    std::cout << "v3 = " << v3 << std::endl;
}

void test15() {
    CS225::SparseVector v;
    for (int i=0;i<6;++i)  v[i]=i+1;

    const CS225::SparseVector v_copy(v);
    std::cout << "v_copy = " << v_copy << std::endl;
    std::cout << "v_copy*v_copy = " << v_copy*v_copy << std::endl;

    std::cout << "10*v_copy = " << 10*v_copy << std::endl;
}

void test16() {
    CS225::SparseVector v;
    for (int i=0;i<6;++i)  v[i]=i+1;
    std::cout << "v = " << v << std::endl;

    CS225::SparseVector v_1(0*v);
    std::cout << "CS225::SparseVector v_1(0*v);\n";
    v_1.PrintRaw();
}

void test17() {
    CS225::SparseVector v;
    for (int i=0;i<6;++i)  v[i]=i+1;

    const CS225::SparseVector v_copy(v);
    std::cout << "v_copy = " << v_copy << std::endl;

    std::cout << "v_copy[4] = " << v_copy[4] << std::endl;

    const CS225::SparseVector v_1(0*v_copy);
    std::cout << "const CS225::SparseVector v_1(0*v_copy);\n";
    v_1.PrintRaw();
}

void test18();
#endif
void (*pTests[])(void) = { 
    test0, test1, test2, test3, 
    test4, test5, //test6, test7, test8, 
    //test9, test10, test11, test12, test13, 
    //test14, test15, test16, test17, test18
};
#if 0
void test18() {
    for (size_t i = 0; i<sizeof(pTests)/sizeof(pTests[0])-1; ++i) {
        pTests[i]();
    }
}
#endif
#include <cstdio> // std::sscanf
int main(int argc, char *argv[] ) {
    if (argc!=2) return 1;

    int test = 0;
    std::sscanf(argv[1],"%i",&test);
    pTests[test]();
    return 0;
}
