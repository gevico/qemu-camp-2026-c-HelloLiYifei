#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct {
    int data[25][2]; // 存储坐标 [row, col]
    int top;
} Stack;

int maze[MAX_ROW][MAX_COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
};

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void InitStack(Stack *s) {
    s->top = -1;
}

void Push(Stack *s, int x, int y) {
    if (s->top < 24) {
        s->top++;
        s->data[s->top][0] = x;
        s->data[s->top][1] = y;
    }
}

void Pop(Stack *s, int *x, int *y) {
    if (s->top >= 0) {
        *x = s->data[s->top][0];
        *y = s->data[s->top][1];
        s->top--;
    }
}

int IsEmpty(Stack *s) {
    return s->top == -1;
}

int parent[MAX_ROW][MAX_COL][2];
int visited[MAX_ROW][MAX_COL];

void InitParent() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            parent[i][j][0] = -1;
            parent[i][j][1] = -1;
        }
    }
}

void InitVisited() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            visited[i][j] = 0;
        }
    }
}

void visit(int x, int y) {
    visited[x][y] = 1;
}

void DFS(int x, int y, int end_x, int end_y) {
    Stack s;
    InitStack(&s);
    
    Push(&s, x, y);
    visit(x, y);

    int curr_x, curr_y;

    // DFS search
    while (!IsEmpty(&s)) {
        Pop(&s, &curr_x, &curr_y);

        if (curr_x == end_x && curr_y == end_y) {
            return;
        }

        for (int i = 3; i >= 0; i--) {
            int next_x = curr_x + dx[i];
            int next_y = curr_y + dy[i];

            if (next_x >= 0 && next_x < MAX_ROW && next_y >= 0 && next_y < MAX_COL) {

                if (maze[next_x][next_y] == 0 && !visited[next_x][next_y]) {
                    visit(next_x, next_y);
                    parent[next_x][next_y][0] = curr_x;
                    parent[next_x][next_y][1] = curr_y;
                    Push(&s, next_x, next_y);
                }
            }
        }
    }
}

void PrintPath(int end_x, int end_y) {
    if (!visited[end_x][end_y]) {
        printf("No path!\n");
        return;
    }

    int path[25][2];
    int path_len = 0;
    
    int x = end_x;
    int y = end_y;

    while (x != -1 && y != -1) {
        path[path_len][0] = x;
        path[path_len][1] = y;
        path_len++;
        
        int prev_x = parent[x][y][0];
        int prev_y = parent[x][y][1];
        x = prev_x;
        y = prev_y;
    }

    for (int i = 0; i < path_len; i++) {
        printf("(%d, %d)\n", path[i][0], path[i][1]);
    }
}

int main(void)
{
    InitParent();
    InitVisited();

    DFS(0, 0, 4, 4);
    PrintPath(4, 4);

    return 0;
}