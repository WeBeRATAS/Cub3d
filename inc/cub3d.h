/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 09:17:43 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/15 13:32:21 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../inc/libft/libft.h"
# include "../inc/minilibx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include <errno.h>

    /* --- Constantes --- */
# define WIN_TITLE "Cub3D"
#define MOVE_SPEED 0.1
#define COLLISION_MARGIN 0.1 // Evita quedarse pegado

  /* --- Estructuras --- */
typedef struct s_texture {
	void    *img_ptr;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;
	int     width;
	int     height;
	char    *path; // Guardar la ruta original
} t_texture;

typedef struct s_color {
	int r;
	int g;
	int b;
	int combined; // Color combinado para mlx (ej: 0xRRGGBB)
	int is_set;   // Flag para saber si ya se parseó
} t_color;

typedef struct s_map {
	char    **grid;
	int     width;
	int     height;
} t_map;

typedef struct s_list 
{
	t_map **map_list;
	
	
}
typedef struct s_player {
	double  pos_x;
	double  pos_y;
	double  dir_x; // Vector de dirección
	double  dir_y;
	double  plane_x; // Plano de la cámara (perpendicular a dir)
	double  plane_y;
	char    start_direction; // 'N', 'S', 'E', 'W'
	int     found; // Flag para asegurar que solo hay un jugador
} t_player;

typedef struct s_config {
	int         win_width;
	int         win_height;
	int         res_set; // Flag para saber si la resolución se parseo
	t_texture   north_tex;
	t_texture   south_tex;
	t_texture   west_tex;
	t_texture   east_tex;
	t_color     floor_color;
	t_color     ceiling_color;
	t_map       map;
	t_player    player;
	int         elements_found; // Bitmask o contador para elementos obligatorios
} t_config;

typedef struct s_mlx_vars {
	void        *mlx_ptr;
	void        *win_ptr;
	void        *img_ptr; // Buffer de imagen para dibujar
	char        *addr;    // Dirección del buffer
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	t_config    config; // Contiene toda la configuración parseada
} t_mlx_vars;

/* --- FUNCTIONS --- */
    // error.c
void	exit_error(char *message, char *details, t_mlx_vars *vars); // vars puede ser NULL al inicio
void	free_config(t_config *config); // Función para liberar toda la memoria de config

/* PARSING*/
void parser_escene(char **av, t_mlx_vars *vars);

#endif
