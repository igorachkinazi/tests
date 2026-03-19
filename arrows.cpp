#include <ncurses.h>
#include <iostream>
#include <cstdio>


using namespace std;

int main() {
    int c;
    bool loop = true;
    cbreak();
    noecho();
    while (loop && (c = getch()) != EOF) {
        if (c == 27) { // Escape sequence
            getch(); // Read '['
            switch (getch()) {
                case KEY_UP:
                    cout << "Up" << std::endl;
                    break;
                case KEY_DOWN:
                    cout << "Down" << std::endl;
                    break;
                case KEY_RIGHT:
                    cout << "Right" << std::endl;
                    break;
                case KEY_LEFT:
                    cout << "Left" << std::endl;
                    break;
            }
        }
        else {
            cout << char(c) << '\n';
            if(char(c) == 'q')
                loop = false;
        }
    }
    return 0;
}

