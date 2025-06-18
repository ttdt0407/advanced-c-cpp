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

### Hàm push_back

```c
void push_back(Node **head, int data)
{
    Node *newNode = node_init(data);
    Node *p = *head;

    if (p == NULL)
        *head = newNode;
    else 
    {
        while(p->nextNode != NULL)
            p = p->nextNode;
        p->nextNode = newNode;
    }
}

```
+ Có 3 bước cơ bản: kiểm tra xem danh sách rỗng hay không, gán con trỏ tạm và duyệt đến node cuối cùng hiện tại trong danh sách trước khi thêm vào node mới, và cuối cùng là gán con trỏ đó địa chỉ của node tiếp theo.
+ Khởi tạo biến tạm p là con trỏ bậc 1 và gán cho nó con trỏ hiện tại head để bắt đầu duyệt qua danh sách liên kết, tránh việc thay đổi giá trị của con trỏ head đầu danh sách.

+ Con trỏ p chỉ copy địa chỉ của con trỏ head, chứ không làm thay đổi giá trị thực sự của nó.


### Hàm display

```c
void display(Node *head)
{
    int i = 0;
    if (head == NULL)
    {
        printf("The linked list is empty !\n");
    }
    else 
    {
        while (head != NULL)
        {
            printf("%d: %d\n", i++, head->data);
            head = head->nextNode;
        }
    }

}
```
+ Hàm display chỉ hiển thị các phần tử trong danh sách liên kết, ta chỉ cần truyền vào một con trỏ bậc 1.

### Hàm pop_back

```c
void pop_back(Node **head)
{
    if (*head == NULL)
        printf("The linked list is empty !\nNothing to pop back\n");
    else if ((*head)->nextNode == NULL)
    {
        free(*head);
        *head = NULL;  // tránh dangling pointer vì vùng nhớ mà con trỏ head trỏ đến đã bị thu hồi
        // return ;  // dùng để trả về cho hàm có kiểu trả về void
    }
    else 
    {
        Node *p = *head;
        Node *p_2;
        while (p->nextNode != NULL)
        {
            p_2 = p;
            p = p->nextNode;
        }
        free(p);
        p_2->nextNode = NULL;
    }
}
```

+ Tương tự như thuật toán của hàm push_back, nhưng thay vì trỏ tới node cuối thì nó lại là giải phóng node cuối hiện tại.
+ Sau đó nó sẽ thay thế con trỏ của node cuối bằng NULL.

