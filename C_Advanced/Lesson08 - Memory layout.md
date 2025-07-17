# Bài 8: Memory layout

<p align = "center">
<img src = "https://media.geeksforgeeks.org/wp-content/uploads/memoryLayoutC.jpg" width = "500" height = "350">

__Chương trình main.exe (trên window), main.hex (nạp vào vi điều khiển) được lưu ở bộ nhớ SSD (ổ đĩa D, E, ...) hoặc Flash.__
__Khi nhấn nút 'run' chương trình trên window cấp nguồn cho vi điều khiển thì những chương trình này sẽ được copy vào bộ nhớ RAM để thực thi.__
__Có 5 vùng nhớ ở trên thanh RAM dùng để lưu trữ dữ liệu của chương trình gồm: text (code segment), initialized data, uninitialized data, heap, stack.__

## 8.1. Text segment (code segment)
+ Chứa mã máy, tức là tập hợp các instruction dùng để thực thi.
+ Không được thay đổi, chỉ được đọc và thực thi (do thanh ghi PC thực thi từ trên xuống dưới theo thứ tự câu lệnh viết ra).





## 8.3. Initialized data
+ Dữ liệu đã được khởi tạo.
+ Giá trị trong phân vùng này khác 0.
+ Chứa biến global (toàn cục) và biến static.
+ Quyền truy cập : ở đây vừa đọc vừa ghi, có thể thay đổi được.
+ Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.
+ Lưu trữ biến hằng số toàn cục (const) và chuỗi hằng toàn cục (string literal) nhưng quyền truy cập là chỉ đọc (đối với trình biên dịch là gcc/g++). Đối với clang thì lưu ở text segment (chỉ đọc).

```c
const int x = 5;  // GCC thường đặt vào .rodata
char myString[] = "Hello";  // GCC thường đặt vào .data vì là mảng có thể sửa.
const char *ptr = "Hello";  // literal "Hello" ở .rodata, con trỏ ptr có thể nằm ở .data hoặc .bss.

```

__Nên sử dụng con trỏ tới hằng với string literal để khi có thay đổi phần tử chuỗi thì trình biên dịch nó sẽ thông báo lỗi__

## 8.4. Uninitialized data (bss segment)

+ Chứa các biến toàn cục hoặc static như ở initialized data, nhưng giá trị khởi tạo = 0 hoặc không khởi tạo giá trị.



```c

const int x = 0; // nằm ở .rodata

```

+ Có thể sử dụng file assembly để check xem các biến có thuộc đúng phân vùng nhớ như đã dự đoán không.
+ Quyền truy cập là đọc và ghi, có thể đọc và thay đổi giá trị của biến.
+ Tất cả các biến sẽ được thu hồi sau khi chương trình kết thúc.

## 8.5. Stack 

+ Chứa các biến cục bộ (trừ static cục bộ), tham số truyền vào.
+ Chứa hằng số cục bộ, có thể thay đổi thông qua con trỏ.

```c

#include <stdio.h>
int *ptr = NULL;
int main()
{   
    
    const int x = 10;
    ptr = &x;
    *ptr = 100;
    printf("%d\n", x);   // 100


    return 0;
}
```
+ Trong ví dụ trên, biến con trỏ ptr được cấp phát ở phân vùng nhớ bss từ đầu và vẫn nằm ở đó không thay đổi dù cho nó có được gán với giá trị địa chỉ của x (nằm ở phân vùng stack).
+ Quyền truy cập là đọc và ghi trong suốt thời gian chạy kể cả đối với các hằng số (cục bộ), nên có thể sử dụng con trỏ để thay đổi hằng số.
+ Sau khi ra khỏi hàm tự động thu hồi vùng nhớ.

## 8.6 Heap 
+ Heap được sử dụng để cấp phát bộ nhớ động trong quá trình thực thi của chương trình.
+ Điều này cho phép chương trình tạo ra và giải phóng bộ nhớ theo nhu cầu, thích ứng với sự biến đổi của dữ liệu trong quá trình chạy.
+ Các hàm như malloc(), calloc(), realloc() được sử dụng để cấp phát và giải phóng free() bộ nhớ trên heap.

### 8.6.1 malloc()
+ Cấp phát vùng nhớ động phụ thuộc vào kích thước mỗi phần tử và số lượng phần tử, với kích thước được chỉ định.
+ Trả về kiểu void* nên phải ép kiểu để có thể truy xuất dữ liệu.
+ Mỗi byte dữ liệu được cấp phát mang dữ liệu rác.
+ Phải kiểm tra xem cấp phát có thành công hay không, vì nếu cấp phát thất bại sẽ trả về con trỏ NULL.
+ Mang giá trị rác.
```c
#include <stdio.h>


int main(int argc, char* argv[])
{
	int *ptr;
	size_t size;
	scanf("%d", &size);

	ptr = (int *)malloc(size * sizeof(int));   // ptr nằm ở stack; calloc,realloc,calloc nằm ở heap.

	if (ptr == NULL)
		return 0;

	for (int i = 0; i < size; i++)
	{
		ptr[i] = 3*i;
	}
		return 0;
}
```
### 8.6.2. realloc()
+ Chứa 2 tham số, tham số đầu tiên là con trỏ tại vùng địa chỉ muốn thay đổi, tham số tiếp theo là kích thước mới.
+ Nên kiểm tra xem có cấp phát thành công hay chưa.
+ Mang giá trị rác.

```c

ptr = (int*) realloc(ptr, 10*sizeof(int));

```

### 8.6.2. calloc()

+ Cấp phát vùng nhớ trên heap chức năng khá giống với malloc.
+ Các ô nhớ được cấp phát tự động khởi tạo về 0.
```c

void *calloc (size_t so_phan_tu, size_t kich_thuoc);

```
### 8.6.2. free()

+ Thu hồi vùng nhớ được cấp phát động khi gọi các hàm malloc(), realloc(), calloc().
+ Nếu không thu hồi, thì mỗi lần cấp phát sau đó nó sẽ có ít vùng nhớ hơn để cấp phát -> không còn đủ bộ nhớ để cấp phát nữa (memory leak).

```c

free(con_tro);

```