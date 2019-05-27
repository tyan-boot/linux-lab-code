#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <pthread.h>


void *read_msg( void* ptr) {
  int fd = *((int*)ptr);
  char buff[1024];

  while(1) {
    memset(buff, 0, sizeof(buff));
    read(fd, buff, sizeof(buff));

    printf("> %s\n", buff);
  }
}

int main() {
  int fd;
  auto path = "/tmp/chat-pipe";
  char buff[1024];
  pthread_t rd_thread;
  
  mkfifo(path, 0666);
  fd = open(path, O_RDWR);

  pthread_create(&rd_thread, nullptr, read_msg, &fd);

  while(1) {
    scanf("%s", &buff);

    write(fd, buff, strlen(buff));
  }
  
}
