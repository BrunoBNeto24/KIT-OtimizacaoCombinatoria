#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "Data.h"
#include "construcao.h"

bool bestImprovementSwap(Solution* s, Data* data);

bool bestImprovement2Opt(Solution* s, Data* data);

bool bestImprovementOrOpt(Solution* s, int n, Data* data);

void BuscaLocal(Solution* s, Data* data);

#endif