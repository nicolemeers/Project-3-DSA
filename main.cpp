#include <fstream>
#include <sstream>
#include <iomanip>
//#include "AdjacencyList.h"
#include "depthFirstSearch.cpp"

using namespace std;


// helper functions
void getDatafromCSVFILE(string fileName, Product adjacencyListSentiment, Product adjacencyListPrice, Product adjacencyListRating);
string parseSentiment(string sentiment);
int parsePrice(string price);
int parseRate(string rate);
string priceIntegrity(string price);

int main() {
    
    //initialize our lists

    map<string, vector<Product>> adjacencyListSentiment;
    map<string, vector<Product>> adjacencyListPrice;
    map<string, vector<Product>> adjacencyListRating;

    // read the data from the file (to fill the lists)
    string fileName = "sentiment.csv";
    getDatafromCSVFILE(fileName, adjacencyListSentiment, adjacencyListPrice, adjacencyListRating);

    string exit = "";

    //query the user:

   do {

        string budget;
        string rating;
        string sentiment;

        cout << "Please enter your budget: ";
        cin >> budget;
        cout << "Please enter in the rating you're looking for: ";
        cin >> rating;
        cout << "Please enter the sentiment you're looking for: ";
        cin >> sentiment;

        int rate = stoi(rating);
        int price = stoi(budget);

        // get the starting products
        string startingProductsByPrice = getStartingProductBySentiment(sentiment, adjacencyListSentiment);
        string startingProductsByRating = getStartingProductByRating(rate, adjacencyListRating);
        string startingProductsBySentiment = getStartingProductByPrice(price, adjacencyListPrice);

        // combine all the starting products into a single vector
        vector<string> allStartingProducts;
        allStartingProducts.push_back(startingProductsByPrice);
        allStartingProducts.push_back(startingProductsByRating);
        allStartingProducts.push_back(startingProductsBySentiment);

        // call dfs
        dfsAll(allStartingProducts, adjacencyListSentiment, adjacencyListPrice, adjacencyListRating);

        // call bfs with the combined starting prodcuts and the adjacency list
        bfsCombined(allStartingProducts, adjacencyListSentiment, adjacencyListPrice, adjacencyListRating);




        cout << "Would you like to search again? (y/n) ";
        cin >> exit;

        // set the string to lowercase
        //transform(exit.begin(), exit.end(), exit.begin(), ::tolower);
        if (exit == "n" || exit == "no") {
            exit == "n";
        }


    } 
    while (exit == "y");


    return 0;
}



// helper functions

void getDatafromCSVFILE(string fileName, map<string, vector<Product>>& adjacencyListSentiment, 
        map<string, vector<Product>>& adjacencyListPrice, map<string, vector<Product>>& adjacencyListRating) {

    ifstream dataFile(fileName);

    int i = 0;

    // there is a line of header informatiom -> ignore this
    string ignoreThis;
    getline(dataFile, ignoreThis);

    // string to store the data from every line
    string lineFromFile;

    // loop through all cvs items
    while(getline(dataFile, lineFromFile)) {

        istringstream stream(lineFromFile);

        i++;

        // tokens we pull from the data line
        string nameToken;
        string priceToken;
        string rateToken;
        string sentimentToken;


        // we need to check if there is a quotation mark first
        char check = lineFromFile.at(0);


        if (check == '"') {
            getline(stream, nameToken, '"');            // ignore the first ""
            getline(stream, nameToken, '"');            
            getline(stream, priceToken, ',');           // ignore the preceding comma
            getline(stream, priceToken, ',');
            getline(stream, rateToken, ',');
            getline(stream, sentimentToken);            // extract the sentiment
        }
        else {
            getline(stream, nameToken, ',');            
            getline(stream, priceToken, ',');
            getline(stream, rateToken, ',');
            getline(stream, sentimentToken);            // extract the sentiment
        }

        // check if the data is broken up into 2 lines:
        if (priceToken == "" && rateToken == "") {

            // do a getline for the next line
            getline(dataFile, lineFromFile);
            istringstream stream(lineFromFile);
            // get the rest of the name
            string secondStringToken;
            getline(stream, secondStringToken, '"');
            getline(stream, priceToken, ',');
            getline(stream, priceToken, ',');
            getline(stream, rateToken, ',');
            getline(stream, sentimentToken);

            // update the name
            nameToken = nameToken + " " + secondStringToken;
        }

        // exclude erroneous inputs
        string temp = priceIntegrity(priceToken);
        if (temp == "") {
            
           continue;
        }

        string name = nameToken;
        int price = parsePrice(priceToken);
        int rate = parseRate(rateToken);
        
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

    if (temp == "") {
        return 0;
    }
    return stoi(temp);
    
}

int parseRate(string rate) {
    
    string temp = "";
    char c = 0;
    for (int i = 0; i < rate.length(); i++) {
        c = rate.at(i);
        if (!isdigit(c)){
            continue;
        }
        temp = temp + c;
    }

    if (temp == "") {
        return 0;
    }
    return stoi(temp);
    
}

string parseSentiment(string sentiment) {


    // need to do a try catch case here
    if (sentiment.size() == 0) {
        return "null";
    }
    string temp = sentiment.substr(sentiment.length()-8, -1);
    
    // check the first character 
    //  -> positive/negative = length 8
    //  -> netural is length 7
    char check = temp.at(0);
    if (!isalpha(check)) {
        temp = temp.substr(1);
    }

    return temp;

}

string priceIntegrity(string price) {
    for (char c: price) {
        if (!isdigit(c)) {
            return "";
        }
    }
    return price;
}

