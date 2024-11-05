#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Structure to represent a city with x and y coordinates
struct City {
    double x, y;
};

// Function to calculate Euclidean distance between two cities
double distance(const City& a, const City& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Function to calculate the total distance of the current tour (solution)
double calculateTotalDistance(const vector<int>& tour, const vector<City>& cities) {
    double totalDistance = 0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        totalDistance += distance(cities[tour[i]], cities[tour[i + 1]]);
    }
    totalDistance += distance(cities[tour.back()], cities[tour.front()]); // Return to the starting city
    return totalDistance;
}

// Simulated Annealing algorithm
vector<int> simulatedAnnealing(const vector<City>& cities, int maxIterations) {
    int n = cities.size();
    vector<int> currentSolution(n);
    vector<int> bestSolution(n);

    // Initialize current solution as a random permutation of city indices
    for (int i = 0; i < n; i++) {
        currentSolution[i] = i;
    }
    random_shuffle(currentSolution.begin(), currentSolution.end());
    bestSolution = currentSolution;

    double currentCost = calculateTotalDistance(currentSolution, cities);
    double bestCost = currentCost;
    
    double temperature = 10000.0;
    double coolingRate = 0.999;

    for (int iter = 0; iter < maxIterations; iter++) {
        // Generate a neighbor solution by swapping two random cities
        vector<int> newSolution = currentSolution;
        int city1 = rand() % n;
        int city2 = rand() % n;
        swap(newSolution[city1], newSolution[city2]);

        double newCost = calculateTotalDistance(newSolution, cities);

        // Accept the new solution if it's better, or with a probability based on temperature
        if (newCost < currentCost || exp((currentCost - newCost) / temperature) > ((double)rand() / RAND_MAX)) {
            currentSolution = newSolution;
            currentCost = newCost;

            // Update the best solution found so far
            if (currentCost < bestCost) {
                bestSolution = currentSolution;
                bestCost = currentCost;
            }
        }

        // Decrease the temperature
        temperature *= coolingRate;
    }

    cout << "Final achieved cost: " << bestCost << endl;
    return bestSolution;
}

// Main function
int main() {
    srand(time(NULL));

    // Define a set of cities (example dataset)
    vector<City> cities = {
        {60, 200}, {180, 200}, {80, 180}, {140, 180}, {20, 160}, 
        {100, 160}, {200, 160}, {140, 140}, {40, 120}, {100, 120}, 
        {180, 100}, {60, 80}, {120, 80}, {180, 60}, {20, 40}, 
        {100, 40}, {200, 40}, {20, 20}, {60, 20}, {160, 20}
    };

    int maxIterations = 10000; // Set the maximum number of iterations

    // Perform Simulated Annealing to solve the TSP
    vector<int> bestSolution = simulatedAnnealing(cities, maxIterations);

    // Output the best solution found
    cout << "Best solution (tour):" << endl;
    for (int city : bestSolution) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}
