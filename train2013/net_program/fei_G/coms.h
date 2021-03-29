#ifndef COMMAND_H
#define COMMAND_H

#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <semaphore.h>

#define NAMELEN 50
#define MSGLEN  1000
#define COMLEN  1500
#define RECFRG  1448
#define HSIZE   10
#define FILENAME 128
#define MSGLIMIT 100
#define HL_HEADERSIZE	4
#define HL_FILESIZE	9
#define HL_FILETYPE	1
#define HL_1416		11
#define CAPACITY     50

#define IMHELP    \
  "Commands: help(h) list(ls) talk(tk) sendfile(sf)\n"\
  "Commands: getfile(gf) refresh(rf) ceaseSend(cs) quit(q)\n"

typedef int (*Mysnd)(int, const char*, int, int);

typedef struct filenode filenode;



typedef struct command
{
  unsigned int version;
  unsigned int packetNo;
  char         senderName[NAMELEN];
  char         senderHost[NAMELEN];
  unsigned int commandNo;
  char         additional[MSGLEN];
  struct sockaddr_in peer;
  filenode *   fileList;
  struct command *next;
}command;



struct filenode 
{
  int    tcpSock;
  unsigned int    fileNo;
  char   fileName[FILENAME];
  char   fileSize[NAMELEN];
  char   mtime[NAMELEN];
  int    fileType;
  char   otherAttrs[2*NAMELEN];
  struct filenode* next;
};



typedef struct gsNode
{
  int tcpSock;
  struct sockaddr_in peer;
  unsigned int packetNo;
  int	 transferring;
  int    cancelled;
  char  *targetDir;
  filenode fileList;
  struct gsNode *next;
} gsNode;



typedef struct msgList
{
  command comHead;
  command *comTail;
} msgList;




extern const char allHosts[];
extern int msgSock;
extern int tcpSock;
extern struct passwd* pwd; 
extern struct utsname sysName;
extern char workDir[FILENAME];
extern int utf8;

extern gsNode sendFHead, getFHead;
extern msgList mList;

extern pthread_mutex_t sendFMutex; 
extern pthread_mutex_t getFMutex; 
extern pthread_mutex_t msgMutex; 
extern pthread_mutex_t usrMutex;
extern sem_t waitNonEmpty, waitNonFull;

extern int msgParser(char *msg, int size, command* com);
extern int msgCreater(char* msg, command* com, size_t msgLen);
extern filenode* getFilelist(const char* comFiles);
extern void initCommand(command *com, unsigned int flag);
extern void deCommand(command *com);
extern void initGsNode(gsNode *gs);
extern void deGsNode(gsNode *gs);

#endif
