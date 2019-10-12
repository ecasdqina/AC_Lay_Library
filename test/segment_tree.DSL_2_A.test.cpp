#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "../data_structure/segment_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	segment_tree<int> seg(n, [](int a, int b) { return std::min(a, b); }, (1LL << 31) - 1);
	while(q--) {
		int type, x, y; scanf("%d%d%d", &type, &x, &y);

		if(type == 0) seg.change(x, y);
		else printf("%d\n", seg.fold(x, y + 1));
	}
	return 0;
}
