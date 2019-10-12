#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_I"

#include <stdio.h>
#include "../data_structure/lazy_segment_tree.hpp"

using i64 = long long;

int main() {
	int n, q; scanf("%d%d", &n, &q);

	auto f = [](i64 a, i64 b) { return a + b; };
	auto g = [](i64 a, i64 b, int l, int r) { return b * (i64)(r - l); };
	auto h = [](i64 a, i64 b) { return b; };
	lazy_segment_tree<i64> seg(n, f, g, h, 0, 1 << 30);
	
	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int s, t, x; scanf("%d%d%d", &s, &t, &x);

			seg.update(s, t + 1, x);
		} else if(type == 1) {
			int s, t; scanf("%d%d", &s, &t);
			
			printf("%lld\n", seg.fold(s, t + 1));
		}
	}

	return 0;
}
