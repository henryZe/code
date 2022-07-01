#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILEID 1001
#define MAX_FILE_BLOCKS 101
#define QUEUE_SIZE 1001

bool __result = true;

void EXPECT_EQ(int test, int reference)
{
    if (test != reference)
        __result = false;
}

#define RECEIVE_REQ 0
#define QUERY_REQ   1

struct node {
    int fileid;
};

struct queue {
    int queue[QUEUE_SIZE];
    int front;
    int rear;
};

int enqueue(struct queue *q, int id)
{
    if (q->rear == (q->front - 1)) {
        return -1;
    }

    q->queue[q->rear] = id;
    q->rear = (q->rear + 1) % QUEUE_SIZE;

    return 0;
}

int dequeue(struct queue *q)
{
    int id;

    if (q->front == q->rear) {
        return -1;
    }

    id = q->queue[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    return id;
}

int queue_peek(struct queue *q)
{
    if (q->front == q->rear) {
        return -1;
    }
    return q->queue[q->front];
}

typedef struct file {
    int status;
    int time_start;
    int block_cnt;
    int residue;
    bool file_block[MAX_FILE_BLOCKS];
} File;

enum {
    UNUSED,
    RECEIVING,
    TIMEOUT,
    COMPLETE,
};

typedef struct fileSystem {
    int timeout;
    int saved_cnt;
    File files[MAX_FILEID];
    struct queue q;
} FileSystem;

FileSystem *FileSystemCreate(int timeout)
{
    FileSystem *f = malloc(sizeof(FileSystem));

    f->timeout = timeout;
    f->saved_cnt = 0;
    for (int i = 1; i < MAX_FILEID; i++) {
        f->files[i].status = UNUSED;
    }

    return f;
}

bool FileSystemRequest(FileSystem *sys, int time, int fileId, int number)
{
    if (sys->files[fileId].status != UNUSED)
        return false;

    sys->files[fileId].status = RECEIVING;
    sys->files[fileId].time_start = time;
    sys->files[fileId].block_cnt = number;
    sys->files[fileId].residue = number;
    for (int i = 0; i < number; i++) {
        sys->files[fileId].file_block[i] = false;
    }

    enqueue(&sys->q, fileId);
    return true;
}

int process_queue(FileSystem *sys, int time)
{
    int cur_file;

    // printf("before %d\n", queue_peek(&sys->q));

    while (1) {
        cur_file = queue_peek(&sys->q);
        if (cur_file < 0)
            // empty
            break;

        if (sys->files[cur_file].status == TIMEOUT) {
            dequeue(&sys->q);
            continue;
        }

        if (sys->files[cur_file].status == COMPLETE) {
            sys->saved_cnt++;
            dequeue(&sys->q);
            continue;
        }

        if (sys->files[cur_file].status == RECEIVING) {
            if (sys->files[cur_file].time_start + sys->timeout <= time) {
                sys->files[cur_file].status = TIMEOUT;
                dequeue(&sys->q);
                continue;
            } else {
                break;
            }
        }
    }

    // printf("after %d\n", queue_peek(&sys->q));

    return 0;
}

int FileSystemReceive(FileSystem *sys, int time, int fileId, int partId)
{
    if (sys->files[fileId].status != RECEIVING)
        return -1;

    if (sys->files[fileId].time_start + sys->timeout < time) {
        sys->files[fileId].status = TIMEOUT;
        return -1;
    }

    if (sys->files[fileId].file_block[partId])
        return -1;

    sys->files[fileId].file_block[partId] = true;
    sys->files[fileId].residue--;
    if (!sys->files[fileId].residue)
        sys->files[fileId].status = COMPLETE;

    process_queue(sys, time);
    return sys->files[fileId].residue;
}

int FileSystemQuery(FileSystem *sys, int time)
{
    process_queue(sys, time);
    return sys->saved_cnt;
}

void FileSystemFree(FileSystem *sys)
{
    free(sys);
}

bool TEST1(void)
{
    FileSystem *sys = FileSystemCreate(3);
    if (!sys) {
        __result = false;
        return false;
    }

    bool req = FileSystemRequest(sys, 0, 5, 2);
    EXPECT_EQ(req, true);
 
    int waittingNum = FileSystemReceive(sys, 1, 5, 1);
    EXPECT_EQ(waittingNum, 1);
 
    waittingNum = FileSystemReceive(sys, 2, 5, 0);
    EXPECT_EQ(waittingNum, 0);
 
    int savedCnt = FileSystemQuery(sys, 3);
    EXPECT_EQ(savedCnt, 1);
 
    FileSystemFree(sys);
}

bool TEST2(void)
{
    FileSystem *sys = FileSystemCreate(7);
    if (!sys) {
        __result = false;
        return false;
    }
 
    EXPECT_EQ(FileSystemRequest(sys, 0, 17, 2), true);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemRequest(sys, 1, 21, 2), true);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemRequest(sys, 2, 35, 1), true);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemReceive(sys, 3, 21, 1), 1);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemReceive(sys, 4, 35, 0), 0);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemReceive(sys, 5, 52, 1), -1);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemRequest(sys, 6, 21, 2), false);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemReceive(sys, 8, 21, 0), 0);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemQuery(sys, 9), 2);
    // printf("debug FileSystemQuery(sys, 9) = %d\n", FileSystemQuery(sys, 9));
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemRequest(sys, 10, 81, 1), true);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemRequest(sys, 13, 76, 1), true);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemReceive(sys, 14, 76, 0), 0);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemQuery(sys, 16), 2);
    printf("%d %d\n", __LINE__, __result);

    EXPECT_EQ(FileSystemQuery(sys, 17), 3);
    printf("%d %d\n", __LINE__, __result);
 
    FileSystemFree(sys);
}

int main(void)
{
    __result = true;
    TEST1();
    if (__result == false)
        printf("TEST1 fail\n");

    __result = true;
    TEST2();
    if (__result == false)
        printf("TEST2 fail\n");

    return 0;
}
