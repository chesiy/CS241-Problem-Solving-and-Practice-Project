#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"LogiticalRegression.h"

using namespace std;

class DataProcess {
private:
	vector<vector<double>>X;
	vector<vector<double>>Y;
	int train_size;
	int test_size;
public:
	//one hot coding
	DataProcess(map<int, vector<double>>tnd,map<int,vector<double>>tsd) {//读入测试集和训练集
		train_size = tnd.size(); test_size = tsd.size();
		Y.resize(tnd.size()+tsd.size(), vector<double>(1));
		X.resize(tnd.size()+tsd.size(), vector<double>(50));
		map<int, vector<double>>total;
		for (int i = 0; i < tnd.size(); i++) {
			total[i].resize(tnd[0].size());
			total[i].assign(tnd[i].begin(), tnd[i].end());
		}
		for (int i = tnd.size(); i < tnd.size() + tsd.size(); i++) {
			total[i].resize(tnd[0].size());
			total[i].assign(tsd[i - tnd.size()].begin(), tsd[i - tnd.size()].end());
		}
		//merge train and test data
		for (int i = 0; i < total.size(); i++) {
			Y[i][0] = total[i][14];
			X[i][0] = (total[i][0] - 39)/13 ;//年龄
			
			if (total[i][1] == 7) {//never work 和 without pay 合并	
				total[i][1] = 6;
			}
			for (int j = 1; j <=7; j++) {//work class 
				if (total[i][1] == j - 1) 
					X[i][j] = 1;
				else 
					X[i][j] = 0;
			}
			X[i][8] = 0;//bias
			X[i][9] = log(total[i][2]+1);//对连续量中可能有大数的fnlgwt,但没有0
			X[i][10] = total[i][4];//学历 education num
			for (int j = 11; j <= 16; j++) {
				if (total[i][5] == 6) 
					total[i][5] = 0;
				if (total[i][5] == j - 11)
					X[i][j] = 1;
				else 
					X[i][j] = 0;
			}
			for (int j = 17; j <= 29; j++) {//occupation
				if (total[i][6] == 13)
					total[i][6] = 2;//AF替换成other service
				if (total[i][6] == j - 17)
					X[i][j] = 1;
				else
					X[i][j] = 0;
			}
			for (int j = 30; j <= 35; j++) {//relationship
				if (total[i][7] == j - 30) 
					X[i][j] = 1;
				else 
					X[i][j] = 0;
			}
			for (int j = 36; j <= 40; j++) {//race
				if (total[i][8] == j - 36) 
					X[i][j] = 1;
				else 
					X[i][j] = 0;
			}
			for (int j = 41; j <= 42; j++) {//sex
				if (total[i][9] == j - 41) 
					X[i][j] = 1;
				else 
					X[i][j] = 0;
			}
			X[i][43] = (total[i][10] - total[i][11])/1000;//capital income

			X[i][44] = total[i][12];//work hours

			if (total[i][13] <= 2 && total[i][13] >= 0)total[i][13] = 0;//将国家按经济发展程度分成4类
			else {
				if (total[i][13] >= 3 && total[i][13] <= 10)total[i][13] = 1;
				else {
					if (total[i][13] >= 11 && total[i][13] <= 21)total[i][13] =2;
					else {
						if (total[i][13] >= 22 && total[i][13] <= 40)total[i][13] =3;
					}
				}
			}
			for (int j = 45; j <= 48; j++) {//native country
				if (total[i][13] == j - 45)
					X[i][j] = 1;
				else
					X[i][j] = 0;
			}
			X[i][49] = 0;//bias
		}
	}
	void print() {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < X[0].size(); j++) {
				cout << X[i][j] << ' ';
			}
			cout << Y[i][0];
			cout << '\n';
		}
	}

	Matrix LogiReg() {//用逻辑回归学习预测收入是否大于50k
		vector<vector<double>>vecX(train_size,vector<double>(X[0].size()));
		vector<vector<double>>vecY(train_size,vector<double>(1));
		for (int i = 0; i < train_size; i++) {
			vecX[i].assign(X[i].begin(), X[i].end());
			vecY[i][0] = Y[i][0];
		}
		LRegression lr(vecX, vecY, train_size, X[0].size());
		lr.Train();
		return lr.getW();
	}
	void LR_Predict(Matrix W) {
		vector<vector<double>>vecX(test_size, vector<double>(X[0].size()));
		vector<vector<double>>vecY(test_size, vector<double>(1));
		for (int i = 0; i < test_size; i++) {
			vecX[i].assign(X[i+train_size].begin(), X[i+train_size].end());//X是前14列
			vecY[i][0] =Y[i+train_size][0];//Y是最后一列，income
		}
		LRegression lr(vecX, vecY,test_size,X[0].size());
		lr.Predict(W);
	}
};