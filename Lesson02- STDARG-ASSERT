# Bài 2: Thư viện STDARG và ASSERT

## Thư viện STDARG <stdarg.h>
Là thư viện header cho phép viết các hàm nhận một số lượng đối số không xác định trước bằng cách sử dụng các macro:
+ va_list: kiểu dữ liệu để lưu trữ danh sách đối số
+ va_start: khởi tạo danh sách đối số
+ va_arg: lấy đối số kế tiếp từ danh sách
+ va_end: thu hồi tài nguyên khi sử dụng danh sách đối số

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
