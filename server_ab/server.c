//
//  main.c
//  server_ab
//
//  Created by mac on 15/12/2018.
//  Copyright © 2018 mac. All rights reserved.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define MES_TO_ALL 8
#define MAX_MES 100
#define MAX_MES_SEND 200
#define DOESNT_EXIST -1
#define DOESNT_NAMED 0
#define NAMED 1


struct client
{
    int client_name;
    int client_to_write;
    struct sockaddr_in addrfrom;
    struct sockaddr_in addrto;
};


struct sockaddr_in Create_servaddr(int i);

void Create_socket(int * sockfd, struct sockaddr_in servaddr);

int Is_port_exist(int num_of_prs, struct sockaddr_in swap, struct client ** chat);

void Create_client(struct client ** chat, int * num_of_prs, struct sockaddr_in swap, char * message);

int Is_partner_named(struct client ** chat, int current_client);

void Find_partner(struct client ** chat, char * message, int current_client, int num_of_prs, int sockfd, unsigned int sizeofclient);

void Send_mes(struct client ** chat, char * message, int current_client, int sockfd, int num_of_prs, int sizeofclient);

int Is_it_to_all(char * message);




int Is_it_to_all(char * message)
{
    int i;
    char to_all[MES_TO_ALL + 1] = {0};
    for(i = 0; i < MES_TO_ALL; i++)
    {
        to_all[i] = message[i];
    }
    to_all[i] = '\0';
    if(!strcmp(to_all, "TO_ALL: ")) return 1;
    else return 0;
}


/*void Find_partner(struct client ** chat, char * message, int current_client, int num_of_prs, int sockfd, unsigned int sizeofclient)
{
    char status_message[MAX_MES] = {0};
    int i;
    assert(chat[num_of_prs]->client_to_write);
    strcpy(chat[current_client]->client_to_write, message);
    for(i = 0; i < num_of_prs; i++)
    {
        if(chat[i])
        {
            if(!strcmp(chat[current_client]->client_to_write, chat[i]->client_name))
            {
                chat[current_client]->addrto.sin_port = chat[i]->addrfrom.sin_port;
                chat[current_client]->addrto.sin_family = chat[i]->addrfrom.sin_family;
                chat[current_client]->addrto.sin_addr.s_addr = chat[i]->addrfrom.sin_addr.s_addr;
                strcpy(status_message, "EXCELLENT! WRITE YOUR FIRST MESSAGE. TO LEAVE WRITE /q\n");
                if(sendto(sockfd, status_message, strlen(status_message), 0, (struct sockaddr *) &(chat[current_client]->addrfrom), sizeofclient) < 0)
                {
                    perror("sendto");
                    close(sockfd);
                    exit(-1);
                }
                return ;
            }
        }
    }
    for(i = 0; i < MAX_MES; i++)
    {
        chat[current_client]->client_to_write[i] = '\0';
    }
    strcpy(status_message, "THIS USER DOES NOT EXIST :( PLS TRY ANYBODY ELSE\n");
    if(sendto(sockfd, status_message, strlen(status_message), 0, (struct sockaddr *) &(chat[current_client]->addrfrom), sizeofclient) < 0)
    {
        perror("sendto");
        close(sockfd);
        exit(-1);
    }
};
*/
void create_client(struct client ** chat, int * num_of_prs, struct sockaddr_in swap, int message)
{
    chat[* num_of_prs] = calloc(1, sizeof(struct client));
    chat[* num_of_prs]->addrfrom.sin_port = swap.sin_port;
    chat[* num_of_prs]->addrfrom.sin_family = swap.sin_family;
    chat[* num_of_prs]->addrfrom.sin_addr.s_addr = swap.sin_addr.s_addr;
    chat[* num_of_prs]->client_name = message;
    (* num_of_prs)++;
}

/*int Is_partner_named(struct client ** chat, int current_client)
{
    if(chat[current_client]->client_to_write[0] == '\0') return DOESNT_NAMED;
    else return NAMED;
}
*/
int Is_port_exist(int num_of_prs, struct sockaddr_in swap, struct client ** chat)
{
    int i;
    for(i = 0; i < num_of_prs; i++)
    {
        if(chat[i])
        {
            if(swap.sin_port == chat[i]->addrfrom.sin_port) return i;
        }
    }
    return DOESNT_EXIST;
};

struct sockaddr_in Create_servaddr(int i)
{
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(51002);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    return server;
}

void Create_socket(int * sockfd, struct sockaddr_in servaddr)
{
    if((* sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("sockfd");
        exit(1);
    }
    if(bind(* sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        close(* sockfd);
        exit(2);
    }
}


int main()
{
    struct sockaddr_in swap;
    int sockfd = 0;
    int num_of_prs = 0;
    unsigned int sizeofclient = 0;
    char * name = calloc(MAX_MES, sizeof(char));
    double message[3];
    
    
    struct sockaddr_in servaddr = Create_servaddr(1);
    Create_socket(&sockfd, servaddr);
    
    struct client ** chat = calloc(1, sizeof(struct client * ));
    chat[num_of_prs] = calloc(1, sizeof(struct client));
    
    for(int i = 0; i < 2;)
    {
        sizeofclient = sizeof(chat[0]->addrfrom);
        if(recvfrom(sockfd, name, MAX_MES - 1, 0, (struct sockaddr *) &swap, &sizeofclient) < 0)
        {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }
        
        //int current_client = Is_port_exist(i, swap, chat);
        create_client(chat, &i, swap, i);
        //Find_partner(chat, name, current_client, i, sockfd, sizeofclient);
        if(recvfrom(sockfd, &(message[i - 1]), MAX_MES - 1, 0, (struct sockaddr *) &swap, &sizeofclient) < 0)
        {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }
        
    }
    message[2] = message[0] + message[1];
    if(sendto(sockfd, message + 2, sizeof(double), 0, (struct sockaddr *) &(chat[0]->addrfrom), sizeofclient) < 0)
    {
        perror("sendto mes");
        close(sockfd);
        exit(-15);
    }
    if(sendto(sockfd, message + 2, sizeof(double), 0, (struct sockaddr *) &(chat[1]->addrfrom), sizeofclient) < 0)
    {
        perror("sendto mes");
        close(sockfd);
        exit(-15);
    }
    return 0;
}
