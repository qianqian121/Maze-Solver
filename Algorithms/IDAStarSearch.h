//
// Created by r00t on 12/15/20.
//

#ifndef AI_PROJECT_IDASTARSEARCH_H
#define AI_PROJECT_IDASTARSEARCH_H

#include "SearchAlgorithmInterface.h"
#include "HeuristicSearch.h"
#include <tuple>

class IDAStarSearch : public SearchAlgorithmInterface, public HeuristicSearch {
private:
    IDAStarSearch() : SearchAlgorithmInterface(), HeuristicSearch() {};

    IDAStarSearch(const IDAStarSearch &);

    void operator=(const IDAStarSearch &);

public:
    int run_algorithm(int **array, int dimension, int *source, int *goal, float time_limit) override;

    std::tuple<Node *, int> DFS_CONTOUR(int **array, int dimension, Node *node, Node *goal, int f_limit);

    static IDAStarSearch &getInstance();
};


#endif //AI_PROJECT_IDASTARSEARCH_H
