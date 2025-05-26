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
### 6.3. volatile

__Từ khoá volatile được sử dụng để báo hiệu cho trình biên dịch rằng một biết có thể thay đổi ngẫu nhiên, ngoài sự kiểm soát của chương trình.__
__volatile giúp ngăn chặn trình biên dịch tối ưu hoá hoặc xoá bỏ những thao tác có thể xảy ra trên biến đó.__
__Dùng volatile khi:__

+ Biến bị thay đổi bởi phần cứng (I/O, register,...).
+ Biến bị thay đổi bởi ISR.
+ Sử dụng tránh trình biên dịch chỉ đọc giá trị 1 lần rồi dùng mãi hay bỏ qua việc đọc lại biến, dưới cụ thể là biến i.

```c
#include "stm32f10x.h"

volatile int i = 0;

int a = 100;

int main()
{
   while(1)
   {
      i = *((int*) 0x20000000);
      if (i > 0) break;
   }
   a = 200;
}

```

### 6.4. register

__Khi khai báo một phép toán nào đó, nó sẽ lưu trữ một vùng địa chỉ trên RAM, sau đó được chuyển qua các thanh ghi (Register), từ các thanh ghi lưu trữ giá trị tiếp tục được chuyển qua ALU, sau khi thực hiện các phép tính được chuyển về lại thanh ghi và trở về RAM.__

__Trong vi điều khiển hoặc máy tính, chương trình trước khi đến RAM thường được lấy từ ổ đĩa D hoặc ổ đĩa Flash.__

__Trong ngôn ngữ lập trình C, từ khoá register được sử dụng để chỉ ra ý muốn của lập trình viên rằng một biến được sử dụng thường xuyên (vòng lặp) và có thể được lưu trữ trong một thanh ghi máy tính, chứ không phải trong bộ nhớ RAM, việc này nhằm giúp tăng tốc độ truy cập.__

__Tuy nhiên đây chỉ là một đề xuất của lập trình viên, trình biên dịch có thể lựa chọn thực hiện theo hay không.__

__Khi lưu trữ ở thanh ghi, không thể lấy địa chỉ của biến register (&).__

Sau đây là chương trình tính toán thời gian khi gán register:

```c

#include <stdio.h>
#include <time.h>



int main(int argv, char *argv[])
{

    clock_t start = clock();   // save the start time
    register int i;

    for (i = 0; i < 2000000; i++);

    clock_t end = clock();     // save the end time


    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("%lf\n", time_taken);



    return 0;
}

```
__Không được khai báo toàn cục bởi vì số lượng thanh ghi có hạn, nên không thể chiếm dụng hết thời gian chương trình__