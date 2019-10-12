#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_F"

#include <stdio.h>
#include "../data_structure/lazy_segment_tree.hpp"

int main() {
	int n, q; scanf("%d%d", &n, &q);

	auto f = [](int a, int b) { return std::min(a, b); };
	auto g = [](int a, int b, int l, int r) { return b; };
	auto h = [](int a, int b) { return b; };
	lazy_segment_tree<int> seg(n, f, g, h, (1LL << 31) - 1, -1);
	
	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int s, t, x; scanf("%d%d%d", &s, &t, &x);

			seg.update(s, t + 1, x);
		} else if(type == 1) {
			int s, t; scanf("%d%d", &s, &t);
			
			printf("%d\n", seg.fold(s, t + 1));
		}
	}

	return 0;
}
