#include <stdio.h>
#include "read_map.h"

// int main(int ac, char **av)
// {
//     if (ac != 2)
//     {
//         printf("Usage: ./fdf <map_file>\n");
//         return (1);
//     }

//     t_map *map = read_map(av[1]);
//     if (!map)
//     {
//         printf("Map reading failed\n");
//         return (1);
//     }

//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->widht; x++)
//             printf("%d ", map->z[y][x]);
//         printf("\n");
//     }

//     free_map(map);
// }
#include "mlx.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Kullanım: %s <map dosyası>\n", argv[0]);
        return 1;
    }

    t_map *map = read_map(argv[1]);
    if (!map)
    {
        printf("Map okunamadı!\n");
        return 1;
    }

    printf("Map boyutları: width=%d, height=%d\n", map->width, map->height);

    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 800, 600, "FdF");

    draw_map(mlx, win, map); // draw_map fonksiyonunu güncelle, map parametre alsın

    mlx_loop(mlx);
    return 0;
}

