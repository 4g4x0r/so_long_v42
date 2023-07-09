#include "so_long.h"

void 	check_argc(int argc)
{
	if (argc < 2)
	{
		perror("No hay argumentos");
		exit(1);
	}
}

int	check_line(char *buffer, int *i, t_in *fw)
{
	static int e;

	buffer[*i] = '\0';
	map_validator(buffer, fw);
	fw->map->mapstruct[e] = (char *)malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	ft_strlcpy(fw->map->mapstruct[e], buffer, ft_strlen(buffer) + 1);
	ft_printf(GREEN"%s\n"DEFAULT, fw->map->mapstruct[e]);
	e++;
	*i = 0;
	return(0);
}

int	first_line_analyzer(char *buffer, t_in *fw)
{
	int a;
	
	fw->map->columns = ft_strlen(buffer);
	a = 0;
	while (buffer[a] != '\0')
	{
		if (buffer[a] != '1' )
		{
			perror("Unclosed first line");
			exit(1);
		}
		a++;
	}
	
	if (a < 3)
	{
		perror("Map too small");
		exit(1);
	}
	
	return(0);
}

int	body_line_analyzer(char *buffer, t_in *fw)
{
	int a;
	static int e;

	a = 0;
	//ft_printf("\nen body_line_analyzer el buffer mide %i y el modelo a seguir %i\n", ft_strlen(buffer), c->columns);
	if (ft_strlen(buffer) != (size_t)fw->map->columns || buffer[a] != '1' ||
	buffer[(fw->map->columns - 1)] != '1')
	{
		perror("Inconsistent map");
		exit(1);
	}
	a++;
	while(a != (fw->map->columns - 1))
	{
		search_entitys(fw, buffer[a], e, a);
		search_items(buffer[a], fw);//aqui es ir revisando el cuerpo del mapa e ir añadiendo si hay un coin pues coin++;
		a++;
	}
	e++;
	return(0);
}
int	search_items(char item, t_in *fw)
{
	if (item == 'C')
		fw->map->coins = fw->map->coins + 1;
	else if (item == 'E')
		fw->map->exitp = fw->map->exitp + 1;
	else if (item == 'P')
		fw->map->startp = fw->map->startp + 1;
	else if (item == '0')
		fw->map->zeros = fw->map->zeros + 1;
	else if (item == '1')
		fw->map->ones = fw->map->ones + 1;
	else
	{
		perror("Invalid character on the map");
		exit(1);
	}
	return(0);
}