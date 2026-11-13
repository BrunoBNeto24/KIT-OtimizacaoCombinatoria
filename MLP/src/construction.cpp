#include "construction.h"

using namespace std;

vector<insertionInfo> calcularCustoInsercao(Solution& s, vector<int> CL, int r, Data* data)
{
    vector<insertionInfo> custoInsercao = vector<insertionInfo>(CL.size());
    int l = 0;
    double l_de_r = calcularLatencia(&s, data);
        for(auto k : CL){
            custoInsercao[l].custoInsertion = l_de_r  + data->getDistance(r, k);
            custoInsercao[l].noInserido = k; 
            l++;
        }
    return custoInsercao;
}

vector<int> nosRestantes(int n){
    vector<int> restantes(n - 1);

    iota(restantes.begin(), restantes.end(), 2);

    return restantes;
}

bool compararCustos(const insertionInfo& a, const insertionInfo& b){
    return a.custoInsertion < b.custoInsertion;
}

void ordenarEmOrdemCrescente(vector<insertionInfo>& custoInserir){
    sort(custoInserir.begin(), custoInserir.end(), compararCustos);
} 

void inserirNaSolucao(Solution* s, insertionInfo noParaInserir){ 
    s->sequence.push_back(noParaInserir.noInserido);
    s->valorObj = s->valorObj + noParaInserir.custoInsertion;
}  

Solution Construcao(Data* data){
    Solution s;
    s.valorObj = 0;
    s.sequence = {1};
    vector<int> CL = nosRestantes(data->getDimension());
    //cout << "O tamanho de Cl: " << CL.size() << endl;
    int r = s.sequence[0];
    while (!CL.empty())
    {
        vector<insertionInfo> custoInsercao = calcularCustoInsercao(s, CL, r, data);
        ordenarEmOrdemCrescente(custoInsercao);
        double alpha = (double) rand() / RAND_MAX;
        int limite = (int) ceil(alpha * custoInsercao.size());
        
        if(limite < 1){
            limite = 1;
        }

        int selecionado = rand() % limite;
        inserirNaSolucao(&s, custoInsercao[selecionado]);
        
        auto valor = find(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido);
        CL.erase(valor);

        r = s.sequence.back();
    }

    s.sequence.push_back(1);
    s.valorObj = calcularValorObj(&s, data);
    
    return s;
}