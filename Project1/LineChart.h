#pragma once
#include<vector>
#include"Graph.h"
#include"GUI.h"
#include"Simple_window.h"
#include"Point.h"
#include<algorithm>
#include<iostream>

using namespace Graph_lib;

class LineGraph :public Shape {
	vector<pair<int,int>>A;
	int xlength, ylength;
	string xname, yname;
	string Header;
	const int Perlen = 12;
public:
	LineGraph(vector<pair<int,int>>a, string xn, string yn, string H) {
		A.resize(a.size());
		A.assign(a.begin(), a.end());
		xname = xn; yname = yn;
		Header = H;
		xlength = Perlen * 100;
		ylength = 200;
	}
	void draw_lines()const;
};