#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <utility>
#include <time.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include "data.h"
#include "pso.h"
using namespace std;
using namespace chrono;
const int n_route = 40/2;
const int max_iter = 50/2;
const double prob_m = 0.2;
const double prob_x = 0.6;
const double prob_a = 0.6;
const double prob_b = 0.6;
const double prob_vns = 1.0;  //default:0.5
const bool is_prins = false;
vector<vector<double>> q_table;
vector<int> cur_state;
const int n_action = 5;
const int n_state = 5;
const double E = 2.71828182845904523536;
const double alpha = 0.5;
const double gamma = 0.9;
volatile int seed = 50;
Route group_best[n_route];
Route global_best;
Route route[n_route];
Customer customer;
string heatmap_path;

string problem_paths[] = { "G:\\蚁群算法\\程序\\ADV\\solomon_25\\C101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_25\\R101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_25\\RC101.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_25\\C201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_25\\R201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_25\\RC201.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_50\\C101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_50\\R101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_50\\RC101.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_50\\C201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_50\\R201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_50\\RC201.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\C101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\R101.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC101.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\C201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\R201.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC201.txt" ,

"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC101.txt" ,"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC102.txt" ,"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC103.txt" ,
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC104.txt" ,"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC105.txt" ,"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC106.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC107.txt","G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC108.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC201.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC202.txt","G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC203.txt", "G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC204.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC205.txt","G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC206.txt","E:\\ADV\\solomon_100\\RC207.txt",
"G:\\蚁群算法\\程序\\ADV\\solomon_100\\RC208.txt" };

string order_paths[] = { "G:\\蚁群算法\\程序\\ADV\\order\\25.txt", "G:\\蚁群算法\\程序\\ADV\\order\\25.txt", "G:\\蚁群算法\\程序\\ADV\\order\\25.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\25.txt","G:\\蚁群算法\\程序\\ADV\\order\\25.txt","G:\\蚁群算法\\程序\\ADV\\order\\25.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\50.txt", "G:\\蚁群算法\\程序\\ADV\\order\\50.txt", "G:\\蚁群算法\\程序\\ADV\\order\\50.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\50.txt","G:\\蚁群算法\\程序\\ADV\\order\\50.txt","G:\\蚁群算法\\程序\\ADV\\order\\50.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt", "G:\\蚁群算法\\程序\\ADV\\order\\100.txt", "G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",

"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt","G:\\蚁群算法\\程序\\ADV\\order\\100.txt",
"G:\\蚁群算法\\程序\\ADV\\order\\100.txt" };

string path_routes[] = { "G:\\蚁群算法\\程序\\ADV\\result\\route\\c101_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r101_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc101_25.txt",
 "G:\\蚁群算法\\程序\\ADV\\result\\route\\c201_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r201_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc201_25.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\c101_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r101_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc101_50.txt",
 "G:\\蚁群算法\\程序\\ADV\\result\\route\\c201_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r201_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc201_50.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\c101_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r101_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc101_100.txt",
 "G:\\蚁群算法\\程序\\ADV\\result\\route\\c201_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\r201_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\route\\rc201_100.txt",

"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc101_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc102_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc103_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc104_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc105_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc106_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc107_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc108_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc201_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc202_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc203_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc204_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc205_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc206_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc207_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\route\\rc208_100.txt",
};

string path_values[] = { "G:\\蚁群算法\\程序\\ADV\\result\\value\\c101_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r101_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc101_25.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\c201_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r201_25.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc201_25.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\c101_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r101_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc101_50.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\c201_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r201_50.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc201_50.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\c101_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r101_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc101_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\c201_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\r201_100.txt" , "G:\\蚁群算法\\程序\\ADV\\result\\value\\rc201_100.txt",

"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc101_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc102_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc103_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc104_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc105_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc106_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc107_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc108_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc201_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc202_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc203_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc204_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc205_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\value\\rc206_100.txt","G:\\蚁群算法\\程序\\ADV\\result\\route\\rc207_100.txt",
"G:\\蚁群算法\\程序\\ADV\\result\\value\\rc208_100.txt",
};

void update() {
	for (int i = 0; i < n_route; i++) {
		if (route[i].fitness < group_best[i].fitness)
			group_best[i] = route[i];
		if (group_best[i].fitness < global_best.fitness)
			global_best = group_best[i];
	}
}

void update_route(Customer& customer, Route& route) {
	route.line.clear();
	route.line.push_back(0);
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		int m = route.info[i].size();
		for (int j = 1; j < m; j++) {
			route.line.push_back(route.info[i][j]);
		}
	}
	if (is_prins)
		prins(customer, route);
	else
		split_route(customer, route);
}

