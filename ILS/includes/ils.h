#ifndef ILS_H
#define ILS_H

#include "Data.h"
#include "construcao.h"
#include "buscaLocal.h"
#include "perturbacao.h"

Solution ILS(int maxIter, int maxIterIls, Data* data);

#endif