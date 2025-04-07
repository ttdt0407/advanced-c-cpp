# Bài 1: Compiler và Macro

__Quá trình biên dịch của compiler, cụ thể ở đây là gcc sẽ trải qua 4 bước chính:__
+ Preprocessing (tiền xử lý) : (.c) -> (.i)
+ Compilation: (.i) -> (.s)
+ Assembly: (.s) -> (.o)
+ Linking: (.o) -> (.exe)

## Bước 1: Preprocessing (tiền xử lý)
+ Từ những file .h và .c sau quá trình tiền xử lý tạo ra 1 file main.i
![Quy trình biên dịch](working-of-preprocessors-in-c.jpg)
