#include "Data.h"
#include "construcao.h"

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