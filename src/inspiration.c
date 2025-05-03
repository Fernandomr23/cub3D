# include "../mlx_linux/mlx.h"
# include "../includes/cub.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <math.h>

/*
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
*/
char *map[] = {
    "1111111111111111111111111",
    "1000000000110000000000001",
    "1011000001110000000000001",
    "1001000000000000000000001",
    "1001000000000000000000001",
    "1111111111111111111111111"
};

void draw_vertical_line(t_cub *cub, int x, int start, int end, int color) {
    for (int y = start; y < end; y++) {
        mlx_pixel_put(cub->mlx, cub->win, x, y, color);
    }
}

void render(t_cub *cub) {
    for (int x = 0; x < WIDTH; x++) {
        cub->ray.camera_x = 2 * x / (double) WIDTH - 1;
        cub->ray.x_dir = cub->player.x_direction + cub->player.x_plane * cub->player.x_camera;
        cub->ray.y_dir = cub->player.y_direction + cub->player.y_plane * cub->player.x_camera;

        cub->ray.map_x = (int)cub->player.x_coord;
        cub->ray.map_y = (int)cub->player.y_coord;

        cub->ray.x_dist_inc = fabs(1 / cub->ray.x_dir);
        cub->ray.y_dist_inc = fabs(1 / cub->ray.y_dir);

        cub->ray.hit = 0;

        if (cub->ray.x_dir < 0) {
            cub->ray.step_x = -1;
            cub->ray.x_dist_lateral = (cub->player.x_coord - cub->ray.map_x) * cub->ray.x_dist_inc;
        } else {
            cub->ray.step_x = 1;
            cub->ray.x_dist_lateral = (cub->ray.map_x + 1.0 - cub->player.x_coord) * cub->ray.x_dist_inc;
        }
        if (cub->ray.y_dir < 0) {
            cub->ray.step_y = -1;
            cub->ray.y_dist_lateral = (cub->player.y_coord - cub->ray.map_y) * cub->ray.y_dist_inc;
        } else {
            cub->ray.step_y = 1;
            cub->ray.y_dist_lateral = (cub->ray.map_y + 1.0 - cub->player.y_coord) * cub->ray.y_dist_inc;
        }

        while (cub->ray.hit == 0) {
            if (cub->ray.x_dist_lateral < cub->ray.y_dist_lateral) {
                cub->ray.x_dist_lateral += cub->ray.x_dist_inc;
                cub->ray.map_x += cub->ray.step_x;
                cub->ray.side = 0;
            } else {
                cub->ray.y_dist_lateral += cub->ray.y_dist_inc;
                cub->ray.map_y += cub->ray.step_y;
                cub->ray.side = 1;
            }
            if (map[cub->ray.map_y][cub->ray.map_x] == '1') 
                cub->ray.hit = 1;
        }

        if (cub->ray.side == 0) 
            cub->ray.wall_dist = (cub->ray.map_x - cub->player.x_coord + (1 - cub->ray.step_x) / 2) / cub->ray.x_dir;
        else 
            cub->ray.wall_dist = (cub->ray.map_y - cub->player.y_coord + (1 - cub->ray.step_y) / 2) / cub->ray.y_dir;

        int line_height = (int) (HEIGHT / cub->ray.wall_dist);

        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        int color;
        if (cub->ray.side == 1)
            color = 0xFF0000;
        else
            color = 0x0000FF;
        draw_vertical_line(cub, x, draw_start, draw_end, color);
    }
}

