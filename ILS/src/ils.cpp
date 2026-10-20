#include "ils.h"


Solution ILS(int maxIter, int maxIterIls, Data data){
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;

    for(int i = 0; i < maxIter; i++){
        Solution s = Construcao(&data);
        Solution best = s;

        int iterILS = 0;

        while (iterILS <= maxIterIls)
        {
            BuscaLocal(&s, &data);
            if(s.valorObj < best.valorObj){
                best = s;
                iterILS = 0;
            }
            s = Perturbacao(best, &data);
            iterILS++;
        }
        if(best.valorObj < bestOfAll.valorObj){
            bestOfAll = best;
        }
    }
    return bestOfAll;
}
