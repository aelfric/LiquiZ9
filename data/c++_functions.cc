#include <iostream>
using namespace std;

void f(double x)           { cout << x * 2 << "\n";    }
void f(double x, double y) { cout << (x+y)* 2 << "\n"; }
void f(int a, int b)       { cout << (a + b) << "\n";  }
//Identify each function call as legal or illegal
int main() {
f(2.5);   //$(legal,illegal)$
f(2);     //$(legal,illegal)$
f(3.5,4); //$(legal,illegal)$
f(2,3);   //$(legal,illegal)$
f('a',2); //$(legal,illegal)$
f("a",2); //$(legal,illegal)$
}
