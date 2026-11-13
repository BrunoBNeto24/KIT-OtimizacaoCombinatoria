#include "solution.h"

void imprimirSolucao(Solution* s){
    if(s == nullptr || s->sequence.empty()){
        cout << "solução vazia" << endl;
    }
    cout << "Custo: " << s->valorObj << endl;
    cout << "Rota: " << endl;
    for(size_t i = 0; i < s->sequence.size(); i++){
        cout << s->sequence[i] << " ";
    }
    cout << endl;
}

double calcularValorObj(Solution* s, Data* data){
    s->valorObj = 0;
    for(size_t i = 1; i < s->sequence.size() - 1; i++){
        s->valorObj += (s->sequence.size() - i + 1) * data->getDistance(s->sequence[i - 1], s->sequence[i]);
    }
    return s->valorObj;
}

double calcularLatencia(Solution* s, Data* data){
    double latencia = 0;
    for(size_t a = 1; a < s->sequence.size() - 1; a++){
        int i = s->sequence[a];
        int ant_i = s->sequence[a - 1];
        latencia += data->getDistance(ant_i, i);
    }
    return latencia;
}