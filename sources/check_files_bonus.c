#include "pipex_bonus.h"

int     ft_check_infile(char *filename, int pipe[2])
{
        int     fd;

        if (access(filename, F_OK) == -1)
        {
                ft_close(-1, pipe);
                ft_exit("pipex: no such file or directory: ", filename);
        }
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
                ft_close(-1, pipe);
                ft_exit("pipex: permission denied: ", filename);
        }
        return (fd);
}

int     ft_check_outfile(char *filename, int pipe[2])
{
        int     fd;

        fd = open(filename,
                        O_RDWR | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd == -1)
        {
                ft_close(-1, pipe);
                perror("pipex");
                exit(EXIT_FAILURE);
        }
        return (fd);
}