vector<int> select_action(vector<vector<double>>& q_table, vector<int>& state, int cur_iter, int max_iter,
	default_random_engine& e) {
	int n = state.size();
	double eps_end = 0.05;
	double eps_start = 0.9;
	double threshold = eps_end + (eps_start - eps_end) * pow(E, -1.0 * cur_iter / max_iter);
	vector<int> ret(n, 0);
	uniform_real<double> r(0.0, 1.0);
	if (r(e) > threshold) {
		for (int i = 0; i < n; i++) {
			int cur = state[i];
			double tmp = -100000000.0;
			for (int j = 0; j < n_action; j++) {
				if (tmp < q_table[cur][j]) {
					tmp = q_table[cur][j];
					ret[i] = j;
				}
			}
		}

	}
	else {
		uniform_int<int>r(0, n_action - 1);
		for (int i = 0; i < n; i++) {
			ret[i] = r(e);
		}
	}
	return ret;
}

int select_action(vector<vector<double>>& q_table, int cur, int cur_iter, int max_iter, default_random_engine& e) {
	double eps_end = 0.05;
	double eps_start = 0.9;
	double threshold = eps_end + (eps_start - eps_end) * pow(E, -1.0 * cur_iter / max_iter);
	uniform_real<double> r(0.0, 1.0);
	if (r(e) > threshold) {
		return max_element(q_table[cur].begin(), q_table[cur].end()) - q_table[cur].begin();
	}
	else {
		//cout << n << endl;
		vector<double> cum(n_action, q_table[cur][0] + 1.0);

		for (int j = 1; j < n_action; j++) {
			cum[j] += (q_table[cur][j] + cum[j - 1]);
		}
		for (int j = 0; j < n_action; j++) {
			cum[j] /= cum[n_action - 1];
		}
		double t = r(e);
		int j = 0;
		while (cum[j] < t) j++;
		return j;
	}
}


void init_q_table(vector<vector<double>>& q_table) {
	q_table.resize(n_state, vector<double>(n_action, 0));
	for (int i = 0; i < n_state; i++) {
		//q_table[i][5] = 0.5;
		//q_table[i][6] = 0.5;
	}
}


void init_cur_state(vector<int>& cur_state, int n, default_random_engine& e) {
	cur_state.resize(n, 0);

	uniform_int<int>r(0, n_state - 1);


	for (int i = 0; i < n; i++) {
		cur_state[i] = r(e);
	}
}

vector<int> select_ind(vector<Route>& route, default_random_engine& e) {
	uniform_real<double>rd(0, 1);
	int n = route.size();
	vector<double> cum(n, route[0].fitness);
	for (int i = 1; i < n; i++) {
		cum[i] = cum[i - 1] + route[i].fitness;
	}
	for (int i = 0; i < n; i++) cum[i] /= cum[n - 1];

	vector<int> ret(n, 0);

	for (int i = 0; i < n; i++) {
		double r = rd(e);
		int j = 0;
		while (cum[j] < r) j++;
		ret[i] = j;
	}
	return ret;
}

void save_qTable(vector<vector<double>>& table) {
	fstream file(heatmap_path, ios::out);
	for (auto& col : table) {
		for (auto& x : col) {
			file << x << " ";
		}
		file << endl;
	}
	file.close();
}



Route ga(string path, string order_path, default_random_engine& random_engine) {


	get_data(path, order_path, customer);

	int n;


	//default_random_engine random_engine(seed);
	//获取城市数目
	n = customer.points.size();


	//计算每个点的K近邻
	vector<vector<int>> k_nearest(n, vector<int>(n, 0));
	cal_k_nearest(customer.dis, k_nearest);

	//构造初始解
	vector<vector<int>> line(n_route, vector<int>(n, 0));
	construct_init_route(k_nearest, line, random_engine);
	for (int i = 0; i < n_route; i++) {
		route[i].line = line[i];
		if (is_prins)
			prins(customer, route[i]);
		else
			split_route(customer, route[i]);
	}

	update();



	// 主程序
	uniform_real<double> r(0.0, 1.0);
	uniform_int<int>randint(0, n_route - 1);

	for (int iter = 0; iter < max_iter; iter++) {

		// 复制当前种群
		Route t_route[n_route];
		for (int t = 0; t < n_route; t++) t_route[t] = route[t];

		for (int i = 0; i < n_route; i++) {

			int ind = randint(random_engine);

			if (r(random_engine) < prob_x) {
				PMX(route[i].line, t_route[ind].line, random_engine);
			}

			if (r(random_engine) < prob_m) {
				mutation(route[i].line, random_engine);
			}
			if (is_prins)
				prins(customer, route[i]);
			else
				split_route(customer, route[i]);

			if (r(random_engine) < prob_vns) {
				crossover_main(customer, route[i]);
				swap_main(customer, route[i]);
				shift_main(customer, route[i]);
				two_opt_main(customer, route[i]);
				exchange_main(customer, route[i]);
				update_route(customer, route[i]);
			}

		}

		update();
	}


	return global_best;
}



