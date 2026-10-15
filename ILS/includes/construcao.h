#ifndef COSNTRUCAO_H
#define CONSTRUCAO_H

#include "Data.h"
#include "solution.h"

using namespace std;

vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, Data* data);
vector<int> escolher3NosAleatorios(int n);
vector<int> nosRestantes(int n, Solution* s);
bool compararCustos(const insertionInfo& a, const insertionInfo& b);
void ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir);
void inserirNaSolucao(Solution* s, insertionInfo noParaInserir);
Solution Construcao(Data* data);

#endif