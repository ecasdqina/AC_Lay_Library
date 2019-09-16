#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C"

#include "../tree/lowest_common_ancestor_doubling.hpp"
#include <stdio.h>

int main() {
	int n; scanf("%d", &n);
	lowest_common_ancestor lca(n);
	for(int i = 0; i < n; i++) {
		int k; scanf("%d", &k);

		while(k--) {
			int p; scanf("%d", &p);

			lca.add_edge(i, p);
		}
	}

	int q; scanf("%d", &q);
	while(q--) {
		int x, y; scanf("%d%d", &x, &y);

		printf("%d\n", lca.query(x, y));
	}
}
