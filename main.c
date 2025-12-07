#include <stdio.h>
#include <fcntl.h>
#include "fdf.h"
// int main(int ac, char *av[])
// {
//     t_data data;

//     if(ac != 2)
//         return 1;
    
//     if(!invalid_file(av[1]))
//     {
//         printf("hatalı dosya");
//         return 1;
//     }
      
//     parse_map(av[1],&data);
//     int i = 0;
//     int j;
//     while(i<data.height)
//     {
//         printf("Harita yüklendi: %d x %d\n",i, data.width[i]);
//         j = 0;
//         while(j<data.width[i])
//         {
//             printf("%d ", data.map[i][j]);
//             j++;
//         }
//         printf("\n");
//         i++;
//     }
    
//     return 0;
// }
#include <mlx.h>
#include <stdlib.h>
static int close_esc(int keykode, t_mlx *mlx)
{
    if(keykode == 65307)
    {
        mlx_destroy_window(mlx->mlx,mlx->mlx);
        exit(0);
    }
    return 0;
}
int main(int ac, char *av[])
{
    t_data data;
    t_mlx mlx;

    if (ac != 2) return 1;
    printf("deneme\n");

    parse_map(av[1], &data);
    printf("deneme\n");

    create_points(&data,av[1]);
    printf("deneme\n");


    printf("height: %d\n", data.height);
    for(int i=0; i<data.height; i++)
        printf("width[%d]: %d\n", i, data.width[i]);
    
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, 1000, 800, "FDF");
    mlx.data = &data;
    mlx.zoom = 20;
    mlx.offset_x = 500;
    mlx.offset_y = 200;

    draw_map(&mlx);
    mlx_key_hook(mlx.win,close_esc,&mlx);
    
    mlx_loop(mlx.mlx);

    return 0;
}
