# Bài 9: Stack - Queue

## 9.1. Cấu trúc dữ liệu

__Là cách tổ chức, và lưu trữ dữ liệu để chúng có thể được sử dụng và truy cập một cách có hiệu quả, đóng vai trò quan trọng trong việc giải quyết các bài toán và tối ưu hoá thuật toán, vì nó ảnh hưởng trực tiếp đến tốc độ thực thi và tính phức tạp của chương trình.__

Có 2 kiểu chính cấu trúc dữ liệu:
+ Cấu trúc dữ liệu tuyến tính (Linear Data Structure): mảng, ngăn xếp, hàng đợi(queue), danh sách liên kết(linked list).
+ Cấu trúc dữ liệu phi tuyến tính (Non-linear Data Structure): đồ thị(graph), cây(tree).


## 9.2. Stack

__Là 1 dạng cấu trúc dữ liệu linear, được lấy ý tưởng từ cách lưu trữ và sắp xếp dữ liệu ở phân vùng stack trong memory layout, tuân thủ theo nguyên tắc FILO (First In - Last Out).__

__Có thể giới hạn stack lưu trữ được tối đa bao nhiêu dữ liệu.__

__Các thao tác trên stack:__
+ push : thêm một phần tử mới vào đỉnh của stack, push = top++.
+ pop : xoá một phần tử đang ở đỉnh của stack, push = top--.
+ peek/top: khởi tạo chỉ số lấy giá trị của phần tử đang ở đỉnh của stack (không xoá).
+ peek/top = -1; khi stack đang rỗng, không thể lấy dữ liệu ra.
+ peek/top = size - 1; stack đang đầy, không thể bỏ vào dữ liệu.

```c
// file stack.h
#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct
{
    int *item;
    int size;
    int top;
} Stack;

void stack_init(Stack *stack, int newSize);

bool stack_empty(Stack stack);

bool stack_full(Stack stack);

void push(Stack *stack, int data);

int pop(Stack *stack);

int top(Stack stack);

#endif //STACK_H

```

```c
// file stack.c

#include "stack.h"


void stack_init(Stack *stack, int newSize)
{
    stack->item = (int *)malloc(newSize * sizeof(int));
    stack->size = newSize;
    stack->top = -1;
}

bool stack_empty(Stack stack)
{
    return (stack.top == -1);
}

bool stack_full(Stack stack)
{
    return (stack.top == stack.size - 1);
}

void push(Stack *stack, int data)
{
    if(stack_full(*stack))
        printf("Stack is full\n");
    else
        stack->item[++stack->top] = data;
}

#define STACK_EMPTY -1

int pop(Stack *stack)
{
    if (stack_empty(*stack))
    {
        printf("Stack is empty\n");
        return STACK_EMPTY;
    }
    else
    {
        int value = stack->item[stack->top];
        stack->item[stack->top--] = 0;
        return value;
    }
}

int top(Stack stack)
{
    if (stack_empty(stack))
        {
            printf("Stack is empty\n");
            return STACK_EMPTY;
        }
    else
        {
            return stack.item[stack.top];
        }
}
```

```c
// file main.c
#include "stack.h"


int main(int argc, char* argv[])
{
    Stack stack_1;
    stack_init(&stack_1, 5);
    push(&stack_1,2);
    push(&stack_1,3);
    push(&stack_1,4);
    push(&stack_1,5);
    push(&stack_1,6);
    push(&stack_1,7);
    push(&stack_1,8);
    push(&stack_1,9);
    push(&stack_1,0);

    
    printf("\n");

    printf("Process push\n");

    for (size_t i = 0; i < stack_1.size; i++)
    {
        printf("data: %d - addr: %p\n", stack_1.item[i],&(stack_1.item[i]));
    }

    printf("\n");

    printf("Process pop\n");

    for (size_t i = 0; i < stack_1.size; i++)
    {
        printf("data: %d - addr: %p\n", top(stack_1), &(stack_1.item[i]));
        pop(&stack_1);
    }

    printf("\n");

    printf("Checking process\n");

    for (size_t i = 0; i < stack_1.size; i++)
    {
        printf("data: %d - addr: %p\n", stack_1.item[i],&(stack_1.item[i]));
    }

    return 0;
}
```
```c
// Application example (factorial)
#include "stack.h"


int factorial(int n)
{   
    if (n < 0)
        return -1;

    int result = 1;
    Stack factorial_stack;

    stack_init(&factorial_stack, n);

    for (size_t i = n; i > 0; i--)
        push(&factorial_stack, i);
    
    while(!stack_empty(factorial_stack))
        result *= pop(&factorial_stack);
  
    return result;
}


int main()
{    

    int result = factorial(5);
    if (result == -1)
    {
        printf("Not valid\n");
    }
    printf("%d", result);
    return 0;
}
```


