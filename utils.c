#include <fcntl.h>
#include <stddef.h>
#include "get_next_line.h"
#include "fdf.h"
int invalid_file(char *file_name)
{
    int i = 0;
    while(file_name[i])
        i++;
    if(i<5)
        return 1;
    //a.fdf
    if(file_name[i-4] == '.' && file_name[i-3] == 'f' 
        && file_name[i-2] == 'd' && file_name[i-1] == 'f')
        return 1;
    return 0;
}
int ft_atoi(char *str)
{
    int res;
    int i = 0;
    int sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while(str[i] >= '0' && str[i] <= '9')
    {
        res = res*10 + (str[i] - '0');
        i++;
    }
    return (res*sign);
}
int get_height(char *file_name)
{
    int fd = open(file_name,O_RDONLY);
    if(fd<0)
        return 1;
    int height = 0;
    char *line;
    while((line = get_next_line(fd)) != NULL)
    {
        height++;
        free(line);
    }
    close(fd);
    return height;
}
int get_width(char *line)
{
    int width = 0;
    char **arr;
    arr = ft_split(line,' ');
    if(!arr)
        return 0;
    while(arr[width])
        width ++;
    int i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
    return width;
}