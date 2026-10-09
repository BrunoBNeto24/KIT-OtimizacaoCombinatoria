#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Data.h"

#define max_Iter 30

using namespace std;

typedef struct Solution
{
    vector<int> sequence;
    double valorObj;
};

typedef struct insertionInfo
{
    int noInserido;
    int arestaRemovida;
    double custoInsertion;
};

void imprimirSolução(Solution* s){
    cout << "Custo: " << s->valorObj << endl;
    cout << "Rota: " << endl;
    for(int i = 0; i < s->sequence.size() - 1; i++){
        cout << s->sequence[i] << " ";
    }
}

double calcularValorObj(Solution* s, Data* data){
    s->valorObj = 0;
    for(int i = 0; s->sequence.size() - 1; i++){
        s->valorObj += data->getDistance(s->sequence[i], s->sequence[i+1]);
    }
    return s->valorObj;
}

vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, Data* data)
{
    vector<insertionInfo> custoInsercao = vector<insertionInfo>((s.sequence.size() - 1) * CL.size());
    int l = 0;
    for(int a = 0; a < s.sequence.size() - 1; a++){
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
        int noAleatorio = 2 + (rand() % n);
        numeros.insert(numeros.begin() + (i + 1), noAleatorio); 
    }
    return numeros;
}

vector<int> nosRestantes(int n, Solution* s){
    vector<int> restantes;
    for(int i = 1; i < n - 1; i++){
        if(i != s->sequence[i - 1]){
            restantes.push_back(i);
        }
    }
    return restantes;
}

bool compararCustos(insertionInfo* a, insertionInfo* b){
    return a->custoInsertion < b->custoInsertion;
}

vector<int> ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir){
    sort(custoInserir.begin(), custoInserir.end(), compararCustos);
} 

void inserirNaSolucao(Solution* s, insertionInfo noParaInserir){ 
    s->sequence.insert(s->sequence.begin() + (noParaInserir.arestaRemovida + 1), noParaInserir.noInserido);
    s->valorObj = s->valorObj + noParaInserir.custoInsertion;
}  

Solution Construcao(Data* data){
    Solution s;
    s.sequence = escolher3NosAleatorios(s.sequence.size());
    vector<int> CL = nosRestantes(s.sequence.size(), &s);

    while (!CL.empty())
    {
        vector<insertionInfo> custoInsercao =  calcularCustoInsercao(s, CL, data);
        ordenarEmOrdemCrescente(custoInsercao);
        double alpha = (double) rand() / RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha * custoInsercao.size()));
        inserirNaSolucao(&s, custoInsercao[selecionado]);
        CL.erase(CL.begin() + selecionado);
    }
    return s;
}

bool bestImprovementSwap(Solution* s, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 1; i < s->sequence.size() - 1; i++)
    {
        int vi = s->sequence[i];
        int prox_vi = s->sequence[i + 1];
        int ant_vi = s->sequence[i - 1];
        for (int j = 1; j < s->sequence.size() - 1; j++)
        {
            int vj = s->sequence[j];
            int prox_vj = s->sequence[j + 1];
            int ant_vj = s->sequence[j - 1];
            double delta = -data->getDistance(ant_vi, vi) - data->getDistance(vi, prox_vi) + data->getDistance(ant_vi, vj) + data->getDistance(vj, prox_vi) - data->getDistance(ant_vj, vj) - data->getDistance(vj, prox_vj) +  data->getDistance(ant_vj, vi) + data->getDistance(vi, prox_vj);

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
            
        }
        
    }
    if(bestDelta < 0){
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->valorObj = s->valorObj + bestDelta;
        return true;
    }
    return false;
    
}


bool bestImprovement2Opt(Solution* s, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    for (int i = 1; i < s->sequence.size() - 1; i++)
    {
       int vi = s->sequence[i];
       int ant_vi = s->sequence[i - 1];
       for (int j = 1; j < s->sequence.size() - 1; j++)
       {
        int vj = s->sequence[j];
        int prox_vj = s->sequence[j + 1];

        double delta = data->getDistance(ant_vi, j) + data->getDistance(i, prox_vj) - data->getDistance(ant_vi, i) - data->getDistance(j, prox_vj);

        if(delta < bestDelta){
            bestDelta = delta;
            best_i = i;
            best_j = j;
        }
       }
    }
    if(bestDelta < 0){
        reverse(s->sequence.begin() + best_i, s->sequence.begin() + best_j + 1);
        s->valorObj = s->valorObj + bestDelta;
        return true;
    }
    return false;
}

