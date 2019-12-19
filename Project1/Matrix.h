#pragma once
#include<cmath>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Matrix {
public:
	vector<vector<double>> A;
	int row;
	int col;
public:
	Matrix() {
		row = 0; col = 0;
	}
	Matrix(const vector<vector<double>>& a) {
		A.resize(a.size(), vector<double>(a[0].size()));
		for (int i = 0; i < a.size(); i++) {
			A[i].assign(a[i].begin(), a[i].end());
		}
		row= A.size();
		col = A[0].size();
	}
	Matrix Divide(double data) {
		vector<vector<double>> ans(row,vector<double>(col));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ans[i][j] = A[i][j] / data;
			}
		}
		return Matrix(ans);
	}
	Matrix Multi(double data) {
		vector<vector<double>> ans(row, vector<double>(col));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				ans[i][j] = A[i][j] *data;
			}
		}
		return Matrix(ans);
	}
	Matrix Transposition() {//×ªÖÃ
		vector<vector<double>>ans(col, vector<double>(row));
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				ans[i][j] = A[j][i];
			}
		}
		return Matrix(ans);
	}
	Matrix& operator=(const Matrix& r) {
		if (this == &r)return *this;
		A.resize(r.row, vector<double>(r.col));
		row = r.row; col = r.col;
		for (int i = 0; i < r.A.size(); i++) {
			A[i].assign(r.A[i].begin(), r.A[i].end());
		}
		return *this;
	}
	Matrix operator+(const Matrix& r) const {
		vector<vector<double>>C;
		if (row == r.row && col ==r. col) {
			C.resize(row, vector<double>(col));
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					C[i][j] = A[i][j] + r.A[i][j];
				}
			}
			Matrix ans(C);
			return ans;
		}
		else {
			throw"invalid Matrix";
		}
	}
	Matrix operator-(const Matrix& r) const {
		vector<vector<double>>C;
		if (row == r.row && col == r.col) {
			C.resize(row, vector<double>(col));
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					C[i][j] = A[i][j] - r.A[i][j];
				}
			}
			Matrix ans(C);
			return ans;
		}
		else {
			throw"invalid Matrix";
		}
	}
	Matrix operator*(const Matrix& r)const {
		vector<vector<double>> C;//ans
		if (col == r.row) {
			C.resize(row, vector<double>(r.col));
			for (int i = 0; i < C.size(); i++) {
				fill(C[i].begin(), C[i].end(), 0);
			}
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < r.col; j++) {
					for (int k = 0; k < col; k++) {
						C[i][j] += A[i][k] * r.A[k][j];	
					}
				//	cerr <<i<<' '<< C[i][j] << ' ';
				}
				//cerr << '\n';
			}
			Matrix ans(C);
			return ans;
		}
		else {
			throw"Invalid Matrix";
		}
	}
	void print() {
		for (int i = 0; i <row; i++) {
			for (int j = 0; j < col; j++) {
				cout << A[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

