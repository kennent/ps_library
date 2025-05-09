#include "./template/template.hpp"
#include "./template/fast-IO.hpp"
#include "./tree/minimum-spanning-tree.hpp"
#include "./tree/heavy-light-decomposition.hpp"

using namespace kENN3N;

int n, m;
const ll MAX = 1'234'567'890;
struct S {
  int x, y;
};
S op (S a, S b) {
  if (a.x < b.x) return {a.x, min(a.y, b.x)};
  else if (a.x > b.x) return {b.x, min(a.x, b.y)};
  else return {a.x, min(a.y, b.y)};
}
S e() { return {MAX, MAX}; }
ll r = MAX*100;

void kENN3N::solve() {
  fastIO();
  cin >> n >> m;
  MinimumSpanningTree<int> mst(n, m);

  if (mst.g.size()+1 != n) {
    cout << -1;
    return;
  }

  LazyHeavyLightDecomposition<int, S, op, e, S, op, op, e> hld(mst.adjg);
  for (int i = 0; i < n; i++) hld.seg.set(i, {MAX, MAX});
  for (auto e: mst.ng) hld.apply(e.u, e.v, {e.w, MAX});
  for (auto e: mst.v) {
    bool isfind = false;
    for (auto ee: mst.adjg[e.u]) if (ee.first == e.v && ee.second == e.w) isfind = true;
    if (isfind) {
      S x = (hld.p[e.u] == e.v ? hld.seg.get(hld.in[e.u]) : hld.seg.get(hld.in[e.v]));
      if (x.x != MAX && x.x != e.w) r = min(r, mst.sum+x.x-e.w);
      else if (x.y != MAX) r = min(r, mst.sum+x.y-e.w);
    }
  }
  if (r != MAX*100) cout << r;
  else cout << -1;
}