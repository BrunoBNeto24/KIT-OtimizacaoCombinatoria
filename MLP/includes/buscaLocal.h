#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Data.h"
#include "solution.h"
#include "subsequence.h"

bool bestImprovementSwap(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data);

bool bestImprovement2Opt(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data);

bool bestImprovementOrOpt(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data, int n);

void BuscaLocal(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data* data);

#endif