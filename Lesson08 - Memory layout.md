# Bài 8: Memory layout

<p align = "center">
<img src = "https://open4tech.com/wp-content/uploads/2017/04/Memory_Layout.jpg" width = "500" height = "350">

__Chương trình main.exe (trên window), main.hex (nạp vào vi điều khiển) được lưu ở bộ nhớ SSD (ổ đĩa D, E, ...) hoặc Flash.__
__Khi nhấn nút 'run' chương trình trên window cấp nguồn cho vi điều khiển thì những chương trình này sẽ được copy vào bộ nhớ RAM để thực thi.__
__Có 5 vùng nhớ ở trên thanh RAM dùng để lưu trữ dữ liệu của chương trình gồm: text, initialized data, uninitialized data, heap, stack.__

## 8.1. Text segment (code segment)
