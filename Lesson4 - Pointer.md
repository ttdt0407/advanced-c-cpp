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
    printf("%zu", sizeof(int*));
    return 0;
}

```
__Kích thước của con trỏ không phụ thuộc vào kiểu dữ liệu mà nó trỏ đến__

 Vì thực chất bản thân con trỏ là biến lưu trữ địa chỉ, nên việc giá trị được lưu trữ tại địa chỉ đó có kích thước là bao nhiêu thì không ảnh hưởng được đến kích thước của con trỏ. 

## 4.3. Cách lưu trữ dữ liệu nhiều byte

__Ta có 2 cách lưu trữ phổ biến với kiểu dữ liệu nhiều byte: Big Endian và Little Endian, thực tế hiện nay Litte Endian được sử dụng phổ biến hơn__

 Chúng là cách lưu trữ dữ liệu nhiều byte vào bộ nhớ; cụ thể bit nào được lưu trước và bit nào được lưu sau. Ví dụ ta có một số gồm 32-bit 0x12345678 và xem xét 2 cách lưu trữ sau

 + Big Endian: lưu trữ theo kiểu mắt đọc con người nên khá dễ nhìn. Lưu từ byte lớn nhất trước: [0x00]: 12  [0x01]: 34  [0x02]: 56  [0x03]: 78
 
 + Little Endian: lưu trữ từ byte nhỏ nhất trước đến byte lớn nhất, khó đọc hơn Big Endian nhưng lại phù hợp cho việc tính toán: [0x00]: 78  [0x01]: 56  [0x02]: 34 [0x03]: 12
 
 + Khi truyền dữ liệu đi thì luôn cần chuẩn hoá các endian, phụ thuộc vào các trường hợp cụ thể, ví dụ như giao tiếp mạng (networking) thì luôn cần chuẩn hoá trở thành Big Endian hay giao tiếp với các hệ thống có kiến trúc khác nhau,...


## 4.4. Ý nghĩa thực sự của kiểu dữ liệu mà con trỏ trỏ đến

__Kiểu dữ liệu mà con trỏ trỏ đến quan trọng khi giải tham chiếu, tức là với kiểu integer, bạn giải tham chiếu đến giá trị mà con trỏ trỏ đến thì vùng giá trị mà con trỏ đọc được sẽ là 4 byte(int), điều này cũng tương tự với các kiểu dữ liệu khác như char, float, double, ...__

 Cần hết sức lưu ý khi giải tham chiếu và cần nắm rõ bản chất con trỏ để tránh các trường hợp lỗi không mong muốn, có thể truy xuất phải các giá trị rác, ví dụ sử dụng tham chiếu đến con trỏ double cho biến integer


 ```c
 #include <stdio.h>


void swap(int* a, int* b)     //
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}


int main(void)
{
    int a = 2;
    int b = 1;

    swap(&a, &b);

    printf("%d %d", a, b);
    return 0;
}

 ```


