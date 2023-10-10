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
//const bool is_prins = true;
//const int n_action = 7;
//const int n_state = 7;
//const double E = 2.71828182845904523536;
//const double alpha = 0.01;
//const double gamma = 0.9;
//Route global_best;
//Route route[n_route];
//Customer customer;
//vector<vector<double>> q_table;
//vector<int> cur_state;
//
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
//
//vector<int> select_action(vector<vector<double>>& q_table, vector<int>& state, int cur_iter, int max_iter,
//	default_random_engine& e) {
//	int n = state.size();
//	double eps_end = 0.05;
//	double eps_start = 0.9;
//	double threshold = eps_end + (eps_start - eps_end) * pow(E, -1.0 * cur_iter / max_iter);
//	vector<int> ret(n, 0);
//	uniform_real<double> r(0.0, 1.0);
//	if (r(e) > threshold) {
//		for (int i = 0; i < n; i++) {
//			int cur = state[i];
//			double tmp = -100000000.0;
//			for (int j = 0; j < n_action; j++) {
//				if (tmp < q_table[cur][j]) {
//					tmp = q_table[cur][j];
//					ret[i] = j;
//				}
//			}
//		}
//
//	}
//	else {
//		uniform_int<int>r(0, n_action - 1);
//		for (int i = 0; i < n; i++) {
//			ret[i] = r(e);
//		}
//	}
//	return ret;
//}
//
//
//void init_q_table(vector<vector<double>>& q_table) {
//	q_table.resize(n_state, vector<double>(n_action, 0));
//}
//
//
//void init_cur_state(vector<int>& cur_state, int n, default_random_engine& e) {
//	cur_state.resize(n, 0);
//
//	uniform_int<int>r(0, n_state - 1);
//
//
//	for (int i = 0; i < n; i++) {
//		cur_state[i] = r(e);
//	}
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
//	init_q_table(q_table);
//	init_cur_state(cur_state, n_route, random_engine);
//
//	// 主程序
//
//	vector<int>cur_action(n_route, 0);
//	uniform_int<int>randint(0, n_route - 1);
//	for (int iter = 0; iter < max_iter; iter++) {
//
//		// 复制当前种群
//		Route t_route[n_route];
//		for (int t = 0; t < n_route; t++) t_route[t] = route[t];
//
//		cur_action = select_action(q_table, cur_state, iter, max_iter, random_engine);
//		for (int i = 0; i < n_route; i++) {
//			uniform_real<double> r(0.0, 1.0);
//			double reward = route[i].fitness;
//
//			if (cur_action[i] == 0) crossover_main(customer, route[i]);
//			else if(cur_action[i] == 1) swap_main(customer, route[i]);
//			else if(cur_action[i] == 2) shift_main(customer, route[i]);
//			else if(cur_action[i] == 3) two_opt_main(customer, route[i]);
//			else if(cur_action[i] == 4) exchange_main(customer, route[i]);
//			else if (cur_action[i] == 5) {
//				int ind = randint(random_engine);
//				PMX(route[i].line, t_route[ind].line, random_engine);
//			}
//
//			else if (cur_action[i] == 6) {
//				mutation(route[i].line, random_engine);
//			}
//
//			update_route(customer, route[i]);
//
//			reward = reward - route[i].fitness;
//
//			int next_state = 0;
//			double tmp = -10000000.0;
//
//			tmp = *max_element(q_table[cur_action[i]].begin(), q_table[cur_action[i]].end());
//
//
//			double cur_value = q_table[cur_state[i]][cur_action[i]];
//			q_table[cur_state[i]][cur_action[i]] = (1.0 - alpha) * cur_value + alpha * (reward + gamma * tmp);
//
//		}
//
//		cur_state.assign(cur_action.begin(), cur_action.end());
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
//	/*prins(customer, ret);*/
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