#pragma once
#include "../ACL/segtree.hpp"
#include "../graph/graph-template.hpp"

template <typename T, class S, S (*Sop)(S, S), S (*Se)()>
struct HeavyLightDecomposition {
  // private:
  public:
    int root, eid;
    vector<int> sz, d, p, top, in, out;
    vector<T> x;
    WeightedFIDXEdges<T> c;
    atcoder::segtree<S, Sop, Se> seg;
    void dfs1(int v) {
      sz[v] = 1;
      for (auto &e: c[v]) {
        d[e.first] = d[v]+1;
        p[e.first] = v;
        dfs1(e.first);
        sz[v] += sz[e.first];
        if (sz[e.first] > sz[c[v][0].first]) swap(e, c[v][0]);
      }
    }
    void dfs2(int v) {
      in[v] = eid++;
      for (auto &[e, w]: c[v]) {
        top[e] = e == c[v][0].first ? top[v] : e;
        dfs2(e);
        x[e] = w;
      }
      out[v] = eid;
    }
  // public:
    HeavyLightDecomposition(WeightedFIDXEdges<T> g, int _root = 0)
      : c(g),
        root(_root),
        eid(0),
        sz(g.size(), 0),
        d(g.size(), 0),
        x(g.size(), 0),
        in(g.size(), -1),
        out(g.size(), -1),
        seg(atcoder::segtree<S, Sop, Se>(g.size()+1)),
        top(g.size(), root),
        p(g.size(), root) {
      dfs1(root);
      dfs2(root);
      // init_seg();
    }

    S query(int u, int v) {
      S r = Se();
      while (top[u] != top[v]) {
        if (d[top[u]] < d[top[v]]) swap(u, v);
        int st = top[u];
        r = Sop(r, seg.prod(in[st], in[u]));
        u = p[st];
      }
      if (d[u] > d[v]) swap(u, v);
      r = Sop(r, seg.prod(in[u], in[v]));
      return r;
    }
    
  /*
  
    required variable:

      size(of subtree), depth, parent, top(of chain), in/out(dfs ordering), child

    required function:

      dfs0: create child use input edges <- template_graph
      dfs1: define depth, parent, size => heavy-light-decomposition (exclude find top by O(1))
      dfs2: dfs ordering && define top
      lca: query(u, v) => u --> ? <-- v
      seg(in lca): use ACL template
  
  */
};