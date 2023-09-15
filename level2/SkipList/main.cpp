#include <memory>
#include <vector>
#include <random>
#include <string_view>
#include <optional>
#include <iostream>

template <
	::std::totally_ordered K,
	typename M,
	double P = 0.5
>
	requires (0.0 < P && P < 1.0)
struct skip_list {
	using key_type = K;
	using mapped_type = M;
	using value_type = ::std::pair<key_type const, mapped_type>;
	static inline auto dist = ::std::bernoulli_distribution(P);

	struct node {
		value_type value;
		::std::vector<::std::shared_ptr<node>> next;

		node(value_type value, ::std::size_t level):
			value(::std::move(value)), next(level) { }

		key_type const& key() const { return value.first; }
		mapped_type& mapped() { return value.second; }
		mapped_type const& mapped() const { return value.second; }
	};

	::std::default_random_engine eng;
	::std::vector<::std::shared_ptr<node>> head;

	skip_list(::std::size_t max_level):
		head(max_level) {}

	::std::size_t random_level() {
		::std::size_t level = 1;
		while (level < head.size() && dist(eng))
			++level;
		return level;
	}

	::std::shared_ptr<node> find_node(key_type const& key) {
		::std::size_t level = head.size();
		::std::shared_ptr<node> p;
		while (level-- > 0) {
			if (auto q = head[level]; q && q->key() < key) {
				p = q;
				break;
			}
		}
		if (!p) return nullptr;
		while (level-- > 0) {
			auto q = p->next[level];
			while (q && q->key() < key) {
				p = q;
				q = q->next[level];
			}
		}
		auto q = p->next[0];
		if (q->key() == key) return q;
		else return nullptr;
	}

	void insert(value_type v) {
		auto x = ::std::make_shared<node>(::std::move(v), random_level());
		::std::size_t level = x->next.size();
		::std::shared_ptr<node> p;
		while (level-- > 0) {
			if (!p) {
				if (!head[level]) {
					head[level] = x;
					continue;
				}
				auto q = head[level];
				if (!(q->key() < x->key())) {
					head[level] = x;
					x->next[level] = q;
					continue;
				}
				p = q;
			}
			auto q = p->next[level];
			while (q && q->key() < x->key()) {
				p = q;
				q = q->next[level];
			}
			p->next[level] = x;
			x->next[level] = q;
		}
	}

	void remove(key_type const& key) {
		::std::size_t level = head.size();
		::std::shared_ptr<node> p;
		while (level-- > 0) {
			if (!p) {
				auto q = head[level];
				if (!q || q->key() > key) {
					continue;
				}
				else if (q->key() == key) {
					head[level] = q->next[level];
					continue;
				}
				else {
					p = q;
				}
			}
			auto q = p->next[level];
			while (q && q->key() < key) {
				p = q;
				q = q->next[level];
			}
			if (q && q->key() == key) {
				p->next[level] = q->next[level];
			}
		}
	}
};

int main() {
	using namespace std;
	skip_list<int, int> l(5);
	l.insert({1, 2});
	l.insert({3, 5});
	l.insert({2, 3});
	cout << l.find_node(2) << '\n';
	l.remove(2);
	cout << l.find_node(2) << '\n';
	l.insert({2, 4});
	cout << l.find_node(2) << '\n';
	return 0;
}