//
// Created by cz241 on 9/20/2023.
//

#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <iostream>

constexpr int DIGITS = 100000;
constexpr int ITERATION = 20;

int main() {
    using namespace ::std;
    using namespace ::boost::multiprecision;
    using F = number<cpp_bin_float<DIGITS>>;
    auto sqr = [](auto&& x) { return x * x; };
    F a = 1, b = 1 / sqrt(F(2)), t = 0.25, p = 1;
    for (int i = 1; i <= ITERATION; ++i) {
        F a_ = (a + b) / 2, b_ = sqrt(a * b), t_ = t - p * sqr(a - a_), p_ = 2 * p;
        a = a_; b = b_; t = t_; p = p_;
    }
    cout.precision(DIGITS);
    cout << sqr(a + b) / (4 * t) << '\n';
    return 0;
}