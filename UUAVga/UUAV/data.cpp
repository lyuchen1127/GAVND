#include "data.h"
using namespace std;

void get_data(string path, string order_path, Customer& customer) {
	//customer.coff = 0.0268742;
	fstream order_data(order_path, ios::in);
	int n;
	order_data >> n;
	//cout << order_path << endl;
	//cout << n << endl;
	int cur_batch = 0;
	for (int i = 0; i < n; i++) {
		int m, v;
		order_data >> m >> v;
		//cout << m << " " << v;
		//system("pause");
		for (int j = 0; j < v; j++) {
			int a;
			order_data >> a;
			//cout << a << endl;
			customer.order[a] = m;
			//customer.order[a] = m*customer.coff;
			customer.batch[a] = cur_batch;
		}
		cur_batch++;
	}
	customer.order[0] = 0;
	order_data.close();

	fstream raw_data(path, ios::in);
	raw_data >> n >> customer.max_cap;
	n += 1;
	//customer.points.resize(n, vector<int>(2, 0));
	//customer.caps.resize(n, 0);
	//customer.dis.resize(n, vector<double>(n, 0));
	//customer.due_date.resize(n, 0);

	int tmp;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (customer.order.count(i) == 1) {
			customer.real_id.push_back(i);
			raw_data >> tmp;
			customer.points.push_back(vector<int>(2, 0));
			raw_data >> customer.points[cnt][0] >> customer.points[cnt][1];
			customer.caps.push_back(0);
			raw_data >> customer.caps[cnt];
			raw_data >> tmp;
			customer.due_date.push_back(0);
			raw_data >> customer.due_date[cnt];
			raw_data >> tmp;
			cnt += 1;
		}
		else {
			raw_data >> tmp;
			raw_data >> tmp >> tmp;
			raw_data >> tmp;
			raw_data >> tmp;
			raw_data >> tmp;
			raw_data >> tmp;
		}
	}
	raw_data.close();

	
	n = customer.points.size();
	customer.n_customer = n;
	cal_dis_matrix(customer.dis, customer.points);
	for (auto& x : customer.dis) customer.coff = max(customer.coff, *max_element(x.begin(), x.end()));
	//customer.coff = customer.max_dis / customer.coff;
	customer.coff /= customer.max_dis;
	//customer.coff = 0.0268742;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			customer.dis[i][j] *= customer.coff;
		}
		customer.due_date[i] *= customer.coff;
	}
	//cout << customer.coff << endl;
	for (auto& x : customer.order) {
		x.second *= customer.coff;
	}

	customer.set_electric_cap();
}

double cal_point_dis(vector<int>& p1, vector<int>& p2) {
	double r1 = p1[0] - p2[0];
	double r2 = p1[1] - p2[1];
	return sqrt(r1 * r1 + r2 * r2);
}

void cal_dis_matrix(vector<vector<double>>& dis, vector<vector<int>>& points) {
	int m = points.size();
	dis.clear();
	dis.resize(m, vector<double>(m, 0));
	for (int i = 0; i < m; i++) {
		for (int j = i; j < m; j++) {
			dis[i][j] = cal_point_dis(points[i], points[j]);
			dis[j][i] = dis[i][j];
		}
	}
}

void cal_k_nearest(vector<vector<double>>& dis, vector<vector<int>>& ret) {
	int n = ret.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ret[i][j] = j;
		}
	}
	for (int i = 0; i < n; i++) {
		sort(ret[i].begin(), ret[i].end(), [&](auto& x, auto& y) {
			return dis[i][x] < dis[i][y];
		});
	}
}

void construct_init_route(vector<vector<int>>& k_nearest, vector<vector<int>>& ret, default_random_engine& e) {
	int n_route = ret.size();
	int n_point = k_nearest.size();
	vector<int>vis(n_point, 0);
	vis[0] = 1;
	ret[0][0] = 0;
	int last = 0;
	for (int i = 1; i < n_point; i++) {
		for (int j = 0; j < n_point; j++) {
			int a = k_nearest[last][j];
			if (vis[a] == 0) {
				ret[0][i] = a;
				last = a;
				vis[a] = 1;
				break;
			}
		}
	}

	for (int i = 1; i < n_route; i++) {
		for (int j = 0; j < n_point; j++) {
			ret[i][j] = j;
		}
		shuffle(ret[i].begin() + 1, ret[i].end(), e);
	}
}


void cal_fitness(Customer& customer, Route& route) {
	route.fitness = 0.0;
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		route.fitness += cal_tour_fitness(customer, route.info[i]);
	}
}

double cal_tour_fitness(Customer& customer, vector<int>& tour, bool is_log) {
	double fitness = 0.0;
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
			b = tour[i+1];
		}
		start_sercive_time = max(start_sercive_time, customer.order[a]);
		fitness += customer.dis[a][b];
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
		if (is_log) {
			cout << customer.real_id[i] << " : " << cur_time << endl;
			//cout << start_sercive_time << endl;
			
		}
		cur_time += customer.dis[a][b];
		penalty += max(0.0, fitness - customer.due_date[b]);
	}

	return (1.0 - customer.alpha) * fitness + customer.alpha * penalty;
	//return penalty;
}

