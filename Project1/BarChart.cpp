#include"BarChart.h"

void BarGraph::draw_lines()const {
	Axis x(Axis::x, Point(50, 300), xlength, A.size());
	Text xx(Point(xlength+60, 300), xname);
	xx.set_color(Color::black);
	xx.draw();
	Axis y(Axis::y, Point(50, 300), ylength, 5, yname);
	x.set_color(Color::black);
	y.set_color(Color::black);
	x.draw(); y.draw();

	Text title(Point(((xlength+50)/2-Header.size()*5), 20),Header);
	title.set_color(Color::red);
	title.draw();
	/*****************x轴&y轴&标题*****************/
	double R = ylength/100 ;//比例系数

	for (int p = 0; p < A.size(); p++) {
		if (A[p] != 0) {
			Graph_lib::Rectangle a(Point(50 + 40 * p, 300 - A[p] * R), Point(80 + 40 * p, 300));
			a.set_color(Color::black);
			a.draw();
		}
	}
	/*****************Bars条条们*********************/

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
	for (int i = 0; i < Xs.size(); i++) {
		if (i % 2) {
			Text xs(Point(53 + 40 * i, 315), Xs[i]);
			xs.set_color(Color::black);
			xs.set_font_size(9);
			xs.draw();
		}
		else {
			Text xs(Point(53 + 40 * i, 328), Xs[i]);
			xs.set_color(Color::black);
			xs.set_font_size(9);
			xs.draw();
		}
	}
    /****************x轴的标识************************/
}

void anotherbargraph::draw_lines()const {
	Graph_lib::Rectangle bigrec(Point(100, 100),Point(100 + xlength, 100 + ylength));
	bigrec.draw();
	Text title(Point(xlength/2-30, 70), Header);
	title.set_color(Color::red);
	title.draw();
	Text xx(Point(xlength + 20, ylength+16), xname);
	xx.set_color(Color::black);
	xx.draw();
	Text yy(Point(105, 100), yname);
	yy.set_color(Color::black);
	yy.draw();
	/**********标题、大的长方形、x轴、y轴标题**************/
	for (int p = 0; p < A.size(); p++) {
			Graph_lib::Rectangle a(Point(100,105+30*p), Point(100+xlength*A[p].first/(A[p].first+A[p].second), 105+30*p+30));
			Graph_lib::Rectangle b(Point(100+xlength * A[p].first / (A[p].first + A[p].second), 105+30*p), Point(100+xlength,105+30*p+30));
			a.set_color(Color::white);
			a.set_fill_color(Color::red);
			a.fill_color();
			a.draw();
			b.set_color(Color::white);
			b.set_fill_color(Color::black);
			b.fill_color();
			b.draw();
	}
	/*****************Bars条条们*********************/
	for (int i = 0; i < A.size(); i++) {
		Text xs(Point(15, 115+30*i), Xs[i]);
		xs.set_color(Color::black);
		xs.set_font_size(10);
		xs.draw();
	}
	/************y轴上的标识*********************/
	Graph_lib::Rectangle aa(Point(105+xlength,150), Point(118 + xlength, 160));
	Graph_lib::Rectangle bb(Point(105+xlength,164), Point(118+xlength,174));
	aa.set_color(Color::white);
	aa.set_fill_color(Color::red);
	aa.fill_color();
	aa.draw();
	bb.set_color(Color::white);
	bb.set_fill_color(Color::black);
	bb.fill_color();
	bb.draw();
	Text aaa(Point(120 + xlength, 158), "income>=50k");
	Text bbb(Point(120 + xlength, 172), "income<50k");
	aaa.set_color(Color::black);
	bbb.set_color(Color::black);
	aaa.set_font_size(9);
	bbb.set_font_size(9);
	aaa.draw();
	bbb.draw();
}