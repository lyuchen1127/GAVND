#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <utility>
#include <fstream>
#include <string>
#include <map>
using namespace std;

typedef struct TabuList {
	vector<pair<int, int> > tabu_list;
	int capacity = 0;
	int pos = 0;
	TabuList(int m) {
		capacity = m;
		pos = 0;
		for (int i = 0; i < m; i++) {
			tabu_list.push_back(make_pair<int, int>(0, 0));
		}
	}

	void push(pair<int, int>& p) {
		tabu_list[pos] = p;
		pos = (pos + 1) % capacity;
	}

}TabuList;

typedef struct Customer {
	vector<vector<int>> points;
	vector<vector<double>> dis;
	vector<int> caps;
	vector<int> due_date;
	map<int,double> order;
	map<int, int>batch;
	int n_customer, max_cap, electric_cap;
	double max_dis = 1500;
	double coff = 0.0;
	double alpha = 0.2;
	vector<int> real_id;

	void set_electric_cap() {
		electric_cap = 18000;
		//electric_cap = max_cap * 0.1 * 0.3;
	}


	double electric_curve(int cur_load) {

		double k = cur_load / this->max_cap;
		// 每秒消耗
		double s = 10 * k + 20;
		return s / 10;

		/*return 0.5;*/
	}

}Customer;



typedef struct Route {
	vector<int> line;
	vector<vector<int>> info;
	double fitness;
	vector<double> detail;
	double alpha;
	Route() {
		alpha = 0.2;
		vector<double>(2, 0).swap(detail);
		fitness = 10000000.0;
	}

	void cal_tour_detail(Customer& customer, vector<int>& tour) {
		double f = 0.0;
		double penalty = 0.0;
		int n = tour.size();
		int a, b;
		double start_sercive_time = 0;
		// 计算距离
		for (int i = 0; i < n; i++) {
			if (i == n - 1) {
				a = tour[i];
				b = tour[0];
			}
			else {
				a = tour[i];
				b = tour[i + 1];
			}
			start_sercive_time = max(start_sercive_time, customer.order[a]);
			f += customer.dis[a][b];
			//penalty += max(0.0, fitness - customer.due_date[b]);
		}

		//计算是否按时到达的惩罚值
		double cur_time = start_sercive_time;
		for (int i = 0; i < n; i++) {
			if (i == n - 1) {
				a = tour[i];
				b = tour[0];
			}
			else {
				a = tour[i];
				b = tour[i + 1];
			}
			cur_time += customer.dis[a][b];
			penalty += max(0.0, f - customer.due_date[b]);
		}

		detail[0] += f;
		detail[1] += penalty;
	}

	void cal_detail(Customer& customer) {
		int n = info.size();
		vector<double>(2, 0).swap(detail);
		for (int i = 0; i < n; i++) {
			 cal_tour_detail(customer, info[i]);
		}
	}

}Route;

typedef struct QTable {
	vector<vector<double>> table;
}QTable;


void get_data(string f, string, Customer& customer);
double cal_point_dis(vector<int>& p1, vector<int>& p2);
void cal_dis_matrix(vector<vector<double>>& dis, vector<vector<int>>& points);
void cal_k_nearest(vector<vector<double>>& dis, vector<vector<int>>& ret);
void construct_init_route(vector<vector<int>>& k_nearesr, vector<vector<int>>& ret, default_random_engine&);
double cal_tour_fitness(Customer&, vector<int>& tour, bool is_log=false);
void cal_fitness(Customer& , Route& route);
bool is_valid(Customer&,  vector<int>& tour);
void prins(Customer&, Route&);
void split_route(Customer& customer, Route& route);
vector<double> cal_tour_detail(Customer&, vector<int>&);

