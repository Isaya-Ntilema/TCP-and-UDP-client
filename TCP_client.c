
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include<stdbool.h>
#define MAX 80
//#define PORT 8080
#define PORT 5000

#define SA struct sockaddr

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

 void func(int sockfd){

    char str[255];
    int num1,num2;
    float fnum1,fnum2;
    int number_to_send;
    int converted_number;
    float float_to_send;
    float float_converted;
    char st[80];

    for(;;)
    {

    read(sockfd, str, sizeof(str));


        printf("From Server : %s\n", str);
        bzero(str, sizeof(str));

            char msg[5] = "OK\n";

          write(sockfd, msg, strlen(msg));
          bzero(msg, sizeof(msg));

    read(sockfd, str, sizeof(str));

    char operator[6];
    char operand1 [20];
    char operand2 [20];
    int ret = sscanf(str, "%s %s %s", operator, operand1, operand2);
    // printf("Operator: %s\n", operator);
    // printf("operand1: %s\n", operand1);
    // printf("operator2: %s\n", operand2);
  
if(operator[0]=='f'){
       
        fnum1 = atof(operand1);
        fnum2 = atof(operand2);
      
        if ((strcmp(operator,"fadd")) == 0){
            float_to_send = fnum1 + fnum2; // Put your value
             }
        if ((strcmp(operator,"fsub")) == 0){
            float_to_send = fnum1 - fnum2; // Put your value
             }
        if ((strcmp(operator,"fmul")) == 0){
            float_to_send = fnum1 * fnum2; // Put your value
             }
        if ((strcmp(operator,"fdiv")) == 0){
            float_to_send = fnum1/fnum2; // Put your value
             }
           bzero(st, sizeof(st));
            sprintf(st, "%f", float_to_send);
            printf("Task from Server: %s\n", str);

            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            //write(sockfd, st, sizeof(st));
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");

            bzero(str, sizeof(str));
            //read(sockfd, str, sizeof(str));
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            }
             //printf("Responds Server : ");
            printf("Response from Server : %s\n", str);
            break;
       
}
        
else{
       num1 = atoi(operand1);
       num2 = atoi(operand2);
      
        if ((strcmp(operator,"add")) == 0){
            number_to_send = num1 + num2; // Put your value
             }
        if ((strcmp(operator,"sub")) == 0){
            number_to_send = num1 - num2; // Put your value
             }
        if ((strcmp(operator,"mul")) == 0){
            number_to_send = num1 * num2; // Put your value
             }
        if ((strcmp(operator,"div")) == 0){
            number_to_send = num1/num2; // Put your value
             }
           bzero(st, sizeof(st));
            sprintf(st, "%d", number_to_send);
            printf("Task from Server: %s\n", str);

            strcat(st,"\n");
            printf("Answer back to server: %s\n",st);
            //write(sockfd, st, sizeof(st));
            if (write(sockfd, st, strlen(st)) < 0)
            printf("Error writing to server\n");

            bzero(str, sizeof(str));
            
            if (read(sockfd, str, sizeof(str)) < 0){
             error("ERROR reading from socket");
            }
             //Printing response from server
            printf("Response from Server : %s\n", str);
            break;
}
           
 }
 }

int main(int argc, char *argv[])
{
	int sockfd, connfd, port;
	struct sockaddr_in servaddr, cli;
	struct hostent *server;

	char delim[]=":";
	char *Desthost=strtok(argv[1],delim);
        char *Destport=strtok(NULL,delim);
        port = atoi(Destport);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket created..\n");
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(Desthost);
	servaddr.sin_port = htons(port); 
	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	func(sockfd);

	close(sockfd);
}
