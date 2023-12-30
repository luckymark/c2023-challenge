#include <bits/stdc++.h>

namespace tkz::b64 {

using byte = unsigned char;

// clang-format off
inline constexpr ::std::array<char, 64> to = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
};
// clang-format on

inline constexpr ::std::array<byte, 256> from = [] {
	::std::array<byte, 256> from;
	::std::ranges::fill(from, 255);
	for (byte i = 0; i < 64; ++i) {
		from[to[i]] = i;
	}
	return from;
}();

inline constexpr struct encode_fn {
	template <::std::input_iterator I, ::std::sentinel_for<I> S, ::std::output_iterator<char> O>
	  requires ::std::convertible_to<::std::iter_value_t<I>, byte>
	static constexpr void operator()(I b, S e, O o) {
		byte s[3];
		::std::size_t i = 0;
		while (b != e) {
			s[i++] = static_cast<byte>(*b++);
			if (i == 3) {
				*o++ = to[(s[0] & byte(0b11111100)) >> 2];
				*o++ = to[((s[0] & byte(0b00000011)) << 4) | ((s[1] & byte(0b11110000)) >> 4)];
				*o++ = to[((s[1] & byte(0b00001111)) << 2) | ((s[2] & byte(0b11000000)) >> 6)];
				*o++ = to[s[2] & byte(0b00111111)];
				i = 0;
			}
		}
		switch (i) {
			case 0:
				break;
			case 1:
				*o++ = to[(s[0] & byte(0b11111100)) >> 2];
				*o++ = to[(s[0] & byte(0b00000011)) << 4];
				*o++ = '=';
				*o++ = '=';
				break;
			case 2:
				*o++ = to[(s[0] & byte(0b11111100)) >> 2];
				*o++ = to[((s[0] & byte(0b00000011)) << 4) | ((s[1] & byte(0b11110000)) >> 4)];
				*o++ = to[(s[1] & byte(0b00001111)) << 2];
				*o++ = '=';
				break;
		}
	}

	template <::std::ranges::range R, ::std::output_iterator<char> O> static constexpr void operator()(R &&r, O o) {
		return operator()(::std::ranges::begin(r), ::std::ranges::end(r), ::std::move(o));
	}
} encode{};

inline constexpr struct decode_fn {
	template <::std::input_iterator I, ::std::sentinel_for<I> S, ::std::output_iterator<byte> O>
	  requires ::std::convertible_to<::std::iter_value_t<I>, char>
	static constexpr void operator()(I b, S e, O o) {
		char c[4];
		::std::size_t i = 0;
		while (b != e) {
			if ((c[i++] = static_cast<char>(*b++)) == '=') {
				--i;
				break;
			}
			if (i == 4) {
				*o++ = from[c[0]] << 2 | from[c[1]] >> 4;
				*o++ = from[c[1]] << 4 | from[c[2]] >> 2;
				*o++ = from[c[2]] << 6 | from[c[3]];
				i = 0;
			}
		}
		switch (i) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				*o++ = from[c[0]] << 2 | from[c[1]] >> 4;
				break;
			case 3:
				*o++ = from[c[0]] << 2 | from[c[1]] >> 4;
				*o++ = from[c[1]] << 4 | from[c[2]] >> 2;
				break;
		}
	}

	template <::std::ranges::range R, ::std::output_iterator<char> O> static constexpr void operator()(R &&r, O o) {
		return operator()(::std::ranges::begin(r), ::std::ranges::end(r), ::std::move(o));
	}
} decode{};

} // namespace tkz::b64

int main() {
	using namespace std;
	string r = "hello world!";
	cout << r << endl;
	string e;
	::tkz::b64::encode(r, back_inserter(e));
	cout << e << endl;
	string d;
	::tkz::b64::decode(e, back_inserter(d));
	cout << d << endl;
	return 0;
}