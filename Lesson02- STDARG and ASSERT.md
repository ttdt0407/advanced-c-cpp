# Bài 2: Thư viện STDARG và ASSERT

## 2.1 Thư viện STDARG <stdarg.h> 
Là thư viện header cho phép viết các hàm nhận một số lượng đối số không xác định trước bằng cách sử dụng các macro:
+ va_list: kiểu dữ liệu để lưu trữ danh sách đối số
+ va_start: khởi tạo danh sách đối số
+ va_arg: lấy đối số kế tiếp từ danh sách
+ va_end: thu hồi tài nguyên khi sử dụng danh sách đối số

### 2.1.1 Sử dụng với hàm khi biết số lượng đối số

``` bash
/* Hàm tính tổng số lượng tham số tuỳ biến */

#include <stdio.h>
#include <stdarg.h>

// Hàm sum nhận vào số lượng đối số là count và một danh sách đối số biến.
int sum(int count, ...) {
    int total = 0;
    // Bước 1: Khai báo biến danh sách đối số
    va_list args;
    
    // Bước 2: Khởi tạo args, count là tham số cố định cuối cùng trước các đối số biến
    va_start(args, count);
    
    // Bước 3: Lặp qua các đối số biến
    for (int i = 0; i < count; i++) {
        // Mỗi lần lấy đối số tiếp theo với kiểu int
        total += va_arg(args, int);
    }
    
    // Bước 4: Kết thúc xử lý danh sách đối số
    va_end(args);
    
    return total;
}

int main(void) {
    // Gọi hàm sum với 3 số: 10, 20, 30
    printf("Sum = %d\n", sum(3, 10, 20, 30));
    return 0;
}
```
### 2.1.2 Sử dụng với hàm khi không cần biết trước số lượng đối số

```bash
#include <stdio.h>
#include <stdarg.h>

#define tong(...) sum(__VA_ARGS__,0)

int sum(int count, ...)
{
    va_list args;
    va_start(args, count);
    int result = count;
    int value;

    while((value = va_arg(args,int)) != 0)
    {
        result += value;
    }

    va_end(args);
    return result;
}

int main(void)
{
    printf("sum = %d", tong(2, 1, 2));
    return 0;
}
```
### 2.1.3 Sử dụng kí tự để làm điểm dừng

``` bash

#include <stdio.h>
#include <stdarg.h>

#define tong(...)  sum(__VA_ARGS__, '\n')

int sum(int count, ...)
{
    va_list args;
    va_list check;     // khai báo biến có kiểu va_list để kiểm tra

    va_start(args, count);  // khởi tạo danh sách args
    va_copy(check, args);  // copy địa chỉ của tham số cố định cuối cùng trước các đối số biến

    int result = count;

    while((va_arg(check,char*)) != (char*)'\n')   // check điều kiện không phải kí tự xuống dòng
    {
        result += va_arg(args,int);
    }
    va_end(args);
    va_end(check);
    return result;
}

int main(void)
{
    printf("%d\n", tong(1, 2, 3, 4));
    return 0;
}
```

### 2.1.4 Sử dụng kiểu dữ liệu struct
```bash
#include <stdio.h>
#include <stdarg.h>

typedef struct {
    int x;
    double y;
} Data;


void disPlay(int count, ...)
{
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        Data temp = va_arg(args, Data);
        printf("The value of x at %d is: %d\n", i, temp.x);
        printf("The value of y at %d is: %f\n", i, temp.y);
    }
    va_end(args);
}

int main(void)
{
    disPlay(3, (Data){2, 5.0}, (Data){3, 2.2}, (Data){22, 39.0});
    return 0;
}
```