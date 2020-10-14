#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("Il faut un seul et unique port");
    exit(1);
  }

  int s = socket(AF_INET, SOCK_DGRAM, 0);
  
  if (s < 0) {
    dprintf(2, "Erreur : Socket\n");
    exit(1);
  
  }
  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons((unsigned short)atol(argv[1]));
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  
  for (int i = 0; i < 8; i++) {
    sin.sin_zero[i] = 0;
  }
 
  if (bind(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) < 0) {
    dprintf(2, "Erreur : Bind\n");
    exit(1);
  }

  char buf[BUF_SIZE + 1];
  bzero(buf, BUF_SIZE + 1);

  struct sockaddr source;
  ssize_t msg_len;
  socklen_t sender_len = sizeof(socklen_t);

  printf("Connecté au port %hu\n", (unsigned short)atol(argv[1]));
  while (strcmp(buf, "quit")) {
    bzero(buf, BUF_SIZE + 1);
    msg_len = recvfrom(s, (void *)buf, BUF_SIZE, 0, (struct sockaddr *)&source, &sender_len);
    printf("%s => %s [taille du message : %zd]\n", inet_ntoa(((struct sockaddr_in *)&source)->sin_addr), buf, msg_len);
  }
  puts("Connection terminé");
  close(s);
}
