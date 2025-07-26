# Bài 15: OOP

## 15.1. Giới thiệu
___OOP (Object-Oriented Programming) là một phương pháp lập trình dựa trên các đối tượng, giúp tổ chức mã nguồn một cách hiệu quả và dễ bảo trì.__

___Trong C++, OOP được hỗ trợ thông qua các khái niệm như lớp (class), đối tượng (object), kế thừa (inheritance), đa hình (polymorphism) và đóng gói (encapsulation).__

## 15.2. Encapsulation (Tính đóng gói)

__Tính đóng gói là ẩn đi các property mật khỏi người dùng. Và để có thể làm được điều này, ta sẽ khai báo các property ở quyền truy cập private/protected (tức là không thể truy cập trực tiếp đến các property này thông qua object bên ngoài).__

__Trong trường hợp muốn đọc hoặc ghi các property này thì ta sẽ truy cập gián tiếp thông qua các method ở quyền truy cập public.__

- Phạm vi private có thể truy cập bên trong lớp, nhưng không thể truy cập từ bên ngoài lớp.


```cpp
#include <iostream>
#include <string>
using namespace std;


class SinhVien
{
    private:
        int id;
        string name;
    
    public:
        void setName(string newName)
        {
            if (checkName(newName))
            {
                name = newName;
                cout << name << endl;
            }        
            else
                cout << "Name is invalid" << endl;
        }

        bool checkName(string newName)
        {
            for (int i = 0; i < newName.length(); i++)
            {
                char c = newName[i];
                if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == ' ')))
                    return false;
                
            }
            return true;
        }

};

int main(void)
{
    SinhVien sv1;

    sv1.setName("Alice");

    return 0;
}
```

- Trong trường hợp trên, ta đã ấn đi property `name` và `id` của lớp `SinhVien`. Người dùng không thể truy cập trực tiếp đến các property này. Thay vào đó, người dùng sẽ sử dụng phương thức `setName` để thiết lập giá trị cho `name`. Phương thức này sẽ kiểm tra tính hợp lệ của tên trước khi gán giá trị.

__Chương trình mẫu tự viết thể hiện tính đóng gói quản lý tài khoản ngân hàng:__

```cpp
#include <iostream>
#include <string>
using namespace std;


/************************************
 * Viết chương trình quản lý tài khoản
 * ngân hàng thể hiện tính encapsulation.
 * 
**************************************/


class TaiKhoanNganHang{
    
    private:
        static int soTaiKhoanTiepTheo;
        int soTaiKhoan;
        string chuTaiKhoan;
        double soDu;
    
    public:
    TaiKhoanNganHang(string chuTaiKhoan, double soDu)
    {
        soTaiKhoan = soTaiKhoanTiepTheo;
        soTaiKhoanTiepTheo++;
        setChuTaiKhoan(chuTaiKhoan);
        this->soDu = soDu;
    }

    bool kiemTraTen(string ten)
    {

        for (char c: ten)
        {
            if (!isalpha(c) && c != ' ')
                return false;
        }
        return true;
    }

    void setChuTaiKhoan(string ten)
    {
        if (kiemTraTen(ten))
            chuTaiKhoan = ten;
        else
            cout << "Ten tai khoan khong hop le !\n";
    }
    void napTien(double soTien)
    {
        if (soTien > 0)
            soDu += soTien;
        else
            return;
    }
    void rutTien(double soTien)
    {
        if (soTien > 0 && soDu >= soTien)   // cho phep rut het tien neu muon
            soDu -= soTien;
        else
            return;
    }

    void hienThiThongTin()
    {
        cout << "Chu tai khoan: " << chuTaiKhoan << endl;
        cout << soTaiKhoan << endl;
        cout << soDu << endl;
    }

};

int TaiKhoanNganHang::soTaiKhoanTiepTheo = 1;

int main(int argc, char *argv[])
{

    TaiKhoanNganHang pp1("Anh", 12234);
    pp1.hienThiThongTin();

    TaiKhoanNganHang pp2("Hieu", 327478);
    pp2.hienThiThongTin();



    return 0;
}
```

## 15.3. Abstraction (Tính trừu tượng)
__Tính trừu tượng là việc ẩn đi các chi tiết cài đặt không cần thiết và chỉ hiển thị các tính năng quan trọng của đối tượng. Điều này giúp người dùng tập trung vào cách sử dụng đối tượng mà không cần quan tâm đến cách nó hoạt động bên trong.__

__Trong C++, tính trừu tượng có thể được thực hiện thông qua các lớp trừu tượng (abstract class) và giao diện (interface). Lớp trừu tượng là lớp không thể khởi tạo đối tượng và thường chứa các phương thức thuần ảo (pure virtual methods).__

