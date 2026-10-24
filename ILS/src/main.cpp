#include "Data.h"
#include "buscaLocal.h"
#include "construcao.h"
#include "perturbacao.h"
#include "ils.h"
#include <chrono>
#include <iomanip>

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    int seed = time(NULL);
    srand(seed);

    int maxIter = 50;
    int n = data.getDimension();
    int maxIterILS;

    if(n >= 150){
        maxIterILS = n / 2;
    } else {
        maxIterILS = n;
    }

    Solution s = ILS(maxIter, maxIterILS, data);

    imprimirSolucao(&s);

    return 0;
}