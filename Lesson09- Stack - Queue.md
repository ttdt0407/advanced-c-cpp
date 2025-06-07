# Bài 9: Stack - Queue

## 9.1. Cấu trúc dữ liệu

__Là cách tổ chức, và lưu trữ dữ liệu để chúng có thể được sử dụng và truy cập một cách có hiệu quả, đóng vai trò quan trọng trong việc giải quyết các bài toán và tối ưu hoá thuật toán, vì nó ảnh hưởng trực tiếp đến tốc độ thực thi và tính phức tạp của chương trình.__

Có 2 kiểu chính cấu trúc dữ liệu:
+ Cấu trúc dữ liệu tuyến tính (Linear Data Structure): mảng, ngăn xếp, hàng đợi(queue), danh sách liên kết(linked list).
+ Cấu trúc dữ liệu phi tuyến tính (Non-linear Data Structure): đồ thị(graph), cây(tree).


## 9.2. Stack

__Là 1 dạng cấu trúc dữ liệu linear, được lấy ý tưởng từ cách lưu trữ và sắp xếp dữ liệu ở phân vùng stack trong memory layout, tuân thủ theo nguyên tắc FILO (First In - Last Out).__

__Có thể giới hạn stack lưu trữ được tối đa bao nhiêu dữ liệu.__

__Các thao tác trên stack:__
+ push : thêm một phần tử mới vào đỉnh của stack, push = top++.
+ pop : xoá một phần tử đang ở đỉnh của stack, push = top--.
+ peek/top: khởi tạo chỉ số lấy giá trị của phần tử đang ở đỉnh của stack (không xoá).
+ peek/top = -1; khi stack đang rỗng, không thể lấy dữ liệu ra.
+ peek/top = size - 1; stack đang đầy, không thể bỏ vào dữ liệu.


