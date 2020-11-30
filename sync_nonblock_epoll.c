#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/epoll.h>

#define N_BUF 1024

int main()
{
    char buf[N_BUF] = {0};
    int fd, size;

    fd = open("file", O_RDONLY | O_NONBLOCK);
    printf("open succeeds. fd : %d\n", fd);

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

            close(fd);
            return 0;
        }

        // let's wait
        int epfd = epoll_create1(0);
        struct epoll_event trg, ret;
        trg.events = EPOLLIN;
        trg.data.fd = 99999; // anything ok (should use ptr though)
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &trg);

        int selected = epoll_wait(epfd, &ret, 1, 5000);
        printf("epoll returns. ready fd n: %d\n", selected);

        if (selected == 0)
        {
            close(fd);
            return 0;
        }
        else
        {
            printf("ready data: %d\n", ret.data.fd);
        }
    }
}