## Preparation

### Install libaio

```sh
sudo apt install libaio1 libaio-dev
```

### compile

```sh
gcc async_libaio.c -laio
```

Just `gcc foo.c` is fine for the other codes.

### make fifo

```sh
mkfifo file
```

### run

```sh
cat file
```

```sh
tee file
```