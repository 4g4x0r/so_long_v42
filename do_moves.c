#include "so_long.h"

char* put_values(char *cadena, entity *entity) {
    char *copia = ft_strdup(cadena);  // Crear una copia de la cadena original
    copia[8] = get_low(entity->value);
    return copia;
}

char get_low(char letter)
{
    if (letter >= 'A' && letter <= 'Z') {
        return letter + 32;
    } else {
        // Si la letra no es mayúscula, se devuelve tal cual
        return letter;
    }
}
char *getdirectionstatic(entity *entity, int	coordx, int	coordy){
	char *imgstep;
	imgstep = put_values("sprites/p_down_t.xpm", entity);//default
	if (coordx == -1) //a
		imgstep = put_values("sprites/p_left_t.xpm", entity);
	else if (coordy == 1) //s
		imgstep = put_values("sprites/p_down_t.xpm", entity);
	else if (coordx == 1) //d
		imgstep = put_values("sprites/p_right_t.xpm", entity);
	else if (coordy == -1) //w
		imgstep = put_values("sprites/p_up_t.xpm", entity);
	return imgstep;
}

void	initplayer(in *fw, entity *entity, int	coordx, int	coordy) {
	fw->map->mapstruct[entity->y][entity->x] = '0';
	if (fw->map->mapstruct[entity->y + coordy][entity->x + coordx] != 'E')
		fw->map->mapstruct[entity->y + coordy][entity->x + coordx] = entity->value;
}
void handlemove(in *fw, entity *entity, int coordx, int coordy){
	initplayer(fw, entity, coordx, coordy);

	entity->x += coordx;
	entity->y += coordy;
	entity->ptr = mlx_xpm_file_to_image(fw->map->mlx, getdirectionstatic(entity, coordx, coordy), &fw->map->width, &fw->map->height);//CARGA LA DIRECCION ESTATICA DEL JUGADOR.
	mlx_do_sync(fw->map->mlx);
	check_e(fw);
}
