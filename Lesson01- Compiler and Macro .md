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
+ Khi quá trình tiền xử lý xảy ra nó sẽ bắt đầu copy toàn bộ source code từ những file này vào file .i
 #inlude có 2 dạng: <> và ""
+ File nằm trong <> sẽ được tìm kiếm trong thư mục hệ thống của compiler, sau đó copy vào file .i
+ File nằm trong "" sẽ được tìm kiếm trong thư mục hiện tại để copy vào file .i
+ Lưu ý: file chưa qua xử lý được gọi là source code, file .i không được gọi là source code

__#define là một loại macro, được gọi là chỉ thị định nghĩa__
+ Định nghĩa mà không quan tâm kiểu dữ liệu là gì, có thể là chuỗi, hàm, số nguyên, số thực,...
+ Có thể sử dụng macro để tạo ra mã nguồn cho nhiều hàm khác nhau thông qua việc thay thế văn bản.:

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
int arr[] = {__VA_ARGS__,0}    \
int sum = 0;                   \
int i = 0;                     \
while(arr[i] != 0)             \
{                              \
   sum += arr[i];              \
   i++;                        \  
}                              \
printf("Sum = %d\n", sum);    
```