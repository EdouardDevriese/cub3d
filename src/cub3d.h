/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdenisse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:38:35 by vdenisse          #+#    #+#             */
/*   Updated: 2024/03/07 10:03:00 by vdenisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVE_SPEED 0.27
# define ROT_SPEED 0.12

# ifndef KEYS_H
#  define KEYS_H
#  ifdef __linux__
#   define K_ESC 65307
#   define K_R 27
#   define K_W 119
#   define K_A 97
#   define K_S 115
#   define K_D 100
#   define K_RIGHT 65361
#   define K_LEFT 65363
#  else
#   define K_ESC 53
#   define K_R 15
#   define K_W 13
#   define K_A 0
#   define K_S 1
#   define K_D 2
#   define K_RIGHT 123
#   define K_LEFT 124
#  endif
#  define I_FORWARD K_W
#  define I_BACKWARD K_S
#  define I_LEFT K_A
#  define I_RIGHT K_D
#  define I_ROLEFT K_RIGHT
#  define I_RORIGHT K_LEFT
# endif

# include "../libft/inc/libft.h"
# include "../mlx_linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <stdint.h>

typedef enum e_orientation
{
	NO,
	SO,
	WE,
	EA
}					t_orientation;

typedef struct s_check
{
	bool			no;
	bool			so;
	bool			ea;
	bool			we;
	bool			f;
	bool			c;

}					t_check;

typedef struct s_player_init
{
	int				pos_x;
	int				pos_y;
	t_orientation	dir;
}					t_player_init;

// pos: vector of the player
// dir: vector of player direction
// plane: vector of camera plane
//->set plane perpendicular to dir
//->plane to dir ratio determines FOV
// orientation: easier for setup, will determine dir vector
typedef struct s_player
{
	double			pos_y;
	double			pos_x;
	double			dir_y;
	double			dir_x;
	double			plane_x;
	double			plane_y;
	t_orientation	orientation;
}					t_player;

typedef struct s_ray
{
	double			camera_x;
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	t_orientation	orientation;
}					t_ray;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct s_drawing
{
	int				x;
	int				y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_pos;
	double			step;
	int				pixel;
	t_mlx			tex[4];
	int32_t			ceiling;
	int32_t			floor;
}					t_drawing;

typedef struct s_data
{
	char			**map;
	t_player_init	i;
	t_player		p;
	t_ray			r;
	t_drawing		d;
	t_mlx			m;
}					t_data;

void				player_init(t_player *p, t_player_init i);
void				calc_ray(int x, t_ray *r, t_player *p);
void				calc_delta_dist(t_ray *r);
void				calc_side_dist(t_ray *r, t_player p);
void				perform_dda(t_ray *r, char **map);
void				calc_line_to_draw(t_ray *r, t_drawing *d);
void				calc_texture_x(t_ray r, t_player p, t_drawing *d);
void				draw_line(t_drawing d, t_ray r, t_mlx *m);
void				draw_ceiling_floor(t_drawing d, t_mlx *m);
void				move_w(t_player *p, char **map);
void				move_a(t_player *p, char **map);
void				move_s(t_player *p, char **map);
void				move_d(t_player *p, char **map);
void				rot_left(t_player *p);
void				rot_right(t_player *p);

int					is_map(char *str);
int					get_draw_info(t_drawing *d, void *mlx, char *map_file);
int					data_init(t_player_init *i, char ***map, char *map_file);
int					map_content_check(char **map);
int					get_dimensions(char *map_src, int *x, int *y);
void				set_drawing_to_null(t_drawing *d);
int					check_info(t_check check);
int32_t				rgb_to_int(int r, int g, int b);
int					check_player_amount(char **map);
int					check_player_pos(char **map);
int					check_tile(char **map, int y, int x);
void				get_player_info(t_player_init *i, char **map);
t_check				check_init(void);
void				mlx_to_tex(t_drawing *d, void *mlx);

#endif
