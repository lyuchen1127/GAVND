#include "pso.h"


void mutation(vector<int>& line, default_random_engine& e) {
	int n = line.size();
	static uniform_int<int> r(1, n - 1);
	int m = r(e);
	while (m--) {
		int a = r(e);
		int b = r(e);
		while (a == b) b = r(e);
		swap(line[a], line[b]);
	}
}
void PMX(vector<int>& line1, vector<int>& line2, default_random_engine& e) {
	int n = line1.size();
	static uniform_int<int> r(1, n - 1);
	int a = r(e);
	int b = r(e);
	while (a == b) b = r(e);
	if (a > b) swap(a, b);
	vector<int> p1(n, 0);
	vector<int> vis(n, 0);
	for (int i = a; i <= b; i++) {
		p1[i] = line1[i];
		vis[line1[i]] = 1;
	}
	int j = 0;
	for (int i = 0; i < a; i++) {
		if (vis[line2[j]] == 0) {
			p1[i] = line2[j];
		}
		else {
			i--;
		}
		j++;
	}
	for (int i = b+1; i < n; i++) {
		if (vis[line2[j]] == 0) {
			p1[i] = line2[j];
		}
		else {
			i--;
		}
		j++;
	}
	line1.assign(p1.begin(), p1.end());
}

void crossover_step(Customer& customer, vector<int>& tour1, vector<int>& tour2) {
	int bp0, bp1;
	double delta = 0;
	double f1 = cal_tour_fitness(customer, tour1) + cal_tour_fitness(customer, tour2);
	int n = tour1.size();
	int m = tour2.size();
	vector<int> opt1;
	vector<int> opt2;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			vector<int> t1;
			vector<int> t2;
			t1.push_back(0); t2.push_back(0);
			for (int a = 1; a <= i; a++) t1.push_back(tour1[a]);
			for (int b = j + 1; b < m; b++) t1.push_back(tour2[b]);

			for (int a = 1; a <= j; a++) t2.push_back(tour2[a]);
			for (int b = i + 1; b < n; b++) t2.push_back(tour1[b]);
			if (is_valid(customer, t1) && is_valid(customer, t2)) {
				double f2 = cal_tour_fitness(customer, t1) + cal_tour_fitness(customer, t2);
				if ((f1 - f2) > delta) {
					bp0 = i;
					bp1 = j;
					delta = f1 - f2;
					opt1.assign(t1.begin(), t1.end());
					opt2.assign(t2.begin(), t2.end());
				}
			}
		}
	}
	vector<int> t1;
	vector<int> t2;
	if (delta != 0) {
		t1.push_back(0); t2.push_back(0);
		for (int a = 1; a <= bp0; a++) t1.push_back(tour1[a]);
		for (int b = bp1 + 1; b < m; b++) t1.push_back(tour2[b]);

		for (int a = 1; a <= bp1; a++) t2.push_back(tour2[a]);
		for (int b = bp0 + 1; b < n; b++) t2.push_back(tour1[b]);
		tour1.assign(t1.begin(), t1.end());
		tour2.assign(t2.begin(), t2.end());

	}
}

void crossover_main(Customer& customer, Route& route) {
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			crossover_step(customer, route.info[i], route.info[j]);

		}
	}

	cal_fitness(customer, route);
}


void shift_step(Customer& customer, vector<int>& tour1, vector<int>& tour2) {
	int bp0, bp1;
	double delta = 0;
	double f1 = cal_tour_fitness(customer, tour1) + cal_tour_fitness(customer, tour2);
	int n = tour1.size();
	int m = tour2.size();
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			vector<int> t1;
			vector<int> t2;
			t1.assign(tour1.begin(), tour1.end());
			t2.assign(tour2.begin(), tour2.end());
			t2.insert(t2.begin() + j, t1[i]);
			t1.erase(t1.begin() + i);
			if (is_valid(customer, t1) && is_valid(customer, t2)) {
				double f2 = cal_tour_fitness(customer, t1) + cal_tour_fitness(customer, t2);
				if ((f1 - f2) > delta) {
					bp0 = i;
					bp1 = j;
					delta = f1 - f2;
				}
			}
		}
	}
	if (delta != 0) {
		vector<int> t1;
		vector<int> t2;
		t1.assign(tour1.begin(), tour1.end());
		t2.assign(tour2.begin(), tour2.end());
		t2.insert(t2.begin() + bp1, t1[bp0]);
		t1.erase(t1.begin() + bp0);
		tour1.assign(t1.begin(), t1.end());
		tour2.assign(t2.begin(), t2.end());
	}
}

