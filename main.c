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
#include "mlx.h"
#include <stdlib.h>
static int close_win(t_mlx *mlx)
{
    free_data_map(mlx->data);
    if(mlx->win)
        mlx_destroy_window(mlx->mlx,mlx->win);
    exit(0);
    return 0;
}
static int handle_key(int keycode, t_mlx *mlx)
{
    if(keycode == 65307 || keycode == 53)
    {
        mlx_destroy_image(mlx->mlx, mlx->img);  // ← Image'i temizle
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    return 0;
}
int main(int ac, char *av[])
{
    t_data data;
    t_mlx mlx;

    if (ac != 2) return 1;

    parse_map(av[1], &data);

    create_points(&data,av[1]);


    // printf("height: %d\n", data.height);
    // for(int i=0; i<data.height; i++)
    //     printf("width[%d]: %d\n", i, data.width[i]);
    if(invalid_file(av[1]))
    {
        mlx.mlx = mlx_init();
        mlx.win = mlx_new_window(mlx.mlx, 1000, 800, "FDF");

        //image
        mlx.img = mlx_new_image(mlx.mlx,1000,800);
        mlx.addr = mlx_get_data_addr(mlx.img,&mlx.bpp,&mlx.line_len,&mlx.endian);

        mlx.data = &data;
        // mlx.zoom = 20;
        // mlx.offset_x = 500;
        // mlx.offset_y = 200;
        
        auto_fit_and_center(&mlx);
        draw_map(&mlx);

        mlx_put_image_to_window(mlx.mlx,mlx.win,mlx.img,0,0);

        mlx_key_hook(mlx.win,handle_key,&mlx);
        mlx_hook(mlx.win,17,0,close_win,&mlx);
        mlx_loop(mlx.mlx);
        //mlx_destroy_display(mlx.mlx);

    }
    
    return 0;
}
