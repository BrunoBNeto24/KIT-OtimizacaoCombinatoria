#include "buscaLocal.h"
#include "subsequence.h"

using namespace std;

bool bestImprovementSwap(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data){
    double bestDelta = 0;
    double delta;
    int best_i, best_j;
    Subsequence total, sigma_1, sigma_2, sigma_3;
    for (size_t i = 1; i < s.sequence.size() - 2; i++)
    {
        int prox_vi = s.sequence[i + 1];
        sigma_1 = subseq_matrix[0][i - 1];
        for (size_t j = i + 1; j < s.sequence.size() - 2; j++)
        {
            int vj = s.sequence[j];
            if(vj == prox_vi){
                sigma_2 = subseq_matrix[i + 1][s.sequence.size() - 1];

                total = Subsequence::Concatenar(sigma_1, subseq_matrix[j][j], data);
                total = Subsequence::Concatenar(total, subseq_matrix[i][i], data);
                total = Subsequence::Concatenar(total, sigma_2, data);

                delta = total.C - s.valorObj;
            } else {
                sigma_2 = subseq_matrix[i + 1][j - 1];

                sigma_3 = subseq_matrix[j + 1][s.sequence.size() - 1];

                total = Subsequence::Concatenar(sigma_1, subseq_matrix[j][j], data);
                total = Subsequence::Concatenar(total, sigma_2, data);
                total = Subsequence::Concatenar(total, subseq_matrix[i][i], data);
                total = Subsequence::Concatenar(total, sigma_3, data);

                delta = total.C - s.valorObj;
            }

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
            
        }
        
    }
    if(bestDelta < 0){
        swap(s.sequence[best_i], s.sequence[best_j]);
        s.valorObj = s.valorObj + bestDelta;
        UpdateParcSubseq(s, subseq_matrix, best_i, best_j, data);
        return true;
    } else{
        return false;
    }
}


bool bestImprovement2Opt(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data){
    double bestDelta = 0;
    int best_i, best_j;
    Subsequence total, sigma_1, sigma_2;
    for (size_t i = 1; i < s.sequence.size() - 2; i++)
    {
       sigma_1 = subseq_matrix[0][i - 1];
       for (size_t j = i + 1; j < s.sequence.size() - 2; j++)
       {
        sigma_2 = subseq_matrix[j + 1][s.sequence.size() - 1];

        total = Subsequence::Concatenar(sigma_1, subseq_matrix[j][i], data);
        total = Subsequence::Concatenar(total, sigma_2, data);

        /*Analisar os casos de onde podem ser adjacentes e podendo utilizar somente o swap*/
        double delta = total.C - s.valorObj;

        if(delta < bestDelta){
            bestDelta = delta;
            best_i = i;
            best_j = j;
        }
       }
    }
    if(bestDelta < 0){
        reverse(s.sequence.begin() + best_i, s.sequence.begin() + best_j + 1);
        s.valorObj = s.valorObj + bestDelta;
        UpdateParcSubseq(s, subseq_matrix, best_i, best_j, data);
        return true;
    } else {
        return false;
    }
}

