#ifndef SO_LONG_H
#define SO_LONG_H

#include <mlx.h>
#include "./src/libft/libft.h"
#include "./src/printf/ft_printf.h"
#include "./inc/colors.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <X11/Xlib.h>//Utilizada para la gestion del multihilo.
#define BUFFER_SIZE 5000
#define BPP 64
// STRUCTS
typedef struct s_map{
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
}				t_map;

typedef struct s_entity{
	void *ptr;
	int width;
	int height;
	void *img;
	int x;
	int	y;
	int endian;
	int stepanimation;
	char value;
}				t_entity;

typedef struct s_in{
	t_map *map;
	t_entity *player;
}				t_in;

/*FUNCIONES DE MAPA*/
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
/*FUNCIONES DE GESTION DE GRÁFICOS*/
void free_map_struct(t_in *fw);
int mlx_process(t_in *fw);
void set_image_ptr(t_in *fw, int y, int x, void **image_ptr);
void copy_image_data(int *buffer_data, int *image_data, int cell_width, int cell_height);
void process_buffer_data(t_in *fw, int *buffer_data);
void put_imgs(t_in *fw);
int key_hook(int keycode, t_in *fw);
int loop_hook(t_in *fw);// PROBANDO
void check_coins(t_in *fw);
void draw_image(t_in *fw, void *img_ptr, int start_x, int start_y);
int get_pixel_color(void *img_ptr, int x, int y);
char *get_direction_static(t_entity *entity, int coordx, int coordy);
int draw_character(t_in *fw, t_entity *entity, int coordx, int coordy);
int close_window_event(t_in *fw);
int expose_window_event(t_in *fw);
/*FUNCIONES DE GESTION DE MOVIMIENTOS*/
int check_e(t_in *fw);
void handle_move(t_in *fw, t_entity *entity, int coordx, int coordy);
int handle_keys(t_in *fw, char key);
int check_move(t_in *fw, int coordX, int coordY);
void init_player(t_in *fw, t_entity *entity, int coordx, int coordy);
char convert_keycode_to_letter(int keycode);
char *put_values(char *cadena, t_entity *entity);
char get_low(char letter);
int is_entity(t_in *fw, int y, int x, int first_time);
void put_item_to_buffer(t_in *fw, int *buffer_data, int y, int x);
#endif