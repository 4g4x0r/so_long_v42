#include "so_long.h"

int close_window_event(in *fw)
{
	printf("\nCerrando el juego...\n");
	mlx_destroy_display(fw->map->mlx);
    exit(0);  // Salir del programa
}

int expose_window_event(in *fw)
{
	if (fw)
	{
		printf("El tamaño de este juego no es modificable.\n");
	}
	return(0);
}