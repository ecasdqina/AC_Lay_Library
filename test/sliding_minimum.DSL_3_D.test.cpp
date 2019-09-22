#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <stdio.h>
#include "../data_structure/sliding_minimum.hpp"

int main() {
	int n, L; scanf("%d%d", &n, &L);
	sliding_minimum<int> sm(L);
	while(n--) {
		int x; scanf("%d", &x);

		sm.push(x);
	}

	for(int i = 0; i < sm.size(); i++) {
		if(i + 1 == sm.size()) printf("%d\n", sm[i]);
		else printf("%d ", sm[i]);
	}
	return 0;
}
