# Bài 14: Class

## 1. Khái niệm

__Trong Cpp, từ khóa "class" được sử dụng để định nghĩa một lớp, là một cấu trúc dữ liệu tự định nghĩa có thể chứa dữ liệu và các hàm liên quan.__
__Là nền tảng của lập trình hướng đối tượng trong Cpp.__


<img src = "https://www.simplilearn.com/ice9/free_resources_article_thumb/Classes_in_C%2B%2B_Example9.PNG" width = "500" height = "350">

- Khác biệt với các kiểu CTDL tự định nghĩa ở trong C như struct hoặc union, class không thể sử dụng typedef.
- Có thể chứa biến hoặc hàm.


## 2. Phạm vi truy cập (Access modifier)

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

## 5. Static

__Từ khóa static có thể được sử dụng cho property hoặc method.__


## 5.1. Static property
__Khi một property khai báo với từ khóa static, thì tất cả object cùng sử dụng địa chỉ của property này.__  

```cpp
class HinhChuNhat{
    public:
        double chieuDai;
        double chieuRong;
        static int var;
};
   
int HinhChuNhat::var;

int main(){
    HinhChuNhat hinh1;
    HinhChuNhat hinh2;
    HinhChuNhat hinh3;

    cout << "address of chieu dai: " << &hinh1.chieuDai << '\n';
    cout << "address of chieu dai: " << &hinh2.chieuDai << '\n';
    cout << "address of chieu dai: " << &hinh3.chieuDai << '\n';

    cout << "address of var: " << &hinh1.var << '\n';
    cout << "address of var: " << &hinh2.var << '\n';
    cout << "address of var: " << &hinh3.var << '\n';
    return 0;
}

```
__Ta dễ thấy được rằng: biến var có từ khóa static được gọi từ 3 object có chung địa chỉ và giá trị. Tức là, 3 đối tượng trên đang sử dụng chung một biến, chung giá trị và chung vùng nhớ.__


## 5.2. Static method

- Method được khởi tạo với từ khóa static sẽ có những đặc điểm sau:
    + Không cần khởi tạo đối tượng để gọi. Tức là có thể gọi trực tiếp từ class.
        ```cpp
        class SinhVien
        {
            public:
                string name;
                int id;
                int age;
                double gpa;

                SinhVien(string _name, int _age, int _id, double _gpa);

                ~SinhVien();
                static void create();
                void display();

                static int x;
        };
            int main(int argc, char* argv[])
        {
            SinhVien::display();   // display không phải là static method nên sẽ báo lỗi
            SinhVien::create();   // create được khởi tạo là static method nên có thể gọi trực tiếp.
        }
        ```
        
    + Không thể truy cập các property hoặc method thành viên không phải là static.

    + Method này có thể được truy cập bằng cách sử dụng tên class và dấu ::.
    ```cpp
    SinhVien::create();
    ```  

# 6. This pointer

__Là một con trỏ ẩn (ẩn danh) có sẵn trong mọi hàm thành viên (method) của class.__

__This pointer trỏ đến đối tượng hiện tại của class.__

```cpp
class SinhVien {
private:
    string name;

public:
    void setName(string name) {
        this->name = name; // Phân biệt: biến thành viên = tham số truyền vào
    }
};
```
- Trong ví dụ trên, `this->name` trỏ đến biến thành viên `name` của đối tượng hiện tại, trong khi `name` là tham số được truyền vào hàm `setName`.
- Điều này rất hữu ích khi tên biến thành viên và tham số hàm trùng nhau, giúp tránh nhầm lẫn.


- This pointer có các đặc điểm sau:
    + Chỉ xuất hiện trong hàm thành viên. Không có trong hàm tĩnh (static method).
    + Trỏ đến đối tượng hiện tại của class.
    + Có kiểu con trỏ đến class hiện tại, trong class Person thì this có kiểu là Person*. Nên có thể truy cập được đến các thành viên của class.
    + Là constant pointer, không thể thay đổi địa chỉ của nó, giá trị con trỏ luôn trỏ đến đối tượng hiện tại.
    + Có thể sử dụng để truy cập các thành viên của class, bao gồm cả biến và hàm.


