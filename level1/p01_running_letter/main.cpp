#include <cstdio>
#include <thread>
#include <curses.h>

int main() {
	using namespace ::std;
	using namespace ::std::chrono_literals;

	initscr();
	cbreak();
	noecho();

	auto f = [](int i) {
		mvaddch(0, i, '*');
		refresh();
		this_thread::sleep_for(50ms);
		clear();
	};
	while (true) {
		for (int i = 0; i < COLS; ++i) f(i);
		for (int i = COLS; i-- > 0; ) f(i);
	}

	return 0;
}