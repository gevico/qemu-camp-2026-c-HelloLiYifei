#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

void InitQueue(Queue* q) {
    for (int i = 0; i < MAX_PEOPLE; i++) {
        q->data[i].id = i + 1;  // 人员编号从1到50
    }
    q->head = 0;
    q->tail = MAX_PEOPLE - 1;
    q->count = MAX_PEOPLE;
}

int outPeople(Queue* q, int out) {
    int id = q->data[out];
    q->data[out] = -1;
    q->count = 0;
    return id;
}

void circular(Queue* q) {
    for (int i = 0; i < 50; i++) {
        int j = 0;
        while (q->count < 5) {
            ++j %= 50;
            if (q->data[j] != -1) {
                q->count ++;
            }
        }
        printf("%d ", outPeople(q, j));
    }
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    InitQueue(&q);
    circular(&q);
    
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}