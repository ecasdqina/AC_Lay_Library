#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "../tree/segment_tree.hpp"

using i64 = long long;

int main() {
	int n, q; scanf("%d%d", &n, &q);

	segment_tree<i64> seg(n, [](i64 a, i64 b) { return a + b; }, 0);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) seg.update(x - 1, y);
		else printf("%d\n", seg.fold(x - 1, y));
	}
	return 0;
}
