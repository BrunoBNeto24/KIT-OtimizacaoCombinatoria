#ifndef COSNTRUCAO_H
#define CONSTRUCAO_H

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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
vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, Data* data);
vector<int> escolher3NosAleatorios(int n);
vector<int> nosRestantes(int n, Solution* s);
bool compararCustos(const insertionInfo& a, const insertionInfo& b);
void ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir);
void inserirNaSolucao(Solution* s, insertionInfo noParaInserir);
Solution Construcao(Data* data);
double calcularValorObj(Solution* s, Data* data);

#endif