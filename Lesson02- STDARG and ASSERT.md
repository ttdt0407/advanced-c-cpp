# Bài 2: Thư viện STDARG và ASSERT

## 2.1 Thư viện STDARG <stdarg.h> 
__Là thư viện header cho phép viết các hàm nhận một số lượng đối số không xác định trước bằng cách sử dụng các macro:__
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
## 2.2 Thư viện ASSERT <assert.h>
__Cung cấp macro assert dùng để kiểm tra điều kiện trong quá trình chạy chương trình của chúng ta__
+ Phát hiện lỗi sớm
+ Giao diện đơn giản
+ Không ảnh hưởng đến sản phẩm cuối cùng
+ Hỗ trợ kiểm thử tự động

### 2.2.1 assert()
Khi sử dụng if else để debug thì bạn sẽ không biết nó ở dòng nào hay ở file nào, điều kiện khiến chương trình thất bại là gì, macro assert thì sẽ có thể thực hiện những việc trên giúp cho chúng ta

```bash
#include <stdio.h>
#include <assert.h>



int main(int argc, const char *argv[])
{
    int x = 9;
    assert(x == 7);    // check that is x equal to 7, if not, display notification (file information, error line and failed condition) and do not implement next codes

    printf("x = %d", x);

    return 0;
}
// return: Assertion failed: x == 7, file main.c, line 9
```
Ta có thể thêm chuỗi vào asser() để khi biểu thức assert thất bại, toàn bộ chuỗi biểu thức (bao gồm cả thông điệp) sẽ được in ra giúp cho giúp việc debug được dễ dàng hơn

``` bash
assert(x == 7 && "x khac 7");

```
Bởi vì trong C, khi bạn xét giá trị của một con trỏ trong biểu thức điều kiện, con trỏ khác NULL được coi là true còn con trỏ bằng NULL được coi là false

### 2.2.2 Sử dụng macro cho assert() để debug 

``` bash

#include <assert.h>
#include <stdio.h>

#define LOG(condition, cmd)    assert(condition && #cmd)
 double divide(int a, int b)
 {
    LOG(b != 0, mau bang 0);

    return (double)a/b;
 }



int main(int argc, const char *argv[])
{
    
    printf("result of a devided by b is : %lf", divide(2,5));

    return 0;
}
```
### 2.2.3 Macro ASSERT_IN_RANGE(value, min, max) set value min, max

``` bash
#include <stdio.h>
#include <assert.h>

#define ASSERT_IN_RANGE(value, min ,max)   assert((value >= min) && (value <= max))

void setValue(int x)
{
    ASSERT_IN_RANGE(x, 1, 100);
    // Assertion failed: (x >= 1) && (x <= 100), file main.c, line 8
}

int main(int argc, const char *argv[])
{
    int x = -1;

    setValue(x);
    printf("Value of x is in range from 1 to 100\n");

    return 0;
}

```
