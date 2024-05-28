#include "so_long.h"
int	check_file_extension(char *filename, char *extension)
{
	size_t	len_filename;
	size_t	len_extension;
	char	*ptr;
	ptr = NULL;
	len_filename = ft_strlen(filename);
	len_extension = ft_strlen(extension);
	if (len_filename < len_extension)
	{
		perror("File: Not valid.");
		exit(1);
	}
	ptr = filename + (len_filename - len_extension);
	if (ft_strncmp(ptr, extension, len_extension) == 0)
		return (0);
	else
	{
		perror("This file does not have the required extension");
		exit(1);
	}
}
int	line_counter(int fd)
{
	char	buffer[BUFFER_SIZE];
	int		line;
	ssize_t	bytes_read;
	int		i;
	i = 0;
	line = 0;
	bytes_read = read(fd, &buffer[i], 1);
	while (bytes_read > 0)
	{
		if (buffer[i] == '\n')
			line++;
		i++;
		bytes_read = read(fd, &buffer[i], 1);
	}
	if (bytes_read == -1)
		error_msg("Error reading file");
	if (line < 2)
		error_msg("Error: Number of insufficient lines");
	return (line);
}
int	map_validator(char *buffer, t_in *fw)
{
	static int	i;
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
	return (0);
}
int	process_line(int fd, t_in *fw)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		i;
	i = 0;
	bytes_read = read(fd, &buffer[i], 1);
	while ((bytes_read) > 0)
	{
		if (buffer[i] == '\n')
			check_line(buffer, &i, fw);
		else
			i++;
		bytes_read = read(fd, &buffer[i], 1);
	}
	if (bytes_read == -1)
		error_msg("Error reading file");
	return (0);
}
int	process_map_file(t_in *fw)
{
	int	fd;
	int	fd2;
	fd = open(fw->map->map_name, O_RDONLY);
	fw->map->lines = line_counter(fd);
	close(fd);
	fd2 = open(fw->map->map_name, O_RDONLY);
	ft_set_variables(fw);
	process_line(fd2, fw);
	if (fw->map->coins < 1 || fw->map->exitp != 1 || fw->map->startp != 1)
	{
		ft_printf("\nInvalid map\nCoins:\t\t%d\nPlayer:\t%d\nExit:\t\t%d\n",
			fw->map->coins, fw->map->startp, fw->map->exitp);
		exit(1);
	}
	if (!path_finder(fw))
		exit(1);
	close(fd2);
	return (0);
}