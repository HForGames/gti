/*
** EPITECH PROJECT, 2023
** gti
** File description:
** main.c
*/

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
    char *path = getcwd(NULL, 0);
    char *temp = calloc( strlen(path) + 15, sizeof(char));
    FILE *fp = fopen(strcat(strcat(temp, path), "/golf_gti_MKII"), "r");
    free(temp);
    free(path);
    char *line = NULL;
    size_t len = 0, read = 1, rlen;
    while ((read = getline(&line, &len, fp)) != -1) {
        (*tab) = realloc((*tab), sizeof(char *) * (len + 1));
        rlen = strlen(line);
        if (rlen > (*max)) (*max) = rlen;
        (*tab)[(*tablen)] = strdup(line);
        (*tablen)++;
    }
    (*tab)[(*tablen)] = NULL;
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
    while ((max) >= -move - COLS) {
        napms(20);
        erase();
        for (int i = 0; tab[i]; i++) {
            if (-move < max) {
                temp = strndup(tab[i], -move);
                mvprintw(LINES / 2 - tablen / 2 + i, COLS + move, "%s ", temp);
                free(temp);
            } else if (0 >= COLS + move) {
                temp = tab[i] + -move - COLS;
                mvprintw(LINES / 2 - tablen / 2 + i, 0, "%s ", temp);
            } else {
                mvprintw(LINES / 2 - tablen / 2 + i, COLS + move, "%s ", tab[i]);
            }
        }
        refresh();
        move--;
    }
    endwin();
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}
