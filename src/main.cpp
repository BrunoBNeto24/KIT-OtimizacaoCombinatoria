#include "Data.h"
#include "buscaLocal.h"

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    int seed = time(NULL);
    srand(seed);

    Solution s = Construcao(&data);
    imprimirSolucao(&s);

    return 0;
}