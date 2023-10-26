#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

void get_golf(size_t *tablen, int *max, char ***tab) {
    (*tablen) = 0;
    (*max) = 0;
    (*tab) = NULL;
#ifdef INTALL_MODE
    char *path = getcwd(NULL, 0);
    if (path == NULL) {
        perror("getcwd");
        exit(1);
    }

    char *file_path = malloc(strlen(path) + 18);
    if (file_path == NULL) {
        perror("malloc");
        exit(1);
    }

    printf("%s\n", path);
    sprintf(file_path, "%s/golf_gti_MKII", path);
    free(path);
#else

    char *file_path = malloc(30);

    sprintf(file_path, "/usr/local/bin/golf_gti_MKII");

#endif
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        perror("fopen");
        free(file_path);
        exit(1);
    }
    free(file_path);

    char *line = NULL;
    size_t len = 0, rlen;
    while (getline(&line, &len, fp) != -1) {
        (*tab) = realloc((*tab), sizeof(char *) * ((*tablen) + 1));
        rlen = strlen(line);
        if ((int)rlen > (*max)) (*max) = rlen;
        (*tab)[(*tablen)] = strdup(line);
        (*tablen)++;
    }
    free(line);
    fclose(fp);
}

int main() {
    size_t tablen;
    int max, move = 0;
    char **tab;
    get_golf(&tablen, &max, &tab);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    initscr();
    curs_set(0);
    char *temp;

    while (max >= -move - COLS) {
        napms(20);
        erase();
        for (int i = 0; tab[i]; i++) {
            if (-move < max) {
                temp = strndup(tab[i], -move);
                mvprintw(LINES / 2 - tablen / 2 + i, COLS + move, "%s", temp);
                free(temp);
            } else if (0 >= COLS + move) {
                temp = tab[i] - move - COLS;
                mvprintw(LINES / 2 - tablen / 2 + i, 0, "%s", temp);
            } else {
                mvprintw(LINES / 2 - tablen / 2 + i, COLS + move, "%s", tab[i]);
            }
        }
        refresh();
        move--;
    }

    endwin();
    for (int i = 0; tab[i]; i++) {
        free(tab[i]);
    }
    free(tab);

    return 0;
}
