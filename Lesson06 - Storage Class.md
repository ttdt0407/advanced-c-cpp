# Bài 6: Storage class

## 6.1. extern

__Là từ khoá dùng để khai báo biến hoặc hàm được định nghĩa ở nơi khác. Giúp chia sẻ biến/hàm giữa nhiều file nguồn.__

+ Không cấp pháp bộ nhớ cho biến, chỉ khai báo để trình biên dịch biết biến/hàm này tồn tại ở nơi khác.
+ Thường dùng để khai báo biến toàn cục trong file header, sau đó định nghĩa ở file nguồn khác.
+ Có thể sử dụng biến hoặc hàm từ file khác mà không cần include file đó bằng cách sử dụng extern và dùng câu lệnh liên kết sau:

```c
gcc ten_ham1.c ten_ham2.c -o ten_ham_moi

```


```c

// File test.c

#include <stdio.h>


int var_global = 50;

void display()
{
    printf("%d\n", var_global);
}
```


```c

// File main.c

#include <stdio.h>

extern int var_global;

extern void display();


int main(int argc, char *argv[])
{

    display();

    return 0;
}

```

```c

gcc main.c test.c -o newmain

```

+ Thực tế khi viết chương trình còn có cả file header nữa.

+ Trong file header không nên chứa biến nếu không thực sự cần thiết chia sẻ cho các file khác, nếu có phải có extern để tránh lỗi trùng lặp.

+ Hàm không cần khai báo extern vì mặc định nó chứa extern rồi, nhưng nên thêm vào để dễ nhận biết là hàm đó sẽ được sử dụng lại.

+ setjmp và longjmp có thể được sử dụng giữa các file nhưng với điều kiện biến jmp_buf env phải được khai báo extern để có thể lưu vị trí setjmp tạo điều kiện cho longjmp trở về được sau này.

## 6.2. static

### 6.2.1. static cục bộ (local static)
__Biến chỉ được khởi tạo một lần duy nhất và giữ nguyên giá trị giữa các lần gọi hàm__
__Biến chỉ có phạm vi trong hàm đó__

```c
#include <stdio.h>

void exampleFunction()
{
    static int count = 0;  // Biến static giữ giá trị qua các lần gọi hàm
    count++;
    printf("Count: %d\n", count);
}

int main()
{
    exampleFunction();  // In ra "Count: 1"
    exampleFunction();  // In ra "Count: 2"
    exampleFunction();  // In ra "Count: 3"
    return 0;
}
```
### 6.2.2. static toàn cục (global static)

__Khi static được sử dụng với biến, hàm toàn cục, nó hạn chế phạm vi của biến, hàm đó chỉ trong file nguồn hiện tại.__
__Được sử dụng thiết kế các file thư viện.__

```c

#ifndef CALCULATION_H
#define CALCULATION_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
    double a,b,c;
    double x1;
    double x2;
    bool has_result;    // 1: có nghiệm, 0: vô nghiệm
} Equation;

// Nhập hệ số
void input_coefficients(Equation *eq);

// Tính delta
static double calculate_delta(double a, double b, double c);

// Giải phương trình
static void solve(Equation *eq);

// Hiển thị kết quả
void display_result(Equation eq);

#endif
```






