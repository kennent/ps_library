#include "./template/template.hpp"
#include "./template/fast-IO.hpp"
#include "./graph/graph-template.hpp"
#include "./tree/heavy-light-decomposition.hpp"

using namespace kENN3N;

int n, m;
struct S {
  bool check;
  ll lsum, rsum, msum, sum, len;
  S(ll x = 0, ll c = false) { lsum = rsum = msum = sum = x; len = check = c; }
  S(ll lsum, ll rsum, ll msum, ll sum, ll len): lsum(lsum), rsum(rsum), msum(msum), sum(sum), len(len) {
    check = true;
  }
};
using F = ll;
const F ID = 11111;
S op(S a, S b) {
  if (!a.check || !b.check) {
    if (!a.check && !b.check) return S();
    if (!a.check) return b;
    else if (!b.check) return a;
  }
  ll lsum = max(a.lsum, a.sum+b.lsum);
  ll rsum = max(b.rsum, a.rsum+b.sum);
  ll msum = max({a.msum, b.msum, lsum, rsum, a.rsum+b.lsum});
  ll sum = a.sum+b.sum;
  return S(lsum, rsum, msum, sum, a.len+b.len);
}
S e() { return S(); }
S mapping(F f, S x) {
  if (f == ID) return x;
  ll r = f*x.len;
  return S(r, r, r, r, x.len);
}
F composition(F f, F g) { return (f == ID ? g : f); }
F id() { return ID; }
vector<int> v;

void kENN3N::solve() {
  fastIO();

  cin >> n;
  v = vector<int>(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  auto [wg, g] = w_fidx_graph<int>(n);
  LazyHeavyLightDecomposition<int, S, op, e, F, mapping, composition, id> hld(g);
  for (int i = 0; i < n; i++) hld.seg.set(hld.in[i], S(v[i], true));

  cin >> m;
  while (m--) {
    int t, u, v, w;
    cin >> t >> u >> v;
    u--, v--;
    if (t == 1) {
      if (hld.in[u] > hld.in[v]) swap(u, v);
      auto r = hld.query(u, v);
      cout << max(0LL, r.msum) << "\n";
    } else {
      cin >> w;
      hld.apply(u, v, w);
    }
  }
}