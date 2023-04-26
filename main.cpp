#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <string>
#include <AdjacencyList.h>

using namespace std;


// helper functions
void getDatafromCSVFILE(string fileName);
string parseSentiment(string sentiment);
int parsePrice(string price);

// we need to read the csv file
    // create 3 adjacency lists
// we also need to check that their input is valid before doing a search?
// do the search based on their input

int main() {
    
    //initialize our lists




    // read the data from the file (to fill the lists)
    string fileName = "sentiment.csv";
    getDatafromCSVFILE(fileName);
    
     // create edges between products in the same price range and with similar sentiments or ratings
    createEdgesPrice();
    createEdgesSentiment();
    createEdgesRating();




    //query the user:

    /* 
    while (check the command)

    command list

    enter in what we would like


    -> budget
    -> gift type
    -> related gifts to recommendations (DFS or BFS)

    }
    */




    //depth first search with x list


    return 0;
}



// helper functions

                                    // we would need the container for the adjacency list, or the way to insert into the list
void getDatafromCSVFILE(string fileName) {

    ifstream dataFile(fileName);

    // there is a line of header informatiom -> ignore this
    string ignoreThis;
    getline(dataFile, ignoreThis);

    // string to store the data from every line
    string lineFromFile;

    // loop through all cvs items
    while(getline(dataFile, lineFromFile)) {

        cout << lineFromFile << endl;

        istringstream stream(lineFromFile);

        // tokens we pull from the data line
        string nameToken;
        string priceToken;
        string rateToken;
        string sentimentToken;

        getline(stream, nameToken, '"');            // ignore the first ""
        getline(stream, nameToken, '"');            
        getline(stream, priceToken, ',');           // ignore the preceding comma
        getline(stream, priceToken, ',');
        getline(stream, rateToken, ',');
        getline(stream, sentimentToken);            // extract the sentiment
        
        string name = nameToken;
        int price = parsePrice(priceToken);
        int rate = stoi(rateToken);
        string sentiment = parseSentiment(sentimentToken);


        // store the price, rate, and sentiments in the appropriate list
        // creates a new Product object with the extracted data
        Product p = {name, price, rate, sentiment};

        // stores the Product in the adjacency list
        adjacencyListSentiment[sentiment].push_back(p);
        adjacencyListPrice[to_string(price)].push_back(p);
        adjacencyListRating[to_string(rate)].push_back(p);
    }
}

int parsePrice(string price) {
    
    string temp = "";
    char c = 0;
    for (int i = 0; i < price.length(); i++) {
        c = price.at(i);
        if (!isdigit(c)){
            continue;
        }
        temp = temp + c;
    }

    return stoi(temp);
    
}


string parseSentiment(string sentiment) {

    string temp = sentiment.substr(sentiment.length()-8, -1);
    
    // check the first character 
    //  -> positive/negative = length 8
    //  -> netural is length 7
    char check = temp.at(0);
    if (!isalpha(check)) {
        temp = temp.substr(1,-1);
    }

    return temp;

}
