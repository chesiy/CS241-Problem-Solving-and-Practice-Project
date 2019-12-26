#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include "BarChart.h"
#include"LineChart.h"
#include"LogiticalRegression.h"
#include<algorithm>

using namespace std;

bool cmp(pair<int, int>a, pair<int, int>b) {
	return a.first < b.first;
}

class Dataset {
private:
	map<int, vector<string>> rawdata;//储存csv文件中读入的原始数据，int是序号
	map<int, vector<double>> data;//储存将字符型转化为数值编码后的数据集，int是序号
	vector<string> header;//储存列名，如“education_num"等
	map<int, vector<string>> cate_refer;//储存文本形式的数据可能出现的所有值，如"Education"中可能出现的"Master"等
	int string_int(string s) {
		int num = 0;
		if (s[0] == ' ')s = s.substr(1, s.size() - 1);
		for (int i = s.length() - 1; i >= 0; i--) {
			num += (s[i] - '0') * pow(10, s.length() - 1 - i);
		}
		return num;
	}
public:
	Dataset() {
		vector<string >tmp = { "age","workclass","fnlwgt","education","education_num","marital_status","occupation",
		"relationship","race","sex","capital_gain","capital_loss","hours_per_week","native_country","income" };
		header.assign(tmp.begin(), tmp.end());

		cate_refer.insert(pair<int, vector<string>>(0, vector<string>({ "" })));
		vector<string> wkc = { " Private"," Self-emp-not-inc"," Self-emp-inc"," Federal-gov"," Local-gov"," State-gov"," Without-pay", " Never-worked" };
		pair<int, vector<string>>workclass(1, wkc);
		cate_refer.insert(workclass);
		cate_refer.insert(pair<int, vector<string>>(2, vector<string>({ "" })));
		vector<string> edu = {" Bachelors"," Some-college", " 11th", " HS-grad"," Prof-school" ," Assoc-acdm"," Assoc-voc", " 9th", " 7th-8th"," 12th",  " Masters"," 1st-4th", " 10th" , " Doctorate"," 5th-6th"," Preschool"  };
		pair<int, vector<string>>education(3, edu);
		cate_refer.insert(education);
		cate_refer.insert(pair<int, vector<string>>(4, vector<string>({ "" })));
		vector<string> mari = { " Married-civ-spouse", " Divorced", " Never-married", " Separated"," Widowed", " Married-spouse-absent", " Married-AF-spouse" };
		pair<int, vector<string>>marital(5, mari);
		cate_refer.insert(marital);
		vector<string> occu = { " Tech-support", " Craft-repair", " Other-service", " Sales", " Exec-managerial", " Prof-specialty", " Handlers-cleaners", " Machine-op-inspct", " Adm-clerical"," Farming-fishing", " Transport-moving", " Priv-house-serv"," Protective-serv", " Armed-Forces" };
		pair<int, vector<string>> occupation(6, occu);
		cate_refer.insert(occupation);
		vector<string> relat = { " Wife", " Own-child", " Husband", " Not-in-family", " Other-relative", " Unmarried" };
		pair<int, vector<string>>relation(7, relat);
		cate_refer.insert(relation);
		vector<string> rac = { " White", " Asian-Pac-Islander", " Amer-Indian-Eskimo", " Other", " Black" };
		pair<int, vector<string>> race(8, rac);
		cate_refer.insert(race);
		vector<string> se = { " Female", " Male" };
		pair<int, vector<string>>sex(9, se);
		cate_refer.insert(sex);
		cate_refer.insert(pair<int, vector<string>>(10, vector<string>({ "" })));
		cate_refer.insert(pair<int, vector<string>>(11, vector<string>({ "" })));
		cate_refer.insert(pair<int, vector<string>>(12, vector<string>({ "" })));
		vector<string> natcou = { 
			" United-States", " Puerto-Rico", " Outlying-US(Guam-USVI-etc)",
			" England", " Ireland",  " Canada", " Hong"," Germany",  " Japan", " Italy"," France",
			" India","China"," Greece", " Philippines"," Vietnam", " Mexico",  " Poland"," Scotland", " Thailand", " Taiwan"," Portugal",
			" South",   " Cuba", " Iran", " Cambodia"," Honduras",  " Jamaica",  " Dominican-Republic"," Laos", " Ecuador", " Haiti", " Columbia", " Hungary", " Guatemala", " Nicaragua", " Yugoslavia", " El-Salvador", " Trinadad&Tobago"," Peru",  " Holand-Netherlands" };
		pair<int, vector<string>> native(13, natcou);
		cate_refer.insert(native);
		vector<string> inc = {" <=50K"," >50K"};
		pair<int, vector<string>> income(14, inc);
		cate_refer.insert(income);
	}
	vector<double>& operator[](const int& idx) {
		map<int, vector<double>>::iterator it = data.find(idx);
		vector < double > ans = it->second;
		return ans;
	}
	/***************************************读入原始数据，处理空数据************************************************/
	bool store_data(string str, int idx) {//读入并剔除空数据
		int ori_pos = 0;
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == ',' || i == str.length() - 1) {
				string tmp;
				if (i == str.length() - 1) {
					tmp = str.substr(ori_pos, i + 1 - ori_pos);
				}
				else {
			       tmp = str.substr(ori_pos, i - ori_pos);
				}
				if (tmp != " ?") {
					rawdata[idx].push_back(tmp);
				}
				else {
					rawdata[idx].clear();
					return false;
				}
				ori_pos = i + 1;
			}
		}
		return true;
	}
	void delete_dot() {//把income的.去掉
		for (int i = 0; i < rawdata.size(); i++) {
			rawdata[i][14] = rawdata[i][14].substr(0, rawdata[i][14].size() - 1);
		}
	}

	/**********************************************预处理数据*****************************************************/
	map<int,vector<double>> encode_data() {//把rawdata转化为处理后的int的数据
		int roll1[] = { 0,2,4,10,11,12 };
		int roll2[] = { 1,3,5,6,7,8,9,13,14 };
		for (int i = 0; i < rawdata.size(); i++) {
			data[i].resize(15);
			for (int j = 0; j < 6; j++) {
				data[i][roll1[j]] = string_int(rawdata[i][roll1[j]]);
			}	
			for (int j = 0; j < 9; j++) {
				for (int k = 0; k < cate_refer[roll2[j]].size(); k++) {
					if (rawdata[i][roll2[j]] == cate_refer[roll2[j]][k]) {
						data[i][roll2[j]] = k;
						break;
					}
				}
			}
		}
		return data;
	}
	/***************************************use for debug**************************************************/
	void print() {
		cout << data.size() << '\n';
		for (int i = 0; i <100; i++) {
			for (int j = 0; j < data[i].size(); j++) {
				cout << data[i][j]<< ' ';
			}
			cout << '\n';
		}
	}
	/*********************************************画图**************************************************/
	void draw_edu_income() {//画education和income的柱状图
		vector<string> edu = { "Bachelor", " college", "  11th", "HS-grad", "Prof-Schl", "Assoc-a", 
		" Assoc-v", " 9th", "  7th-8th", "12th", "Masters", "1st-4th", "10th", "Doctor", "5th-6th", "Preschool" };
		double monny[18] = { 0 };
		int num[18] = { 0 };
		for (int i = 0; i < data.size(); i++) {
			num[(int)data[i][3]]++;
			if ((int)data[i][14] == 1) {
				monny[(int)data[i][3]]++;
			}
		}
		for (int i = 0; i < 16; i++) {
			monny[i] *= 100;
			monny[i] /= num[i];
		}
		vector<int> nus(monny, monny + 16);
		BarGraph b(nus, "education", "income",  "Education - Income Graph",edu);
		Point tl(100, 100);           // to become top left  corner of window
		Simple_window win(tl, 600, 400, "Canvas");    // make a simple window
		win.attach(b);
		win.wait_for_button();       // give control to the display engine*/
	}
	void draw_mari_income() {//画婚姻状况和收入关系
		vector<string> mari = { "Married-civ-spouse", "Divorced", "Never-married", "Separated","Widowed", "Married-spouse-absent", "Married-AF-spouse" };
		double money[7] = { 0 };
		int num[7] = { 0 };
		for (int i = 0; i < data.size(); i++) {
			num[(int)data[i][5]]++;
			if (data[i][14] == 1) {
				money[(int)data[i][5]]++;
			}
		}
		for (int i = 0; i < 7; i++) {
		//	cout << money[i] << ' ' << num[i] << '\n';
			money[i] *= 100;
			money[i] /= num[i];
		}
		vector<int> nus(money, money + 7);
		BarGraph b(nus, "Marital Status", "income", "Marital Status-Income Graph", mari);
		Point tl(100, 100);           // to become top left  corner of window
		Simple_window win(tl, 600, 400, "Canvas");    // make a simple window
		win.attach(b);
		win.wait_for_button();       // give control to the display engine*/
	}
	void draw_workhour_income() {//画工作时间和收入关系
		vector<int> num(100,0) ;
		vector<int> money(100,0) ;
		for (int i = 0; i < data.size(); i++) {
			num[data[i][12]]++;
			if (data[i][14] == 1) {
				money[data[i][12]]++;
			}
		}
		vector<pair<int, int>> ys;
		for (int i = 0; i < 100; i++) {
			if (num[i] != 0) {
				ys.push_back(pair<int, int>(i, money[i] * 100 / num[i]));
			}
		}
		sort(ys.begin(), ys.end(), cmp);
		LineGraph l(ys, "work hour", "income", "Work hour-Income Graph");
		Point tl(100, 100);           // to become top left  corner of window
		Simple_window win(tl, 1000, 400, "Canvas");    // make a simple window
		win.attach(l);
		win.wait_for_button();       // give control to the display engine*/
	}
	void draw_occupation_income() {//画职业和收入关系
		vector<pair<int, int>>num(14);
		for (int i = 0; i < data.size(); i++) {
			if(data[i][14]==0)
				num[data[i][6]].second++;
			else {
				num[data[i][6]].first++;
			}
		}
		vector<string> occup={ " Tech-support", " Craft-repair", " Other-service", " Sales", " Exec-managerial", " Prof-specialty", " Handlers-cleaners", " Machine-op-inspct", " Adm-clerical"," Farming-fishing", " Transport-moving", " Priv-house-serv"," Protective-serv", " Armed-Forces" };
		anotherbargraph gr(num, "number", "occupation", "Occupation-Income Graph", occup);
		Point tl(100, 100);           // to become top left  corner of window
		Simple_window win(tl, 600, 400, "Canvas");    // make a simple window
		win.attach(gr);
		win.wait_for_button();       // give control to the display engine*/
	}
	
	 /************************************************************************************************/
};