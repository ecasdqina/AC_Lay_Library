#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include <stdio.h>
#include "../data_structure/fenwick_tree.hpp"

int main() {
	struct node {
		using value_type = int;

		static int identity() { return 0; }
		static int operation(int a, int b) { return a + b; }
		static int inverse(int x) { return -x; }
	};
	
	int n, q; scanf("%d%d", &n, &q);
	fenwick_tree<node> tree(n);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) tree.update(x - 1, y);
		else printf("%d\n", tree.fold(x - 1, y));
	}
	return 0;
}
