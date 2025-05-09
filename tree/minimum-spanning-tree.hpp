#pragma once
#include "../ACL/dsu.hpp"

template <typename T>
struct MinimumSpanningTree {
  // public:
    MinimumSpanningTree(int _n, int _m, bool idx1 = true)
      : n(_n),
        sum(0),
        v(_m),
        adjg(_n) {
      vector<Data> _v(_m);
      atcoder::dsu dsu(n);
      int cnt = 0;
      for (int i = 0; i < v.size(); i++) {
        cin >> v[i].u >> v[i].v >> v[i].w;
        if (idx1) v[i].u--, v[i].v--;
        _v[i] = v[i];
      }
      sort(_v.begin(), _v.end(), [] (Data a, Data b) {
        return a.w < b.w;
      });
      for (auto e: _v) {
        if (!dsu.same(e.u, e.v)) {
          dsu.merge(e.u, e.v);
          sum += e.w;
          g.push_back(e);
          adjg[e.u].push_back({e.v, e.w});
          adjg[e.v].push_back({e.u, e.w});
        } else ng.push_back(e);
      }
    }
  // private:
    int n;
    long long sum;
    struct Data {
      int u, v;
      T w;
    };
    vector<Data> v, g, ng;
    vector<vector<pair<int, T>>> adjg;
};