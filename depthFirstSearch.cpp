#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include "AdjacencyList.h"

using namespace std;


void dfs(map<string, vector<Product>> graph, vector<string> startingProducts);
void dfsAll(vector<string> startingProducts, map<string, vector<Product>> adjacencyListSentiment, 
            map<string, vector<Product>> adjacencyListPrice, map<string, vector<Product>> adjacencyListRating);




void dfsAll(vector<string> startingProducts, map<string, vector<Product>> adjacencyListSentiment, 
            map<string, vector<Product>> adjacencyListPrice, map<string, vector<Product>> adjacencyListRating) {

    dfs(adjacencyListSentiment, startingProducts);        // sentiment
    dfs(adjacencyListRating, startingProducts);       // rating
    dfs(adjacencyListPrice, startingProducts);    // price

}

void dfs(map<string, vector<Product>> graph, vector<string> startingProducts) {

    // create a stack to store nodes to visit
    stack<string> stk;
    // create a set to keep track of visited nodes
    set<string> visited;

    string current;         // the "u" vertex we will keep track of

    // add the starting product to the stack
    for (string startProduct : startingProducts) {
        // add the start node to the queue and mark it as visited
        stk.push(startProduct);
    }

    while(!stk.empty()) {

        current = stk.top();
        stk.pop();

        visited.insert(current);

        // print out the current product
        cout << current << endl;

        // loop through descendents (adjacent) of current node
        if (visited.find(current) != visited.end()) {
            continue;
        }

        // get the node in the map. Get the vector attached to it
        vector<Product> adjacent;
        adjacent = graph[current];

        for (int i = 0; i < adjacent.size(); i++) {
            if (visited.find(adjacent.at(i).name) != visited.end()) {
                continue;
            }
            stk.push(adjacent.at(i).name);
            visited.insert(adjacent.at(i).name);
        }

    }

}
