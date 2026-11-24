#include "Data.h"
#include "buscaLocal.h"
#include "construction.h"
#include "perturbacao.h"
#include "subsequence.h"
#include "MLP.h"
#include <chrono>
#include <iomanip>

int main(int argc, char** argv){
    auto data = Data(argc, argv[1]);
    data.read();

    int seed = time(NULL);
    srand(seed);

    int maxIter = 10;
    int n = data.getDimension();
    int maxIterILS;

    maxIterILS = min(100, n);

    auto inicio = chrono::steady_clock::now();

    Solution s = MLP(maxIter, maxIterILS, data);

    auto fim = chrono::steady_clock::now();

    chrono::duration<double> tempo = fim - inicio;

    imprimirSolucao(&s);
    
    cout << fixed << setprecision(6);
    cout << "Tempo: " << tempo.count() << "segundos" << endl;

    /*Solution s = Construcao(&data);
    imprimirSolucao(&s);

    vector<vector<Subsequence>> subsequ_matriz = vector<vector<Subsequence>>(s.sequence.size(), vector<Subsequence>(s.sequence.size()));

    UpdateAllSubseq(s, subsequ_matriz, &data);

    BuscaLocal(s, subsequ_matriz, &data);
    imprimirSolucao(&s);

    s = Perturbacao(s, subsequ_matriz, &data);
    imprimirSolucao(&s);*/

    return 0;
}