#define _CRT_SECURE_NO_WARNINGS

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "BarChart.h"
#include<fstream>
#include<vector>
#include <iostream>
#include<cstring>
#include"datastruct.h"
#include"Matrix.h"
#include"ProcessData.h"

using namespace std;
int main()
{
	ifstream in("adult-training.csv", ios::in);
	string line;
	Dataset da;
	int i = 0;
	while (getline(in, line)) {
		if (da.store_data(line, i)) {
			i++;
		}
	}
	ifstream test("adult-test.csv", ios::in);
	Dataset Ts;
	 i = 0;
	getline(test, line);
	while (getline(test, line)) {
		if (Ts.store_data(line, i)) {
			i++;
		}
	}
	Ts.delete_dot();
	map<int,vector<double>>Train_data=da.encode_data();
	map<int, vector<double>>Test_data = Ts.encode_data();
	DataProcess pro(Train_data,Test_data);
	pro.print();

	cout << "\n*****\n";
	da.draw_edu_income();
	da.draw_mari_income();
	da.draw_workhour_income();
	da.draw_occupation_income();
	
	Matrix W=pro.LogiReg();
	W.print();
	/**************************Predict*****************************/
	pro.LR_Predict(W);
}

//------------------------------------------------------------------------------
