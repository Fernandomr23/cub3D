# include "../mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

# define KEY_ARROW_L 65361
# define KEY_ARROW_R 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 100
# define KEY_D 115

typedef struct s_vars {
    void *mlx;
    void *win;
    struct s_player *player;
} t_vars;

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

char *map[] = {
    "111111111111111",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001",
    "100000000000001"
    "111111111111111",
    NULL
};

void draw_vertical_line(t_vars *vars, int x, int start, int end, int color) {
    for (int y = start; y < end; y++) {
        mlx_pixel_put(vars->mlx, vars->win, x, y, color);
    }
}

void render(t_vars *vars) {
    t_player *player = vars->player;
    for (int x = 0; x < WIN_WIDTH; x++) {
        double camera_x = 2 * x / (double)WIN_WIDTH - 1;
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        int map_x = (int)player->x;
        int map_y = (int)player->y;

        double side_dist_x;
        double side_dist_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        int step_x;
        int step_y;

        int hit = 0;
        int side;

        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (player->x - map_x) * delta_dist_x;
        } else {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (player->y - map_y) * delta_dist_y;
        } else {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
        }

        while (hit == 0) {
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            } else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_y][map_x] == '1') hit = 1;
        }

        if (side == 0) perp_wall_dist = (map_x - player->x + (1 - step_x) / 2) / ray_dir_x;
        else perp_wall_dist = (map_y - player->y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(WIN_HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + WIN_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WIN_HEIGHT / 2;
        if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

        int color = (side == 1) ? 0xFF0000 : 0x00FF00;
        draw_vertical_line(vars, x, draw_start, draw_end, color);
    }
}

int key_hook(int keycode, t_vars *vars) {
    t_player *player = vars->player;
    printf("Keycode: %d\n", keycode);
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == KEY_ARROW_L) { // Left arrow key
        double old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
        player->dir_y = old_dir_x * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
        double old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(-ROT_SPEED) - player->plane_y * sin(-ROT_SPEED);
        player->plane_y = old_plane_x * sin(-ROT_SPEED) + player->plane_y * cos(-ROT_SPEED);
    }
    if (keycode == KEY_ARROW_R) { // Right arrow key
        double old_dir_x = player->dir_x;
        player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
        player->dir_y = old_dir_x * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
        double old_plane_x = player->plane_x;
        player->plane_x = player->plane_x * cos(ROT_SPEED) - player->plane_y * sin(ROT_SPEED);
        player->plane_y = old_plane_x * sin(ROT_SPEED) + player->plane_y * cos(ROT_SPEED);
    }
    if (keycode == KEY_W) {
        if (map[(int)(player->y)][(int)(player->x + player->dir_x * MOVE_SPEED)] == '0')
            player->x += player->dir_x * MOVE_SPEED;
        if (map[(int)(player->y + player->dir_y * MOVE_SPEED)][(int)(player->x)] == '0')
            player->y += player->dir_y * MOVE_SPEED;
    }
    if (keycode == KEY_S) {
        if (map[(int)(player->y)][(int)(player->x - player->dir_x * MOVE_SPEED)] == '0')
            player->x -= player->dir_x * MOVE_SPEED;
        if (map[(int)(player->y - player->dir_y * MOVE_SPEED)][(int)(player->x)] == '0')
            player->y -= player->dir_y * MOVE_SPEED;
    }
    if (keycode == KEY_A) {
        if (map[(int)(player->y)][(int)(player->x + player->dir_x * MOVE_SPEED)] == '0')
            player->x += player->dir_y * MOVE_SPEED;
        if (map[(int)(player->y + player->dir_y * MOVE_SPEED)][(int)(player->x)] == '0')
            player->y -= player->dir_x * MOVE_SPEED;
    }
    if (keycode == KEY_D) {
        if (map[(int)(player->y)][(int)(player->x - player->dir_x * MOVE_SPEED)] == '0')
            player->x -= player->dir_y * MOVE_SPEED;
        if (map[(int)(player->y - player->dir_y * MOVE_SPEED)][(int)(player->x)] == '0')
            player->y += player->dir_x * MOVE_SPEED;
    }
    mlx_clear_window(vars->mlx, vars->win);
    render(vars);
    return (0);
}

int main(void) {
    t_vars vars;
    t_player player;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Raycasting Game");

    player.x = 4.5;
    player.y = 4.5;
    player.dir_x = -1;
    player.dir_y = 0;
    player.plane_x = 0;
    player.plane_y = 0.66;

    vars.player = &player;

    render(&vars);

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_loop(vars.mlx);
    return (0);
}
