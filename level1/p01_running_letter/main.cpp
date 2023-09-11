#include <cstdio>
#include <thread>
#include <unistd.h>
#include <sys/ioctl.h>

int main() {
	using namespace std;
	using namespace std::chrono_literals;
	winsize s;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &s);
	int w = s.ws_col;
	auto print_frame = [&](int c) {
		for (int i = 0; i < w; ++i) {
			if (i == c) putchar('*');
			else putchar(' ');
		}
		putchar('\r');
		std::this_thread::sleep_for(50ms);
	};
	while (true) {
		for (int i = 0; i < w; ++i) print_frame(i);
		for (int i = w; i-- > 0; ) print_frame(i);
	}
	return 0;
}