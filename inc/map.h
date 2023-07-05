#ifndef MAPS_H
#define MAPS_H

#include "../so_long.h"
#include "colors.h"
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <X11/Xlib.h>//Utilizada para la gestion del multihilo.

void check_argc(int argc);
int check_file_extension(char *filename, char *extension);
int process_map_file(t_in *fw);
int line_counter(int fd);
int process_line(int fd, t_in *fw);
int check_line(char *buffer, int *i, t_in *fw);
int map_validator(char *buffer, t_in *fw);
int first_line_analyzer(char *buffer, t_in *fw);
int body_line_analyzer(char *buffer, t_in *fw);
void search_entitys(t_in *fw, char letter, int e, int num);
int last_line_analyzer(char *buffer, t_in *fw);
int search_items(char item, t_in *fw);
int path_finder(t_in *fw);
int dfs(int row, int col, int **visited, t_in *fw);

#endif