#include <stdlib.h>

static int is_sep(char c, char sep)
{
    return (c == sep);
}

static int word_count(const char *s, char sep)
{
    int i = 0;
    int count = 0;

    while (s[i])
    {
        while (s[i] && is_sep(s[i], sep))
            i++;
        if (s[i])
            count++;
        while (s[i] && !is_sep(s[i], sep))
            i++;
    }
    return count;
}

static char *word_dup(const char *s, int start, int end)
{
    char *word;
    int i = 0;

    word = malloc((end - start + 1) * sizeof(char));
    if (!word)
        return NULL;
    while (start < end)
        word[i++] = s[start++];
    word[i] = '\0';
    return word;
}

char **ft_split(char *s, char sep)
{
    char    **arr;
    int     i = 0;
    int     j = 0;
    int     start;

    if (!s)
        return NULL;
    arr = malloc((word_count(s, sep) + 1) * sizeof(char *));
    if (!arr)
        return NULL;
    while (s[i])
    {
        while (s[i] && is_sep(s[i], sep))
            i++;
        start = i;
        while (s[i] && !is_sep(s[i], sep))
            i++;
        if (i > start)
            arr[j++] = word_dup(s, start, i);
    }
    arr[j] = NULL;
    return arr;
}
