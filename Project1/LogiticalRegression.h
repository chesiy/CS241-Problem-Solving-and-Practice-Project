#pragma once
#include<algorithm>
#include<cassert>
#include"Matrix.h"
#include"fstream"
#include<algorithm>


class LRegression {
private:
	Matrix W;//权重
	Matrix X;//样本
	Matrix Y;//训练集中的实际值
	
	int Xnum;//样本个数
	int Feanum;//特征数
	int iterationtimes;//迭代次数
	double learnrate;//学习速率
	
	Matrix sigmoid(Matrix ma) {
		vector<vector<double>> ans(ma.row,vector<double>(ma.col));
		for (int i = 0; i < ma.row; i++) {
			for (int j = 0; j < ma.col; j++) {
				ans[i][j] = 1.0 / (1.0 + 1.0 * exp(-ma.A[i][j]));
				if (ans[i][j] == 1.0) ans[i][j] -= (1e-8);
				if (ans[i][j] == 0.0) ans[i][j] += (1e-8);
			}
		}
		Matrix Ans(ans);
		return Ans;
	}

	double auc(const std::vector<std::pair<double, int>>& r1) {
		int totalSize = r1.size();
		int totalStep = 0;
		int sum = 0;
		std::fstream aucCal("aucCal.txt", std::ios::out);
		for (int i = totalSize - 1; i >= 0; --i) {
			aucCal << r1[i].first << " " << r1[i].second << std::endl;
		}
		return -1;
	}

	double Count_Loss(Matrix Py) {
		//把sigmoid后得到的Y的估计值(Py)
		//与真实值比较，计算损失
		double J = 0.0;
		int acc = 0;
		for (int i = 0; i < Xnum; i++) {
			J += -Y.A[i][0] * log(Py.A[i][0]) - ((1 - Y.A[i][0]) * log(1 - Py.A[i][0]));
			if (Py.A[i][0] >= 0.4 && Y.A[i][0]) acc++;
			else if (Py.A[i][0] < 0.4 && !Y.A[i][0]) acc++;
		}
		std::cout << "Current Accuracy in Train set: " << 1.0 * acc / Xnum << std::endl;
		return J / Xnum;
	}
	void StoreW(Matrix w) {//File IO
		ofstream out;
		out.open("Wfile", ofstream::app);//写入的数据会在原文件后面
		out << "W=\n";
		for (int i = 0; i < w.row; i++) {
			for (int j = 0; j < w.col; j++) {
				out << w.A[i][j] << ' ';
			}
			out << '\n';
		}
	}
	void StorePy(Matrix w) {//File IO
		ofstream out;
		out.open("Wfile", ofstream::app);//写入的数据会在原文件后面
		out << "Py=\n";
		for (int i = 0; i < w.row; i++) {
			for (int j = 0; j < w.col; j++) {
				out << w.A[i][j] << ' ';
			}
			out << '\n';
		}
	}
	void Upd(Matrix Py) {
		Matrix dW = X.Transposition() * (Py-Y);
		dW = dW.Divide(Xnum);
	//	StoreW(W);//在更新W矩阵之前把它存到文件里
		W = W - dW.Multi(learnrate);
		cout <<"Current Loss:"<< Count_Loss(Py) << "\n\n";
	}
public:
	LRegression(Matrix x, Matrix y,int xnum, int fnum):Xnum(xnum),Feanum(fnum),iterationtimes(20),learnrate(0.001) {
		X = x;
		Y = y;
		vector<vector<double>>tmp(fnum, vector<double>(1));
		double a[] = { 0.0203613,
0.00185757,
0.00961322,
0.0108061,
0.0102268,
0.00979863,
0.00974426,
0.0099791,
0.01,
- 0.0851486,
0.00762821,
0.0165917,
0.00673811,
0.000578391,
0.00915973,
0.00927023,
0.00968759,
0.00995526,
0.00870448,
0.00680759,
0.0093317,
0.0122369,
0.0116128,
0.00876117,
0.00863172,
0.00745081,
0.00926949,
0.00940003,
0.00982801,
0.0100358,
0.0108064,
0.00513906,
0.0159243,
0.00401488,
0.00911481,
0.00702622,
0.00450323,
0.00985987,
0.00976778,
0.0098155,
0.00807934,
0.00261518,
0.00941054,
0.470497,
- 0.00832676,
0.0031069,
0.0100436,
0.00936809,
0.00950715,
0.0099956
		};
		for (int i = 0; i < fnum; i++) {
			tmp[i][0] = a[i];
		}
		Matrix M(tmp); 
		W = M;
	}
	void Train() {
		while (iterationtimes--) {
			Matrix Z = X * W;
			Matrix py = sigmoid(Z);
		//	StorePy(py);
			Upd(py);
		}
	}
	Matrix getW() {
		return W;
	}
	void Predict(Matrix W) {//预测
		Matrix Z = X * W;
		Matrix py = sigmoid(Z);
		vector<pair<double, int>>res(Xnum);
		int TP = 0;//True Positive
		int FP = 0;//False Positive 
		int TN = 0;//True Negative
		int FN = 0;//False Negative
		for (int i = 0; i < Xnum; i++) {
			res[i].first = py.A[i][0];
			res[i].second = Y.A[i][0];
			if (py.A[i][0] >= 0.5 && Y.A[i][0]) TP++;
			else if (py.A[i][0] >= 0.5 && !Y.A[i][0]) FN++;
			else if (py.A[i][0] < 0.5 &&  Y.A[i][0]) FP++;
			else if (py.A[i][0] < 0.5 && !Y.A[i][0]) TN++;
		}
		double acc = 1.0 * (TP + TN) / Xnum;
		double precision = 1.0 * TP / (TP + FP);
		double recall = 1.0 * TP / (TP + FN);
		cout << "\nAccuracy in test set: " << acc <<'\n';
	}
};