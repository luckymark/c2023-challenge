#include <cstdio>
#include <vector>

int main() {
	using namespace std;

	constexpr int n = 100;
	vector<bool> v(n + 1);
	vector<int> ps;
	for (int i = 2; i <= n; ++i) {
		if (!v[i]) ps.push_back(i);
		for (int p : ps) {
			if (i * p > n) break;
			v[i * p] = true;
			if (i % p == 0) break;
		}
	}
	for (int i = 4; i <= n; i += 2) {
		for (int p : ps) {
			if (!v[i - p]) {
				printf("%d = %d + %d\n", i, p, i - p);
				break;
			}
		}
	}

	return 0;
}