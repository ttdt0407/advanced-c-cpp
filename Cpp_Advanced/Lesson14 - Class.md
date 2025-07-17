# Bài 14: Class

## 1. Class trong Cpp

__Trong Cpp, từ khóa "class" được sử dụng để định nghĩa một lớp, là một cấu trúc dữ liệu tự định nghĩa có thể chứa dữ liệu và các hàm liên quan.__
__Là nền tảng của lập trình hướng đối tượng trong Cpp.__

- Khác biệt với các kiểu CTDL tự định nghĩa ở trong C như struct hoặc union, class không thể sử dụng typedef.
- Có thể chứa biến hoặc hàm.

## 2. Phạm vi truy cập của class trong Cpp

__Là cách quy định mức độ truy cập của các thành viên (biến và phương thức) trong một lớp.__

__Cung cấp 3 phạm vi truy cập chính:__
+ public.
+ private.
+ protected.

__Mỗi phạm vi truy cập sẽ có các đặc điểm riêng biệt và liên quan đến các tính chất hướng đối tượng khác nhau.__

- Nếu ta khai báo mà không đề cập gì đến phạm vi truy cập thì mặc định là không thể truy xuất được các biến thành viên ở bên ngoài.

```cpp
class Sinhvien
{
    public:
    string name; // ten sinh vien
    string id; // mssv
    int age;
    float gpa;
};

```

- Cho nên ta cần thêm các từ khóa để có thể sử dụng tùy theo mục đích, phạm vi truy cập (access specifiers).

## 2.1. public trong class

```cpp

public:

```

- Cho phép truy xuất các biến thành viên từ bên ngoài class.
- Có thể chứa hàm.

```cpp

class Sinhvien
{
    public:
    string name; // ten sinh vien
    string id; // mssv
    int age;
    float gpa;

    void display()
    {   
        cout << "Ten:" << name << endl;
        cout << "ID:" << id << endl;
        cout << "Tuoi:" << age << endl;
        cout << "Gpa:" << gpa << endl;
    }
};
```

- Có thể khởi tạo hoặc truy xuất từ bên trong lẫn bên ngoài.

```cpp
class Sinhvien
{
    public:
        string name; // ten sinh vien
        string id; // mssv
        int age;
        float gpa;



    // ham khoi tao ben trong class

        void create()
        {
            Sinhvien sv2;

            sv2.name = "trump";
            sv2.id = "1231";
            sv2.age = 17;
            sv2.gpa = 2.5;
            sv2.display();
        }

        // ham in ra cac gia tri cua class
        void display()
        {
            cout << "Ten: " << name << endl;
            cout << "ID: " << id << endl;
            cout << "Tuoi: " << age << endl;
            cout << "Gpa: " << gpa << endl;
        }
};

```





