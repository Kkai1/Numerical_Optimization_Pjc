#include "homework01.h"
#include <stdio.h>


using namespace std;
int main(){
    homework01* work1 = new homework01();
    vector<double> x0{1.5,1.5};
    work1->LineSearch(x0);

    return 0;
}

