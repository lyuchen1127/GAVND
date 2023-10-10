#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <cmath>
#include <utility>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

void mutation(vector<int>& line, default_random_engine& e);
void PMX(vector<int>& line1, vector<int>& line2, default_random_engine& e);

void crossover_main(Customer&, Route& route);
void crossover_step(Customer&, vector<int>& tour1,
	vector<int>& tour2);

void shift_main(Customer&, Route& route);
void shift_step(Customer&, vector<int>& tour1,vector<int>& tour2);

void two_opt_main(Customer&, Route& route);
void two_opt_step(Customer&, vector<int>& tour1);

void exchange_main(Customer&, Route& route);
void exchange_step(Customer&, vector<int>& tour1);


void reform(vector<int>& route);

void swap_main(Customer&, Route& route);
void swap_step(Customer&, vector<int>& tour1, vector<int>& tour2);