## 9.2. Queue
__Queue là một cấu trúc dữ liệu tuân theo nguyên tắc FIFO (First In First Out).__
__Hàng đợi có 3 loại:__
+ Hàng đợi tuyến tính (Linear Queue).
+ Hàng đợi vòng tròn (Circular Queue).
+ Hàng đợi ưu tiên (Priority Queue).


### 9.2.1. Các đặc điểm chung của hàng đợi tuyến tính và vòng tròn
__Các thao tác cơ bản ở trên hàng đợi bao gồm:__
+ enqueue: thêm phần tử vào cuối hàng đợi, chỉ tác động lên rear.
+ dequeue: lấy/xoá phần tử ở đầu hàng đợi, chỉ tác động lên front.
+ front: đọc giá trị của phần tử đứng đầu hàng đợi.
+ rear: đọc giá trị của phần tử đứng cuối hàng đợi.
+ Kiểm tra hàng đợi đầy/rỗng.
+ Hàng đợi đầy: rear = size - 1.
+ Muốn kiểm tra hàng đợi rỗng cần lưu ý 2 trường hợp: front và rear đều bằng -1; hoặc front > rear.

### 9.2.2. Linear Queue

+ Trong linear queue, nếu rear đã đạt tới max, thì queue sẽ được coi là đầy và không thể thêm phần tử mới, ngay cả khi phía trước còn khoảng trống do các phần tử đã xoá.
+ Chỉ có thể thêm phần tử mới khi đã dequeue toàn bộ các phần tử hiện có (queue rỗng hoàn toàn và front được reset về vị trí ban đầu).

```c
// file linear_queue.h
#ifndef LINEAR_QUEUE_H
#define LINEAR_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int *item;
    int size;
    int front;
    int rear;
}LiQueue;

// khoi tao thong so ban dau cho mang
void liqueue_init(LiQueue *liqueue, int newSize);

// kiem tra rong
bool liqueue_empty(LiQueue liqueue);

// kiem tra day
bool liqueue_full(LiQueue liqueue);

// them phan tu cuoi hang doi
void enqueue(LiQueue *liqueue, int data);

// lay/xoa phan tu dau hang doi
int dequeue(LiQueue *liqueue);

// doc phan tu dau
int front(LiQueue liqueue);

// doc phan tu cuoi
int rear(LiQueue liqueue);

// hien thi toan bo hang doi hien tai
void display(LiQueue liqueue);

#endif // LINEAR_QUEUE_H
```

