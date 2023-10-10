//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <random>
//#include <cmath>
//#include <utility>
//#include <ctime>
//#include <windows.h>
//#include <cstdio>
//#include <cstdlib>
//#include <chrono>
//#include "data.h"
//#include "pso.h"
//using namespace std;
//using namespace chrono;
//const int n_route = 40;
//const int max_iter = 200;
//const double prob_m = 0.2;
//const double prob_x = 0.6;
//const double prob_a = 0.6;
//const double prob_b = 0.6;
//const double prob_vns = 0.1;  //default:0.5
//const bool is_prins = true;
//vector<vector<double>> q_table;
//vector<int> cur_state;
//const int n_action = 5;
//const int n_state = 5;
//const double E = 2.71828182845904523536;
//const double alpha = 0.5;
//const double gamma = 0.9;
//volatile int seed = 50;
//Route group_best[n_route];
//Route global_best;
//Route route[n_route];
//Customer customer;
//
//string problem_paths[] = { "E:\\ADV\\solomon_25\\C101.txt", "E:\\ADV\\solomon_25\\R101.txt", "E:\\ADV\\solomon_25\\RC101.txt",
//"E:\\ADV\\solomon_25\\C201.txt", "E:\\ADV\\solomon_25\\R201.txt", "E:\\ADV\\solomon_25\\RC201.txt",
//"E:\\ADV\\solomon_50\\C101.txt", "E:\\ADV\\solomon_50\\R101.txt", "E:\\ADV\\solomon_50\\RC101.txt",
//"E:\\ADV\\solomon_50\\C201.txt", "E:\\ADV\\solomon_50\\R201.txt", "E:\\ADV\\solomon_50\\RC201.txt",
//"E:\\ADV\\solomon_100\\C101.txt", "E:\\ADV\\solomon_100\\R101.txt", "E:\\ADV\\solomon_100\\RC101.txt",
//"E:\\ADV\\solomon_100\\C201.txt", "E:\\ADV\\solomon_100\\R201.txt", "E:\\ADV\\solomon_100\\RC201.txt" ,
//
//"E:\\ADV\\solomon_100\\RC101.txt" ,"E:\\ADV\\solomon_100\\RC102.txt" ,"E:\\ADV\\solomon_100\\RC103.txt" ,
//"E:\\ADV\\solomon_100\\RC104.txt" ,"E:\\ADV\\solomon_100\\RC105.txt" ,"E:\\ADV\\solomon_100\\RC106.txt",
//"E:\\ADV\\solomon_100\\RC107.txt","E:\\ADV\\solomon_100\\RC108.txt", "E:\\ADV\\solomon_100\\RC201.txt",
//"E:\\ADV\\solomon_100\\RC202.txt","E:\\ADV\\solomon_100\\RC203.txt", "E:\\ADV\\solomon_100\\RC204.txt", 
//"E:\\ADV\\solomon_100\\RC205.txt","E:\\ADV\\solomon_100\\RC206.txt","E:\\ADV\\solomon_100\\RC207.txt",
//"E:\\ADV\\solomon_100\\RC208.txt" };
//
//string order_paths[] = { "E:\\ADV\\order\\25.txt", "E:\\ADV\\order\\25.txt", "E:\\ADV\\order\\25.txt",
//"E:\\ADV\\order\\25.txt","E:\\ADV\\order\\25.txt","E:\\ADV\\order\\25.txt", 
//"E:\\ADV\\order\\50.txt", "E:\\ADV\\order\\50.txt", "E:\\ADV\\order\\50.txt",
//"E:\\ADV\\order\\50.txt","E:\\ADV\\order\\50.txt","E:\\ADV\\order\\50.txt",
//"E:\\ADV\\order\\100.txt", "E:\\ADV\\order\\100.txt", "E:\\ADV\\order\\100.txt",
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt",
//
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt", 
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt", 
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt", 
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt", 
//"E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt","E:\\ADV\\order\\100.txt", 
//"E:\\ADV\\order\\100.txt"};
//
//string path_routes[] = { "E:\\ADV\\result\\route\\c101_25.txt" , "E:\\ADV\\result\\route\\r101_25.txt" , "E:\\ADV\\result\\route\\rc101_25.txt",
// "E:\\ADV\\result\\route\\c201_25.txt" , "E:\\ADV\\result\\route\\r201_25.txt" , "E:\\ADV\\result\\route\\rc201_25.txt",
//"E:\\ADV\\result\\route\\c101_50.txt" , "E:\\ADV\\result\\route\\r101_50.txt" , "E:\\ADV\\result\\route\\rc101_50.txt",
// "E:\\ADV\\result\\route\\c201_50.txt" , "E:\\ADV\\result\\route\\r201_50.txt" , "E:\\ADV\\result\\route\\rc201_50.txt",
//"E:\\ADV\\result\\route\\c101_100.txt" , "E:\\ADV\\result\\route\\r101_100.txt" , "E:\\ADV\\result\\route\\rc101_100.txt",
// "E:\\ADV\\result\\route\\c201_100.txt" , "E:\\ADV\\result\\route\\r201_100.txt" , "E:\\ADV\\result\\route\\rc201_100.txt",
//
//"E:\\ADV\\result\\route\\rc101_100.txt","E:\\ADV\\result\\route\\rc102_100.txt","E:\\ADV\\result\\route\\rc103_100.txt",
//"E:\\ADV\\result\\route\\rc104_100.txt","E:\\ADV\\result\\route\\rc105_100.txt","E:\\ADV\\result\\route\\rc106_100.txt",
//"E:\\ADV\\result\\route\\rc107_100.txt","E:\\ADV\\result\\route\\rc108_100.txt","E:\\ADV\\result\\route\\rc201_100.txt",
//"E:\\ADV\\result\\route\\rc202_100.txt","E:\\ADV\\result\\route\\rc203_100.txt","E:\\ADV\\result\\route\\rc204_100.txt",
//"E:\\ADV\\result\\route\\rc205_100.txt","E:\\ADV\\result\\route\\rc206_100.txt","E:\\ADV\\result\\route\\rc207_100.txt",
//"E:\\ADV\\result\\route\\rc208_100.txt",
// };
//
//string path_values[] = { "E:\\ADV\\result\\value\\c101_25.txt" , "E:\\ADV\\result\\value\\r101_25.txt" , "E:\\ADV\\result\\value\\rc101_25.txt",
//"E:\\ADV\\result\\value\\c201_25.txt" , "E:\\ADV\\result\\value\\r201_25.txt" , "E:\\ADV\\result\\value\\rc201_25.txt",
//"E:\\ADV\\result\\value\\c101_50.txt" , "E:\\ADV\\result\\value\\r101_50.txt" , "E:\\ADV\\result\\value\\rc101_50.txt",
//"E:\\ADV\\result\\value\\c201_50.txt" , "E:\\ADV\\result\\value\\r201_50.txt" , "E:\\ADV\\result\\value\\rc201_50.txt",
//"E:\\ADV\\result\\value\\c101_100.txt" , "E:\\ADV\\result\\value\\r101_100.txt" , "E:\\ADV\\result\\value\\rc101_100.txt",
//"E:\\ADV\\result\\value\\c201_100.txt" , "E:\\ADV\\result\\value\\r201_100.txt" , "E:\\ADV\\result\\value\\rc201_100.txt",
//
//"E:\\ADV\\result\\value\\rc101_100.txt","E:\\ADV\\result\\value\\rc102_100.txt","E:\\ADV\\result\\value\\rc103_100.txt",
//"E:\\ADV\\result\\value\\rc104_100.txt","E:\\ADV\\result\\value\\rc105_100.txt","E:\\ADV\\result\\value\\rc106_100.txt",
//"E:\\ADV\\result\\value\\rc107_100.txt","E:\\ADV\\result\\value\\rc108_100.txt","E:\\ADV\\result\\value\\rc201_100.txt",
//"E:\\ADV\\result\\value\\rc202_100.txt","E:\\ADV\\result\\value\\rc203_100.txt","E:\\ADV\\result\\value\\rc204_100.txt",
//"E:\\ADV\\result\\value\\rc205_100.txt","E:\\ADV\\result\\value\\rc206_100.txt","E:\\ADV\\result\\route\\rc207_100.txt",
//"E:\\ADV\\result\\value\\rc208_100.txt",
//};
//
//uniform_int<int>randint(0, n_action - 1);
//uniform_real<double> r(0.0, 1.0);
//
//void update() {
//	for (int i = 0; i < n_route; i++) {
//		if (route[i].fitness < group_best[i].fitness)
//			group_best[i] = route[i];
//		if (group_best[i].fitness < global_best.fitness)
//			global_best = group_best[i];
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
//	if (is_prins)
//		prins(customer, route);
//	else
//		split_route(customer, route);
//}
//
//
//int select_action(vector<vector<double>>& q_table, int cur, int cur_iter, int max_iter, default_random_engine& e) {
//	double eps_end = 0.3;
//	double eps_start = 1.0;
//	//double threshold = eps_end + (eps_start - eps_end) * (1.0* (max_iter - cur_iter) / 1.0*max_iter);
//	double threshold = eps_end + (eps_start - eps_end) * pow(E, -1.0 * cur_iter / max_iter);
//
//	if (cur_iter * 3 < max_iter) return randint(e);
//
//	if (r(e) > threshold) {
//		return max_element(q_table[cur].begin(), q_table[cur].end()) - q_table[cur].begin();
//	}
//	else {
//		vector<double> cum(n_action, q_table[cur][0] + 1.0);
//
//		for (int j = 1; j < n_action; j++) {
//			cum[j] += (q_table[cur][j] + cum[j - 1]);
//		}
//		for (int j = 0; j < n_action; j++) {
//			cum[j] /= cum[n_action - 1];
//		}
//		double t = r(e);
//		int j = 0;
//		while (cum[j] < t) j++;
//		return randint(e);
//	}
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
//	for (int i = 0; i < n; i++) {
//		cur_state[i] = randint(e);
//	}
//}
//
//vector<int> select_ind(vector<Route>& route, default_random_engine& e) {
//	int n = route.size();
//	vector<double> cum(n, route[0].fitness);
//	for (int i = 1; i < n; i++) {
//		cum[i] = cum[i - 1] + route[i].fitness;
//	}
//	for (int i = 0; i < n; i++) cum[i] /= cum[n - 1];
//
//	vector<int> ret(n, 0);
//
//	for (int i = 0; i < n; i++) {
//		double _r = r(e);
//		int j = 0;
//		while (cum[j] < _r) j++;
//		ret[i] = j;
//	}
//	return ret;
//}
//
//Route dpso(string path, string order_path, default_random_engine& random_engine) {
//
//
//	get_data(path, customer);
//	get_order_data(order_path, customer);
//
//	int n;
//
//	customer.set_electric_cap();
//
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
//	construct_init_route(k_nearest, line, random_engine);
//	for (int i = 0; i < n_route; i++) {
//		route[i].line = line[i];
//		split_route(customer, route[i]);
//	}
//
//	update();
//
//
//
//	// 主程序
//
//	uniform_real<double> r(0.0, 1.0);
//	for (int iter = 0; iter < max_iter; iter++) {
//
//		for (int i = 0; i < n_route; i++) {
//			if (r(random_engine) < prob_a) {
//				PMX(route[i].line, group_best[i].line, random_engine);
//			}
//			if (r(random_engine) < prob_b) {
//				PMX(route[i].line, global_best.line, random_engine);
//			}
//			if (r(random_engine) < prob_m) {
//				mutation(route[i].line, random_engine);
//			}
//
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
//Route rl(string path, string order_path, default_random_engine& random_engine) {
//
//	vector<QTable> all_table(n_route);
//
//	get_data(path, customer);
//	get_order_data(order_path, customer);
//
//	int n;
//
//	customer.set_electric_cap();
//
//	//获取城市数目
//	n = customer.points.size();
//
//
//	//计算每个点的K近邻
//	vector<vector<int>> k_nearest(n, vector<int>(n, 0));
//	cal_k_nearest(customer.dis, k_nearest);
//
//
//	//构造初始解
//	vector<vector<int>> line(n_route, vector<int>(n, 0));
//	construct_init_route(k_nearest, line, random_engine);
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
//	void (*vns[5])(Customer&, Route&) = { swap_main, shift_main, crossover_main, two_opt_main, exchange_main };
//
//	// 主程序
//	vector<int>cur_action(n_route, 0);
//	for (int iter = 0; iter < max_iter; iter++) {
//
//		// 复制当前种群
//		vector<Route> t_route;
//		for (int t = 0; t < n_route; t++) t_route.push_back(route[t]);
//
//		vector<int> idxs = select_ind(t_route, random_engine);
//		//cur_action = select_action(q_table , cur_state, iter, max_iter, random_engine);
//		for (int i = 0; i < n_route; i++) {
//
//			if (r(random_engine) < prob_x) {
//				int ind = idxs[i];
//				PMX(route[i].line, t_route[ind].line, random_engine);
//			}
//
//			if (r(random_engine) < prob_m) {
//				mutation(route[i].line, random_engine);
//			}
//			if (r(random_engine) < prob_a) {
//				PMX(route[i].line, group_best[i].line, random_engine);
//			}
//			if (r(random_engine) < prob_b) {
//				PMX(route[i].line, global_best.line, random_engine);
//			}
//
//			if (is_prins)
//				prins(customer, route[i]);
//			else
//				split_route(customer, route[i]);
//
//			int cs = cur_state[i];
//			double before_fitness = route[i].fitness;
//			double reward;
//			if (r(random_engine) < prob_vns) {
//				for (int u = 0; u < 5; u++) {
//					int ca = select_action(q_table, cs, iter, max_iter, random_engine);
//
//					//if(iter >= 150) ca = randint(random_engine);
//
//					vns[ca](customer, route[i]);
//					//if (route[i].fitness < before_fitness) reward = -1;
//					//else reward = 1;
//
//					reward = (before_fitness - route[i].fitness) * 10;
//					before_fitness = route[i].fitness;
//					double tmp = *max_element(q_table[cur_action[i]].begin(), q_table[cur_action[i]].end());
//					q_table[cs][ca] = (1.0 - alpha) * q_table[cs][ca] + alpha * (reward + gamma * tmp);
//					cs = ca;
//				}
//			}
//
//			update_route(customer, route[i]);
//
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
//Route ga(string path, string order_path, default_random_engine& random_engine) {
//
//
//	get_data(path, customer);
//	get_order_data(order_path, customer);
//
//	int n;
//
//	customer.set_electric_cap();
//
//	//default_random_engine random_engine(seed);
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
//	construct_init_route(k_nearest, line, random_engine);
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
//	uniform_real<double> r(0.0, 1.0);
//	uniform_int<int>randint(0, n_route - 1);
//
//	for (int iter = 0; iter < max_iter; iter++) {
//
//		// 复制当前种群
//		Route t_route[n_route];
//		for (int t = 0; t < n_route; t++) t_route[t] = route[t];
//
//		for (int i = 0; i < n_route; i++) {
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
//int main(int argc, char* argv[]) {
//	//srand(20);
//	Route ret;
//
//	seed = atoi(argv[1]);
//	//int id = atoi(argv[2]);
//	string problem_path = argv[2];
//	string order_path = argv[3];
//	string path_route = argv[4];
//	string path_value = argv[5];
//
//
//	fstream ret_route(path_route, ios::out | ios::app);
//	fstream ret_value(path_value, ios::out | ios::app);
//
//
//	static default_random_engine random_engine(seed);
//	auto start = system_clock::now();
//	ret = rl(problem_path, order_path, random_engine);
//	auto end = system_clock::now();
//	auto time_used = duration_cast<duration<double>>(end - start);
//
//
//
//	//cout << "程序用时: " << time_used.count() << "s" << endl;
//	//cout << ret.fitness << endl;
//
//	//for (auto& x : ret.info) {
//	//	for (auto& y : x) {
//	//		cout << y << " ";
//	//	}
//	//}
//	//cout << endl;
//
//	//保存运行结果
//	ret_value << time_used.count() << endl;
//	ret_value << ret.fitness << endl;
//
//	for (auto& x : ret.info) {
//		for (auto& y : x) {
//			ret_route << y << " ";
//		}
//	}
//	ret_route << endl;
//
//
//	ret_route.close();
//	ret_value.close();
//	return 0;
//}