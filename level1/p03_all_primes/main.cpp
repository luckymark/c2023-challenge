#include <iostream>
#include <vector>
#include <chrono>

// O(n)
std::vector<unsigned> sieve(unsigned n) {
	std::vector<bool> v(n + 1);
	std::vector<unsigned> ps;

	for (unsigned i = 2; i <= n; ++i) {
		if (!v[i]) ps.push_back(i);
		for (unsigned p : ps) {
			if (i * p > n) break;
			v[i * p] = true;
			if (i % p == 0) break;
		}
	}

	return ps;
}

int main() {
	using namespace std;
	using namespace chrono;

	auto start = chrono::steady_clock::now();
	auto primes = sieve(1000);
	auto end = chrono::steady_clock::now();

	for (unsigned p : primes) cout << p << ' ';
	cout << endl;
	cout << "Time cost for the calculation: " << (end - start) << endl;

	return 0;
}