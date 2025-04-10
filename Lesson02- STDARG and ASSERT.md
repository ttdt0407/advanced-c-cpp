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
### 2.1.3 Sử