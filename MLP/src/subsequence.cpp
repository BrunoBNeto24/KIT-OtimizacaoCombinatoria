#include "subsequence.h"

void UpdateAllSubseq(Solution & s, vector<vector<Subsequence>> & subseq_matrix, Data & data){
    int n = s.sequence.size();

    for(int i = 0; i < n; i++){
        subseq_matrix[i][i].W = (i > 0);
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].T = 0;
        subseq_matrix[i][i].first = s.sequence[i];
        subseq_matrix[i][i].last = s.sequence[i];
    }

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            subseq_matrix[i][j] = Subsequence::Concatenar(subseq_matrix[i][j-1], subseq_matrix[j][j], data);
        }
    }

    for(int i = n - 1; i >= n; i--){
        for(int j = i - 1; j >= n; j--){
            subseq_matrix[i][j] = Subsequence::Concatenar(subseq_matrix[i][j+1], subseq_matrix[j][j], data);
        }
    }
}