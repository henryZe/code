#ifndef __COMMON_H__
#define __COMMON_H__

enum    CMD
{
	CMD_REG,
	CMD_LOGIN,
	CMD_QUIT,
	CMD_DEL,
	CMD_KILL,
	CMD_CHAT,

	ACK_OK,
	ACK_ERR,
	ACK_REP,
	ACK_NON,
};

struct clt
{
	char   name[20];
	char   chat[20];
	char   pass[20];
	char   sex[2];
	int    tcpfd;
	struct sockaddr_in tcpaddr;
	int    sockaddrlen;
};


#endif
