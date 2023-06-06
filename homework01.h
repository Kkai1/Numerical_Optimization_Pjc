#ifndef HOMEWORK01_H
#define HOMEWORK01_H

#include <math.h>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

class homework01
{
public:
    vector<double> x0{1,1};
    double c = 0.02;
    bool found = false;
    int maxIter = 7000;
    double tolerance = 0.001; //容许误差
public:
    homework01();
    homework01(vector<double> x,int tolerate,int maxIter);

    //Rosenbrock函数的计算
    double Rosenbrock(vector<double> x);

    //Rosenbrock梯度的计算
    vector<double> RosenbrockGrandient(vector<double> x);

    //Rosenbrock的Hessian计算
    vector<vector<double>> RosenbrockHessian(vector<double> x);

    //求取合适的alpha  线搜索回退法
    double Armijo(vector<double> x,vector<double> grad);

    //Rosenbrock迭代求解 线搜索方法
    vector<double> LineSearch(vector<double> x);

};

#endif