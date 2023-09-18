#include <cstdio>
#include <curses.h>

int main() {
	using namespace ::std;

	static constexpr int X = 11, Y = 11;
	static constexpr char map[X * Y] = {
		'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
		'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'O', '#',
		'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#',
		'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
		'#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
		'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
		'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#',
		'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
		'#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#',
		'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',
		'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
	};
	static constexpr auto getm = [](int x, int y) -> char {
		return map[y * X + x];
	};

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	for (int y = 0; y < Y; ++y)
		for (int x = 0; x < X; ++x)
			mvaddch(y, x, getm(x, y));
	int px = 1, py = 9;
	mvaddch(py, px, '*');
	refresh();

	while (true) {
		if (getm(px, py) == 'O') {
			clear();
			mvaddstr(0, 0, "You win!\n");
			refresh();
			return 0;
		}
		int c = getch();
		int npx = px, npy = py;
		switch (c) {
			case 'w': --npy; break;
			case 'a': --npx; break;
			case 's': ++npy; break;
			case 'd': ++npx; break;
			default: break;
		}
		if (getm(npx, npy) != '#') {
			mvaddch(py, px, getm(px, py));
			mvaddch(npy, npx, '*');
			px = npx;
			py = npy;
			refresh();
		}
	}
}