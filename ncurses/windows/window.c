#include <stdlib.h>

#include <ncurses.h>

int main(void)
{
    initscr(); /* start ncurses*/
    cbreak();
    noecho();
    refresh();

    WINDOW *win = newwin(20, 40, (LINES - 20) / 2, (COLS - 20) / 2);
    box(win, 0, 0);
    wrefresh(win);

    mvwprintw(win, 2, 2, "Hello, world!");
    wrefresh(win);

    getch();

    delwin(win);
    endwin(); /* end ncurses */
    return EXIT_SUCCESS;
}
