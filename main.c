#include <stdio.h>
#include <fcntl.h>
#include "fdf.h"
int main(int ac, char *av[])
{
    t_data data;

    if(ac != 2)
        return 1;
    
    if(!invalid_file(av[1]))
    {
        printf("hatalı dosya");
        return 1;
    }
      
    parse_map(av[1],&data);
    int i = 0;
    while(i<data.height)
    {
        printf("Harita yüklendi: %d x %d\n", data.height, data.width[i]);
        i++;
    }
    
    return 0;
}