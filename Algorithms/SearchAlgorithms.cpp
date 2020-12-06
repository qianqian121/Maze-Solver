//
// Created by adar on 12/5/2020.
//
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct Node{
private:
    float cost;
    int row;
    int col;
public:
    Node():cost(0),row(0),col(0){};
    Node(float cost,int x,int y):cost(cost),row(x),col(y){};
    float getCost(){return cost;};
    int getRow(){return row;};
    int getCol(){return col;};
    bool operator==(const Node &node){return this->row == node.row && this->col == node.col;};
    friend  bool operator<(const Node &node1,const Node &node2);
};

bool operator<(const Node &node1,const Node &node2){return node1.cost < node2.cost;}


int uniformCostSearch(int **array, int dimension,int *start, int *target){
    int pathCost = 0 ;
    vector<string> path = vector<string>();
    vector<struct Node> explored = vector<struct Node>();
    priority_queue<struct Node> openList = priority_queue<struct Node>();
    struct Node sourceNode = Node(0, start[0], start[1]);
    struct Node goalNode = Node(0, target[0], target[1]);
    struct Node current_node;
    openList.push(sourceNode);
    while (!openList.empty()){
         current_node = openList.top();
         openList.pop();
         if(current_node == goalNode)
             // reached to goal state
             return 0;
         explored.push_back(current_node);
         //UP
         if(current_node.getRow() - 1 >= 0 && array[current_node.getRow() -1][current_node.getCol()] >=0){
             struct Node node = Node(array[current_node.getRow() -1][current_node.getCol()],current_node.getRow() -1,current_node.getCol());
             if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
         }

         //UP-RIGHT
        if(current_node.getRow() - 1 >= 0 && current_node.getCol() + 1 < dimension && array[current_node.getRow() -1][current_node.getCol() +1] >=0){
            struct Node node = Node(array[current_node.getRow() -1][current_node.getCol() +1],current_node.getRow() -1,current_node.getCol() +1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //RIGHT
        if(current_node.getCol() + 1 < dimension && array[current_node.getRow()][current_node.getCol() +1] >= 0){
            struct Node node = Node(array[current_node.getRow()][current_node.getCol() +1],current_node.getRow(),current_node.getCol()+1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //DOWN-RIGHT
        if(current_node.getRow() + 1 < dimension && current_node.getCol() +1 <dimension && array[current_node.getRow() + 1][current_node.getCol() +1] >= 0){
            struct Node node = Node(array[current_node.getRow() + 1][current_node.getCol() +1],current_node.getRow() +1,current_node.getCol() +1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //DOWN
        if(current_node.getRow() + 1 < dimension && array[current_node.getRow() + 1][current_node.getCol()] >= 0){
            struct Node node = Node(array[current_node.getRow() + 1][current_node.getCol()],current_node.getRow() +1,current_node.getCol());
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //DOWN-LEFT
        if(current_node.getCol() - 1 >= 0 && current_node.getRow() +1 <dimension && array[current_node.getRow() +1][current_node.getCol() -1] >= 0){
            struct Node node = Node(array[current_node.getRow() +1][current_node.getCol() -1],current_node.getRow() +1,current_node.getCol() -1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //LEFT
        if(current_node.getCol() - 1 >= 0 && array[current_node.getRow()][current_node.getCol() -1] >= 0){
            struct Node node = Node(array[current_node.getRow()][current_node.getCol() -1],current_node.getRow(),current_node.getCol() -1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
         //UP-LEFT
        if(current_node.getRow() - 1 >= 0 && current_node.getCol() - 1 >= 0  && array[current_node.getRow() -1][current_node.getCol() - 1] >= 0){
            struct Node node = Node(array[current_node.getRow() -1][current_node.getCol() - 1],current_node.getRow() -1,current_node.getCol() -1);
            if(!count(explored.begin(),explored.end(),node))
                openList.push(node);
        }
    }
    return 1;
}
