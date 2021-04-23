#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

void write_file(int socket_tcp)
{
    int n;
    FILE *fp;
    char *filename = "servidor.txt";
    char buffer[1024];

    fp = fopen(filename, "w");
    while (1)
    {
        n = recv(socket_tcp, buffer, 1024, 0);
        if (n <= 0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, 1024);
    }
    return;
}

int main()
{
    char *ip = "127.0.0.1";
    int porta = 8080;
    int e;

    int socket_tcp, novo_socket;
    struct sockaddr_in endereco_socket_tcp, endereco_novo_socket;
    socklen_t tamanho_endereco_novo_socket;

    socket_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_tcp < 0)
    {
        perror("Erro de socket");
        exit(1);
    }
    printf("\n\t Socket do servidor criado.\n");

    endereco_socket_tcp.sin_family = AF_INET;
    endereco_socket_tcp.sin_port = porta;
    endereco_socket_tcp.sin_addr.s_addr = inet_addr(ip);

    e = bind(socket_tcp, (struct sockaddr *)&endereco_socket_tcp, sizeof(endereco_socket_tcp));
    if (e < 0)
    {
        perror("Erro de bind");
        exit(1);
    }

    if (listen(socket_tcp, 10) == 0)
    {
        printf("\t Pronto para receber...\n");
    }
    else
    {
        perror("Erro ao receber.");
        exit(1);
    }

    tamanho_endereco_novo_socket = sizeof(endereco_novo_socket);
    novo_socket = accept(socket_tcp, (struct sockaddr *)&endereco_novo_socket, &tamanho_endereco_novo_socket);
    write_file(novo_socket);
    printf("\t Dados recebidos com sucesso.\n\n");

    return 0;
}