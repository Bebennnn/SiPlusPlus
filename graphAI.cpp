#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <algorithm> // Added for reverse function
using namespace std;

// Node structure representing a building
struct Node {
    int id;
    string name;
};

// Edge structure representing a road between buildings
struct Edge {
    int destination;
    int weight; // distance
};

class Graph {
private:
    unordered_map<int, vector<Edge>> adjacencyList; // Adjacency list representation
    unordered_map<int, string> buildingNames;       // Mapping building ID to names

public:
    // Add a building to the graph
    void addBuilding(int id, string name) {
        buildingNames[id] = name;
        adjacencyList[id] = vector<Edge>();
    }

    // Add a road (edge) between two buildings
    void addRoad(int from, int to, int distance) {
        if (buildingNames.find(from) != buildingNames.end() &&
            buildingNames.find(to) != buildingNames.end()) {
            adjacencyList[from].push_back({to, distance});
            adjacencyList[to].push_back({from, distance}); // Undirected graph
        } else {
            cout << "Error: One or both buildings do not exist.\n";
        }
    }

    // Display the adjacency list (graph representation)
    void displayGraph() {
        for (auto &[id, edges] : adjacencyList) {
            cout << "Building " << id << " (" << buildingNames[id] << "):\n";
            for (auto &edge : edges) {
                cout << "  -> " << edge.destination << " (" << buildingNames[edge.destination]
                     << ", Distance: " << edge.weight << ")\n";
            }
            cout << endl;
        }
    }

    // Retrieve building name by ID
    string getBuildingName(int id) {
        return buildingNames[id];
    }

    // Dijkstra's algorithm to find the shortest path
    vector<int> findShortestPath(int start, int end) {
        unordered_map<int, int> distances;
        unordered_map<int, int> previous;
        for (auto &[id, _] : adjacencyList) {
            distances[id] = INT_MAX;
        }
        distances[start] = 0;

        auto cmp = [&](int a, int b) { return distances[a] > distances[b]; };
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
        pq.push(start);

        while (!pq.empty()) {
            int current = pq.top();
            pq.pop();

            for (auto &edge : adjacencyList[current]) {
                int neighbor = edge.destination;
                int newDist = distances[current] + edge.weight;

                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    previous[neighbor] = current;
                    pq.push(neighbor);
                }
            }
        }

        // Check if there's a path to the destination
        if (distances[end] == INT_MAX) {
            cout << "No path found from " << getBuildingName(start) << " to " << getBuildingName(end) << ".\n";
            return {};
        }

        // Reconstruct the path
        vector<int> path;
        for (int at = end; at != start; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    Graph campus;

    // Add buildings
    campus.addBuilding(1, "Telkom University Landmark Tower");
    campus.addBuilding(37, "Masjid Syamsul Ulum");
    campus.addBuilding(2, "Kantin TULT");
    campus.addBuilding(3, "Asrama Putra");

    // Add roads (edges)
    campus.addRoad(1, 2, 5);
    campus.addRoad(2, 3, 10);
    campus.addRoad(3, 37, 7);

    // Display the graph
    cout << "Campus Map (Adjacency List):\n";
    campus.displayGraph();

    // Find the shortest path
    int start = 37;
    int end = 1;
    vector<int> path = campus.findShortestPath(start, end);

    // Display the shortest path
    if (!path.empty()) {
        cout << "\nShortest Path from " << campus.getBuildingName(start) << " to "
             << campus.getBuildingName(end) << ":\n";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << " (" << campus.getBuildingName(path[i]) << ")";
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    return 0;
}

