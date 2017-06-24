#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define WIN_HEIGHT 20
#define WIN_WIDTH 30

struct menu {
    const char **items;
    size_t n_items;
    size_t highlighted_item;
};

WINDOW *create_window(void)
{
    int rows, columns;
    getmaxyx(stdscr, rows, columns);

    WINDOW *win = newwin(WIN_HEIGHT, WIN_WIDTH, (rows - WIN_HEIGHT) / 2, (columns - WIN_WIDTH) / 2);
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

void draw_menu(WINDOW *win, struct menu *menu)
{
    for (size_t i = 0; i < menu->n_items; i++) {
        if (menu->highlighted_item == i) {
            wattron(win, A_REVERSE);
            mvwprintw(win, i + 2, 2, menu->items[i]);
            wattroff(win, A_REVERSE);
        } else {
            mvwprintw(win, i + 2, 2, menu->items[i]);
        }
    }

    wrefresh(win);
}

int main(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    refresh();
    WINDOW *win = create_window();

    struct menu menu;
    menu.n_items = 4;
    menu.items = malloc(sizeof(const char *) * menu.n_items);
    menu.highlighted_item = 0;
    menu.items[0] = "Test";
    menu.items[1] = "Hello";
    menu.items[2] = "How are you?";
    menu.items[3] = "Good?";
    
    int ch = 0;
    do {
        switch (ch) {
            case 'k':
            case KEY_UP:
                if (menu.highlighted_item > 0) {
                    menu.highlighted_item--;
                }
                break;
            case 'j':
            case KEY_DOWN:
                if (menu.highlighted_item < menu.n_items - 1) {
                    menu.highlighted_item++;
                }
                break;
        }

        draw_menu(win, &menu);
        wmove(win, 2 + menu.highlighted_item, 2 + strlen(menu.items[menu.highlighted_item]));
        wrefresh(win);
    } while ((ch = getch()) != EOF && ch != 'q');

    delwin(win);
    endwin();
    return EXIT_SUCCESS;
}
