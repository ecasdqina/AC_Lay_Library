#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "AC_Lay_Library/tree/union_find_tree.cpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	union_find_tree uf(n);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) uf.unite(x, y);
		else printf("%d\n", uf.same(x, y));
	}
}
