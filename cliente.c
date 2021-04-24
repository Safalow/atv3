#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

void enviar_arquivo(FILE *fp, int socket_tcp)
{
    char data[1024] = {0};

    while (fgets(data, 1024, fp) != NULL)
    {
        if (send(socket_tcp, data, sizeof(data), 0) == -1)
        {
            perror("Erro ao enviar arquivo.");
            exit(1);
        }
        bzero(data, 1024);
    }
}

int main()
{
    char *ip = "127.0.0.1";
    int porta = 8080;
    int e;

    int socket_tcp;
    struct sockaddr_in endereco_servidor;
    FILE *fp;
    char *filename = "cliente.txt";

    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_tcp < 0)
    {
        perror("Erro de socket");
        exit(1);
    }

    endereco_servidor.sin_family = AF_INET;
    endereco_servidor.sin_port = porta;
    endereco_servidor.sin_addr.s_addr = inet_addr(ip);

    e = connect(socket_tcp, (struct sockaddr *)&endereco_servidor, sizeof(endereco_servidor));
    if (e == -1)
    {
        perror("Erro de socket");
        exit(1);
    }
    printf("\n\t Conectado ao servidor.\n");

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("Erro ao ler o arquivo.");
        exit(1);
    }

    enviar_arquivo(fp, socket_tcp);
    printf("\t Dados do arquivo transferidos com sucesso.\n");

    printf("\t Encerrando conexão.\n\n");
    close(socket_tcp);

    return 0;
}
