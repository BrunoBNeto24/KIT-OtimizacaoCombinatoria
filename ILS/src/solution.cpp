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
    for(size_t i = 0; i < s->sequence.size() - 1; i++){
        s->valorObj += data->getDistance(s->sequence[i], s->sequence[i+1]);
    }
    return s->valorObj;
}
