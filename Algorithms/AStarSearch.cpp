//
// Created by r00t on 12/14/20.
//

#include "AStarSearch.h"
#include <vector>
#include <set>

using std::multiset;
using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;


int AStarSearch::run_algorithm(int **array, int dimension, int *source, int *goal, float time_limit) {
    // closed list
    unordered_map<pair<int, int>, shared_ptr<Node>, pair_hash> visited = unordered_map<pair<int, int>, shared_ptr<Node>, pair_hash>();
    // open list
    multiset<shared_ptr<Node>,lessCompNodePointers> openList = multiset<shared_ptr<Node>,lessCompNodePointers>();
    shared_ptr<vector<shared_ptr<Node>>> successors;
    shared_ptr<Node> current_node;
    // time out indicator
    bool time_out;
    // row and col hold the matrix direction according to node actions.
    // g_cost is the actual weight of the path
    int expand_counter, h_cost = _heuristic_function(pair<int, int>(source[0], source[1]),
                                                     pair<int, int>(goal[0], goal[1])), g_cost = 0;
    sumNodeHeuristic(h_cost);
    // init the source node
    shared_ptr<Node> sourceNode (new Node(h_cost, g_cost, source[0], source[1], 0));
    // insert source node coordinates to the path
    sourceNode->insertElementToPath(pair<int, int>(sourceNode->getRow(), sourceNode->getCol()));
    // init goal node for goal reached comparison
    shared_ptr<Node> goalNode (new Node(0, 0, goal[0], goal[1], 0));
    // insert the source node to the open list
    openList.insert(sourceNode);
    while (!openList.empty()) {
        // update current time for time out checking
        setCurrentTime(clock());
        // get the node with the smallest h_cost value
        current_node = *openList.begin();
        openList.erase(openList.begin());
        time_out = (diff_clock(getCurrentTime(), getStartTime()) >= time_limit);
        // if goal node reached or time out stop the search
        if (*current_node == *goalNode || time_out) {
            setExplored(visited.size());
            if (!time_out) {
                setEndStatus(true);
            }
            print_path(array, dimension, *current_node);
            generate_stats(*current_node);
            return 0;
        }
        // mark current node as visited
        visited[pair<int, int>(current_node->getRow(), current_node->getCol())] = current_node;
        // zero the expand counter for the current node in order to check cutoffs
        expand_counter = 0;
        // loop over node actions
        successors = current_node->successors(array,dimension);
        for(const auto& successor :*successors){
            expand_counter++;
            h_cost = _heuristic_function(pair<int, int>(successor->getRow(), successor->getCol()), pair<int, int>(goalNode->getRow(), goalNode->getCol()));
            successor->setHeuristicCost(successor->getActualCost() + h_cost);
            sumNodeHeuristic(h_cost);
            // use std::find as it uses operator== for comparison
            auto open_list_iterator = std::find_if(openList.begin(), openList.end(), [&successor](const shared_ptr<Node>& node){return *node == *successor;});
            auto explored_iterator = visited.find(pair<int, int>(successor->getRow(), successor->getCol()));
            // if the node is not visited and not in the open list, add it to open list.
            if (explored_iterator == visited.end() && open_list_iterator == openList.end())
                openList.insert(successor);
            // if the node is present in the open list but have a higher h_cost , remove it and insert the better one.
            else if (open_list_iterator != openList.end() &&
                    (*open_list_iterator)->getHeuristicCost() > successor->getHeuristicCost()) {
                openList.erase(open_list_iterator);
                openList.insert(successor);
            }
            // if the node has been visited with higher h_cost, remove it from visited and insert it to open list with better h_cost
            else if (explored_iterator != visited.end() &&
                       explored_iterator->second->getHeuristicCost() > successor->getHeuristicCost()) {
                visited.erase(explored_iterator);
                openList.insert(successor);
            }
            // if we didnt get into one of the above cond, we didnt expended this node so decrement expend_counter.
            else expand_counter--;

        }
        if (!expand_counter) {
            // cut off occurrence
            update_cutoffs(current_node->getDepth());
        }
    }
    // no solution found
    setExplored(visited.size());
    generate_stats(*current_node);
    return 1;
}


AStarSearch &AStarSearch::getInstance() {
    static AStarSearch instance;
    return instance;
}

void AStarSearch::generate_stats(const Node &current_node) {
    AlgorithmStatistics::generate_stats(current_node);
    HeuristicSearch::generate_heuristic_stats();
}