int key_hook(int keycode, t_cub *cub) {
    printf("Keycode: %d\n", keycode);
    if (keycode == 65307) // Escape key
        exit(0);
    if (keycode == KEY_ARROW_L) { // Left arrow key
        double old_dir_x = cub->player.x_direction;
        cub->player.x_direction = cub->player.x_direction * cos(-ROTATION_SPEED) - cub->player.y_direction * sin(-ROTATION_SPEED);
        cub->player.y_direction = old_dir_x * sin(-ROTATION_SPEED) + cub->player.y_direction * cos(-ROTATION_SPEED);
        double old_plane_x = cub->player.x_plane;
        cub->player.x_plane = cub->player.x_plane * cos(-ROTATION_SPEED) - cub->player.y_plane * sin(-ROTATION_SPEED);
        cub->player.y_plane = old_plane_x * sin(-ROTATION_SPEED) + cub->player.y_plane * cos(-ROTATION_SPEED);
    }
    if (keycode == KEY_ARROW_R) { // Right arrow key
        double old_dir_x = cub->player.x_direction;
        cub->player.x_direction = cub->player.x_direction * cos(ROTATION_SPEED) - cub->player.y_direction * sin(ROTATION_SPEED);
        cub->player.y_direction = old_dir_x * sin(ROTATION_SPEED) + cub->player.y_direction * cos(ROTATION_SPEED);
        double old_plane_x = cub->player.x_plane;
        cub->player.x_plane = cub->player.x_plane * cos(ROTATION_SPEED) - cub->player.y_plane * sin(ROTATION_SPEED);
        cub->player.y_plane = old_plane_x * sin(ROTATION_SPEED) + cub->player.y_plane * cos(ROTATION_SPEED);
    }
    if (keycode == KEY_W) {
        if (map[(int)(cub->player.y_coord)][(int)(cub->player.x_coord + cub->player.x_direction * MOVEMENT_SPEED)] == '0')
            cub->player.x_coord += cub->player.x_direction * MOVEMENT_SPEED;
        if (map[(int)(cub->player.y_coord + cub->player.y_direction * MOVEMENT_SPEED)][(int)(cub->player.x_coord)] == '0')
            cub->player.y_coord += cub->player.y_direction * MOVEMENT_SPEED;
    }
    if (keycode == KEY_S) {
        if (map[(int)(cub->player.y_coord)][(int)(cub->player.x_coord - cub->player.x_direction * MOVEMENT_SPEED)] == '0')
            cub->player.x_coord -= cub->player.x_direction * MOVEMENT_SPEED;
        if (map[(int)(cub->player.y_coord - cub->player.y_direction * MOVEMENT_SPEED)][(int)(cub->player.x_coord)] == '0')
            cub->player.y_coord -= cub->player.y_direction * MOVEMENT_SPEED;
    }
    if (keycode == KEY_A) {
        if (map[(int)(cub->player.y_coord)][(int)(cub->player.x_coord + cub->player.x_direction * MOVEMENT_SPEED)] == '0')
            cub->player.x_coord += cub->player.y_direction * MOVEMENT_SPEED;
        if (map[(int)(cub->player.y_coord + cub->player.y_direction * MOVEMENT_SPEED)][(int)(cub->player.x_coord)] == '0')
            cub->player.y_coord -= cub->player.x_direction * MOVEMENT_SPEED;
    }
    if (keycode == KEY_D) {
        if (map[(int)(cub->player.y_coord)][(int)(cub->player.x_coord - cub->player.x_direction * MOVEMENT_SPEED)] == '0')
            cub->player.x_coord -= cub->player.y_direction * MOVEMENT_SPEED;
        if (map[(int)(cub->player.y_coord - cub->player.y_direction * MOVEMENT_SPEED)][(int)(cub->player.x_coord)] == '0')
            cub->player.y_coord += cub->player.x_direction * MOVEMENT_SPEED;
    }
    mlx_clear_window(cub->mlx, cub->win);
    render(cub);
    return (0);
}

int main(void) {
    t_cub   cub;

    cub.mlx = mlx_init();
    cub.win = mlx_new_window(cub.mlx, WIDTH, HEIGHT, "Raycasting Game");

    cub.player.x_coord = 4;
    cub.player.y_coord = 1;
    cub.player.x_direction = -1;
    cub.player.y_direction = 0;
    cub.player.x_plane = cub.player.y_direction * .66;
    cub.player.y_plane = cub.player.x_direction * .66;

    render(&cub);

    mlx_key_hook(cub.win, key_hook, &cub);
    mlx_loop(cub.mlx);
    return (0);
}
