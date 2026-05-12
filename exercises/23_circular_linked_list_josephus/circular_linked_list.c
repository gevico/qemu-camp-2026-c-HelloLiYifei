#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    // TODO: 在这里添加你的代码
    Node* head = NULL;
    Node* current = NULL;

    for (int i = 1; i <= n; i++) {
        // 创建新节点
        Node* new_node = (Node*)malloc(sizeof(Node));
        new_node->id= i;
        new_node->next = NULL;

        if (i == 1) {
            head = new_node;
        } else {
            current->next = new_node;
        }
        current = new_node;
    }

    if (head != NULL) {
        current->next = head;
    }

    return head;
}

void free_list(Node* head) {
    // TODO: 在这里添加你的代码
    if (head == NULL) {
        return;
    }

    Node* current = head;
    
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
}
