#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_E"

#include <stdio.h>
#include "../data_structure/lazy_segment_tree.hpp"

using i64 = long long;

int main() {
	int n, q; scanf("%d%d", &n, &q);

	auto f = [](i64 a, i64 b) { return a + b; };
	auto g = [](i64 a, i64 b, int l, int r) { return a + b * (i64)(r - l); };
	auto h = [](i64 a, i64 b) { return a + b; };
	lazy_segment_tree<i64> seg(n, f, g, h, 0, 0);
	
	while(q--) {
		int type; scanf("%d", &type);

		if(type == 0) {
			int s, t, x; scanf("%d%d%d", &s, &t, &x);

			seg.update(s - 1, t, x);
		} else if(type == 1) {
			int i; scanf("%d", &i);
			
			printf("%d\n", seg[i - 1]);
		}
	}

	return 0;
}