void shift_main(Customer& customer, Route& route) {
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			shift_step(customer, route.info[i], route.info[j]);
		}
	}
	cal_fitness(customer, route);
}

void exchange_step(Customer& customer, vector<int>& tour1) {
	int bp0, bp1;
	double delta = 0;
	vector<int> t1;
	double f1 = cal_tour_fitness(customer, tour1);
	int n = tour1.size();
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			t1.assign(tour1.begin(), tour1.end());
			swap(t1[i], t1[j]);
			double f = cal_tour_fitness(customer, t1);
			if (is_valid(customer, t1)) {
				if ((f1 - f) > delta) {
					delta = f1 - f;
					bp0 = i;
					bp1 = j;
				}
			}
		}
	}

	if (delta != 0) {
		swap(tour1[bp0], tour1[bp1]);
	}
}


void exchange_main(Customer& customer, Route& route) {
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		exchange_step(customer, route.info[i]);
	}
	cal_fitness(customer, route);
}


void reform(vector<int>& route) {
	int n = route.size();
	vector<int> tmp(n);
	tmp.assign(route.begin(), route.end());
	int i = 0;
	for (; i < n; i++) if (route[i] == 0) break;
	for (int j = 0; j < n; j++) {
		tmp[j] = route[(i + j) % n];
	}
	route.assign(tmp.begin(), tmp.end());
}

void two_opt_step(Customer& customer, vector<int>& tour1) {
	int bp0, bp1;
	double delta = 0;
	vector<int> t1;
	double f1 = cal_tour_fitness(customer, tour1);
	int n = tour1.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			t1.assign(tour1.begin(), tour1.end());
			reverse(t1.begin() + i, t1.begin() + j + 1);
			if (i == 0) reform(t1);
			if (is_valid(customer,t1)) {
				double f = cal_tour_fitness(customer, t1);
				if ((f1 - f) > delta) {
					delta = f1 - f;
					bp0 = i;
					bp1 = j;
				}
			}
		}
	}
	
	if (delta != 0) {
		reverse(tour1.begin() + bp0, tour1.begin() + bp1 + 1);
		if (bp0 == 0) reform(tour1);
	}
}

void two_opt_main(Customer& customer, Route& route) {
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		two_opt_step(customer, route.info[i]);
	}
	cal_fitness(customer, route);
}

void swap_step(Customer& customer, vector<int>& tour1,vector<int>& tour2) {
	int bp0, bp1;
	double delta = 0.0;
	double f0 = cal_tour_fitness(customer, tour1) + cal_tour_fitness(customer, tour2);
	int n = tour1.size();
	int m = tour2.size();
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			vector<int> t1;
			vector<int> t2;
			t1.assign(tour1.begin(), tour1.end());
			t2.assign(tour2.begin(), tour2.end());
			swap(t1[i], t2[j]);
			if (is_valid(customer, t1) && is_valid(customer, t2)) {
				double f1 = cal_tour_fitness(customer, t1) + cal_tour_fitness(customer, t2);
				if ((f0 - f1) > delta) {
					bp0 = i;
					bp1 = j;
					delta = (f0 - f1);
				}
			}
		}
	}
	if (delta != 0) {
		vector<int> t1;
		vector<int> t2;
		t1.assign(tour1.begin(), tour1.end());
		t2.assign(tour2.begin(), tour2.end());
		swap(t1[bp0], t2[bp1]);
		tour1.assign(t1.begin(), t1.end());
		tour2.assign(t2.begin(), t2.end());
	}
}

void swap_main(Customer& customer, Route& route) {
	int n = route.info.size();
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			swap_step(customer, route.info[i], route.info[j]);
		}
	}
	cal_fitness(customer, route);
}