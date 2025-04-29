# Bài 4: Pointer
**Là một biến dùng để lưu giữ địa chỉ của một đối tượng khác, đó có thể là biến, mảng hoặc hàm. Việc sử dụng con trỏ khiến ta thực hiện các thao tác trên bộ nhớ một cách linh hoạt hơn.**

## 4.1. Cú pháp con trỏ

__Cách khai báo con trỏ__

```c

int *ptr_int;        // con trỏ trỏ đến kiểu int 
char *ptr_char;      // con trỏ trỏ đến kiểu char
float *ptr_float;    // con trỏ trỏ đến kiểu float
int (*ptr_arr)[10];  // con trỏ trỏ đến mảng gồm 10 phần tử integer
```

__Lấy địa chỉ của một biến__

 Chỉ có thể lấy địa chỉ của một biến đã được khai báo rồi

```c
int x = 0;

int *ptr_x = &x;

```

__Truy cập giá trị của biến mà con trỏ trỏ đến - giải tham chiếu (dereference)__

```c

int x = 2;

int *ptr_x = &x;
int y = *ptr_x;

printf("%d", y);   // y == x

```

## 4.2. Kích thước con trỏ

__Kích thước của con trỏ phụ thuộc hoàn toàn vào kiến trúc máy tính và trình biên dịch hoặc kiến trúc của vi xử lý (stm32, esp32,...), tương tự với các kiểu dữ liệu như char, int, double, long long,...__
 
 Có thể kiểm tra kích thước con trỏ bằng cách sử dụng sizeof()

```c
#include <stdio.h>


int main(void)
{
    printf("%zu", sizeof(int*));
    return 0;
}

```
__Kích thước của con trỏ không phụ thuộc vào kiểu dữ liệu mà nó trỏ đến__

 Vì thực chất bản thân con trỏ là biến lưu trữ địa chỉ, nên việc giá trị được lưu trữ tại địa chỉ đó có kích thước là bao nhiêu thì không ảnh hưởng được đến kích thước của con trỏ. 

## 4.3. Cách lưu trữ dữ liệu nhiều byte

__Ta có 2 cách lưu trữ phổ biến với kiểu dữ liệu nhiều byte: Big Endian và Little Endian, thực tế hiện nay Litte Endian được sử dụng phổ biến hơn__

 Chúng là cách lưu trữ dữ liệu nhiều byte vào bộ nhớ; cụ thể bit nào được lưu trước và bit nào được lưu sau. Ví dụ ta có một số gồm 32-bit 0x12345678 và xem xét 2 cách lưu trữ sau

 + Big Endian: lưu trữ theo kiểu mắt đọc con người nên khá dễ nhìn. Lưu từ byte lớn nhất trước: [0x00]: 12  [0x01]: 34  [0x02]: 56  [0x03]: 78
 
 + Little Endian: lưu trữ từ byte nhỏ nhất trước đến byte lớn nhất, khó đọc hơn Big Endian nhưng lại phù hợp cho việc tính toán: [0x00]: 78  [0x01]: 56  [0x02]: 34 [0x03]: 12
 
 + Khi truyền dữ liệu đi thì luôn cần chuẩn hoá các endian, phụ thuộc vào các trường hợp cụ thể, ví dụ như giao tiếp mạng (networking) thì luôn cần chuẩn hoá trở thành Big Endian hay giao tiếp với các hệ thống có kiến trúc khác nhau,...


## 4.4. Ý nghĩa thực sự của kiểu dữ liệu mà con trỏ trỏ đến

__Kiểu dữ liệu mà con trỏ trỏ đến quan trọng khi giải tham chiếu, tức là với kiểu integer, bạn giải tham chiếu đến giá trị mà con trỏ trỏ đến thì vùng giá trị mà con trỏ đọc được sẽ là 4 byte(int), điều này cũng tương tự với các kiểu dữ liệu khác như char, float, double, ...__

 Cần hết sức lưu ý khi giải tham chiếu và cần nắm rõ bản chất con trỏ để tránh các trường hợp lỗi không mong muốn, có thể truy xuất phải các giá trị rác, ví dụ sử dụng tham chiếu đến con trỏ double cho biến integer


 ```c
 #include <stdio.h>


void swap(int* a, int* b)     //
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}


int main(void)
{
    int a = 2;
    int b = 1;

    swap(&a, &b);

    printf("%d %d", a, b);
    return 0;
}

 ```

## 4.5. Các kiểu con trỏ thường gặp
### 4.5.1. Void pointer

__Dùng để trỏ tới bất kì địa chỉ nào mà không cần phải quan tâm đến kiểu dữ liệu tại địa chỉ mà nó trỏ tới__

