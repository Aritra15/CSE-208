#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()

class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj;

    Graph(int V) : V(V), adj(V) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w); // For bidirectional graph
    }

    vector<int> bidirectionalDijkstra(int src, int target);
};

vector<int> Graph::bidirectionalDijkstra(int src, int target) {
    vector<int> df(V, INF);
    vector<int> db(V, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Qf; // Forward queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Qb; // Backward queue

    df[src] = 0;
    db[target] = 0;

    Qf.push({0, src});
    Qb.push({0, target});

    int mu = INF; // Initialize mu to infinity

    while (!Qf.empty() && !Qb.empty()) {
        int u = Qf.top().second;
        Qf.pop();

        int v = Qb.top().second;
        Qb.pop();

        for (const auto& neighbor : adj[u]) {
            int x = neighbor.first;
            int weight = neighbor.second;

            // Relaxation
            if (df[u] + weight < df[x]) {
                df[x] = df[u] + weight;
                Qf.push({df[x], x});
            }

            // Check for intersection
            if (db[x] != INF && df[x]  + db[x] < mu) {
                mu = df[x]  + db[x];
            }
        }

        for (const auto& neighbor : adj[v]) {
            int x = neighbor.first;
            int weight = neighbor.second;

            // Relaxation
            if (db[v] + weight < db[x]) {
                db[x] = db[v] + weight;
                Qb.push({db[x], x});
            }

            // Check for intersection
            if (df[x] != INF && df[x]  + db[x] < mu) {
                mu = df[x]  + db[x];
            }
        }

        // Check if the true distance is found
        if (df[u] + db[v] >= mu) {
            break;
        }
    }

    return df; // Return the distances from the source
}

int main() {
    int V ;
    cin>>V;
    Graph g(V);

    int E;
    cin>>E;
    for(int i=0;i<E;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.addEdge(u-1,v-1,w);
    }

    int src;
    int target;
    cin>>src>>target;

    vector<int> result = g.bidirectionalDijkstra(src-1, target-1);
    for (int i = 0; i < V; ++i) {
        cout << "Shortest distance from " << src-1 << " to " << i << " is: " << result[i] << endl;
    }

    return 0;
}
