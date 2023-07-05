#include "so_long.h"

int check_file_extension(char *filename, char *extension)
{
	size_t len_filename;
	size_t len_extension;
	
	len_filename = ft_strlen(filename);
	len_extension = ft_strlen(extension);
	if (len_filename < len_extension)
	{
		perror("File: Not valid.");
		exit(1);
	}
	char *ptr = filename + (len_filename - len_extension);
	if (ft_strncmp(ptr, extension, len_extension) == 0)
	{
		return(0);
	}
	else
	{
		perror("This file does not have the required extension");
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
		perror("Error reading file");
		exit(1);
	}
	if (line < 2)
	{
		perror("Number of insufficient lines");
		exit(1);
	}
	return(line);
}
int map_validator(char *buffer, t_in *fw)
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
		perror("Error");
		exit(1);
	}
	return(0);
}
int process_line(int fd, t_in *fw)
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
		perror("Error reading file");
		exit(1);
	}
	return(0);
}

int process_map_file(t_in *fw)
{
	int fd = open(fw->map->map_name, O_RDONLY);
	fw->map->lines = line_counter(fd);
	close(fd);
	int fd2 = open(fw->map->map_name, O_RDONLY);

	process_line(fd2, fw);
	if (fw->map->coins < 1 || fw->map->exitp != 1 || fw->map->startp != 1)
	{
		ft_printf("\nInvalid map\nCoins:\t\t%d\nPlayer:\t%d\nExit:\t\t%d\n",
		 fw->map->coins, fw->map->startp, fw->map->exitp);
		exit(1);
	}
	ft_printf(YELLOW"\nColumns:\t\t"RED"%d\n"YELLOW"Rows:\t\t\t"RED"%d\n"
	YELLOW"Coins:\t\t\t"RED"%d\n"YELLOW"Ones:\t\t\t"RED"%d\n"YELLOW"Zeros:\t\t\t"
	RED"%d\n"YELLOW"Entry point:\t\t"RED"%d\n"YELLOW"Punto de salida:\t"
	RED"%d\n"DEFAULT, fw->map->columns,fw->map->lines, fw->map->coins,
	fw->map->ones, fw->map->zeros, fw->map->startp, fw->map->exitp);// DEBUG
	ft_printf(CYAN"\n****"RED"PLAYER"CYAN"***\n"RED"x: "MAGENTA"%i\t"RED"y: "
	MAGENTA"%i\n"CYAN"*************"DEFAULT, fw->player->x, fw->player->y);
	if (!path_finder(fw))
		exit(1);
	close(fd2);
	return (0);
}