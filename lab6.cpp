#include <iostream>
#include<bitset>
using namespace std;

void exercise_1()
{
    cout<<endl<<"Exercise 1:"<<endl;
    int x,y,z;
    x=5;
    y=5;
    asm(
        "mov %[X], %[Z]\n"
        "inc %[X]\n"
        "imul %[X], %[Y]\n"
        "sub $6, %[Y]\n"
        "add %[Y], %[Z]\n"
        : [Z] "=m" (z)
        : [X] "r" (x), [Y] "r" (y)
        : "cc", "memory"
      );
    cout <<"z = "<< z <<  endl;
}

void exercise_2()
{
    cout<<endl<<"Exercise 2:"<<endl;
    int x=50,z;
    asm(
        "lea 123(%%eax,1), %%eax\n"
        : "=a" (z)
        : "a" (x)
        : "cc"
      );

      cout << "Z = " << z << endl;
}

void exercise_3()
{
    cout<<endl<<"Exercise 3:"<<endl;
    int c_reg = 0;
    int d_reg = 0;
    asm(
        "xor %%eax, %%eax\n"
        "mov $1, %%eax\n"
        "cpuid\n"
        :[F] "=&c" (c_reg), [D] "=&d" (d_reg)
        : : "%eax", "%ebx"
    );
    cout<< "c_reg" << bitset<32> (c_reg);
    cout<<endl;
    cout<<"d_reg" <<bitset<32> (d_reg);
    cout<<endl;

    cout<<"Fpu supported(0 bit d_reg)" <<endl;
    cout<<"SSE1 supported(25 bit d_reg)" <<endl;
    cout<<"SSE2 supported(26 bit d_reg)" <<endl;
    cout<<"Avx supported(28 bit c_reg)" <<endl;
    cout<<"SSE3 supported(0 bit c_reg)" <<endl;
    cout<<"SSE4.1 supported(19 bit c_reg)" <<endl;
    cout<<"SSE4.2 supported(20 bit c_reg)" <<endl;
}

void exercise_4()
{
    cout<<endl<<"Exercise 4:"<<endl;
    double x = 0.1;
    double y = 0;
    asm (
      "vaddsd  %[I], %[X], %[X]\n"
      : "=x" (y)
      :[X] "x" (x), [I] "x" (76.0)
      :"cc"
    );
    cout << "y="<< y<<endl;
}

void exercise_5()
{
    cout<<endl<<"Exercise 5:"<<endl;
    double x = 0.1;
    double y = 0;
    double add = 76;
    asm(
       "fldl %[X]\n" // st(0) = %[X]
       "faddl %[A]\n" // st(0) = %[X] + %[A]
       "fstpl %[Y]\n" // %[Y] = %[X] + %[A], стек пуст
        :[Y]"=m"(y)
        :[X]"m"(x), [A]"m"(add)
        :"cc"
    );
    cout << "y="<< y<<endl;
}

void exercise_6()
{
    cout<<endl<<"Exercise 6:"<<endl;
    double x[4] = {1.1, 4.8, 2.6, 5.9};
    double y[4] = {11.3, 1.3, 9.8, 4.4};
    double z[4] = {0, 0, 0, 0};
    asm(
        "vmovupd %[X], %%ymm1\n"
        "vmovupd %[Y], %%ymm2\n"
        "vaddpd %%ymm1, %%ymm2, %%ymm3\n"
        "vsubpd %%ymm2, %%ymm1, %%ymm4\n"
        "vdivpd %%ymm4, %%ymm3, %%ymm3\n"
        "vmovupd %%ymm3, %[Z]\n"
        :[Z] "=m" (z)
        :[X] "m" (x), [Y] "m" (y)
        :"cc", "ymm1", "ymm2", "ymm3", "ymm4", "memory"
    );
    for(int i = 0; i < 4; i++)
        cout << z[i] <<endl;
}

void exercise_7()
{
    cout<<endl<<"Exercise 7:"<<endl;
    alignas(32)double x[4] = {1.1, 4.8, 2.6, 5.9};
    alignas(32)double y[4] = {11.3, 1.3, 9.8, 4.4};
    alignas(32)double z[4] = {0, 0, 0, 0};
    asm(
        "vmovapd %[X], %%ymm1\n"
        "vmovapd %[Y], %%ymm2\n"
        "vaddpd %%ymm1, %%ymm2, %%ymm3\n"
        "vsubpd %%ymm2, %%ymm1, %%ymm4\n"
        "vdivpd %%ymm4, %%ymm3, %%ymm3\n"
        "vmovapd %%ymm3, %[Z]\n"
        :[Z] "=m" (z)
        :[X] "m" (x), [Y] "m" (y)
        :"cc", "ymm1", "ymm2", "ymm3", "ymm4", "memory"
    );
    for(int i = 0; i < 4; i++)
        cout << z[i] <<endl;
}

int main()
{
    exercise_1();
    exercise_2();
    exercise_3();
    exercise_4();
    exercise_5();
    exercise_6();
    exercise_7();
    return 0;
}
