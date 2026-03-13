/***
 * Name: Sangam Prajapati
 * Class: CSC3430 - Algorithm Design
 * Date: 03/12/2026
 * 
 * 0/1 Knapsack Problem - Dynamic programming approach
 */


 #include <iostream>
 #include <vector>
 #include <algorithm>


/**
 * struct representing items in the knapsack
 */
struct Item {
    int weight;             // weight of the item
    int value;              // profit/value gained from the item
};


int main() {

    /***
     * list of available items
     * each item is represented as {weight, value}
     */
    std::vector<Item> items = {{2, 12}, {1, 10}, {3, 20}, {2, 15}};

    int capacity = 5;               // max capacity of the knapsack
    int n = items.size();           // number of items


    /***
     * create the dynamic programming table
     * 
     * M[i][w] represents the maximum value 
     * obtained using the girst i tems with a knapsack capacity of w
     */
    std::vector<std::vector<int>> M(n + 1, std::vector<int>(capacity + 1, 0));

    // build the DP table using a bottom-up approach
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // if current item's weight exceed current capacity, dont include, copy from above
            if (items[i - 1].weight > w) {
                M[i][w] = M[i -1][w];
            }
            else {
                int exclude = M[i - 1][w];
                int include = items[i - 1].value + M[i - 1][w - items[i - 1].weight];
                M[i][w] = std::max(exclude, include);           // take maximum of the two values
            }
        }
    }

    std::cout << "Maximum value that can be obtained: " << M[n][capacity] << std::endl;
    std::cout << "\nSelected items:\n";
    int w = capacity;

    for (int i = n; i > 0; i--) {
        if(M[i][w] != M[i - 1][w]) {
            std::cout << "Item " << i
                      << " (weight = " << items[i - 1].weight 
                      << ", value = " << items[i - 1].value
                      << ")\n";
            w = w - items[i - 1].weight;        // reduce the remaining capacity by weight
        }
    }
    return 0;
}
