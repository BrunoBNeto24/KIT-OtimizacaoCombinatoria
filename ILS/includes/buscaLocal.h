#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Data.h"
#include "solution.h"

bool bestImprovementSwap(Solution* s, Data* data);

bool bestImprovement2Opt(Solution* s, Data* data);

bool bestImprovementOrOpt(Solution* s, Data* data, int n);

void BuscaLocal(Solution* s, Data* data);

#endif