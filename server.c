//
//  main.c
//  messenger
//
//  Created by mac on 09.12.2018.
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
    char client_name[MAX_MES];
    char client_to_write[MAX_MES];
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




void Send_mes(struct client ** chat, char * message, int current_client, int sockfd, int num_of_prs, int sizeofclient)
{
    int i = 0;
    if(strcmp(message, "/q\n"))
    {
        if(Is_it_to_all(message))
        {
            char writer_with_message[MAX_MES_SEND] = {0};
            for(i = 0; i < MAX_MES && chat[current_client]->client_name[i] != '\n'; i++)
            {
                writer_with_message[i] = chat[current_client]->client_name[i];
            }
            writer_with_message[i]= '\0';
            strcat(writer_with_message, ":");
            strcat(writer_with_message, message);
            for(i = 0; i < num_of_prs; i++)
            {
                if(chat[i])
                {
                    if(sendto(sockfd, writer_with_message, strlen(writer_with_message), 0, (struct sockaddr *) &(chat[i]->addrfrom), sizeofclient) < 0)
                    {
                        printf("pers_num = %d\n", i);
                        perror("sendto mes all");
                        close(sockfd);
                        exit(-15);
                    }
                }
            }
        }
        else
        {
            char writer_with_message[MAX_MES_SEND] = {0};
            for(i = 0; i < MAX_MES && chat[current_client]->client_name[i] != '\n'; i++)
            {
                writer_with_message[i] = chat[current_client]->client_name[i];
            }
            writer_with_message[i]= '\0';
            strcat(writer_with_message, ":");
            strcat(writer_with_message, message);
            if(sendto(sockfd, writer_with_message, strlen(writer_with_message), 0, (struct sockaddr *) &(chat[current_client]->addrto), sizeofclient) < 0)
            {
                perror("sendto mes");
                close(sockfd);
                exit(-15);
            }
        }
    }
    else if(strcmp(message, "/q\n") == 0)
    {
        char leave_mes[MAX_MES_SEND] = {0};
        strcpy(leave_mes, "YOUR PARTNER JUST LEAVED. SO SAD...LEAVE OR CHAT WITH OTHER USER\n");
        if(sendto(sockfd, leave_mes, strlen(leave_mes), 0, (struct sockaddr *) &(chat[current_client]->addrto), sizeofclient) < 0){
            perror("sendto mes");
            close(sockfd);
            exit(-15);
        }
        for(; i < num_of_prs; i++)
        {
            if(chat[i])
            {
                if(!strcmp(chat[current_client]->client_name, chat[i]->client_to_write)) break;
            }
        }
        if(i != num_of_prs)
        {
            bzero(chat[i]->client_to_write, MAX_MES);
            bzero(&chat[i]->addrto, sizeof(chat[i]->addrto));
            free(chat[current_client]);
        }
    }
}

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


void Find_partner(struct client ** chat, char * message, int current_client, int num_of_prs, int sockfd, unsigned int sizeofclient)
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

void Create_client(struct client ** chat, int * num_of_prs, struct sockaddr_in swap, char * message)
{
    chat[* num_of_prs] = calloc(1, sizeof(struct client));
    chat[* num_of_prs]->addrfrom.sin_port = swap.sin_port;
    chat[* num_of_prs]->addrfrom.sin_family = swap.sin_family;
    chat[* num_of_prs]->addrfrom.sin_addr.s_addr = swap.sin_addr.s_addr;
    strcpy(chat[* num_of_prs]->client_name, message);
    (* num_of_prs)++;
}

int Is_partner_named(struct client ** chat, int current_client)
{
    if(chat[current_client]->client_to_write[0] == '\0') return DOESNT_NAMED;
    else return NAMED;
}

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
    char message[MAX_MES] = {0};
    
    struct sockaddr_in servaddr = Create_servaddr(1);
    Create_socket(&sockfd, servaddr);
    
    struct client ** chat = calloc(1, sizeof(struct client * ));
    chat[num_of_prs] = calloc(1, sizeof(struct client));
    
    
    while(1)
    {
        sizeofclient = sizeof(chat[0]->addrfrom);
        if(recvfrom(sockfd, message, MAX_MES - 1, 0, (struct sockaddr *) &swap, &sizeofclient) < 0)
        {
            perror("recvfrom");
            close(sockfd);
            exit(-1);
        }
        
        int current_client = Is_port_exist(num_of_prs, swap, chat);
        if(current_client == DOESNT_EXIST)
        {
            Create_client(chat, &num_of_prs, swap, message);
        }
        else if(Is_partner_named(chat, current_client) == DOESNT_NAMED)
        {
            Find_partner(chat, message, current_client, num_of_prs, sockfd, sizeofclient);
        }
        else
            Send_mes(chat, message, current_client, sockfd, num_of_prs, sizeofclient);
    }
    
    return 0;
}

