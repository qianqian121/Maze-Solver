//
// Created by r00t on 12/15/20.
//

#include "HeuristicSearch.h"

void HeuristicSearch::setHeuristicFunction(int (*heuristicFunction)(const pair<int, int> &, const pair<int, int> &)) {
    _heuristic_function = heuristicFunction;
}

void HeuristicSearch::sumNodeHeuristic(int h) {
    _nodes_heuristic_sum += h;
    _no_of_nodes++;
}

double HeuristicSearch::getAvg() const {
    return (_nodes_heuristic_sum / _no_of_nodes);
}

