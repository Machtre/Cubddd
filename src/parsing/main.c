/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuisson <mbuisson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:57:45 by mbuisson          #+#    #+#             */
/*   Updated: 2026/01/20 18:52:03 by mbuisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_extension(char *file, char *ext)
{
	int len;
	
	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (!ft_strncmp(file + len - 4, ext, 4));
}

// int main(int ac, char **av)
// {
// 	if (ac != 2)
// 	{
// 		error("Usage: ./cub3d <map.cub>", 2);
// 		return 0;
// 	}
// 	if (!check_extension(av[1], ".cub"))
// 	{
// 		error("Invalid file extension", 2);
// 		return 0;

// 	}
// 	parse_cub(av[1]);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_data	*data;

// 	data = NULL;

// 	if (argc != 2)
// 	{
// 		error(data, "Usage: ./cub3D <map.cub>");
// 		return (1);
// 	}

// 	init_data(data);
// 	parse_cub(argv[1]);

// 	/* Si on arrive ici, le parsing est OK */
// 	printf("Parsing OK ✅\n");
// 	printf("Map size: %d x %d\n", data->map.width, data->map.height);
// 	printf("Player start: %c at (%f, %f)\n",
// 		data->player.start_dir,
// 		data->player.x,
// 		data->player.y);

// 	free_data(data);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data	data;
	(void)argc;
	// if (argc != 2)
	// {
	// 	error("Usage: ./cub3D <map.cub>");
	// 	return (1);
	// }

	init_data(&data);
	parse_cub(&data, argv[1]);

	printf("Parsing OK ✅\n");
	printf("Map size: %d x %d\n", data.map.width, data.map.height);
	printf("Player start: %c at (%f, %f)\n",
		data.player.start_dir,
		data.player.x,
		data.player.y);

	free_data(&data);
	return (0);
}


