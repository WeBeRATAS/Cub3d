/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:48:56 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/15 13:06:35 by rbuitrag         ###   ########.fr       */
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
        printf("Intentando limpiar recursos de MLX...\n");

        // Destruir imágenes (texturas) - ¡Ajusta según tu estructura!
        // Asumiendo que tienes una subestructura 'textures' o similar en 'vars'
		// y punteros como 'north_img', 'south_img', etc.
		if (vars->config.north_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.north_tex.img_ptr);
        if (vars->config.south_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.south_tex.img_ptr);
        if (vars->config.east_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.east_tex.img_ptr);
        if (vars->config.west_tex.img_ptr)
            mlx_destroy_image(vars->mlx_ptr, vars->config.west_tex.img_ptr);
        // Añade aquí cualquier otra imagen (sprite, floor, ceiling si las tienes)

        // Destruir la ventana
        if (vars->win_ptr)
            mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);

        // Destruir la conexión con el display (Importante en Linux)
        // En macOS (MiniLibX OpenGL), mlx_destroy_window puede ser suficiente,
        // pero mlx_destroy_display es común en versiones X11.
        // Consulta la documentación de tu MiniLibX específica.
        #ifdef __linux__ // O la macro adecuada para tu entorno si usas X11
            mlx_destroy_display(vars->mlx_ptr);
        #endif

        // Liberar el puntero mlx_ptr (resultado de mlx_init)
        // IMPORTANTE: Algunas versiones de MiniLibX (especialmente en Linux después
        // de mlx_destroy_display) requieren liberar este puntero. Otras no, o
        // incluso puede causar un crash. Verifica tu MiniLibX.
        // Si no estás seguro, coméntalo inicialmente.
        free(vars->mlx_ptr);
        vars->mlx_ptr = NULL; // Evita doble liberación si algo más intenta limpiar
    }
    else
    {
        printf("MLX no inicializado o 'vars' es NULL, omitiendo limpieza de MLX.\n");
    }
	exit (EXIT_FAILURE);
}


int	main (int ac, char **av)
{
	 t_mlx_vars vars;
	 (void)av;

	 if (ac != 2)
		 exit_error("Usage: ./cub3d <map_file.cub>\n", NULL, NULL);
	/* Inicializar vars a cero/NULL */
	 ft_memset(&vars, 0, sizeof(t_mlx_vars));
	 /* Parsear y validar */
	 parser_scene(av[1], &vars);

	return (0);
}
