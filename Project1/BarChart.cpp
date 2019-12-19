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