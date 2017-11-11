#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include "aria.h"

#pragma comment(lib,"ws2_32.lib")

void swcmd(char * c,ArRobot* robot);
int reccmd(ArRobot* robot);
void up(ArRobot* robot);
void down(ArRobot* robot);
void right(ArRobot* robot);
void left(ArRobot* robot);

int main(int argc, char* argv[])
{
	//robot�ĳ�ʼ����
	Aria::init();
	ArRobot robot;
	ArArgumentParser parser(&argc,argv);
	ArSimpleConnector connector(&parser);
	parser.loadDefaultArguments();
	if(!connector.parseArgs())//��������������
	{

		printf("δ֪����\n");

		Aria::exit(0);

		exit(1);

	}

	if(!connector.connectRobot(&robot))
	{
		printf("����ʧ��\n");

		Aria::exit(0);

		exit(1);

	}

	robot.runAsync(true);//���첽ģʽ����

	//robot.lock();
	robot.enableMotors();//����������
	
	reccmd(&robot);//��������
    
	robot.disableMotors();
	Aria::exit(0);

    return 0;
}


void up(ArRobot* robot)
{
	//printf("UP\n");
	robot->move(150);
}

void down(ArRobot* robot)
{
	//printf("DOWN\n");
	robot->move(-100);
}

void left(ArRobot* robot)
{
	//printf("LEFT\n");
	robot->setDeltaHeading(10);
}

void right(ArRobot* robot)
{
	//printf("RIGHT\n");
	robot->setDeltaHeading(-10);
}

//�Խ��������ʶ��
void swcmd(char * c,ArRobot* robot)
{
	char cmd=c[0];
	switch(cmd)
	{
		case 'U':	up(robot);break;
		case 'D':	down(robot); break;
		case 'L':	left(robot); break;
		case 'R':	right(robot);break;
		default:
			printf("%s������Ч!\n",c);
			break;
	}
}

int reccmd(ArRobot* robot)
{
	//��ʼ��WSA
    WORD sockVersion = MAKEWORD(2,2);
    WSADATA wsaData;
    if(WSAStartup(sockVersion, &wsaData)!=0)
    {
        return 0;
    }

    //�����׽���
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(slisten == INVALID_SOCKET)
    {
        printf("socket error !");
		getchar();
        return 0;
    }

    //��IP�Ͷ˿�
    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8888);
    sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
    if(bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
    {
        printf("bind error !\n");
    }

    //��ʼ����
    if(listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen error !");
		getchar();
        return 0;
    }

    //ѭ����������
    SOCKET sClient;
    sockaddr_in remoteAddr;
    int nAddrlen = sizeof(remoteAddr);
    char revData[255]; 
    while (true)
    {
        printf("�ȴ���������!\n");
        sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
        if(sClient == INVALID_SOCKET)
        {
            printf("accept error !");
            continue;
        }
        printf("���ܵ�һ�����ӣ�%s", inet_ntoa(remoteAddr.sin_addr));
        

        //��������
        int ret = recv(sClient, revData, 255, 0);        
        if(ret > 0)
        {
            revData[ret] = 0x00;
			printf("��%s���\n",revData);
			swcmd(revData,robot);
        }
		else
		{
			printf("\n");
		}

        //��������
        char * sendData = strcat(revData,"����ͳɹ���\n");
        send(sClient, sendData, strlen(sendData), 0);
		if (revData[0]=='E')
				break;
        closesocket(sClient);
    }
    WSACleanup();
	return 1;
}