/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 13:31:10 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_config_line(char **tokens, t_config *c)
{
	const t_parser	parsers[] = {
		{"NO", parse_texture},
		{"SO", parse_texture}, {"WE", parse_texture},
		{"EA", parse_texture}, {"F", parse_color},
		{"C", parse_color}, {NULL, NULL}
	};
	int				i;

	i = -1;
	while (parsers[++i].id)
	{
		if (ft_strncmp(tokens[0], parsers[i].id) == 0)
		{
			parsers[i].func(tokens, c);
			free_split(tokens);
			return (SUCCESS);
		}
	}
	free_split(tokens);
	return (ERROR);
}

static int	handle_line(char *line, t_config *c, int *map_started, t_list **ml)
{
	char	**tokens;

	if (is_empty_line(line) && !(*map_started))
		return (SUCCESS);
	tokens = ft_split(line, ' ');
	if (!tokens)
		exit_error("Memory error", "ft_split failed", NULL);
	if (tokens[0] && is_config_identifier(tokens[0]))
		return (parse_config_line(tokens, c));
	else if (is_map_line(line, tokens))
	{
		*map_started = 1;
		return (add_map_line(line, ml));
	}
	free_split(tokens);
	return (ERROR);
}

static char	*process_file_lines(t_config *c, t_list **map_list, int fd)
{
    char	*line;
    int		map_started;

    map_started = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (handle_line(line, c, &map_started, map_list) == ERROR)
        {
            free(line);
            ft_lstclear(map_list, free);
            exit_error("Invalid line in scene file", line, NULL);
        }
        free(line);
    }
    if (line == NULL)
    {
        ft_lstclear(map_list, free);
        exit_error("File read error", "get_next_line failed", NULL);
	}
	return (line);
}

int	parse_scene_file(char *filename, t_config *config)
{
	int		fd;
	int		dir_fd;
	char	*line;
	t_list	*map_list;

	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)) || 
        ft_strlen(filename) < 5 || 
        ft_strncmp(filename, ".cub", ft_strlen(filename) != 0))
        exit_error("File error", "Invalid file extension. Expected .cub", NULL);
	dir_fd = open(filename, O_DIRECTORY);
	if (dir_fd >= 0)
	{
		close(dir_fd);
		exit_error("File error", "Provided path is a directory, not a file", NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("File open error", filename, NULL);
	map_list = NULL;
	line = process_file_lines(config, &map_list, fd);
	close(fd);
	validate_scene_elements(config);
	process_map_data(&map_list, config);
	return (SUCCESS);
}
int	parser_scene(char **av, t_mlx_vars *vars)
{
	t_config	config;

	ft_memset(&config, 0, sizeof(t_config));
	if (parse_scene_file(av[1], &config) == ERROR)
		exit_error("Scene parsing failed", av[1], vars);
	transfer_config_to_vars(&config, vars);
	free_config(&config);
	return (0);
}