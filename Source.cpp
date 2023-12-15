#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
struct Graph {
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) : V(v), E(e) {}
};

// Функция для сравнения ребер по их весу
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Алгоритм Прима-Краскала
void primMST(Graph& graph) {
    vector<Edge> result;
    vector<int> parent(graph.V, -1);
    vector<int> key(graph.V, INT_MAX);
    vector<bool> inMST(graph.V, false);

    key[0] = 0;

    for (int count = 0; count < graph.V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < graph.V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        inMST[u] = true;

        for (const Edge& edge : graph.edges) {
            if (edge.src == u && !inMST[edge.dest] && edge.weight < key[edge.dest]) {
                parent[edge.dest] = u;
                key[edge.dest] = edge.weight;
            }
        }
    }

    int minWeight = 0;
    for (int i = 1; i < graph.V; ++i) {
        result.push_back({ parent[i], i, key[i] });
        minWeight += key[i];
    }

    cout << "Minimum spanning tree (Prima-Cruscala):\n"; //Минимальное остовное дерево 
    for (const Edge& edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << "\n";
    }

    cout << "Minimum spanning tree length: " << minWeight << "\n"; //Длина минимального остовного дерева
}

// Алгоритм Дейкстры
void dijkstra(Graph& graph, int start) {
    vector<int> dist(graph.V, INT_MAX);
    dist[start] = 0;

    for (int count = 0; count < graph.V - 1; ++count) {
        int u = -1;
        for (int v = 0; v < graph.V; ++v) {
            if (dist[v] != INT_MAX && (u == -1 || dist[v] < dist[u]))
                u = v;
        }

        for (const Edge& edge : graph.edges) {
            if (edge.src == u && dist[u] != INT_MAX && dist[u] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[u] + edge.weight;
            }
        }
    }

    cout << "Shortest distances from the top " << start << " (Dijkstra's algorithm): \n"; //Кратчайшие расстояния от вершины 
    for (int i = 0; i < graph.V; ++i) {
        cout << "To the top" << i << ": " << dist[i] << "\n"; //До вершины
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges of the graph: "; //Введите количество вершин и ребер графа
    cin >> V >> E;

    Graph graph(V, E);

    cout << "Enter the graph edges (src dest weight):\n"; //Введите ребра графа 
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.edges.push_back({ src, dest, weight });
    }

    sort(graph.edges.begin(), graph.edges.end(), compareEdges);

    primMST(graph);

    int startVertex;
    cout << "Enter the starting vertex for Dijkstra's algorithm:: "; //Введите начальную вершину для алгоритма Дейкстры: 
    cin >> startVertex;
    dijkstra(graph, startVertex);

    return 0;
}