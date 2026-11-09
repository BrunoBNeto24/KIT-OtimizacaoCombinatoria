#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include "Data.h"

using namespace std;

struct Solution
{
    vector<int> sequence;
    double valorObj;
};


struct insertionInfo
{
    int noInserido;
    int arestaRemovida;
    double custoInsertion;
};

void imprimirSolucao(Solution* s);
double calcularValorObj(Solution* s, Data* data);

#endif