bool bestImprovementOrOpt(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data, int n){
    double bestDelta = 0;
    int best_i, best_j;
    Subsequence total, sigma_1, sigma_2, sigma_3;
    switch (n)
    {
    case 1:
        for (size_t i = 1; i < s.sequence.size() - 2; i++)
        {
            for (size_t j = i + 1; j < s.sequence.size() - 1; j++)
            {
                /*if(j == i - 1 || j == i){
                    continue;
                }*/
                
                sigma_1 = subseq_matrix[0][i - 1];
                sigma_2 = subseq_matrix[i + 1][j - 1];
                sigma_3 = subseq_matrix[j + 1][s.sequence.size() - 1];

                total = Subsequence::Concatenar(sigma_1, sigma_2, data);
                total = Subsequence::Concatenar(total, subseq_matrix[j][j], data);
                total = Subsequence::Concatenar(total, subseq_matrix[i][i], data);
                total = Subsequence::Concatenar(total, sigma_3, data);

                double delta = total.C - s.valorObj;

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            int valorBest_i = s.sequence[best_i];
            s.sequence.erase(s.sequence.begin() + best_i);
            if(best_i < best_j){
                best_j =  best_j - 1;
            }
            s.sequence.insert(s.sequence.begin() + (best_j + 1), valorBest_i);
            s.valorObj = s.valorObj + bestDelta;
            UpdateParcSubseq(s, subseq_matrix, best_i, best_j, data);
            return true;
        } else {
            return false;
        }
        break;
    case 2:
        for (size_t i = 1; i < s.sequence.size() - 3; i++)
        {
            for (size_t j = i + 2; j < s.sequence.size() - 1; j++)
            {
                /*if(j == i - 1 || j == i || j == i + 1){
                    continue;
                }*/

                sigma_1 = subseq_matrix[0][i - 1];
                sigma_2 = subseq_matrix[i + 2][j - 1];
                sigma_3 = subseq_matrix[j + 1][s.sequence.size() - 1];

                total = Subsequence::Concatenar(sigma_1, sigma_2, data);
                total = Subsequence::Concatenar(total, subseq_matrix[j][j], data);
                total = Subsequence::Concatenar(total, subseq_matrix[i][i + 1], data);
                total = Subsequence::Concatenar(total, sigma_3, data);

                double delta = total.C - s.valorObj;

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            int valorBest_i = s.sequence[best_i];
            int valorproxBest_i = s.sequence[best_i + 1];
            s.sequence.erase(s.sequence.begin() + (best_i + 1));
            s.sequence.erase(s.sequence.begin() + best_i);
            
            if(best_i < best_j){
                best_j = best_j - 2;
            }

            s.sequence.insert(s.sequence.begin() + (best_j + 1), valorBest_i);
            s.sequence.insert(s.sequence.begin() + (best_j + 2), valorproxBest_i);
            s.valorObj = s.valorObj + bestDelta;

            UpdateParcSubseq(s, subseq_matrix, best_i, best_j, data);
            return true;
        } else {
            return false;
        }   
        break;
    case 3:
        for (size_t i = 1; i < s.sequence.size() - 4; i++)
        {
            for (size_t j = i + 3; j < s.sequence.size() - 1; j++)
            {
                /*if(j == i - 1 || j == i || j == i + 1 || j == i + 2){
                    continue;
                }*/

                sigma_1 = subseq_matrix[0][i - 1];
                sigma_2 = subseq_matrix[i + 3][j - 1];
                sigma_3 = subseq_matrix[j + 1][s.sequence.size() - 1];

                total = Subsequence::Concatenar(sigma_1, sigma_2, data);
                total = Subsequence::Concatenar(total, subseq_matrix[j][j], data);
                total = Subsequence::Concatenar(total, subseq_matrix[i][i + 2], data);
                total = Subsequence::Concatenar(total, sigma_3, data);

                double delta = total.C - s.valorObj;

                if(delta < bestDelta){
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        if(bestDelta < 0){
            int valorBest_i = s.sequence[best_i];
            int valorBest_i2 = s.sequence[best_i + 1];
            int valorBest_i3 = s.sequence[best_i + 2];

            s.sequence.erase(s.sequence.begin() + best_i + 2);
            s.sequence.erase(s.sequence.begin() + best_i + 1);
            s.sequence.erase(s.sequence.begin() + best_i);

            if(best_i < best_j){
                best_j = best_j - 3;
            }

            s.sequence.insert(s.sequence.begin() + best_j + 1, valorBest_i);
            s.sequence.insert(s.sequence.begin() + best_j + 2, valorBest_i2);
            s.sequence.insert(s.sequence.begin() + best_j + 3, valorBest_i3);


            s.valorObj = s.valorObj + bestDelta;

            UpdateParcSubseq(s, subseq_matrix, best_i, best_j, data);
            return true;
        } else {
            return false;
        }
        break;
    default:
        return false;
        break;
    }
}

void BuscaLocal(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data){
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (NL.empty() == false)
    {
        int n = (rand() % NL.size());

        switch (NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, subseq_matrix, data);
            break;
        case 2:
            improved = bestImprovement2Opt(s, subseq_matrix, data);
            break;
        case 3:
            improved = bestImprovementOrOpt(s, subseq_matrix, data, 1);
            break;
        case 4:
            improved = bestImprovementOrOpt(s, subseq_matrix, data, 2);
            break;
        case 5:
            improved = bestImprovementOrOpt(s, subseq_matrix, data, 3);
            break;
        default:
            break;
        }
        if(improved){
            NL = {1, 2, 3, 4, 5};
        } else {
            NL.erase(NL.begin() + n);
        } 
    }
}