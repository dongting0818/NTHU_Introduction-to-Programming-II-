//#include "13475.h"
#include"finction.h"
Matrix::~Matrix(){}

Matrix::Matrix():n(n){
    matrix = new long long *[n];
    for(int i=0;i<n;i++){
        matrix[i] = new long long[n];
    }
    toZero();
}