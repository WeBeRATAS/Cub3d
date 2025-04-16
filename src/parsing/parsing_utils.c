/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:25:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 10:33:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_empty_line(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

static int	is_config_identifier(const char *id)
{
	static const char	*valid[] = {
		"R", "NO", "SO", "WE", "EA", "F", "C", NULL
	};
	int					i;

	i = -1;
	while (valid[++i])
		if (ft_strcmp(id, valid[i]) == 0)
			return (1);
	return (0);
}

int	is_map_line(char *line, char **tokens)
{
	int	i;

	if (!tokens[0])
		return (0);
	i = -1;
	while (tokens[0][++i])
	{
		if (!ft_strchr(" 01NSEW", tokens[0][i]))
			return (0);
	}
	(void)line;
	return (1);
}
int	add_map_line(char *line, t_list **map_list)
{
	char	*trimmed;
	t_list	*new_node;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		exit_error("Memory error", "strtrim failed", NULL);
	new_node = ft_lstnew(trimmed);
	if (!new_node)
	{
		free(trimmed);
		exit_error("Memory error", "lstnew failed", NULL);
	}
	ft_lstadd_back(map_list, new_node);
	return (SUCCESS);
}
