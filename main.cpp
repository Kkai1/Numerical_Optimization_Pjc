#include "homework01.h"
#include <stdio.h>


using namespace std;
int main(){
    homework01* work1 = new homework01();
    vector<double> x0{0.5,2};
    work1->LineSearch(x0);

    return 0;
}

