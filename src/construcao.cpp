#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include "Data.h"
#include "construcao.h"

using namespace std;

vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, Data* data)
{
    vector<insertionInfo> custoInsercao = vector<insertionInfo>((s.sequence.size() - 1) * CL.size());
    int l = 0;
    for(size_t a = 0; a < s.sequence.size() - 1; a++){
        int i = s.sequence[a];
        int j = s.sequence[a + 1];
        for(auto k : CL){
            custoInsercao[l].custoInsertion = data->getDistance(i, k) + data->getDistance(k, j) - data->getDistance(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a; 
            l++;
        }
    }
    return custoInsercao;
}

vector<int> escolher3NosAleatorios(int n){
    vector<int> numeros = {1, 1};
    for(int i = 0; i < 3; i++){
        int noAleatorio = 2 + (rand() % (n - 1));
        numeros.insert(numeros.begin() + (i + 1), noAleatorio); 
    }
    return numeros;
}

vector<int> nosRestantes(int n, Solution* s){
    vector<int> restantes;

    vector<bool> presentesNaSolucao(n + 1, false);

    for(int no : s->sequence){
        presentesNaSolucao[no] = true;
    }

    for(int i = 1; i <= n; i++){
        if(!presentesNaSolucao[i]){
            restantes.push_back(i);
        }
    }
    return restantes;
}

bool compararCustos(const insertionInfo& a, const insertionInfo& b){
    return a.custoInsertion < b.custoInsertion;
}

void ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir){
    sort(custoInserir.begin(), custoInserir.end(), compararCustos);
} 

void inserirNaSolucao(Solution* s, insertionInfo noParaInserir){ 
    s->sequence.insert(s->sequence.begin() + (noParaInserir.arestaRemovida + 1), noParaInserir.noInserido);
    s->valorObj = s->valorObj + noParaInserir.custoInsertion;
}  

Solution Construcao(Data* data){
    Solution s;
    s.valorObj = 0;
    s.sequence = escolher3NosAleatorios(data->getDimension());
    vector<int> CL = nosRestantes(data->getDimension() , &s);
    cout << "O tamanho de Cl: " << CL.size() << endl;
    while (!CL.empty())
    {
        vector<insertionInfo> custoInsercao =  calcularCustoInsercao(s, CL, data);
        ordenarEmOrdemCrescente(custoInsercao);
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        inserirNaSolucao(&s, custoInsercao[selecionado]);

        auto valor = find(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido);
        CL.erase(valor);
    }
    return s;
}


void imprimirSolucao(Solution* s){
    if(s == nullptr || s->sequence.empty()){
        cout << "solução vazia" << endl;
    }
    cout << "Custo: " << s->valorObj << endl;
    cout << "Rota: " << endl;
    for(size_t i = 0; i < s->sequence.size() - 1; i++){
        cout << s->sequence[i] << " ";
    }
    cout << s->sequence[0] << endl;
}

double calcularValorObj(Solution* s, Data* data){
    s->valorObj = 0;
    for(int i = 0; s->sequence.size() - 1; i++){
        s->valorObj += data->getDistance(s->sequence[i], s->sequence[i+1]);
    }
    return s->valorObj;
}
