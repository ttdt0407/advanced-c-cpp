# Bài 10: Linked list
__Là cấu trúc dữ liệu lấy ý tưởng từ mảng, bao gồm các node và mỗi node chứa 2 thành phần là giá trị và con trỏ đến node tiếp theo.__

__Cách triển khai linked list:__
+ Xây dựng các node.
+ Liên kết các node lại với nhau.
-> Tạo thành một danh sách liên kết.

## Bước 1: Xây dựng từng node (được xem là 1 linked list)
+ malloc : cấp phát động vùng nhớ.
+ gán dữ liệu vào (struct).
+ khởi tạo con trỏ (struct).

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
### Hàm create_node

```c
typedef struct Node
{
    int data;
    struct Node *nextNode;

}Node;


Node *create_node(int data)
{
    Node *node;
    node = (Node *)malloc(sizeof(int));
    node->data = data;
    node->nextNode = NULL;
    return node;
}

```
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


### Hàm size

```c
int size(Node *head)
{   
    int index = 0;
    if (head == NULL)
    {
        printf("The linked list is empty !\n");
    }
    while (head != NULL)
    {
        head = head->nextNode;
        index++;
    }
    return index;
}

```
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
+ Hoặc có thể sử dụng hàm pop_back như sau:

```c
void pop_back(Node **head) {
  Node *p = *head;

  if (*head == NULL) {
    printf("The linked list is empty !\n");
    return;
  }

  else if (size(*head) == 1)  // trường hợp khi linked list chỉ có 1 node
  {
      free(*head);  // giải phóng vùng nhớ head
      *head = NULL; // gán con trỏ head bằng null
  }

  else 
   {
      int index;
      while (p->nextNode != NULL && index != size(p) - 2)
      {
        index++;
        p = p->nextNode;
      }

    free(p->nextNode);
    p->nextNode = NULL;
    }
}
```

### Hàm push_front

```c
void push_front(Node **head, int data) {
  Node *newNode = create_node(data);
  newNode->nextNode = *head;
  *head = newNode;
    }
```
+ Tạo ra node mới đặt ở đầu linked list.
+ Con trỏ trong node mới sẽ trỏ tới node head ban đầu.
+ Node head ban đầu được gán lại tới node mới được tạo ra.


### Hàm insert

```c
/* Hàm insert dùng để thêm một node bất kỳ vào danh sách liên kết */

void insert (Node **head, int data, int pos)
{
  Node *newNode = create_node(data);
  Node *p = *head;
    if (*head == NULL)
    {
        *head = newNode;
    } else if (pos == 0) {   // kiểm tra xem node đó có phải node thứ 0
      push_front(head,data);
      }
    else {

      uint8_t count = 0;
    while ((p != NULL) && (count != pos - 1))
    {
        count++;
        p = p->nextNode;
    }
    if (count == pos - 1)
    {
        newNode->nextNode = p->nextNode; 
        p->nextNode = newNode;  // point to the new node
    }
}
}
```

### Hàm pop_front

```c
void pop_front(Node **head) {
  if (*head == NULL) {
    printf("The linked list is empty !\n");
    return;
  }
    Node *temp = *head;  // khởi tạo biến tạm con trỏ gán cho Node đầu
    (*head) = (*head)->nextNode; // cập nhật vị trí Node đầu tiên linked list
    free(temp);
   
}
```

### Hàm erase

```c
/* Xoa 1 node o vi tri bat ky */
void erase(Node **head, int pos) {
  Node *p = *head; // tạo một con trỏ Node tới Node đầu
   if (p == NULL) {  
    printf("The linked list is empty !\n");
    return;
   } else if (pos == 0) {  // nếu vị trí cần xóa là vị trí đầu : 0
     Node *tmp = *head; // tạo thêm con trỏ tạm gán cho địa chỉ Node đầu
     *head = (*head)->nextNode;  
     free(tmp);  
     return;
   } else {
     uint8_t count = 0;
     Node *f = NULL;
     while (p->nextNode != NULL && count != pos - 1) {    // duyệt đến vị trí Node ở trước Node cần phải xóa
       count++;
       p = p->nextNode;
     }
     if (count != pos - 1 || p->nextNode == NULL) {  // kiểm tra điều kiện xem vị trí Node cần xóa có vượt quá số lượng Node hiện có hay không
       printf("Position out of bounds !\n");
       return;
     }
     else   // tiến hành xóa Node 
     {
     f = p->nextNode->nextNode;  // dùng một biến tạm lưu địa chỉ Node phía sau Node cần xóa
     free(p->nextNode);  // giải phóng vùng nhớ Node cần xóa
     p->nextNode = f;   // liên kết thành danh sách liên kết mới 
     }
   }
}
```
