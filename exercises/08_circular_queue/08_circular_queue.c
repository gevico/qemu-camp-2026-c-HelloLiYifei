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
    int id = q->data[out].id;
    q->data[out].id = -1;
    q->count--;
    return id;
}

void circular(Queue* q) {
    int j = 0;
    while (q->count > 1) {
        int count_steps = 0;
        // 数5个人
        while (count_steps < 5) {
            if (q->data[j].id != -1) {
                count_steps++;
            }
            if (count_steps < 5) {
                j = (j + 1) % 50;
            }
        }
        printf("淘汰: %d\n", outPeople(q, j));
        // 移动到下一个人
        j = (j + 1) % 50;
        while (q->data[j].id == -1 && q->count > 0) {
            j = (j + 1) % 50;
        }
    }
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    InitQueue(&q);
    circular(&q);
    
    for (int i = 0; i < MAX_PEOPLE; i++) {
        if (q.data[i].id != -1) {
            printf("最后剩下的人是: %d\n", q.data[i].id);
            break;
        }
    }

    return 0;
}