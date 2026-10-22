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

    //auto inicio = chrono::steady_clock::now();

    Solution s = ILS(maxIter, maxIterILS, data);

    //auto fim = chrono::steady_clock::now();

    //chrono::duration<double> tempo = fim - inicio;

    imprimirSolucao(&s);
    //cout << fixed << setprecision(6);
    //cout << "Tempo: " << tempo.count() << "segundos" << endl;

    /*Solution s = Construcao(&data);
    imprimirSolucao(&s);

    BuscaLocal(&s, &data);
    imprimirSolucao(&s);

    s = Perturbacao(s, &data);
    imprimirSolucao(&s);

    s.valorObj = calcularValorObj(&s, &data);
    imprimirSolucao(&s);*/

    return 0;
}