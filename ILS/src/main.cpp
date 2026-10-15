#include "Data.h"
#include "buscaLocal.h"
#include "construcao.h"
#include "perturbacao.h"

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    int seed = time(NULL);
    srand(seed);

    Solution s = Construcao(&data);
    imprimirSolucao(&s);

    BuscaLocal(&s, &data);
    imprimirSolucao(&s);

    /*Perturbacao(s, &data);
    imprimirSolucao(&s);*/

    return 0;
}