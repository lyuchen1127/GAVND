//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <random>
//#include <cmath>
//#include <utility>
//#include <time.h>
//#include <windows.h>
//#include <cstdio>
//#include <cstdlib>
//#include "data.h"
//#include "pso.h"
//using namespace std;
//const int n_route = 50;
//const int max_iter = 50;
//const double prob_m = 0.2;
//const double prob_x = 0.6;
//const double prob_vns = 0.5;
//const bool is_prins = true;
//Route global_best;
//Route route[n_route];
//Customer customer;
//
//void update() {
//	for (int i = 0; i < n_route; i++) {
//		if (route[i].fitness < global_best.fitness)
//			global_best = route[i];
//	}
//}
//
//void update_route(Customer& customer, Route& route) {
//	route.line.clear();
//	route.line.push_back(0);
//	int n = route.info.size();
//	for (int i = 0; i < n; i++) {
//		int m = route.info[i].size();
//		for (int j = 1; j < m; j++) {
//			route.line.push_back(route.info[i][j]);
//		}
//	}
//	//split_route(customer, route);
//	if (is_prins)
//		prins(customer, route);
//	else
//		split_route(customer, route);
//}
//
//Route process(string path, string order_path) {
//
//
//	get_data(path, customer);
//	get_order_data(order_path, customer);
//
//	int n;
//
//	customer.set_electric_cap();
//
//	default_random_engine random_engine(0);
//	//获取城市数目
//	n = customer.points.size();
//
//
//	//计算每个点的K近邻
//	vector<vector<int>> k_nearest(n, vector<int>(n, 0));
//	cal_k_nearest(customer.dis, k_nearest);
//
//	//构造初始解
//	vector<vector<int>> line(n_route, vector<int>(n, 0));
//	construct_init_route(k_nearest, line);
//	for (int i = 0; i < n_route; i++) {
//		route[i].line = line[i];
//		if (is_prins)
//			prins(customer, route[i]);
//		else
//			split_route(customer, route[i]);
//	}
//
//	update();
//
//
//
//	// 主程序
//
//
//	for (int iter = 0; iter < max_iter; iter++) {
//
//		// 复制当前种群
//		Route t_route[n_route];
//		for (int t = 0; t < n_route; t++) t_route[t] = route[t];
//
//		for (int i = 0; i < n_route; i++) {
//			uniform_real<double> r(0.0, 1.0);
//			uniform_int<int>randint(0, n_route - 1);
//
//			int ind = randint(random_engine);
//
//			if (r(random_engine) < prob_x) {
//				PMX(route[i].line, t_route[ind].line, random_engine);
//			}
//
//			if (r(random_engine) < prob_m) {
//				mutation(route[i].line, random_engine);
//			}
//			if (is_prins)
//				prins(customer, route[i]);
//			else
//				split_route(customer, route[i]);
//
//			if (r(random_engine) < prob_vns) {
//				crossover_main(customer, route[i]);
//				swap_main(customer, route[i]);
//				shift_main(customer, route[i]);
//				two_opt_main(customer, route[i]);
//				exchange_main(customer, route[i]);
//				update_route(customer, route[i]);
//			}
//
//		}
//
//		update();
//	}
//
//
//	return global_best;
//}
//
//
//
//
//int main() {
//	string problem_path = "E:\\ADV\\solomon_100\\C101.txt";
//	string order_path = "E:\\ADV\\order\\RC101_100.txt";
//	string path = "E:\\ADV\\result\\rc101_100.txt";
//	fstream result(path, ios::out);
//
//	srand(20);
//	Route ret;
//
//	//vector<int>test_0 = { 0,9,20, 12};
//	//vector<int>test_1 = { 0,9,20 };
//	//vector<int>test_2 = { 0,12 };
//
//	ret = process(problem_path, order_path);
//
//	//cout << cal_tour_fitness(customer, test_0) << endl;
//	//cout << cal_tour_fitness(customer, test_1) << endl;
//	//cout << cal_tour_fitness(customer, test_2) << endl;
//	
//	//int n = ret.line.size();
//	//for (int i = 0; i < n; i ++) {
//	//	result >> ret.line[i];
//	//}
//
//	prins(customer, ret);
//
//
//	for (auto& x : ret.line) {
//		cout << x << " ";
//	}
//
//	cout << endl;
//
//	for (auto& x : ret.info) {
//		for (auto& y : x) {
//			cout << y << " ";
//		}
//		cout << endl;
//	}
//
//	cout << ret.fitness << endl;
//
//	//split_route(customer, ret);
//	//for (auto& x : ret.info) {
//	//	for (auto& y : x) {
//	//		cout << y << " ";
//	//	}
//	//	cout << endl;
//	//}
//
//	//cout << ret.fitness << endl;
//
//
//
//	//保存运行结果
//	for (auto& x : ret.info) {
//		for (auto& y : x) {
//			result << y << " ";
//		}
//		result << endl;
//	}
//
//
//	//for (auto& x : ret.line) {
//	//	result << x << " ";
//	//}
//
//	//result << endl;
//
//	return 0;
//}