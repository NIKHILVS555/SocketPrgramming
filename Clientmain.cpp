#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <pthread.h>
// error : For printing the errror and exit the program on error
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
//ReadData : thred function for continously checking the socket for reading data
void * ReadData(void *threadid) {
    int sockfd = *(int * )threadid;
   while(1)
   {
       char buffer[255]={0};
     int n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Server : %s\n",buffer);
   }
}
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    
    std::cout<<"Enter the port number";
    std::cin>>portno;// = atoi(argv[2]);
    char serveradd[255];
    std::cout<<"enter the server Address:";
    std::cin>> serveradd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(serveradd);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //printf("Please enter the message: ");
    bzero(buffer,256);
    //fgets(buffer,255,stdin);
      pthread_t threads;
    int rc = pthread_create(&threads, NULL, ReadData, (void *)&sockfd);
      
      if (rc) {
         std::cout << "Error:unable to create thread," << rc << std::endl;
         exit(-1);
      }
    while(1)
    {
    std::cin>>buffer;
    n = write(sockfd,buffer,strlen(buffer));
    
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    }
    
    close(sockfd);
    return 0;
}