__Trong trường hợp này, ta sẽ viết một chương trình tính thể tích hình hộp chữ nhật thể hiện tính trừu tượng:__

__Tính trừu tượng ẩn đi các chi tiết cài đặt phức tạp, không cần thiết đối với người dùng. Tính đóng gói lại ẩn đi dữ liệu bên trong của đối tượng, chỉ cho phép truy cập thông qua các phương thức công khai.__


```cpp
/*********************************************
* Viết chương trình tính thể tích hình hộp chữ
* nhật thể hiện tính trừu tượng
**********************************************/
class TheTichHinhHopChuNhat
{   
    private:
        int chieu_dai = 0;
        int chieu_rong = 0;
        int chieu_cao = 0;
        long long the_tich = 0;
        void TinhTheTich(int chieu_dai, int chieu_rong, int chieu_cao)
        {
            this->the_tich = (long long)chieu_dai * chieu_rong * chieu_cao;
        }
        bool KiemTraChieuDai(int chieu_dai)
        {
            if (chieu_dai > 0)
                return true;
            return false;
        }
         bool KiemTraChieuRong(int chieu_rong)
        {
            if (chieu_rong > 0)
                return true;
            return false;
        }
         bool KiemTraChieuCao(int chieu_cao)
        {
            if (chieu_cao > 0)
                return true;
            return false;
        }

    public:
        void InRaKetQua()
        {
            if (the_tich == 0)
                cout << "Du lieu khong hop le!";
            cout << "\nThe tich la: " << this->the_tich << endl;
        }
        
        void NhapSo(int chieu_dai, int chieu_rong, int chieu_cao){
            bool hop_le = true;
            if (KiemTraChieuDai(chieu_dai))
                this->chieu_dai = chieu_dai;
            else
            {    
                cout << "Chieu dai khong hop le nhes ~~" << endl;
                hop_le = false;
            }
            if (KiemTraChieuRong(chieu_rong))
                this->chieu_rong = chieu_rong;
            else
            {    
                cout << "Chieu rong khong hop le nhes ~~" << endl;
                hop_le = false;
            }
            
            if (KiemTraChieuCao(chieu_cao))
                this->chieu_cao = chieu_cao;
            else
            {    
                cout << "Chieu cao khong hop le nhes ~~" << endl;
                hop_le = false;
            }
            if (hop_le)
            {
                TinhTheTich(this->chieu_dai, this->chieu_rong, this->chieu_cao);
            }
        }

};


int main()
{

    // TheTichHinhHopChuNhat s1;

    // s1.NhapSo(2, 3, 4);
    // s1.InRaKetQua();

    TheTichHinhHopChuNhat s6;
    s6.NhapSo(1, -6, -8);
    s6.InRaKetQua();

    return 0;
}
```


## 15.4. Inheritance (Tính kế thừa)

__Ta có ví dụ sau:__

```cpp


class SinhVien
{
    public:
        string ten;
        int id;
        string chuyenNganh;
};

class HocSinh
{
    public:
        string ten;
        int id;
        string lop;
};

class GiaoVien
{
    public:
        string ten;
        int id;
        string chuyenMon;
};

```

__Liệu có thể nào gộp các lớp này lại với nhau không? Câu trả lời là có, ta sẽ sử dụng tính kế thừa để làm điều này.__

- Tính kế thừa (inheritance) là khả năng tái sử dụng lại các property và method của một lớp cha (base class) trong một lớp con (derived class) và mở rộng thêm các tính năng. Điều này giúp giảm thiểu mã lặp lại và tăng tính tái sử dụng của mã nguồn.

- Có 3 kiểu kế thừa là public, protected và private. Những property và method của lớp cha sẽ được kế thừa vào lớp con với quyền truy cập tương ứng.

- Kiểu kế thừa (public, protected, private) sẽ quyết định phạm vi truy cập của các thành phần được kế thừa — tức là ảnh hưởng đến việc lớp con nhìn thấy và sử dụng chúng như thế nào. Riêng các thành phần private của lớp cha thì không được kế thừa trực tiếp, nên lớp con không thể truy cập hay thay đổi phạm vi truy cập của chúng. Tuy nhiên, nếu lớp cha cung cấp các hàm public hoặc protected để truy cập vào private, thì lớp con vẫn có thể sử dụng gián tiếp thông qua các hàm đó.

```cpp
class Cha {
    // Thuộc tính và phương thức lớp cha
};

class Con : public Cha {
    // Kế thừa Cha theo kiểu public
};
```
