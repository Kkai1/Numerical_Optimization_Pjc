#include "homework01.h"

homework01::homework01(){}

double homework01::Rosenbrock(vector<double> x){
    int dimension = x.size();
    double res = 0;
    for(int i = 0;i < dimension/2;i++){
        res += 100*pow(pow(x[2*i-1]*x[2*i-1],2)-x[2*i],2)+pow(x[2*i]-1,2);
    }
    return res; 
}

vector<double> homework01::RosenbrockGrandient(vector<double> x){
    vector<double> grad(x.size(),0);
    //保证维度是偶数
    if(grad.size() % 2 != 0){
        cout << "x_dimension error" << endl;
        return vector<double>();
    }
    for(int i = 0;i < grad.size();i+=2){
        grad[i] = 400 * x[i] * (pow(x[i],2) - x[i+1]) + 2 * (x[i] - 1);
        grad[i+1] = -200 * (pow(x[i],2) - x[i+1]);
    }
    return grad;
}

vector<vector<double>> homework01::RosenbrockHessian(vector<double> x){
    vector<vector<double>> Hessian(x.size(),vector<double>(x.size(),0));
    for(int i = 0;i < x.size();i+=2){
        for(int j = 0;j < x.size();j+=2){
            Hessian[i][j] = 1200 * pow(x[i],2) - 400 * x[i+1] + 2;
            Hessian[i+1][j] = -400 * x[i];
            Hessian[i][j+1] = -400 * x[i];
            Hessian[i+1][j+1] = 200;
        }
    }
    return Hessian;
}

//求数组的平方和
double power(vector<double> nums){
    double res = 0;
    for(double d:nums){
        res += d*d;
    }
    return res;
}

double homework01::Armijo(vector<double> x,vector<double> grad){
    //初始步长为1
    double lemeta = 1;
    //迭代的下一次状态量
    vector<double> Nextx(x.size(),0);
    for(int i = 0;i < x.size();i++){
        Nextx[i] = x[i] - lemeta * grad[i];
    }
    while (Rosenbrock(Nextx) > (Rosenbrock(x) - c * lemeta * (power(grad)))){
        lemeta /= 2;
        for(int i = 0;i < x.size();i++){
            Nextx[i] = x[i] - lemeta * grad[i];
        }
    }
    //输出可行步长
    return lemeta;
}

vector<double> homework01::LineSearch(vector<double> x){
    //迭代次数
    int iter = 0;
    vector<double> cur_x = x;
    //搜索步长
    double lemata;
    while(iter < maxIter && found == false){
        vector<double> grad = homework01::RosenbrockGrandient(cur_x);
        //梯度的误差
        double error = sqrt(power(grad));
        //输出迭代信息
        //printf("cur_x = [%f,%f],Rosenbrock:%f,iter = %d,grad = [%f,%f],error = %f\n",cur_x[0],cur_x[1],Rosenbrock(cur_x),iter,grad[0],grad[1],error);
        printf("Rosenbrock:%f,iter = %d,error = %f\n",Rosenbrock(cur_x),iter,error);
        if(error < tolerance){
            found = true;
            break;
        }else{
            lemata = homework01::Armijo(cur_x,grad);
            //输出步长
            cout << lemata << endl;
            for(int i = 0;i < x.size();i++){
                cur_x[i] = x[i] - lemata * grad[i];
            }
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

homework01::homework01(vector<double> x,int tolerate,int maxIter){
    this->x0 = x;
    this->tolerance = tolerance;
    this->maxIter = maxIter;
}
