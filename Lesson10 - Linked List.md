# Bài 10: Linked list
__Là cấu trúc dữ liệu lấy ý tưởng từ mảng, bao gồm các node và mỗi node chứa 2 thành phần là giá trị và con trỏ đến node tiếp theo.__

__Cách triển khai linked list:__
+ Xây dựng các node.
+ Liên kết các node lại với nhau.
-> Tạo thành một danh sách liên kết.

## Bước 1: Xây dựng từng node (được xem là 1 linked list)
+ malloc : cấp phát động vùng nhớ.
+ gán dữ liệu vào. (struct)
+ khởi tạo con trỏ. (struct)

## Bước 2: Liên kết các node (liên kết thành 1 linked list)
+ gán các giá trị cho con trỏ để liên kết các node.
+ kết nối các node (dslk riêng biệt) thành một dslk.
+ node cuối cùng trong linked list là node có con trỏ null.

## Cách triển khai linked list
__Cần khai báo tag (label) cho struct để có thể triển khai danh sách liên kết.__

```c

typedef struct Node{

    int data;
    struct Node *next;  
} Node;

```

+ Kích thước của struct trên là 8 byte (4 byte int data + 4 byte padding) + 8 byte (struct Node* next). Vì đây là kiến trúc máy tính 64-bit, nên kích thước của con trỏ là 8 byte.

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *node_init(int data)
{
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}


int main ()
{
    Node *head = node_init(1);
    Node *second = node_init(5);
    Node *third = node_init(10);
    Node *tail = node_init(100);

    // lien ket cac node
    head->nextNode = second;
    second->nextNode = third;
    third->nextNode = tail;
    tail->nextNode = NULL;

    
    return 0;
}
```

+ Các thao tác trên linked list (danh sách liên kết)

```c
Node *createNode(int value);                    // tạo 1 Node bất kỳ
void push_back(Node **array, int value);        // thêm 1 node vào cuối list
void push_front(Node **array, int value);       // thêm 1 node vào đầu list
void insert(Node **array, int value, int pos);  // thêm 1 node vào vị trí bất kỳ
void pop_back(Node **array);                    // xóa 1 node cuối list
void pop_front(Node **array);                   // xóa 1 node đầu list
void erase(Node **array, int pos);              // xóa 1 node vị trí bất kỳ
int front(Node *array);                         // đọc giá trị node đầu tiên
int back(Node *array);                          // đọc giá trị node cuối cùng
int get(Node *array, int pos);                  // đọc giá trị node bất kỳ
int size(Node *array);                          // đếm số lượng node hiện tại
bool empty(Node *array);                        // kiểm tra list rỗng
void clear(Node **head);                        // xóa toàn bộ node
```
__Sử dụng con trỏ cấp 2 để có thể thay đổi các con trỏ đã khởi tạo trong node, sử dụng với các hàm thêm/xoá nodes.__

### Hàm push back
