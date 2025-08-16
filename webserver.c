// webserver.c - Simple Multithreaded Web Server in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void *handle_client(void *arg) {
    int client_sock = *((int *)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    int read_size = recv(client_sock, buffer, BUFFER_SIZE, 0);
    if (read_size > 0) {
        buffer[read_size] = '\0';
        printf("Received request:\n%s\n", buffer);

        // Simple HTTP response
        char response[BUFFER_SIZE];
        FILE *html_file = fopen("index.html", "r");
        if (html_file == NULL) {
            char *error = "HTTP/1.1 404 NOT FOUND\r\nContent-Type: text/html\r\n\r\n<h1>404 File Not Found</h1>";
            send(client_sock, error, strlen(error), 0);
        } else {
            char file_content[BUFFER_SIZE];
            fread(file_content, sizeof(char), BUFFER_SIZE, html_file);
            fclose(html_file);

            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", file_content);
            send(client_sock, response, strlen(response), 0);
        }
    }

    close(client_sock);
    return NULL;
}

int main() {
    int server_sock, client_sock, *new_sock;
    struct sockaddr_in server, client;
    socklen_t addr_len = sizeof(struct sockaddr_in);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    listen(server_sock, 10);
    printf("Web Server started on port %d\n", PORT);

    while ((client_sock = accept(server_sock, (struct sockaddr *)&client, &addr_len))) {
        pthread_t tid;
        new_sock = malloc(1);
        *new_sock = client_sock;
        pthread_create(&tid, NULL, handle_client, (void *)new_sock);
        pthread_detach(tid);
    }

    close(server_sock);
    return 0;
}
