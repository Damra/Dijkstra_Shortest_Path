#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

class Graph {
    int V; // Düğüm sayısı
    vector<vector<pii>> adj; // Komşuluk listesi

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Yönlü olmayan graf için
    }

    void dijkstra(int src, int dest) {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<int> dist(V, INT_MAX);
        vector<int> parent(V, -1);

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto &[v, weight] : adj[u]) {
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                    parent[v] = u;
                }
            }
        }

        cout << "En kısa yol uzunluğu: " << dist[dest] << endl;
        cout << "Yol: ";
        printPath(parent, dest);
        cout << endl;
    }

    void printPath(vector<int> &parent, int j) {
        if (parent[j] == -1)
            return;
        printPath(parent, parent[j]);
        cout << j << " ";
    }
};

int main() {
    int V = 9;
    Graph g(V);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    int src = 0;
    int dest = 4;
    g.dijkstra(src, dest);

    return 0;
}