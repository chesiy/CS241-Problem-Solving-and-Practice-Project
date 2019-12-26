#pragma once
#include<vector>
#include"Graph.h"
#include"GUI.h"
#include"Simple_window.h"
#include"Point.h"
#include<algorithm>
#include<iostream>

using namespace Graph_lib;

class BarGraph:public Shape {
	vector<int>A;
	int xlength,ylength;
	string xname, yname;
	string Header;
	vector<string> Xs;
public:
	BarGraph(vector<int>a,string xn,string yn,string H,vector<string> xs) {
		A.resize(a.size());
		A.assign(a.begin(),a.end());
		Xs.resize(xs.size());
		Xs.assign(xs.begin(), xs.end());
		xname = xn; yname = yn;
		Header = H;
		xlength = 40 * A.size();
		ylength = 200;
	}
	void draw_lines()const;
};

class anotherbargraph :public Shape {
private:
	vector<pair<int, int>>A;
	int xlength, ylength;
	string xname, yname;
	string Header;
	vector<string>Xs;
public:
	anotherbargraph(vector<pair<int, int>>a, string xn, string yn, string H, vector<string>xs) {
		A.resize(a.size());
		A.assign(a.begin(), a.end());
		Xs.resize(xs.size());
		Xs.assign(xs.begin(), xs.end());
		xname = xn; yname = yn;
		Header = H;
		ylength = 30 * A.size()+50;
		xlength = 350;
	}
	void draw_lines()const;
};

