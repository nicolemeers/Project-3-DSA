#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <map>
#include <stack>

using namespace std;


string findStartNodeSentiment(map<string, vector<pair<string, string>>>& graph, string userInput);
string findStartNodeRank(map<string, vector<pair<string, int>>>& graph, string userInput);
string findStartNodePrice(map<string, vector<pair<string, int>>>& graph, string userInput);
vector<string> dfsSentiment(map<string, vector<pair<string, string>>>& graph, string startingProduct);
vector<string> dfs(map<string, vector<pair<string, int>>>& graph, string startingProduct);


string findStartNodeSentiment(map<string, vector<pair<string, string>>>& graph, string userInput) {

    auto iter = graph.begin();
    for (iter; iter != graph.end(); iter++) {
        for (int i = 0; i < iter->second.size(); i++) {
            if (iter->second.at(i).second == userInput) {
                return iter->second.at(i).first;
            }
        }
    }

    return "null";

}

string findStartNodeRank(map<string, vector<pair<string, int>>>& graph, string userInput) {

    int input = stoi(userInput);

    auto iter = graph.begin();
    for (iter; iter != graph.end(); iter++) {
        for (int i = 0; i < iter->second.size(); i++) {
            if (iter->second.at(i).second == input) {
                return iter->second.at(i).first;
            }
        }
    }

    return "null";

}

string findStartNodePrice(map<string, vector<pair<string, int>>>& graph, string userInput) {

    int input = stoi(userInput);

    // we need to check the range, not the specific value
    // for now, assume within 20% of desired product
    float rangeShift = (float)input * 0.2;
    int upperRange = input + rangeShift;
    int lowerRange = input - rangeShift;

    //so +/- this value would still be a valid input

    auto iter = graph.begin();
    for (iter; iter != graph.end(); iter++) {
        for (int i = 0; i < iter->second.size(); i++) {
            if (iter->second.at(i).second == input) {
                return iter->second.at(i).first;
            }
            else if (iter->second.at(i).second <= upperRange && iter->second.at(i).second >= lowerRange) {
                return iter->second.at(i).first;
            }
        }
    }


    return "null";

}

// we are input one attribute for the search
// we are input an adjacency list
// edges -> similarity between products
// -> ex: price. Specific price range -> edge between two products in the list means they are within the same price range

// we will search budget, rating, and sentiment



// lets do the sentiment first

// sentiment can be:
        // positive
        // neutral
        // negative

        // we are given a preference. We need to make sure with give a starting node with the correct preference
vector<string> dfsSentiment(map<string, vector<pair<string, string>>>& graph, string startingProduct){

    // we output the list of products that is similar to what was input by the user
    vector<string> results;

    // we add the name to the stack
    stack<string> stk;
    set<string> visited;
    vector<pair<string,string>> adjacent;
    string current;                 // the "u" vertex that we wil look at

    stk.push(startingProduct);
    results.push_back(startingProduct);

    while (!stk.empty()) {
        
        current = stk.top();
        stk.pop();

        // check if the vertex has been visited
        if (visited.find(current) != visited.end()) {
            continue;
        }

        // set the current vertex to visited
        visited.emplace(current);
        results.push_back(current);

        // get all of the adjacent nodes -> if not visited, add to stack
        adjacent = graph[current];
        for (int i = 0; i < adjacent.size(); i++) {
            if (visited.find(adjacent.at(i).first) != visited.end()) {
                continue;
            }
            stk.push(adjacent.at(i).first);
        }
    }
    return results;
}

vector<string> dfs(map<string, vector<pair<string, int>>>& graph, string startingProduct){

    // we output the list of products that is similar to what was input by the user
    vector<string> results;

    // we add the name to the stack
    stack<string> stk;
    set<string> visited;
    vector<pair<string,int>> adjacent;
    string current;                 // the "u" vertex that we wil look at

    stk.push(startingProduct);
    results.push_back(startingProduct);

    while (!stk.empty()) {
        
        current = stk.top();
        stk.pop();

        // check if the vertex has been visited
        if (visited.find(current) != visited.end()) {
            continue;
        }

        // set the current vertex to visited
        visited.emplace(current);
        results.push_back(current);

        // get all of the adjacent nodes -> if not visited, add to stack
        adjacent = graph[current];
        for (int i = 0; i < adjacent.size(); i++) {
            if (visited.find(adjacent.at(i).first) != visited.end()) {
                continue;
            }
            stk.push(adjacent.at(i).first);
        }
    }
    return results;
}