+ Việc sử dụng con trỏ void cho phép lập trình viên lưu giữ giá trị địa chỉ của bất kì biến nào mà con trỏ trỏ đến.
+ Tuy nhiên không thể giải tham chiếu đến vị trí đó bởi trình biên dịch không thể biết được kích thước thực sự của giá trị nằm tại địa chỉ đó, tránh việc truy xuất các giá trị không mong muốn.
+ Ta có thể truy xuất giá trị của con trỏ void bằng cách sử dụng ép kiểu để giới hạn vùng giá trị có thể truy xuất cho con trỏ.

```c
#include <stdio.h>

int main(void)
{
    
    int x = 10;
    void *ptr_int = &x;

    printf("Adrress: %p Value: %d", ptr_int, *(int*) ptr_int); // typecasting void pointer to integer pointer

    return 0;
}

```
__Câu hỏi đặt ra là tại sao phải sử dụng con trỏ void trong khi ở ví dụ trên có thể sử dụng con trỏ có cùng kiểu dữ liệu với biến được trỏ đến ?__
 
 Việc sử dụng con trỏ có kiểu void có thể làm tăng tính linh hoạt của chương trình, nếu cứ mỗi biến được tạo ra cần 1 con trỏ để truy cập hay thì sẽ tốn nhiều tài nguyên, tốn nhiều thời gian khởi tạo hay theo dõi, thay vào đó ta chỉ cần 1 con trỏ void và sử dụng ép kiểu để có thể truy xuất được bất kì biến nào trong chương trình. Điều này giúp giảm bớt số lượng con trỏ cần thiết và làm cho mã nguồn trở nên tổng quát và dễ bảo trì hơn.

### 4.5.2. Pointer and Array
__Bản thân tên của mảng chính là một con trỏ lưu giữ giá trị địa chỉ của phần tử đầu tiên trong mảng__

```c

int arr1[] = {1, 2, 3, 4, 5};
char arr2[] = "Seventeen";

void *ptr_void = arr1;
printf("Value of the second element in array 1: %d", *((int *) ptr_void + 1));

```

+ Ở ví dụ trên, nếu ta sửa lại thành *(int*) (ptr_void + 1) thì sẽ sai kết quả, bởi vì kiểu con trỏ void khi cộng 1 sẽ tự động cộng 1 byte (đối với gcc), tức là cộng thêm số byte tương đương với kiểu char. Do vậy ta cần ép kiểu trước rồi mới cộng 1 cho địa chỉ của mảng.
+ Tên mảng chính là con trỏ đến địa chỉ bắt đầu của mảng, nếu viết như sau: arr1[2]
 tương đương với *((int *) ptr_void + 2) nếu bạn dùng kiểu con trỏ void

__Mảng con trỏ bao gồm các phần tử mà mỗi phần tử là một con trỏ chứa địa chỉ của một biến khác__

+ Mảng con trỏ chứa địa chỉ của các biến có kiểu dữ liệu cùng với kiểu dữ liệu mảng con trỏ trỏ đến
+ Với mảng con trỏ kiểu void thì có thể chứa địa chỉ các kiểu dữ liệu khác nhau

```c
#include <stdio.h>


int main(void)
{
    int x = 2;
    double y = 1.88;
    long long z = 24432535;


    int *ptr_int = &x;
    double *ptr_double = &y;
    long long *ptr_longlong = &z;


    void *ptr_void;

    int *arr1[] = {&x, &y, &z};  // không hợp lệ
    double *arr2[] = {&x, &y, &z};  // không hợp lệ
    long long *arr3[] = {&x, &y, &z};  // không hợp lệ

    void *arr4[] = {ptr_int, ptr_double, ptr_longlong}; // hợp lệ

    printf("Dia chi: %p %p %p \nGia tri: %d %.2lf %lld", *arr1[0], arr1[1], arr1[2], *arr1[0], *(double*) arr1[1], *(long long*) arr1[2]); // báo lỗi vì là mảng con trỏ double chỉ có thể chứa địa chỉ của biến có kiểu dữ liệu int
    printf("Dia chi: %p %p %p \nGia tri: %d %.2lf %lld", arr2[0], arr2[1], arr2[2],*(int*)arr1[0], *arr1[1], *(long long*) arr1[2]); // báo lỗi vì là mảng con trỏ double chỉ có thể chứa địa chỉ của biến có kiểu dữ liệu double
    printf("Dia chi: %p %p %p \nGia tri: %d %.2lf %lld", arr3[0], arr3[1], arr3[2], *(int*)arr1[0], *(double*) arr1[1], *arr1[2]); // báo lỗi vì là mảng con trỏ double chỉ có thể chứa địa chỉ của biến có kiểu dữ liệu long long
    printf("Dia chi: %p %p %p \nGia tri: %d %.2lf %lld", arr4[0], arr4[1], arr4[2], *(int*)arr1[0], *(double*) arr1[1], *(long long*) arr1[2]); // không gây lỗi vì mảng con trỏ void hợp lệ chứa địa chỉ của các biến khác nhau
    return 0;
}

```

