#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
  const unsigned reuse = (argc == 2 && strcmp(argv[1], "reuse") == 0);
  int s = -1;
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("socket() failed");
      exit(1);
    }
  printf("using socket=%d\n", socket);

  if (reuse)
    {
      int on = 1;
      printf("setsockopt(SO_REUSEADDR)\n");
      if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        {
          perror("setsockopt(SO_REUSEADDR) failed");
        }
    }

  struct sockaddr_in saddr;
  bzero((char *) &saddr, sizeof(saddr));
  saddr.sin_family      = AF_INET;
  saddr.sin_addr.s_addr = htonl(INADDR_ANY);
  saddr.sin_port        = htons(12345);

  if (bind(s, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)
    {
      perror("bind() failed");
      exit(1);
    }

  listen(s, 5);

  while (1)
    {
      struct sockaddr_in caddr;
      socklen_t caddr_len = sizeof(caddr);
      int s2;
      if ((s2 = accept(s, (struct sockaddr *) &caddr, &caddr_len)) < 0)
        {
          perror("accept() failed");
          exit(1);
        }
      close(s2);
    }

  return 0;
}


