# Bài 7: Struct và Union

## 7.1. struct

### 7.1.1. Tổng quan
__Là một cấu trúc dữ liệu cho phép lập trình viên tự định nghĩa một kiểu dữ liệu mới bằng cách nhóm các biến có các kiểu dữ liệu khác nhau lại với nhau, struct cho phép tạo ra một thực thể dữ liệu lớn hơn và có tổ chức hơn từ các thành viên của nó.__

+ Cú pháp:

```c

struct name_struct
{

    <data_type 1> <member 1>;
    <data_type 2> <member 2>;

};


typedef struct {

    <data_type 1> <member 1>;
    <data_type 2> <member 2>;

} type_name;



```

+ Các biến nằm trong struct được gọi là biến thành viên.
+ Nếu biến con trỏ đến một kiểu dữ liệu struct thì khi truy xuất phải dùng dấu mũi tên thay vì dấu chấm đối với biến thông thường.

```c

typedef struct
{
    char *name;
    int stt;
} user;

user u1, *u2, u3;



int main()
{
    u1.stt = 1;
    u1.name = "actor1";

    u2->stt = 10;
    u2->name = "actor2";

    return 0;
}

```

### 7.1.2. Tính kích thước của struct bất kỳ

Vì là kiểu dữ liệu tự định nghĩa nên không có kích thước sẵn và giống nhau giữa mỗi struct.

#### 7.1.2.1. Data alignment

+ Khi khai báo một struct ở C/C++, trình biên dịch phải quyết định cách bố trí của các thành viên struct trong bộ nhớ. Yêu cầu đặt ra là mỗi thành viên trong struct phải nằm ở địa chỉ phù hợp.
+ Nếu một thành viên không được đặt đúng alignment, CPU có thể cần nhiều chu kỳ hơn để đọc/ghi dữ liệu.
+ Padding là các ô nhớ trống không chứa dữ liệu được thêm vào để thoả mãn alignment.
+ Struct có alignment bằng alignment lớn nhất của bất kỳ thành viên nào trong đó.
+ Kích thước của struct là bội số của alignment của chính nó.
+ Padding có thể xuất hiện giữa các thành viên hoặc cuối struct.
+ Các thành viên có thứ tự nằm liền kề nhau.


```c

typedef struct 
{   
    uint8_t v1[9];
    uint64_t v2[3];
    uint16_t v3[10];
    uint32_t v4[2];

} sample_1;

```

__Với ví dụ trên ta có thể xác định bằng phương pháp sau:__

__alignment = 8;__
+ v1[0] -> v1[7]
+ v1[8] + 7 padding
+ v2[0]
+ v2[1]
+ v2[2]
+ v3[0] ... v3[3]
+ v3[4] ... v3[7]
+ v3[8], v3[9] + v4[1]
+ v4[2] + 4 padding

__Kích thước của struct = tổng số lượng ô nhớ được sử dụng + số padding__

#### 7.1.2.2. Bit field

__Bit field là một thành phần đặc biệt của cấu trúc struct cho phép bạn sử dụng một số lượng bit được chỉ định cụ thể dùng cho lưu trữ một biến số nguyên. Thay vì sử dụng kích thước của một kiểu dữ liệu, ví dụ int: 4 bytes - 32 bits. Bạn có thể "cắt nhỏ" bộ nhớ theo số bit giúp tiết kiệm không gian bộ nhớ và mô tả chính xác hơn ý nghĩa của dữ liệu (ví dụ trạng thái bật/tắt chỉ cần 1 bit)__

```c



struct Example 
{
    int32_t flag  : 1;	// chỉ sử dụng 1 trong 32 bit
    int64_t count : 4;	// chỉ sử dụng 4 trong 64 bit
};

```

__Không thể lấy địa chỉ của các thành viên trong struct sử dụng bit field__
__Ứng dụng để cấu hình GPIO, giao thức (UART, SPI, v.v)__
__Ứng dụng để xây dựng cấu trúc dữ liệu (Stack,Queue,Linked List,JSON, v.v)__

