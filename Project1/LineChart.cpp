#include"LineChart.h"
//传进来的数组A按照A.first的值从小到大排序（A.first是x轴，A.second是y轴)

void LineGraph::draw_lines()const {
	Axis x(Axis::x, Point(50, 300), xlength, 100);
	Text xx(Point(xlength + 60, 300), xname);
	xx.set_color(Color::black);
	xx.draw();
	Axis y(Axis::y, Point(50, 300), ylength, 5, yname);
	x.set_color(Color::black);
	y.set_color(Color::black);
	x.draw(); y.draw();

	Text title(Point(((xlength + 50) / 2 - Header.size() * 3), 20), Header);
	title.set_color(Color::red);
	title.draw();
	/*****************x轴&y轴&标题*****************/
	double R = ylength / 100;//比例系数
	Lines lines;
	for (int p = 0; p < A.size(); p++) {
			Graph_lib::Circle a(Point(50+(A[p].first-A[0].first)*Perlen,300-A[p].second*R),3);
			a.set_color(Color::black);
			a.draw();
	}
	for (int p = 0; p < A.size() - 1; p++) {
		lines.add(Point(50 + (A[p].first - A[0].first)*Perlen, 300 - A[p].second * R), Point(50 + Perlen*(A[p + 1].first - A[0].first), 300 - A[p + 1].second * R));
	}
	lines.set_color(Color::dark_green);
	lines.draw();
	/*****************Points点点们 用线连起来******************/
	for (int i = 0; i < 6; i++) {
		string num = "0.";
		num += to_string(i * 2);
		if (i == 5) num = "1.0";
		Text n(Point(30, 300 - i * 40), num);
		n.set_color(Color::black);
		n.set_font_size(10);
		n.draw();
	}
	/******************y轴的标识**********************/
	
	for (int i = 0; i <=1+A[A.size()-1].first ; i++) {
		Text xs(Point(50 + Perlen * i, 315), to_string(i));
		xs.set_color(Color::black);
		xs.set_font_size(9);
		xs.draw();
	}
	/****************x轴的标识************************/
}