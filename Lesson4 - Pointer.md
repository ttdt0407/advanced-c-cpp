# Bài 4: Pointer
**Là một biến dùng để lưu giữ địa chỉ của một đối tượng khác, đó có thể là biến, mảng hoặc hàm. Việc sử dụng con trỏ khiến ta thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.**

## 4.1. Cú pháp con trỏ

__Cách khai báo con trỏ__

```c

int *ptr_int;        // con trỏ trỏ đến kiểu int 
char *ptr_char;      // con trỏ trỏ đến kiểu char
float *ptr_float;    // con trỏ trỏ đến kiểu float
int (*ptr_arr)[10];  // con trỏ trỏ đến mảng gồm 10 phần tử integer
```

__Lấy địa chỉ của một biến__

 Chỉ có thể lấy địa chỉ của một biến đã được khai báo rồi

```c
int x = 0;

int *ptr_x = &x;

```

__Truy cập giá trị của biến mà con trỏ trỏ đến - giải tham chiếu (dereference)__

```c

int x = 2;

int *ptr_x = &x;
int y = *ptr_x;

printf("%d", y);   // y == x

```

## 4.2. Kích thước con trỏ

__Kích thước của con trỏ phụ thuộc hoàn toàn vào kiến trúc máy tính và trình biên dịch hoặc kiến trúc của vi xử lý (stm32, esp32,...), tương tự với các kiểu dữ liệu như char, int, double, long long,...__
 
 Có thể kiểm tra kích thước con trỏ bằng cách sử dụng sizeof()

```c
#include <stdio.h>


int main(void)
{
    printf("%d ", sizeof(int*));
    return 0;
}

```
__Kích thước của con trỏ không phụ thuộc vào kiểu dữ liệu mà nó trỏ đến__

 Vì thực chất bản thân con trỏ là biến lưu trữ địa chỉ, nên việc giá trị được lưu trữ tại địa chỉ đó có kích thước là bao nhiêu thì không ảnh hưởng được đến kích thước của con trỏ. 

