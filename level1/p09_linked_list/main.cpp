#include <iostream>

struct node {
	node* next;
	int value;
};

int main() {
	using namespace ::std;

	node* head = 
		new node {
			.next = new node {
				.next = new node {
					.next = new node {
						.next = nullptr,
						.value = 3,
					},
					.value = 5
				},
				.value = 2,
			},
			.value = 1,
		};

	// display
	for (auto curr = head; curr; curr = curr->next) {
		cout << curr << ": " << curr->value << '\n';
	}

	// reverse
	{
		auto p = head;
		auto q = p->next;
		p->next = nullptr;
		while (q) {
			auto r = q->next;
			q->next = p;
			p = q;
			q = r;
		}
		head = p;
	}

	// display again
	for (auto curr = head; curr; curr = curr->next) {
		cout << curr << ": " << curr->value << '\n';
	}

	auto find = [](node* p, int value) -> node* {
		for (; p; p = p->next) {
			if (p->value == value) {
				return p;
			}
		}
		return nullptr;
	};
	auto f1 = find(head, 5);
	cout << f1 << ": " << (f1 ? f1->value : -1) << '\n';
	auto f2 = find(f1 ? f1->next : nullptr, 5);
	cout << f2 << ": " << (f2 ? f2->value : -1) << '\n';

	return 0;
}