int main(int argc, char* argv[]) {
	//srand(20);

	//seed = atoi(argv[1]);
	//int id = atoi(argv[2]);
	seed = 0;
	int id = 0;
	string problem_path = problem_paths[id];
	string order_path = order_paths[id];

	// 不知道下批到达时间
	//string problem_path = "G:\\蚁群算法\\程序\\ADV\\solomon_25\\C104.txt";
	//string order_path = "G:\\蚁群算法\\程序\\ADV\\order\\25.txt";
	heatmap_path = "G:\\蚁群算法\\程序\\ADV\\heatmap\\C104.txt";

	string path_route = path_routes[id];
	string path_value = path_values[id];
	fstream ret_route(path_route, ios::out | ios::app);
	fstream ret_value(path_value, ios::out | ios::app);


	static default_random_engine random_engine(seed);
	auto start = system_clock::now();
	Route ret;
	ret= ga(problem_path, order_path, random_engine);
	//ret = rl(problem_path, order_path, random_engine);
	auto end = system_clock::now();
	auto time_used = duration_cast<duration<double>>(end - start);


	cout << "程序用时: " << time_used.count() << "s" << endl;
	cout << "目标函数值: " << ret.fitness << endl;
	//ret.cal_detail(customer);
	//cout << "距离花费: " << ret.detail[0] << endl;
	//cout << "惩罚: " << ret.detail[1] << endl;


	//for (auto& x : ret.info) {
	//	cout << "................" << endl;
	//	cal_tour_fitness(customer, x, true);
	//}

	//cout << "路径信息: " << endl;
	//for (auto& x : ret.info) {
	//	cout << "Fitness: " << cal_tour_fitness(customer, x) << endl;
	//	vector<double> tmp;
	//	tmp = cal_tour_detail(customer, x);
	//	cout << "距离花费: " << tmp[0] << endl;
	//	cout << "惩罚: " << tmp[1] << endl;

	//	cout << "[";
	//	for (auto& y : x) {
	//		int ry = customer.real_id[y];
	//		//cout << customer.real_id[y] << ",";
	//		cout << ry << "(" << customer.batch[ry] << ")" << ",";
	//		//cout << y << ",";
	//	}
	//	cout << "]" << endl;

	//}
	//cout << endl;


	//vector<vector<int>> info = { {0,15,23,12,8,5,3,6,9,},  {0,22,24,20,14,7,1,13,19,} ,
	//			{0,18,21,25,17,11,4,2,10,16,}
	//};

	//vector<vector<int>> info = { {0, 7, 8, 6, 4, 2, 1, 3, 5, } };
	//vector<vector<int>> info = { {0,22,24,20,14,7,1,13,19,} };


	//Route ret;
	//ret.info = info;
	//get_data(problem_path, order_path, customer);

	//int n = info[0].size();
	//for (int i = 1; i <= n; i++) {
	//	if (i == n) {
	//		cout << customer.dis[info[0][i - 1]][0] << endl;
	//	}
	//	else {
	//		cout << customer.dis[info[0][i - 1]][info[0][i]] << ", ";
	//	}
	//}


	/*....................................................................*/

	//update_route(customer, ret);

	//cout << "Max Cap: " << customer.electric_cap << endl;
	//for (auto& x : ret.info) {
	//	cout << is_valid(customer, x) << endl;
	//}

	//for (auto& x : ret.info) {
	//	cout << "{";
	//	for (auto& y : x) {
	//		//cout << customer.real_id[y] << ",";
	//		cout << y << ",";
	//	}
	//	cout << "}" << endl;
	//}
	//cout << endl;

	//cal_fitness(customer, ret);
	//ret.cal_detail(customer);

	//cout << ret.fitness << endl;
	//cout << "Distance: " << ret.detail[0] << endl;
	//cout << "Penalty: " << ret.detail[1] << endl;




	/*。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。*/

	//auto end = system_clock::now();
	//auto time_used = duration_cast<duration<double>>(end - start);



	//cout << "程序用时: " << time_used.count() << "s" << endl;


	//保存运行结果
	//ret_value << time_used.count() << endl;
	//ret_value << ret.fitness << endl;

	//for (auto& x : ret.info) {
	//	for (auto& y : x) {
	//		ret_route << y << " ";
	//	}
	//}
	//ret_route << endl;


	//ret_route.close();
	//ret_value.close();
	return 0;
}