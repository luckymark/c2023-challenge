#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>
#include <iomanip>

constexpr int DIGITS = 100000;
constexpr int ITERATION = 20;

inline constexpr auto sqr(auto&& x) { return x * x; }

// https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm
template <int DIGITS, int ITERATION>
auto Gauss_Legendre() {
	using namespace ::boost::multiprecision;
	using F = number<cpp_bin_float<DIGITS>>;
	F a = 1,
	  b = 1 / sqrt(F(2)),
	  t = 0.25,
	  p = 1;
	for (int i = 1; i <= ITERATION; ++i) {
		F a_ = (a + b) / 2,
		  b_ = sqrt(a * b),
		  t_ = t - p * sqr(a - a_),
		  p_ = 2 * p;
		a = a_; b = b_; t = t_; p = p_;
	}
	return sqr(a + b) / (4 * t);
}

int main() {
	using namespace ::std;
	cout << setprecision(DIGITS) << Gauss_Legendre<DIGITS, ITERATION>() << '\n';
	return 0;
}