```c
// file linear_queue.c
#include "linear_queue.h"
#define QUEUE_EMPTY -1


void liqueue_init(LiQueue *liqueue, int newSize)
{
    liqueue->item = (int *)malloc(sizeof(int) * newSize);
    liqueue->size = newSize;
    liqueue->front = QUEUE_EMPTY;
    liqueue->rear = QUEUE_EMPTY;
}

bool liqueue_empty(LiQueue liqueue)
{
    return ((liqueue.front == QUEUE_EMPTY) || (liqueue.front > liqueue.rear));
}

bool liqueue_full(LiQueue liqueue)
{
    return (liqueue.rear == liqueue.size - 1);
}

void enqueue(LiQueue *liqueue, int data)
{
    if(liqueue_full(*liqueue))
        printf("The queue is full\n");
    else 
    {
        if (liqueue->front == QUEUE_EMPTY)
            liqueue->front = liqueue->rear = 0;
        else 
            liqueue->rear++;
        liqueue->item[liqueue->rear] = data;
    }

}

int dequeue(LiQueue *liqueue)
{
    if(liqueue_empty(*liqueue))
    {
        printf("The queue is empty\n");
        return QUEUE_EMPTY;
    }
    else 
    {   
        int value = liqueue->item[liqueue->front];
        liqueue->item[liqueue->front] = 0;
        if ((liqueue->front == liqueue->rear) && (liqueue->rear == liqueue->size - 1))
            liqueue->front = liqueue->rear = QUEUE_EMPTY;
        else
            liqueue->front++;

        return value;
    }
}

int front(LiQueue liqueue)
{
    if (liqueue_empty(liqueue))
    {
        printf("The queue is empty\n");
        return QUEUE_EMPTY;
    }
    else
    {
        printf("Value at front: %d\n", liqueue.item[liqueue.front]);
        return liqueue.item[liqueue.front];
    }
}

int rear(LiQueue liqueue)
{
    if (liqueue_empty(liqueue))
    {
        printf("The queue is empty\n");
        return QUEUE_EMPTY;
    }
    else
    {
        printf("Value at rear: %d\n", liqueue.item[liqueue.rear]);
        return liqueue.item[liqueue.rear];
    }
}

void display(LiQueue liqueue)
{   
    if (liqueue_empty(liqueue))
    {
        printf("The queue is empty\n");
    }
    for (size_t i = liqueue.front; i <= liqueue.rear; i++)
    {
        printf("%d\n", liqueue.item[i]);
    }
}
```

```c
// file main.c
#include "linear_queue.h"

int main(void)
{
    LiQueue liqueue;

    liqueue_init(&liqueue, 5);

    // cap phat 6 phan tu
    printf("ENQUE\n");
    enqueue(&liqueue, 1);
    enqueue(&liqueue, 2);
    enqueue(&liqueue, 3);
    enqueue(&liqueue, 4);
    enqueue(&liqueue, 5);
    enqueue(&liqueue, 6); // phan tu bi du, queue is full

    // hien thi cac phan tu
    printf("\n");
    printf("Display\n");
    display(liqueue);
    printf("REAR\n");
    rear(liqueue);
    printf("FRONT\n");
    front(liqueue);

    // xoa, lay cac phan tu (tru phan tu cuoi)
    printf("\n");
    printf("DEQUEUE\n");
    dequeue(&liqueue);
    dequeue(&liqueue);
    dequeue(&liqueue);
    dequeue(&liqueue);

    // hien thi cac phan tu
    printf("\n");
    printf("Display\n");
    display(liqueue);
    printf("REAR\n");
    rear(liqueue);
    printf("FRONT\n");
    front(liqueue);

    // them cac phan tu khi ma queue is full(chi con 1 phan tu cuoi)
    printf("\n");
    printf("DEQUEUE\n");
    enqueue(&liqueue, 1);   // bao queue is full
    enqueue(&liqueue, 2);   // bao queue is full
    printf("Display\n");
    display(liqueue);
    printf("REAR\n");
    rear(liqueue);
    printf("FRONT\n");
    front(liqueue);


    return 0;
}
```

```c
// dung cmd: gcc main.c linear_queue.h -o main
//           ./main
```

### 9.2.3. Circular Queue
+ Bởi vì linear queue có những khuyết điểm như khi giá trị rear đạt max thì không thể thêm giá trị mới nên người ta khá ít sử dụng, thay vào đó là sử dụng circular queue.
+ Ở circular queue, khi rear đã đạt max và front khác đã di chuyển, rear có thể quay vòng về vị trí 0 để nhận thêm phần tử mới.
+ Công thức kiểm tra queue is full:
```c

front == (rear + 1) % size

```


