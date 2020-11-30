#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define N_BUF 1024

int main()
{
    char buf[N_BUF];
    int fd, size;

    fd = open("file", O_RDONLY);
    puts("open succeeds");

    size = read(fd, buf, N_BUF - 1);
    puts("read succeeds");

    buf[size] = '\0';

    printf("%s", buf);

    close(fd);

    return 0;
}