#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#define N_BUF 1024

int main()
{
    char buf[N_BUF] = {0};
    int fd, size;

    fd = open("file", O_RDONLY | O_NONBLOCK);
    puts("open succeeds");

    while (1)
    {
        size = read(fd, buf, N_BUF - 1);

        // see man 7 fifo
        // read returns successfully if the fifo is not opened
        printf("read returns. ret: %d, errno: %d\n", size, errno);

        if (size >= 0)
        {
            buf[size] = '\0';
            printf("%s", buf);
            break;
        }

        puts("sleep");

        // looks bad
        sleep(1);
    }

    close(fd);
    return 0;
}