bool is_valid(Customer& customer, vector<int>& tour) {
	int pd;
	pd = 0;
	// 判断运货量是否超载
	int n = tour.size();
	for (int i = 1; i < n; i++) {
		int a = tour[i];
		pd += customer.caps[a];
		if (pd > customer.max_cap) {
			return false;
		}
	}

	double cur_consume = 0.0;

	// 判断电量是否充裕
	for (int i = 1; i <= n; i++) {
		int a;

		if (i == n)
			a = tour[0];
		else
			a = tour[i];
		int b = tour[i - 1];

		cur_consume += customer.electric_curve(pd) * customer.dis[a][b];

		if (cur_consume > customer.electric_cap) {
			return false;
		}

		pd -= customer.caps[a];
	}


	return true;
}

void split_route(Customer& customer, Route& route) {
	vector<vector<int>>().swap(route.info);
	int cur_cap, cut_time;
	int cur_route = 0;
	route.info.push_back(vector<int>(1, 0));
	int n = route.line.size();


	for (int i = 1; i < n; i++) {
		int a = route.line[i];
		route.info[cur_route].push_back(a);
		if (is_valid(customer, route.info[cur_route])) {
			continue;
		}
		else {
			route.info[cur_route].pop_back();
			route.info.push_back(vector<int>(1, 0));
			cur_route += 1;
			route.info[cur_route].push_back(a);
			if (!is_valid(customer, route.info[cur_route])) {
				cout << "数据有问题！" << endl;
			}
		}
	}



	cal_fitness(customer, route);
}

void prins(Customer& customer, Route& route) {
	int cur;
	// 包含depot点
	int n = route.line.size();
	int cur_tour = 0;
	vector<int>pre(n, 0);
	vector<double> fit(n, 0);

	for (int i = 1; i < n; i++) {

		vector<int>tmp(1, 0);
		int a = route.line[i];
		tmp.push_back(route.line[i]);
		fit[i] = cal_tour_fitness(customer, tmp);
		//cout << cal_tour_fitness(customer, tmp) << " " << 2*customer.dis[0][a] << endl;
		fit[i] += fit[i - 1];
		pre[i] = i - 1;
	}

	//cout << fit[2] << endl;
	//vector<int>tr(1, 0);
	//tr.push_back(6); tr.push_back(13);
	//cout << cal_tour_fitness(customer, tr) << endl;

	//for (auto& x : fit) cout << x << " ";
	//cout << endl;

	pre[0] = -1;

	for (int i = 0; i < n; i++) {
		int a = route.line[i];
		vector<int>tmp(1, 0);

		for (int j = i + 1; j < n; j++) {
			int b = route.line[j];
			tmp.push_back(b);
			// if (i == 0) cout << max_load << endl;
			if (is_valid(customer, tmp)) {
				//cout << tmp.size() << endl;
				//if(i == 0 && j == 2)
				//	cout << fit[i] << " " << cal_tour_fitness(customer, tmp) << " " << fit[j] << endl;
				if (fit[i] + cal_tour_fitness(customer, tmp) < fit[j]) {
					//cout << i << " " << j << endl;
					fit[j] = fit[i] + cal_tour_fitness(customer, tmp);
					pre[j] = i;
				}
			}
			else {
				break;
			}
		}
	}

	//for (auto& x : pre) cout << x << " ";
	//cout << endl;

	vector<vector<int>>().swap(route.info);
	cur = 0;

	//for (auto& x : pre)cout << x << " ";
	//cout << endl;

	int idx = n - 1;
	while (1) {
		int a = pre[idx];
		if (a == -1) break;
		route.info.push_back(vector<int>(1, 0));
		for (int i = a + 1; i <= idx; i++) {
			route.info[cur].push_back(route.line[i]);
		}
		cur += 1;
		idx = pre[idx];
	}
	reverse(route.info.begin(), route.info.end());

	//int idx = n - 1;

	//vector<int> tmp;
	//while (1) {
	//	if (pre[idx] == -1) break;
	//	tmp.push_back(pre[idx]);
	//	idx = pre[idx];
	//}

	//reverse(tmp.begin(), tmp.end());
	//tmp[0] = 1;
	//tmp.push_back(n);
	//int nV = tmp.size();
	////for (auto x : tmp) cout << x << endl;

	//for (int i = 0; i < nV - 1; i++) {
	//	route.info.push_back(vector<int>(1, 0));
	//	for (int j = tmp[i]; j < tmp[i + 1]; j++) {
	//		route.info[cur].push_back(route.line[j]);
	//	}
	//	cur++;
	//}

	cal_fitness(customer, route);
}

vector<double> cal_tour_detail(Customer& customer, vector<int>& tour) {
	double f = 0.0;
	double penalty = 0.0;
	vector<double> ret(2, 0);
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

	ret[0] = f;
	ret[1] = penalty;
	return ret;
}