#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Data.h"
#include "buscaLocal.h"

using namespace std;

bool bestImprovementSwap(Solution* s, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    bool improved = false;
    for (size_t i = 1; i < s->sequence.size() - 2; i++)
    {
        int vi = s->sequence[i];
        int prox_vi = s->sequence[i + 1];
        int ant_vi = s->sequence[i - 1];
        for (size_t j = i + 1; j < s->sequence.size() - 2; j++)
        {
            int vj = s->sequence[j];
            int prox_vj = s->sequence[j + 1];
            int ant_vj = s->sequence[j - 1];
            double delta = -data->getDistance(ant_vi, vi) - data->getDistance(vi, prox_vi) + data->getDistance(ant_vi, vj) + data->getDistance(vj, prox_vi) - data->getDistance(ant_vj, vj) - data->getDistance(vj, prox_vj) +  data->getDistance(ant_vj, vi) + data->getDistance(vi, prox_vj);
            //Tratar caso onde o i e o j são adjacentes

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
            
        }
        
    }
    if(bestDelta < 0){
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->valorObj = s->valorObj + bestDelta;
        improved = true;
    }
    return improved; 
}


bool bestImprovement2Opt(Solution* s, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    for (size_t i = 1; i < s->sequence.size() - 1; i++)
    {
       int vi = s->sequence[i];
       int ant_vi = s->sequence[i - 1];
       for (size_t j = i + 1; j < s->sequence.size() - 1; j++)
       {
        int vj = s->sequence[j];
        int prox_vj = s->sequence[j + 1];

        double delta = data->getDistance(ant_vi, vj) + data->getDistance(vi, prox_vj) - data->getDistance(ant_vi, vi) - data->getDistance(vj, prox_vj);

        if(delta < bestDelta){
            bestDelta = delta;
            best_i = i;
            best_j = j;
        }
       }
    }
    if(bestDelta < 0){
        reverse(s->sequence.begin() + best_i, s->sequence.begin() + best_j + 1);
        s->valorObj = s->valorObj + bestDelta;
        return true;
    }
    return false;
}

bool bestImprovementOrOpt(Solution* s, int n, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    switch (n)
    {
    case 1:
        for (size_t i = 1; i < s->sequence.size() - 2; i++)
        {
            int vi = s->sequence[i];
            int prox_vi = s->sequence[i + 1];
            int ant_vi = s->sequence[i - 1];
            for (size_t j = 1; j < s->sequence.size() - 2; j++)
            {
                int vj = s->sequence[j];
                int prox_vj = s->sequence[j + 1];
                
                double delta = - data->getDistance(ant_vi, vi) - data->getDistance(vi, prox_vi) + data->getDistance(vj, vi) + data->getDistance(vi, prox_vj) + data->getDistance(ant_vi, prox_vi);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
        int valorBest_i = s->sequence[best_i];
        s->sequence.erase(s->sequence.begin() +  best_i);
        if(best_i < best_j){
            best_j =  best_j - 1;
        }
        s->sequence.insert(s->sequence.begin() + (best_j + 1), valorBest_i);
        s->valorObj = s->valorObj + bestDelta;
        return true;
        }
        return false;
        break;
    case 2:
        for (size_t i = 1; i < s->sequence.size() - 3; i++)
        {
            int vi = s->sequence[i];
            int prox_i = s->sequence[i + 1];
            int prox2_i = s->sequence[i + 2];
            int ant_i = s->sequence[i - 1];
            for (size_t j = 1; j < s->sequence.size() - 3; j++)
            {
                int vj = s->sequence[j];
                int prox_j = s->sequence[j + 1];
                
                double delta = data->getDistance(vj, vi) + data->getDistance(prox_i, prox_j) + data->getDistance(ant_i, prox2_i) - data->getDistance(ant_i, vi) - data->getDistance(prox_i, prox2_i) - data->getDistance(vj, prox_j);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            s->valorObj = s->valorObj + bestDelta;
            return true;
        }
        return false;
        break;
    case 3:
        for (size_t i = 1; i < s->sequence.size() - 4; i++)
        {
            int vi = s->sequence[i];
            //int prox_i = s->sequence[i + 1]; desncessário para o casos do Or-opt-3
            int prox2_i = s->sequence[i + 2];
            int prox3_i = s->sequence[i + 3];
            int ant_i = s->sequence[i - 1];
            for (size_t j = 1; j < s->sequence.size() - 4; j++)
            {
                int vj = s->sequence[j];
                int prox_j = s->sequence[j + 1];
                
                double delta = data->getDistance(vj, vi) + data->getDistance(prox2_i, prox_j) + data->getDistance(ant_i, prox3_i) - data->getDistance(ant_i, vi) - data->getDistance(prox2_i, prox3_i) - data->getDistance(vj, prox_j);

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            s->valorObj = s->valorObj + bestDelta;
            return true;
        }
        return false;
        break;
    default:
        return false;
        break;
    }
}

void BuscaLocal(Solution* s, Data* data){
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch (NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, data);
            break;
        case 2:
            improved = bestImprovement2Opt(s, data);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, 1, data);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, 2, data);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, 3, data);
            break;
        }
        if(improved){
            NL = {1, 2, 3, 4, 5};
        } else {
            NL.erase(NL.begin() + n);
        }    
    }
}