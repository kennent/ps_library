#include "./template/template.hpp"
#include "./template/fast-IO.hpp"
#include "./ACL/segtree.hpp"
#include "./tree/heavy-light-decomposition.hpp"

using namespace kENN3N;

int n, m;
using S = int;
S op(S a, S b) { return max(a, b); }
S e() { return 0; }

void kENN3N::solve() {
  fastIO();
  cin >> n;
  auto [wg, g] = w_fidx_graph<int>(n);
  HeavyLightDecomposition<int, S, op, e> hld(g);
  for (int i = 0; i < n; i++) hld.seg.set(hld.in[i], hld.x[i]);

  cin >> m;
  while (m--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (t == 1) {
      auto x = wg[a-1];
      if (hld.p[x.from] == x.to) hld.seg.set(hld.in[x.from], hld.x[x.from] = b);
      else hld.seg.set(hld.in[x.to], hld.x[x.to] = b);
    } else cout << hld.query(a-1, b-1) << "\n";
  }
}