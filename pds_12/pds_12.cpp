#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include <stack>
#include <list>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MAX_VERTICES = 100;

list<pair<int, int>> graph[MAX_VERTICES];  

void dijkstra(int start, int n, int dist[], int prev[]) {
    bool visited[MAX_VERTICES] = { false };
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    priority_queue<pair<int, int>, deque<pair<int, int>>, greater<>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.first; 
            int weight = edge.second;  

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({ dist[v], v });
            }
        }
    }
}

void printShortestPath(int start, int end, int prev[]) {
    if (prev[end] == -1) {
        cout << "No path exists from " << start + 1 << " to " << end + 1 << endl;
        return;
    }

    stack<int> path;
    for (int v = end; v != -1; v = prev[v]) {
        path.push(v);
    }

    cout << "Shortest path from " << start + 1 << " to " << end + 1 << ": ";
    while (!path.empty()) {
        cout << (path.top() + 1) << " ";
        path.pop();
    }
    cout << endl;
}

int main() {
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        inputFile >> u >> v >> w;
        u--; v--;  
        graph[u].push_back({ v, w });
    }

    inputFile.close();

    char choice;
    do {
        cout << "Choose an option:\n1. Find shortest path between two vertices\n2. Find shortest path from a vertex to all other vertices\nEnter choice: ";
        cin >> choice;

        int dist[MAX_VERTICES], prev[MAX_VERTICES];

        if (choice == '1') {
            int start, end;
            cout << "Enter start vertex: ";
            cin >> start;
            cout << "Enter end vertex: ";
            cin >> end;
            start--; end--;  

            dijkstra(start, n, dist, prev);

            if (dist[end] == INF) {
                cout << "No path exists from " << start + 1 << " to " << end + 1 << endl;
            }
            else {
                cout << "Shortest distance from " << start + 1 << " to " << end + 1 << " is: " << dist[end] << endl;
                printShortestPath(start, end, prev);
            }
        }
        else if (choice == '2') {
            int start;
            cout << "Enter start vertex: ";
            cin >> start;
            start--; 

            dijkstra(start, n, dist, prev);

            cout << "Shortest distances from vertex " << start + 1 << " to all other vertices:\n";
            for (int i = 0; i < n; i++) {
                if (dist[i] == INF) {
                    cout << "Vertex " << i + 1 << ": INF\n";
                }
                else {
                    cout << "Vertex " << i + 1 << ": " << dist[i] << endl;
                }
            }
        }
        else {
            cout << "Invalid choice!" << endl;
        }

        cout << "Do you want to perform another operation? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}