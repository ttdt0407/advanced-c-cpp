# Bài 8: Memory layout

<p align = "center">
<img src = "https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.geeksforgeeks.org%2Fmemory-layout-of-c-program%2F&psig=AOvVaw3XxA1CncYHKB5mjbvdNbjr&ust=1748853117325000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCLDr5Nnnz40DFQAAAAAdAAAAABAE" width = "500" height = "350">

__Chương trình main.exe (trên window), main.hex (nạp vào vi điều khiển) được lưu ở bộ nhớ SSD (ổ đĩa D, E, ...) hoặc Flash.__
__Khi nhấn nút 'run' chương trình trên window cấp nguồn cho vi điều khiển thì những chương trình này sẽ được copy vào bộ nhớ RAM để thực thi.__
__Có 5 vùng nhớ ở trên thanh RAM dùng để lưu trữ dữ liệu của chương trình gồm: text, initialized data, uninitialized data, heap, stack.__

## 8.1. Text segment (code segment)
