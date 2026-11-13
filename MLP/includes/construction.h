#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include "Data.h"
#include "solution.h"
#include <numeric>

using namespace std;

vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, int r, Data* data);
vector<int> nosRestantes(int n);
bool compararCustos(const insertionInfo& a, const insertionInfo& b);
void ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir);
void inserirNaSolucao(Solution* s, insertionInfo noParaInserir);
Solution Construcao(Data* data);

#endif