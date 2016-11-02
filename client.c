#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include "cJSON.h"
#define PORT 8886
int main(int argc,char **argv)
{
	struct sockaddr_in s_addr,c_addr;
	int sock;
	int addr_len;
	int len;
	char buf1[128];
	char buf[]="Hello everyone1!";
	char buff[]="Hello everyone2!";
	char bufff[]="Hello everyone3!";
	char *out ;
	cJSON *root,*fmt,*array,*dir1,*numberarray;
	root=cJSON_CreateObject();//创建项目
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());//在项目上添加项目
	cJSON_AddItemToObject(root, "array", array=cJSON_CreateArray());//在项目上添加项目
	cJSON_AddItemToObject(root, "numberarray", numberarray=cJSON_CreateArray());//在项目上添加项目
	cJSON_AddItemToArray(array,dir1=cJSON_CreateObject());
	cJSON_AddItemToArray(numberarray,cJSON_CreateNumber(1900));//类似的有cJSON_CreateString(char[])方法;
	cJSON_AddItemToArray(numberarray,cJSON_CreateNumber(1901));
	cJSON_AddNumberToObject(dir1,"1", 1800);
	cJSON_AddNumberToObject(dir1,"2", 1801);
	cJSON_AddStringToObject(fmt,"type", "rect");//在项目上的项目上添加字符串，这说明cJSON是可以嵌套的
	cJSON_AddNumberToObject(fmt,"width", 1920);
	cJSON_AddNumberToObject(fmt,"height", 1080);
	cJSON_AddNumberToObject(fmt,"frame rate", 24);
	out=cJSON_Print(root);
	if((sock=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("socket error!");
		exit(errno);
	}
	else
	{
		//printf("socket successful!");
	}
	s_addr.sin_family=AF_INET;
	s_addr.sin_port=PORT;
	s_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	addr_len=sizeof(s_addr);
	len=sendto(sock,out,512,0,(struct sockaddr*)&s_addr,addr_len);
	printf("%s\n",out);
	//printf("%d",sizeof(out));
	cJSON_Delete(root);
	free(out);
	/*
	while(1)
	{
		len = recvfrom(sock, buf1, sizeof(buf1) - 1, 0, (struct sockaddr*)&c_addr, &addr_len);
		if(len<0)
		{
			printf("recv error!");
			exit(errno);
		}
		else
		{
			printf("收到服务器的回应：%s\n",buf1);
			break;
		}
	}
	*/
	if(len<0)
	{
		printf("send error!");
		return 3;
	}
	//printf("send successful!");
	return 0;
}