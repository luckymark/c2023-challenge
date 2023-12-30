#include <iostream>

bool is_prime(unsigned n) {
	if (n == 0 || n == 1) return false;
	for (unsigned i = 2; i * i <= n; ++i)
		if (n % i == 0) return false;
	return true;
}

int main() {
	using namespace std;

	unsigned n;
	cin >> n;
	cout << n << ' ' << (is_prime(n) ? "is" : "is not") << ' ' << "prime." << endl;

	return 0;
}