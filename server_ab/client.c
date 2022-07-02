//
//  client.c
//  server_ab
//
//  Created by mac on 15/12/2018.
//  Copyright © 2018 mac. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE_OF_PREFIX 4
#define MAX_MES 100
#define REC_MAX_MES 200


void Send_mes(char * sendline, struct sockaddr_in servaddr, int sockfd);
void Intro(char * sendline, struct sockaddr_in servaddr, int sockfd);
void Who_you_wanna_send_mes(char * sendline, struct sockaddr_in servaddr, int sockfd);




void Resieve_mes(double * recvline, int sockfd)
{

    
    recvfrom(sockfd, recvline, REC_MAX_MES, 0, (struct sockaddr * ) NULL, NULL);

    printf("%f", *recvline);
}

void Send_mes(char * sendline, struct sockaddr_in servaddr, int sockfd)
{
    if(sendto(sockfd, sendline, strlen(sendline) + 1, 0 , (struct sockaddr * ) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("sendto");
        exit(1);
    }
}

void Intro(char * sendline, struct sockaddr_in servaddr, int sockfd)
{
    //printf("WELCOME HERE\nENTER YOUR NAME\n");
    fgets(sendline, MAX_MES, stdin);
    Send_mes(sendline, servaddr, sockfd);
    //printf("ENTER NAME OF USER YOU WANT TO SEND MESSAGE\n");
}

void Who_you_wanna_send_mes(char * sendline, struct sockaddr_in servaddr, int sockfd)
{
    fgets(sendline, MAX_MES, stdin);
    Send_mes(sendline, servaddr, sockfd);
}




int main(int argc, char ** argv)
{
    int i = 0;
    int sockfd = 0;
    double * recvline = 0;
    char sendline[REC_MAX_MES] = {0};
    struct sockaddr_in servaddr, cliaddr;
    int you = 0;
    
    
    if(argc != 2)
    {
        printf("YOU FORGET ABOUT SERVER ID\n");
        exit(-1);
    }
    
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("sockfd");
        exit(-1);
    }
    
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(0);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if(bind(sockfd, (struct sockaddr * ) &cliaddr, sizeof(cliaddr)) < 0)
    {
        perror("bind");
        close(sockfd);
        exit(1);
    }
    
    while(1)
    {
        Think_of(you);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(51002);
    
    if(inet_aton(argv[1], &servaddr.sin_addr) == 0)
    {
        perror("inet_aton");
        close(sockfd);
        exit(1);
    }
    
    pid_t pid = fork();
    
    if(pid)
    {
        Intro(sendline, servaddr, sockfd);
        while(1)
        {
            for(i = 0; i < MAX_MES; i++)
            {
                sendline[i] = '\0';
            }
            fgets(sendline, MAX_MES, stdin);
            Send_mes(sendline, servaddr, sockfd);
            if(!strcmp(sendline, "/q\n"))
            {
                kill(pid, SIGKILL);
                break;
            }
        }
    }
    else while(1)
        Resieve_mes(recvline, sockfd);
    close(sockfd);
    return 0;
}
