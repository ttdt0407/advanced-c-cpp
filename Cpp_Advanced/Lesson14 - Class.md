# Bài 14: Class

## 1. Khái niệm

__Trong Cpp, từ khóa "class" được sử dụng để định nghĩa một lớp, là một cấu trúc dữ liệu tự định nghĩa có thể chứa dữ liệu và các hàm liên quan.__
__Là nền tảng của lập trình hướng đối tượng trong Cpp.__


<img src = "https://www.simplilearn.com/ice9/free_resources_article_thumb/Classes_in_C%2B%2B_Example9.PNG" width = "500" height = "350">

- Khác biệt với các kiểu CTDL tự định nghĩa ở trong C như struct hoặc union, class không thể sử dụng typedef.
- Có thể chứa biến hoặc hàm.


## 2. Phạm vi truy cập (Acces modifier)

__Là cách quy định mức độ truy cập của các thành viên (biến và hàm) trong cùng một lớp.__

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

- Thành viên (biến, hàm) được khai báo là public có thể được truy cập từ bất kỳ đâu:
+ Từ bên trong class.
+ Từ các class khác.
+ Từ bên ngoài file/class (bên ngoài module).

- Không giới hạn truy cập bởi phạm vi, không phụ thuộc vào:
+ Class kế thừa hay không kế thừa.
+ Có nằm trong cùng module/file hay không.


### Public

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
## 3. Constructor

__Là một method sẽ được tự động gọi khi khởi tạo object.__

- Có tên trùng với tên của class.
- Không có kiểu trả về.
- Thường dùng để khởi tạo thông số ban đầu của các biến thành viên.
- Tự động gọi khi khởi tạo một đối tượng.
### 3.1 Constructor mặc định (không có tham số)

```cpp

class SinhVien
{
    public:

        string name;
        int id;
        int age;
        double gpa;

        // Không có tham số
        SinhVien()
        {
            name = "abc";
            id = 2134321;
            age = 25;
            gpa = 3.8;
        }
};

int main ()
{
    SinhVien sv1;

    cout << sv1.name << endl;
    cout << sv1.id << endl;
    cout << sv1.age << endl;
    cout << sv1.gpa << endl;
    return 0;
}

```

- Không có tham số truyền vào, tự động được gọi sau khi khởi tạo sv1.


### 3.2. Constructor có tham số 


```cpp
class SinhVien
{
    public:

        string name;
        int id;
        int age;
        double gpa;

        // Có tham số chưa khởi tạo 
        SinhVien(string _name, int _id, int _age, double _gpa)
        {
            name = _name;
            id = _id;
            age = _age;
            gpa = _gpa;
        }

        void display()
        {
            cout << name << endl;
            cout << id << endl;
            cout << age << endl;
            cout << gpa << endl;
        }
};

int main ()
{
    SinhVien sv1("abc", 22432422, 21, 2.7);
    sv1.display();
    return 0;
}
```

- Truyền tham số vào mỗi khi khởi tạo một giá trị mới.
- 

### 3.3. Constructor có tham số được khởi tạo sẵn

```cpp
class SinhVien
{
    public:

        string name;
        int id;
        int age;
        double gpa;

        // Có tham số được khởi tạo sẵn
        SinhVien(string _name = "xyz", int _id = 123211, int _age = 8, double _gpa = 3.5)
        {
            name = _name;
            id = _id;
            age = _age;
            gpa = _gpa;
        }

        void display()
        {
            cout << name << endl;
            cout << id << endl;
            cout << age << endl;
            cout << gpa << endl;
        }
};

int main ()
{
    SinhVien sv1("abc", 22432422, 21, 2.7);
    sv1.display();

    SinhVien sv2;
    sv2.display();
    return 0;
}

```

- Gán giá trị ngay tại tham số cho đối tượng.

### 3.4. Constructor kiểu initalizer list

```cpp
class SinhVien
{
    public:

        string name;
        int id;
        int age;
        double gpa;

        // Initializer list
        SinhVien(string _name, int _id, int _age, double _gpa) : name(_name), id(_id), age(_age), gpa(_gpa) {}

        void display()
        {
            cout << name << endl;
            cout << id << endl;
            cout << age << endl;
            cout << gpa << endl;
        }
};

int main ()
{
    SinhVien sv2("abc", 22, 123, 2.5);
    sv2.display();
    return 0;
}
```
## 4. Destructor

__Là một method sẽ tự động gọi trước khi object được giải phóng.__

- Có tên trùng với tên class và có thêm dấu ~.
- Thường dùng để xóa toàn bộ dữ liệu chứa trong các biến thành viên.
- Khác với constructor, destructor không có tham số.
```cpp
class SinhVien
{
    public:

        string name;
        int id;
        int age;
        double gpa;

        SinhVien(string _name = "abc", int _id = 22222, int _age = 18, double _gpa = 3.7)
        {
            name = _name;
            id = _id;
            age = _age;
            gpa = _gpa;
            display();
        }


        // Destructor
        ~SinhVien()
        {
            name = "";
            age = 0;
            id = 0;
            gpa = 0.0;
            display();
        }

        void display()
        {
            cout << name << endl;
            cout << id << endl;
            cout << age << endl;
            cout << gpa << endl;
        }
};

int main ()
{
    SinhVien sv2;
    return 0;
}
```

## 5. Static Property


