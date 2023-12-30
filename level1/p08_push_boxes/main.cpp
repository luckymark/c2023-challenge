#include <curses.h>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <memory>
#include <functional>

struct File {
	struct Deleter {
		static void operator()(FILE* f) {
			::std::fclose(f);
		}
	};

	::std::unique_ptr<FILE, Deleter> f;

	File(::std::filesystem::path path, const char* modes):
		f(::std::fopen(path.c_str(), modes))
	{ }

	FILE* get() const { return this->f.get(); }
};

struct Position { int y, x; };

enum Direction {
	UP = 'w',
	LEFT = 'a',
	DOWN = 's',
	RIGHT = 'd'
};

Position advance(Position p, Direction d) {
	switch (d) {
		case UP: --p.y; break;
		case DOWN: ++p.y; break;
		case LEFT: --p.x; break;
		case RIGHT: ++p.x; break;
	}
	return p;
}

enum Mask : unsigned char {
	EMPTY = 0,
	WALL = 1 << 0,
	PLAYER = 1 << 1,
	BOX = 1 << 2,
	DEST = 1 << 3,
};
using Cell = ::std::underlying_type_t<Mask>;

bool contains(Cell c, Mask m) { return c & m; }
void set(Cell& c, Mask m) { c |= m; }
void remove(Cell& c, Mask m) { c &= ~m; }

char toChar(Cell c) {
	switch (c) {
		case EMPTY: return '.';
		case WALL: return '#';
		case PLAYER: return 'P';
		case PLAYER | DEST: return 'P';
		case BOX: return 'B';
		case DEST: return 'O';
		case BOX | DEST: return 'V';
		default: assert(false); // invalid state
	}
}

Cell fromChar(char c) {
	switch (c) {
		case '.': return EMPTY;
		case '#': return WALL;
		case 'P': return PLAYER;
		case 'B': return BOX;
		case 'O': return DEST;
		default: assert(false); // invalid map
	}
}

struct Map {
	int rows, cols;
	::std::vector<Cell> cells;
	::std::vector<Position> dests;
	Position player;

	int indexOf(Position p) const { return p.y * cols + p.x; }
	Cell& get(Position p) { return cells[indexOf(p)]; }
	Cell get(Position p) const { return cells[indexOf(p)]; }

	explicit Map(File&& f) {
		::std::fscanf(f.get(), "%dx%d", &rows, &cols);
		cells.resize(rows * cols);
		for (int y = 0; y < rows; ++y) {
			assert(::std::fgetc(f.get()) == '\n');
			for (int x = 0; x < cols; ++x) {
				Position p{y, x};
				switch (get(p) = fromChar(::std::fgetc(f.get()))) {
					case PLAYER: player = p; break;
					case DEST: dests.push_back(p); break;
					default: break;
				}
			}
		}
	}

	bool step(Direction d, ::std::invocable<Position, Cell> auto&& f) {
		Position p1 = advance(player, d);
		if (contains(get(p1), WALL)) return false;
		if (contains(get(p1), BOX)) {
			Position p2 = advance(p1, d);
			if (contains(get(p2), WALL)) return false;
			if (contains(get(p2), BOX)) return false;
			remove(get(p1), BOX);
			set(get(p2), BOX);
			::std::invoke(f, p2, get(p2));
		}
		remove(get(player), PLAYER);
		set(get(p1), PLAYER);
		::std::invoke(f, p1, get(p1));
		::std::invoke(f, player, get(player));
		player = p1;
		return true;
	}

	bool win() const {
		for (auto&& p : dests) {
			if (!contains(get(p), BOX)) {
				return false;
			}
		}
		return true;
	}
};

int main() {
	using namespace std;
	namespace fs = std::filesystem;

	initscr();
	cbreak();

	clear();
	mvprintw(0, 0, "Enter the level name: ");
	refresh();
	string level;
	level.resize_and_overwrite(80, [](char* buf, int size) {
		getnstr(buf, size);
		return strlen(buf);
	});

	noecho();
	curs_set(0);

	fs::path mapPath = fs::current_path() / "map" / (level + ".txt");
	fs::path scorePath = fs::current_path() / "score" / (level + ".txt");

	Map map(File(mapPath, "r"));
	auto print = [](Map const& map) {
		clear();
		for (int y = 0; y < map.rows; ++y) {
			for (int x = 0; x < map.cols; ++x) {
				mvaddch(y, x, toChar(map.get({y, x})));
			}
		}
		refresh();
	};
	int steps = 0;
	while (!map.win()) {
		print(map);
		auto c = getch();
		switch (c) {
			case UP: case DOWN: case LEFT: case RIGHT: {
				bool succeed = map.step(Direction(c), [](Position p, Cell c) {
					mvaddch(p.y, p.x, toChar(c));
				});
				if (succeed) ++steps;
				break;
			}
			default: break;
		}
	}
	print(map);
	mvprintw(map.rows + 1, 0, "You win! Steps: %d\n", steps);
	refresh();
	File scoreFile(scorePath, "a");
	fprintf(scoreFile.get(), "%d\n", steps);

	return 0;
}
