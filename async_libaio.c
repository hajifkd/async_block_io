#include <libaio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define N_BUF 1024

void callback(io_context_t ctx, struct iocb *iocb, long res, long res2)
{
    char *buf = (char *)iocb->u.c.buf;
    puts("callback called");
    buf[iocb->u.c.nbytes] = '\0';
    printf("%s", buf);
}

int main()
{
    char buf[N_BUF];
    int fd, size;

    fd = open("file", O_RDONLY);
    puts("open succeeds");

    // see man **3** io_queue_init
    io_context_t ctx;
    struct iocb *ptr, iocb;
    io_queue_init(1, &ctx);
    io_prep_pread(&iocb, fd, buf, N_BUF - 1, 0);
    io_set_callback(&iocb, callback);
    ptr = &iocb;
    io_submit(ctx, 1, &ptr);

    // callback does not called unless io_queue_run is called
    // AIO is single-threaded (e.g. POSIX AIO)
    io_queue_run(ctx);

    return 0;
}