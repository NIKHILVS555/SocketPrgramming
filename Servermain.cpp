#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//ReadData : thred function for continously checking the socket for reading data

void * ReadData(void *threadid) {
    int sockfd = *(int * )threadid;
   while(1)
   {
       char buffer[255]={0};
     int n = read(sockfd,buffer,255);
   // if (n < 0) 
    //    error("ERROR reading from socket");
    printf("Client : %s\n",buffer);
   }
}
int main()
{
    int port;
    std::cout<<"Enter the Port";
    std::cin>>port;

    int SockHandle=socket(AF_INET,SOCK_STREAM,0);
    if(SockHandle<0)
      {
          std::cout<<"Invalid Socket Handle";
          return 1;
      }
      
    sockaddr_in serverSocket,cli_addr;
    memset(&serverSocket,0,sizeof(sockaddr_in));
    serverSocket.sin_family=AF_INET;
    serverSocket.sin_addr.s_addr=INADDR_ANY;
    serverSocket.sin_port=htons(port);
    if(bind(SockHandle,(sockaddr *)&serverSocket,sizeof(serverSocket))<0)
    {
        std::cout<<"Socket bind Failed";
        return 1;
    }
    listen(SockHandle,5);
    socklen_t clilen = sizeof(cli_addr);
    int newsockfd = accept(SockHandle, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
     {
         std::cout<<"ERROR on accept";
     }
     char buffer[256];
     bzero(buffer,256);

     pthread_t threads;
     int rc = pthread_create(&threads, NULL, ReadData, (void *)&newsockfd);
      
      if (rc) {
         std::cout << "Error:unable to create thread," << rc << std::endl;
         exit(-1);
      }


     /*int n = read(newsockfd,buffer,255);
     if (n < 0) 
     {
         std::cout<<"ERROR reading from socket";
         return 1;
      
     }
     printf("Here is the message: %s\n",buffer);*/

     while (1)
     {
         std::cin >> buffer;
         int n = write(newsockfd, buffer, strlen(buffer));
         if (n < 0)
         {
             std::cout << "ERROR writing to socket";
             return 1;
         }
     }
     close(newsockfd);
     close(SockHandle);
    return 1;
}