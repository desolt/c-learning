#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        printf("Colors are not supported on this terminal emulator! :(\n");
        exit(EXIT_FAILURE);
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); /* Pair color values to 1 */

    attron(COLOR_PAIR(1));
    printw("Hello, world!");
    attroff(COLOR_PAIR(1));

    getch();

    endwin();
    return EXIT_SUCCESS;
}
