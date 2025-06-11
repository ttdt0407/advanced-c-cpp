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
