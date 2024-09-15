#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define BACKLOG 10
#define BUFFER_SIZE 1024

int main(int argc, char **argv){
  if(argc != 2){
    printf("Usage: %s <port>\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  printf("Port: %d\n", port);

  int n_client = 0;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port);

  bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
  printf("[+]Bind\n");

  listen(sockfd, BACKLOG);
  printf("[+]Listening for the client\n");

  int i = 1;
  while(i){
    int client_socket = accept(sockfd, NULL, NULL);
    n_client++;
    printf("Client %d connected\n", n_client);

    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    
    if(bytes_received > 0) {
      buffer[bytes_received] = '\0';
      printf("Received from client: %s", buffer);
      send(client_socket, buffer, bytes_received, 0);
    }

    close(client_socket);
  }

  close(sockfd);
  return 0;
}
