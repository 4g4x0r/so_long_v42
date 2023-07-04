#include "so_long.h"
int check_file_extension(char *filename, char *extension)
{
	size_t len_filename;
    size_t len_extension;
    len_filename = ft_strlen(filename);
    len_extension = ft_strlen(extension);

	if (len_filename < len_extension)
	{
		perror("Fichero no válido");
		exit(1);
	}
	char *ptr = filename + (len_filename - len_extension);
	if (ft_strncmp(ptr, extension, len_extension) == 0)
	{
		return(0);
	}
	else
	{
		perror("Este fichero no tiene la extensión requerida");
		exit(1);
	}
}
int line_counter(int fd)
{
    char buffer[BUFFER_SIZE];
	int	line;
    ssize_t bytes_read;
	int i;
	
	i = 0;
	line = 0;
    while ((bytes_read = read(fd, &buffer[i], 1)) > 0)
    {
        if (buffer[i] == '\n')
            line++;
		i++;
    }
    if (bytes_read == -1)
    {
        perror("Error al leer el archivo");
        exit(1);
    }
	if (line < 2)
	{
		perror("Número de líneas insuficientes");
		exit(1);
	}
    return(line);
}
int map_validator(char *buffer, in *fw)
{
	static int i;

	if (i == 0 && i < fw->map->lines)
	{
		first_line_analyzer(buffer, fw);
		i++;
	}
	else if (i > 0 && (i + 1) < fw->map->lines)
	{
		body_line_analyzer(buffer, fw);
		i++;
	}
	else if ((i + 1) == fw->map->lines)
		last_line_analyzer(buffer, fw);
	else
	{
		perror("Error, tremenda fumada");
		exit(1);
	}
	return(0);
}

int process_line(int fd, in *fw)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
	int i;

	i = 0;
    while ((bytes_read = read(fd, &buffer[i], 1)) > 0)
    {
        if (buffer[i] == '\n')
            check_line(buffer, &i, fw);
        else
            i++;
    }
    if (bytes_read == -1)
    {
        perror("Error al leer el archivo");
        exit(1);
    }
    return(0);
}

int process_map_file(in *fw)
{
	int fd = open(fw->map->map_name, O_RDONLY);
	fw->map->lines = line_counter(fd);
	close(fd);
	int fd2 = open(fw->map->map_name, O_RDONLY);
	fw->map->coins = 0;
	fw->map->startp = 0;
	fw->map->zeros = 0;
	fw->map->ones = 0;
	fw->map->exitp = 0;
	process_line(fd2, fw);
	if (fw->map->coins < 1 || fw->map->exitp != 1 || fw->map->startp != 1)
	{
		ft_printf("\nMapa no válido\nCoins:\t\t%d\nJugador:\t%d\nSalida:\t\t%d\n", fw->map->coins, fw->map->startp, fw->map->exitp);
		exit(1);
	}
	ft_printf(YELLOW"\nColumnas:\t\t"RED"%d\n"YELLOW"Filas:\t\t\t"RED"%d\n"YELLOW"Coins:\t\t\t"RED"%d\n"YELLOW"Unos:\t\t\t"RED"%d\n"YELLOW"Ceros:\t\t\t"RED"%d\n"YELLOW"Punto de entrada:\t"RED"%d\n"YELLOW"Punto de salida:\t"RED"%d\n"DEFAULT, fw->map->columns, fw->map->lines, fw->map->coins, fw->map->ones, fw->map->zeros, fw->map->startp, fw->map->exitp);// DEBUG
	ft_printf(CYAN"\n****"RED"PLAYER"CYAN"***\n"RED"x: "MAGENTA"%i\t"RED"y: "MAGENTA"%i\n"CYAN"*************\n"DEFAULT, fw->player->x, fw->player->y);
	if (!path_finder(fw))
		exit(1);
	close(fd2);
	return (0);
}