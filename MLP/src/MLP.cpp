#include "MLP.h"

Solution MLP(int maxIter, int maxIterIls, Data data){
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;

    for(int i = 0; i < maxIter; i++){
        Solution s = Construcao(&data);
        Solution best = s;

        vector<vector<Subsequence>> subsequ_matriz = vector<vector<Subsequence>>(s.sequence.size(), vector<Subsequence>(s.sequence.size()));

        UpdateAllSubseq(s, subsequ_matriz, &data);

        int iterILS = 0;

        while (iterILS <= maxIterIls)
        {
            BuscaLocal(s, subsequ_matriz, &data);
            
            if(s.valorObj < best.valorObj){
                best = s;
                iterILS = 0;
            }
            s = Perturbacao(best, subsequ_matriz, &data);
            iterILS++;
        }
        if(best.valorObj < bestOfAll.valorObj){
            bestOfAll = best;
        }
    }
    return bestOfAll;
}