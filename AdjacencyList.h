#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Product {
    string name;
    int price;
    int rating;
    string sentiment;
};

map<string, vector<Product>> adjacencyListSentiment;
map<string, vector<Product>> adjacencyListPrice;
map<string, vector<Product>> adjacencyListRating;

void createEdgesPrice() {
    // sets the threshold for the price difference
    int threshold = 50;

    // loops through each price group in the adjacency list
    for (auto const& priceGroup : adjacencyListPrice) {
        // get the list of products for the current price group
        vector<Product> products = priceGroup.second;

        // loops through each product in the current price group
        for (int i = 0; i < products.size(); i++) {
            Product p1 = products[i];

            // compares the current product with the rest of the products in the smae price range
            for (int j = i+1; j < products.size(); j++) {
                Product p2 = products[j];

                // calculates the price diff between the two products
                int priceDiff = abs(p1.price - p2.price);

                // if the price difference is not in the threshold, adds an edge between the two products
                if (priceDiff <= threshold) {
                    adjacencyListPrice[p1.name].push_back(p2);
                    adjacencyListPrice[p2.name].push_back(p1);
                }
            }
        }
    }
}

void createEdgesSentiment() {
    // loops through each sentiment group in the adjacency list
    for (auto const& sentimentGroup : adjacencyListSentiment) {
        // gets the list of products for the current group
        vector<Product> products = sentimentGroup.second;

        // loops through each product in the current group
        for (int i = 0; i < products.size(); i++) {
            Product p1 = products[i];

            // compares the current product with the rest of the products in the group
            for (int j = i+1; j < products.size(); j++) {
                Product p2 = products[j];

                // calculates sentiment similarity between two products
                int sentimentDiff = 0;
                if (p1.sentiment[0] == 'n' && p2.sentiment[0] == 'n') {
                    // neutral 
                    sentimentDiff = (p1.sentiment.size() == p2.sentiment.size()) ? 0 : 1;
                } else {
                    // positive/negative 
                     // check the first character of the sentiment strings
                    char p1_sentiment = p1.sentiment[0];
                    char p2_sentiment = p2.sentiment[0];
                // adds an edge between the two products if their sentiment is positive or negative
                    if ((p1_sentiment == 'p' && p2_sentiment == 'p') || (p1_sentiment == 'n' && p2_sentiment == 'n')) {
                        sentimentDiff = 0; 
                    }
                }
                // if the sentiment difference is 0, adds edge between the two products
                if (sentimentDiff == 0) {
                    adjacencyListSentiment[p1.name].push_back(p2);
                    adjacencyListSentiment[p2.name].push_back(p1);
                }
            }
        }
    }
}

void createEdgesRating() {
    // loops through each rating group in the adjacency list
    for (auto const& ratingGroup : adjacencyListRating) {
        // gets the list of products 
        vector<Product> products = ratingGroup.second;

        // loops through each product in the current group
        for (int i = 0; i < products.size(); i++) {
            Product p1 = products[i];

            // compare the current products with the rest of the products in the group
            for (int j = i+1; j < products.size(); j++) {
                Product p2 = products[j];

                // calculate the rating difference between the two products
                int ratingDiff = abs(p1.rating - p2.rating);

                // if the rating difference is less than or equal to 0, adds edge between the two products
                if (ratingDiff <= 0) {
                    adjacencyListRating[p1.name].push_back(p2);
                    adjacencyListRating[p2.name].push_back(p1);
                }
            }
        }
    }
}

void readEdges(map<string, vector<Product>> adjacencyList) {
    // loops through each key-value pair in the adjacency list
    for (auto const& kv : adjacencyList) {
        string productName = kv.first;
        vector<Product> connectedProducts = kv.second;

        // prints the edges for the current product
        cout << "Edges for " << productName << ":" << endl;
        for (Product product : connectedProducts) {
            cout << "\t" << product.name << endl;
        }
    }
}