bool bestImprovementOrOpt(Solution* s, int n, Data* data){
    switch (n)
    {
    case 1:
        double bestDelta = 0;
        int best_i, best_j;
        for (int i = 1; i < s->sequence.size() - 1; i++)
        {
            int vi = s->sequence[i];
            int prox_vi = s->sequence[i + 1];
            int ant_vi = s->sequence[i - 1];
            for (int j = 1; j < s->sequence.size() - 1; j++)
            {
                int vj = s->sequence[j];
                int prox_vj = s->sequence[j + 1];
                
                double delta = - data->getDistance(ant_vi, i) - data->getDistance(i, prox_vi) + data->getDistance(j, i) + data->getDistance(i, prox_vj) + data->getDistance(ant_vi, prox_vi);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
        s->valorObj = s->valorObj + bestDelta;
        return true;
        }
        return false;
        break;
    case 2:
        double bestDelta = 0;
        int best_i, best_j;
        for (int i = 1; i < s->sequence.size() - 1; i++)
        {
            int vi = s->sequence[i];
            int prox_i = s->sequence[i + 1];
            int prox2_i = s->sequence[i + 2];
            int ant_i = s->sequence[i - 1];
            for (int j = 1; j < s->sequence.size() - 1; j++)
            {
                int vj = s->sequence[j];
                int prox_j = s->sequence[j + 1];
                
                double delta = data->getDistance(j, i) + data->getDistance(prox_i, prox_j) + data->getDistance(ant_i, prox2_i) - data->getDistance(ant_i, i) - data->getDistance(prox_i, prox2_i) - data->getDistance(j, prox_j);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            s->valorObj = s->valorObj + bestDelta;
            return true;
        }
        return false;
        break;
    case 3:
        double bestDelta = 0;
        int best_i, best_j;
        for (int i = 1; i < s->sequence.size() - 1; i++)
        {
            int vi = s->sequence[i];
            //int prox_i = s->sequence[i + 1]; desncessário para o casos do Or-opt-3
            int prox2_i = s->sequence[i + 2];
            int prox3_i = s->sequence[i + 3];
            int ant_i = s->sequence[i - 1];
            for (int j = 1; j < s->sequence.size() - 1; j++)
            {
                int vj = s->sequence[j];
                int prox_j = s->sequence[j + 1];
                
                double delta = data->getDistance(j, i) + data->getDistance(prox2_i, prox_j) + data->getDistance(ant_i, prox3_i) - data->getDistance(ant_i, i) - data->getDistance(prox2_i, prox3_i) - data->getDistance(j, prox_j);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            s->valorObj = s->valorObj + bestDelta;
            return true;
        }
        break;
    default:
        return false;
        break;
    }
}

void BuscaLocal(Solution* s, Data* data){
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch (NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, data);
            break;
        case 2:
            improved = bestImprovement2Opt(s, data);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, 1, data);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, 2, data);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, 3, data);
            break;
        }
        if(improved){
            NL = {1, 2, 3, 4, 5};
        } else {
            NL.erase(NL.begin() + n);
        }    
    }
}

Solution Pertubucao(Solution s, Data* data){
    Solution s_linha = s;

    int maximo = ceil(s_linha.sequence.size() / 10.0);
    
    int tam_1 = 2 + (rand() % maximo - 1);
    int tam_2 = 2 + (rand() % maximo - 1);

    int opcoes_i = (s_linha.sequence.size() - 1) - tam_1 - tam_2;
    int i = 1 + (rand() % opcoes_i);

    int min_j = i + tam_1;
    int max_j = (s_linha.sequence.size() - 1) - tam_2;
    int opcoes_j = max_j - min_j + 1;
    int j = min_j + (rand() % opcoes_j);

    vector<int> sequencia_perturbada;

    sequencia_perturbada.insert(sequencia_perturbada.end(), s_linha.sequence.begin(), s_linha.sequence.begin() + i);
    sequencia_perturbada.insert(sequencia_perturbada.end(), s_linha.sequence.begin() + j, s_linha.sequence.begin() + (j + tam_2));
    sequencia_perturbada.insert(sequencia_perturbada.end(), s_linha.sequence.begin() + (i + tam_1), s_linha.sequence.begin() + j);
    sequencia_perturbada.insert(sequencia_perturbada.end(), s_linha.sequence.begin() + i, s_linha.sequence.begin() + (i + tam_1));
    sequencia_perturbada.insert(sequencia_perturbada.end(), s_linha.sequence.begin() + (j + tam_2), s_linha.sequence.end());

    s_linha.sequence = sequencia_perturbada;

    s_linha.valorObj = calcularValorObj(&s_linha, data);

    return s_linha;
}

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    Solution s = Construcao(&data);
    imprimirSolução(&s);

    BuscaLocal(&s, &data);
    imprimirSolução(&s);

    return 0;
}