/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:56 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 13:00:45 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_error(char *message, char *details, t_mlx_vars *vars)
{
	printf("Error\n");
	if (message)
		printf("%s ", message);
	if (details)
		printf ("%s ", details);
	if (vars && vars->mlx_ptr)
    {
        if (vars->config.north_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.north_tex.img_ptr);
        if (vars->config.south_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.south_tex.img_ptr);
        if (vars->config.east_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.east_tex.img_ptr);
        if (vars->config.west_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.west_tex.img_ptr);
        // Destruir la ventana
        if (vars->win_ptr)
            mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
        mlx_destroy_display(vars->mlx_ptr);
        free(vars->mlx_ptr);
        vars->mlx_ptr = NULL;
    }
    exit (EXIT_FAILURE);
}
static void	print_controls(void)
{
	printf(CYAN "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": strafe left\t");
	printf(CYAN "\tD" RESET ": strafe right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	printf("\n");
}

int	main (int ac, char **av)
{
	t_mlx_vars vars;
	 
	if (ac != 2)
		 exit_error("Usage: ./cub3d <path/to/map_file.cub>\n", NULL, NULL);
	/* Inicializar vars a cero/NULL */
	ft_memset(&vars, 0, sizeof(t_mlx_vars));
	if (parser_scene(av[1], &vars) != 0)
        return (1);
    /* cargar texturas, cargar colores, render images */
    print_controls();
    
	return (0);
}
