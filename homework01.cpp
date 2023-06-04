#include "homework01.h"

homework01::homework01(){}

double homework01::Rosenbrock(vector<double> x){
    double res = 100*pow(pow(x[0],2)-x[1],2)+pow(x[0]-1,2);
    return res; 
}

vector<double> homework01::RosenbrockGrandient(vector<double> x){
    double gradX1 = 400 * x[0] * (pow(x[0],2) - x[1]) + 2 * (x[0] - 1);
    double gradX2 = -200 * (pow(x[0],2) - x[1]);
    return {gradX1,gradX2};
}

vector<vector<double>> homework01::RosenbrockHessian(vector<double> x){
    double H00 = 1200 * pow(x[0],2) - 400 * x[1] + 2;
    double H01 = -400 * x[0];
    double H10 = -400 * x[0];
    double H11 = 200;
    return {{H00,H01},{H10,H11}};
}

double homework01::Armijo(vector<double> x,vector<double> grad){
    double lemeta = 1;
    vector<double> Nextx(2,0);
    
    Nextx[0] = x[0] - lemeta * grad[0];
    Nextx[1] = x[1] - lemeta * grad[1];
    while (Rosenbrock(Nextx) > Rosenbrock(x) - c * lemeta * (pow(grad[0],2)+pow(grad[1],2))){
        lemeta /= 2;
        Nextx[0] = x[0] - lemeta * grad[0];
        Nextx[1] = x[1] - lemeta * grad[1];
    }
    return lemeta;
}

vector<double> homework01::LineSearch(vector<double> x){
    int iter = 0;
    vector<double> cur_x = x;
    double lemata;
    while(iter < maxIter && found == false){
        vector<double> grad = homework01::RosenbrockGrandient(cur_x);
        double error = sqrt(pow(grad[0],2) + pow(grad[1],2));
        //输出迭代信息
        printf("cur_x = [%f,%f],Rosenbrock:%f,iter = %d,grad = [%f,%f],error = %f\n",cur_x[0],cur_x[1],Rosenbrock(cur_x),iter,grad[0],grad[1],error);
        if(error < tolerance){
            found = true;
            break;
        }else{
            lemata = homework01::Armijo(cur_x,grad);
            //输出步长
            cout << lemata << endl;
            cur_x[0] = cur_x[0] - lemata * grad[0];
            cur_x[1] = cur_x[1] - lemata * grad[1];
            iter++;
        }
        
    }
    
    if(found == true){
        printf("find the result:x = [%f,%f],iter = %d",cur_x[0],cur_x[1],iter);
    }else{
        printf("out of the maxIter!");
    }
    return cur_x;
}

/*
homework01::homework01(vector<int> x,int tolerate,int maxIter){
    this->x0 = x;
    this->tolerance = tolerance;
    this->maxIter = maxIter;
}
*/