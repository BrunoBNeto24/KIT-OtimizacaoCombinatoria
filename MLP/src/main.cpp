#include "Data.h"
#include "buscaLocal.h"
#include "construction.h"
#include "perturbacao.h"
//#include "MLP.h"
#include <chrono>
#include <iomanip>

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    int seed = time(NULL);
    srand(seed);

    Solution s = Construcao(&data);
    imprimirSolucao(&s);

    return 0;
}