#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 6 // Batas maksimal stack 6 elemen

// Struktur Node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Struktur Stack
typedef struct Stack {
    Node* top;
    int count;
} Stack;

// Fungsi untuk membuat stack baru
void createStack(Stack* stack) {
    stack->top = NULL;
    stack->count = 0;
}

// Fungsi recycle untuk membebaskan memori node
void recycle(Node* node) {
    free(node);  // Membebaskan memori
}

// Fungsi push
bool push(Stack* stack, int data) {
    if (stack->count >= MAX_STACK_SIZE) {
        return false;  // Stack penuh jika elemen sudah mencapai MAX_STACK_SIZE
    }
    Node* newPtr = (Node*)malloc(sizeof(Node));
    if (newPtr == NULL) {
        return false;  // Jika memori habis
    }
    newPtr->data = data;
    newPtr->next = stack->top;
    stack->top = newPtr;
    stack->count++;  // Tambahkan elemen
    return true;
}

// Fungsi pop 
bool pop(Stack* stack, int* dataOut) {
    if (stack->top == NULL) {
        return false; // Stack kosong
    }
    Node* dltPtr = stack->top;
    *dataOut = stack->top->data;
    stack->top = stack->top->next;
    recycle(dltPtr);  
    stack->count--;  // Kurangi elemen
    return true;
}

// Fungsi untuk mendapatkan elemen teratas stack
bool stackTop(Stack* stack, int* dataOut) {
    if (stack->top == NULL) {
        return false; // Stack kosong
    }
    *dataOut = stack->top->data;
    return true;
}

// Fungsi untuk mengecek apakah stack kosong
bool emptyStack(Stack* stack) {
    return stack->top == NULL;
}

// Fungsi untuk mengecek apakah stack penuh
bool fullStack(Stack* stack) {
    return stack->count >= MAX_STACK_SIZE;
}

// Fungsi untuk menghitung jumlah elemen di stack
int stackCount(Stack* stack) {
    return stack->count;
}

// Fungsi untuk menghancurkan stack
void destroyStack(Stack* stack) {
    Node* temp;
    while (stack->top != NULL) {
        temp = stack->top;
        stack->top = stack->top->next;
        recycle(temp);  // Menggunakan recycle
    }
    stack->count = 0;
}

// Fungsi utama dengan pilihan menu
int main() {
    Stack stack;
    int choice, value;
    bool success;

    createStack(&stack);

    do {
        printf("\nPilih Operasi Stack:\n");
        printf("1. Push Stack\n");
        printf("2. Pop Stack\n");
        printf("3. Stack Top\n");
        printf("4. Empty Stack\n"); // Cek Stack Kosong
        printf("5. Full Stack\n"); // Cek Stack Penuh
        printf("6. Stack Count\n"); // Hitung Elemen Stack
        printf("7. Destroy Stack\n"); // Hancurkan Stack
        printf("8. Keluar\n");
        printf("Masukkan pilihan Anda: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan nilai untuk push: ");
                scanf("%d", &value);
                success = push(&stack, value);
                if (success)
                    printf("Push berhasil.\n");
                else
                    printf("Push gagal. Stack penuh.\n");
                break;

            case 2:
                success = pop(&stack, &value);
                if (success)
                    printf("Pop berhasil. Nilai yang di-pop: %d\n", value);
                else
                    printf("Pop gagal. Stack kosong.\n");
                break;

            case 3:
                success = stackTop(&stack, &value);
                if (success)
                    printf("Elemen teratas stack: %d\n", value);
                else
                    printf("Stack kosong.\n");
                break;

            case 4:
                if (emptyStack(&stack))
                    printf("Stack kosong.\n");
                else
                    printf("Stack tidak kosong.\n");
                break;

            case 5:
                if (fullStack(&stack))
                    printf("Stack penuh.\n");
                else
                    printf("Stack tidak penuh.\n");
                break;

            case 6:
                printf("Jumlah elemen di stack: %d\n", stackCount(&stack));
                break;

            case 7:
                destroyStack(&stack);
                printf("Stack telah dihancurkan.\n");
                break;

            case 8:
                printf("Keluar dari program.\n");
                destroyStack(&stack);
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 8);

    return 0;
}

