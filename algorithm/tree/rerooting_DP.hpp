#include <vector>
#include <map>

void solve() {
	std::vector<std::vector<int>> g;

	using value = int;
	std::vector<std::map<int, value>> dp(g.size());
	auto solve = [&](auto&& solve, int v, int par, bool flag) -> value {
		if(dp[v].count(par)) return dp[v][par];

		value val = value();
		if(flag or par == -1) {
			for(auto e: g[v]) {
				if(e == par) continue;

				val = val + solve(solve, e, v, flag);
			}
		} else {
			value parent_val = solve(solve, par, v, flag);
			value around_val = solve(solve, v, -1, flag);
			
			val = around_val - parent_val;
		}

		return dp[v][par] = val;
	};
	solve(solve, 0, -1, 1);

	for(int v = 0; v < g.size(); v++) solve(solve, v, -1, 0);
}

// description
// https://scrapbox.io/ecasdqina-compro/%E5%85%A8%E6%96%B9%E4%BD%8D%E6%9C%A8_DP

// verify
// https://atcoder.jp/contests/s8pc-4/submissions/7449326
// https://yukicoder.me/submissions/377951
