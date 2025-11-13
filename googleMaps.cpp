#include <bits/stdc++.h>

using namespace std;

const int NUM_CITIES = 6;

const string cities[NUM_CITIES] = {
    "Mumbai", "Delhi", "Jaipur", "Kolkata", "Chennai", "Bengaluru"
};

const int INF = numeric_limits<int>::max();


int getCityIndex(string cityName) {
    for (int i = 0; i < NUM_CITIES; i++) {
        if (cities[i] == cityName) {
            return i;
        }
    }
    return -1; 
}

int findMinDistanceNode(int dist[], bool visited[]) {
    int minDistance = INF;
    int minIndex = -1;

    for (int i = 0; i < NUM_CITIES; i++) {
        if (!visited[i] && dist[i] < minDistance) {
            minDistance = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void printPath(int prev[], int destIndex) {
    vector<string> path;
    int currentIndex = destIndex;

    while (currentIndex != -1) {
        path.push_back(cities[currentIndex]);
        currentIndex = prev[currentIndex];
    }

    reverse(path.begin(), path.end());

    cout << "Path:  ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}


void dijkstra(int graph[NUM_CITIES][NUM_CITIES], string srcCity, string destCity) {
    int srcIndex = getCityIndex(srcCity);
    int destIndex = getCityIndex(destCity);

    int dist[NUM_CITIES];
    bool visited[NUM_CITIES];
    int prev[NUM_CITIES];

    for (int i = 0; i < NUM_CITIES; i++) {
        dist[i] = INF;
        visited[i] = false;
        prev[i] = -1;
    }

    dist[srcIndex] = 0;

    for (int count = 0; count < NUM_CITIES - 1; count++) {
        int u = findMinDistanceNode(dist, visited);

        if (u == -1) {
            break;
        }
        
        visited[u] = true;
        
        if (u == destIndex) {
            break;
        }

        for (int v = 0; v < NUM_CITIES; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF && 
                (dist[u] + graph[u][v] < dist[v])) 
            {
                dist[v] = dist[u] + graph[u][v]; 
                prev[v] = u; 
            }
        }
    }

    cout << "\n--- Results ---" << endl;
    if (dist[destIndex] == INF) {
        cout << "No path found from " << srcCity << " to " << destCity << "." << endl;
    } else {
        cout << "Destination: " << destCity << endl;
        cout << "Distance:  " << dist[destIndex] << " km" << endl;
        printPath(prev, destIndex);
    }
}


int main() {
    int graph[NUM_CITIES][NUM_CITIES] = {
      // M(0)  D(1)   J(2)   K(3)   C(4)   B(5)
        {0,   1400,   950,     0,   1350,  1000}, // 0: Mumbai
        {1400,   0,   270,   1500,    0,   2150}, // 1: Delhi
        {950,   270,    0,   1600,  2100,  2000}, // 2: Jaipur
        {0,    1500,  1600,    0,   1650,  1900}, // 3: Kolkata
        {1350,   0,   2100,  1650,    0,   350}, // 4: Chennai
        {1000, 2150,  2000,  1900,   350,    0}  // 5: Bengaluru
    };
    
    for (int i = 0; i < NUM_CITIES; i++) {
        for (int j = 0; j < NUM_CITIES; j++) {
            if (i != j && graph[i][j] == 0) {
                graph[i][j] = INF;
            }
        }
    }

    cout << "Welcome to the Dijkstra's Pathfinding App!" << endl;
    cout << "Available cities:" << endl;
    for (int i = 0; i < NUM_CITIES; i++) {
        cout << " - " << cities[i] << endl;
    }

    string startCity, endCity;

    while (true) {
        cout << "\nEnter your starting city: ";
        getline(cin, startCity);
        if (getCityIndex(startCity) != -1) {
            break;
        }
        cout << "Invalid city name. Please choose from the list." << endl;
    }

    while (true) {
        cout << "Enter your destination city: ";
        getline(cin, endCity);
        if (getCityIndex(endCity) != -1) {
            break;
        }
        cout << "Invalid city name. Please choose from the list." << endl;
    }

    dijkstra(graph, startCity, endCity);

    return 0;
}