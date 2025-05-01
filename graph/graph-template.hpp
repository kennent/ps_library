#pragma once

template <typename T = int>
struct Edge {
  int from, to;
  T cost;
  
  Edge(int _to, T _cost = 1): from(-1), to(_to), cost(_cost) {} // from is array index
  Edge(int _from, int _to, T _cost): from(_from), to(_to), cost(_cost) {} // only edge save, ex) use in prim

  Edge &operator= (const int &x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};

template <typename T>
using WeightedEdges = vector<Edge<T>>;
template <typename T>
using WeightedFIDXEdges = vector<vector<pair<int, T>>>;
using UnweightedEdges = vector<vector<int>>;

template <typename T>
pair<WeightedEdges<T>, WeightedFIDXEdges<T>> w_fidx_graph(int n, int m = -1, bool is_directed = false, bool is_1idx = true) {
  WeightedEdges<T> wg;
  WeightedFIDXEdges<T> g(n), c(n);
  if (m == -1) m = n-1;
  while (m--) {
    int u, v;
    T w;
    cin >> u >> v >> w;
    if (is_1idx) u--, v--;
    wg.emplace_back(u, v, w);
    g[u].push_back({v, w});
    if (!is_directed) g[v].push_back({u, w});
  }
  queue<pair<int,int>> q;
  q.push({0, -1});
  while (q.size()) {
    auto [v, pv] = q.front();
    q.pop();
    for (auto &[e, w]: g[v]) {
      if (e != pv) {
        c[v].emplace_back(e, w);
        q.push({e, v});
      }
    }
  }
  return {wg, c};
}