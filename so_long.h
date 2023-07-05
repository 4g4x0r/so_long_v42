#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include "./src/libft/libft.h"
#include "colors.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <X11/Xlib.h>//Utilizada para la gestion del multihilo.
#define BUFFER_SIZE 5000
#define BPP 64
// STRUCTS
typedef struct{
	char *map_name;
	int	lines;
	int columns;
	int coins;
	int	exitp;
	int startp;
	int	zeros;
	int ones;
	char *mapstruct[BUFFER_SIZE];
	void *mlx;
	void *mlx_win;
	void *wall_ptr;
	void *floor_ptr;
	void *exit_ptr;
	void *coin_ptr;
	int width;
	int height;
	int exit_x;
	int exit_y;
	int moves;
	int coins_gained;
	int endian;
}map;

typedef struct{
	void *ptr;
	int width;
	int height;
	void *img;
	int x;
	int	y;
	int endian;
	int stepanimation;
	char value;
}entity;

typedef struct {
	map *map;
	entity *player;
} in;


/*FUNCIONES PRINTF*/
int	ft_printf(const char *fmt, ...);
/*FUNCIONES DE MAPA*/
void check_argc(int argc);
int check_file_extension(char *filename, char *extension);
int process_map_file(in *fw);
int line_counter(int fd);
int process_line(int fd, in *fw);
int check_line(char *buffer, int *i, in *fw);
int map_validator(char *buffer, in *fw);
int first_line_analyzer(char *buffer, in *fw);
int body_line_analyzer(char *buffer, in *fw);
void search_entitys(in *fw, char letter, int e, int num);
int last_line_analyzer(char *buffer, in *fw);
int search_items(char item, in *fw);
int path_finder(in *fw);
int dfs(int row, int col, int **visited, in *fw);
/*FUNCIONES DE GESTION DE GRÁFICOS*/
void free_map_struct(in *fw);
int mlx_process(in *fw);
void put_imgs(in *fw);
int key_hook(int keycode, in *fw);
int loop_hook(in *fw);// PROBANDO
void check_coins(in *fw);
void draw_image(in *fw, void *img_ptr, int start_x, int start_y);
int get_pixel_color(void *img_ptr, int x, int y);
char *get_direction_static(entity *entity, int coordx, int coordy);
int draw_character(in *fw, entity *entity, int coordx, int coordy);
int close_window_event(in *fw);
int expose_window_event(in *fw);
/*FUNCIONES DE GESTION DE MOVIMIENTOS*/
int check_e(in *fw);
void handle_move(in *fw, entity *entity, int coordx, int coordy);
int handle_keys(in *fw, char key);
int check_move(in *fw, int coordX, int coordY);
void init_player(in *fw, entity *entity, int coordx, int coordy);
char convert_keycode_to_letter(int keycode);
char* put_values(char *cadena, entity *entity);
char get_low(char letter);
int is_entity(in *fw, int y, int x, int first_time);
void put_item_to_buffer(in *fw, int *buffer_data, int y, int x);
#endif