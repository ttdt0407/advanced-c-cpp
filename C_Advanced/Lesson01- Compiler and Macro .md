# Bài 1: Compiler và Macro

__Quá trình biên dịch của compiler, cụ thể ở đây là gcc sẽ trải qua 4 bước chính:__
+ Preprocessing (tiền xử lý) : (.c) -> (.i)
+ Compilation: (.i) -> (.s)
+ Assembly: (.s) -> (.o)
+ Linking: (.o) -> (.exe)
<p align = "center">
<img src = "https://techvidvan.com/tutorials/wp-content/uploads/sites/2/2021/06/working-of-preprocessors-in-c.jpg" width = "500" height = "350">

## Bước 1: Preprocessing (tiền xử lý)

+ Từ những file .h và .c sau quá trình tiền xử lý tạo ra 1 file main.i
(expanded source code)

+ Câu lệnh để tạo ra file main.i:

```bash
gcc -E main.c -o main.i
```
__Ta nhận thấy trong file main.i có những đặc điểm sau:__

+ Trong file .i copy toàn bộ mã nguồn từ các file mà chúng ta đưa vào từ #include <> hoặc #include ""
+ Xoá bỏ các comment 
+ Những macro cũng bị thay thế 
+ Biến và các identifiers còn lại được giữ nguyên

### Macro trong C
Là những từ mà chỉ những thông tin được xử lý ở quá trình tiền xử lý, có nhiều loại macro

__#include là một loại macro, được gọi là chỉ thị bao hàm tệp__
+ Khi quá trình tiền xử lý xảy ra nó sẽ bắt đầu copy toàn bộ code từ những file này vào file .i
 #inlude có 2 dạng: <> và ""
+ File nằm trong <> sẽ được tìm kiếm trong thư mục hệ thống của compiler, sau đó copy vào file .i
+ File nằm trong "" sẽ được tìm kiếm trong thư mục hiện tại để copy vào file .i
+ Lưu ý: file chưa qua xử lý được gọi là source code, file .i không được gọi là source code

__#define là một loại macro, được gọi là chỉ thị định nghĩa__
+ Định nghĩa mà không quan tâm kiểu dữ liệu là gì, có thể là chuỗi, hàm, số nguyên, số thực,...
+ Có thể sử dụng macro để tạo ra mã nguồn cho nhiều hàm khác nhau thông qua việc thay thế văn bản:

``` bash
#define CREATE_FUNC(name, cmd)   \
void name()                      \
{                                \ 
    printf(cmd);                 \
}

CREATE_FUNC(test1, "this is function test1()");
CREATE_FUNC(test2, "this is function test2()");
CREATE_FUNC(test3, "this is function test3()");
```
__Các toán tử trong #define__
+ '##' được sử dụng để nối chuỗi

``` bash

#define CREATE_VAR(name)    \
int int_##name;             \
double double_##name;       \

```

+ '#' chuẩn hoá đoạn văn bản thành chuỗi

``` bash

#define CREATE_STRING(cmd)    \
        printf(#cmd)          
```
+ 'variadic' cho phép hàm có thể nhận một số lượng tham số truyền vào không xác định, dấu 3 chấm chính là cho trình biên dịch biết tham số truyền vào không xác định

``` bash
#define sum(...) __VA_ARGS__
```
Ví dụ để tính tổng dùng variadic:

``` bash
#define sum(...)               \
int arr[] = {__VA_ARGS__,0};    \
int sum = 0;                   \
int i = 0;                     \
while(arr[i] != 0)             \
{                              \
   sum += arr[i];              \
   i++;                        \  
}                              \
printf("Sum = %d\n", sum);    
```
__#undef dùng để huỷ định nghĩa trước đó đã được sử dụng__

``` bash

#define DATA 50


int main(int argc, char const *argv[])
{
    #undef DATA
    #define DATA 20

    printf("data = %d", data);
    
    return 0;
}
```

__#ifndef, #ifdef, #else, #if, #elif được gọi là chỉ thị điều kiện dùng để kiểm tra sự tồn tại của 1 macro__

+ #ifdef dùng để kiểm tra xem 1 macro đã được định nghĩa hay chưa. Nếu đã được định nghĩa, các đoạn mã bên trong sẽ được biên dịch, được kết thúc bằng #endif

```bash
#define DATA 5

#ifdef DATA
    int arr[DATA] = {1,2,3,4,5};
#endif
```
+ #ifndef dùng để kiểm tra xem 1 macro đã được định nghĩa chưa. Nếu chưa các đoạn mã bên trong sẽ được biên dịch, được kết thúc bằng #endif

```bash
#ifndef DATA

#define DATA
    int arr[DATA] = {1,2,3,4,5};
#endif
```
+ #ifdef và #ifndef thường được sử dụng để thiết kế thư viện, ví dụ trong file .h

```bash

#ifndef TEST_H
#define TEST_H

void display();

#endif
```
+ #if, #elif, #else là các chỉ thị điều kiện tiền xử lý trong C/C++ cho phép bạn kiểm tra các biểu thức (phải là hằng số) và quyết định compile đoạn mã nào

```bash

#define STM32 1
#define ESP32 2
#define ATMEGA324 3

#define MCU STM32


#if MCU == STM32
    void digitalWrite(Pin pin, Status state)
    {
        // Digital write
    }

#elif MCU == ATMEGA324
    void digitalWrite(Pin pin, Status state)
    {
        // Digital write
    }
#else 
    void digitalWrite(Pin pin, Status state)
    {
        // Digital write
    }
#endif

```
## Bước 2: Compilation

+ Chuyển file main.i thành file main.s (hợp ngữ)
+ Có câu lệnh như sau:
``` bash
gcc -S main.i -o main.s
```

## Bước 3: Assembly

+ Chuyển file main.s thành file main.o (chuỗi 0 và 1)
+ Câu lệnh như sau:

``` bash
gcc -c main.s -o main.o
```

## Bước 4: Linking
+ Liên kết các file .o để tạo ra file main.exe (trên Windows) hoặc main trên Linux và macOs
+ Ví dụ trong chương trình có file test.c test.h và main.c:
``` bash
gcc main.o test.o -o main
./main

```





