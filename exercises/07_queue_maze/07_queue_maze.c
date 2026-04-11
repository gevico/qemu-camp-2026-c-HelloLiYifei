#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

struct Queue {
	int data[25][2]; 
	int front;
	int rear;
};

struct Queue q;

void InitQueue() {
	q.front = 0;
	q.rear = 0; 
}

int IsEmpty() {
	return q.front == q.rear;
}

void EnQueue(int x, int y) {
	q.data[q.rear][0] = x;
	q.data[q.rear][1] = y;
	q.rear++;
}

int DeQueue(int *x, int *y) {
	if (IsEmpty())
		return 0;
	*x = q.data[q.front][0];
	*y = q.data[q.front][1];
	q.front++;
	return 1;
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
    // 四个方向：下、右、上、左
    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};
    
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        
        if (new_x >= 0 && new_x < MAX_ROW && new_y >= 0 && new_y < MAX_COL &&
            maze[new_x][new_y] == 0 && visited[new_x][new_y] == 0) {
            
            visited[new_x][new_y] = 1;
            parent[new_x][new_y][0] = x;
            parent[new_x][new_y][1] = y;
            EnQueue(new_x, new_y);
        }
    }
}

void BFS(int x, int y, int x_goal, int y_goal) {
	EnQueue(x, y);
	visited[x][y] = 1;

	while (!IsEmpty()) {
		int curr_x, curr_y;
		DeQueue(&curr_x, &curr_y);
		
		if (curr_x == x_goal && curr_y == y_goal) {
			return;
		}
		
		visit(curr_x, curr_y);
	}
}

void PrintPath(int x, int y) {
	printf("(%d, %d)\n", x, y);
	if (parent[x][y][0] != -1 && parent[x][y][1] != -1) {
		PrintPath(parent[x][y][0], parent[x][y][1]);
	}
}


int main(void)
{
	InitQueue();
	InitParent();
	InitVisited();

	BFS(0, 0, 4, 4);

	PrintPath(4, 4);
	return 0;
}