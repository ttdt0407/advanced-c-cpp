# Bài 12: Algorithm

## 1. Bubble Sort
### Khái niệm
__Bubble Sort - thuật toán sắp xếp nổi bọt, hoạt động dựa trên nguyên tắc hoán đổi phần tử liền kề để đưa phần tử lớn hơn về cuối danh sách, hoặc phần tử nhỏ hơn về đầu danh sách.__

__Thuật toán gồm các bước sau:__
1. Duyệt danh sách từ đầu tới cuối.
2. So sánh 2 phần tử liền kề, nếu phần tử trước lớn hơn phần tử sau thì thực hiện hoán đổi vị trí.
3. Lặp lại quá trình cho đến khi không còn sự hoán đổi nào xảy ra (mảng đã được sắp xếp).

```c

void bubble_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] < arr[j+1])
            {
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
            }
        }
    }
}

```

+ Đầu tiên ta cần lặp n-1 lần để chuyển hết tất cả các số đến vị trí đúng của nó. Bởi vì số cuối cùng sẽ tự về vị trí đúng sau khi số n-1 được dịch chuyển nên không cần lần dịch chuyển thứ n.
+ Sau đó mỗi lần dịch chuyển một số, ta cần n - i - 1 lần dịch chuyển giữa các cặp số. Nếu là lần lặp thứ 0 thì n - 1, nếu là lần lặp thứ 1 thì sẽ là n - 2, lần thứ 3 thì sẽ là n - 3,...
+ Trong mỗi lần dịch chuyển giữa một cặp giá trị, ta cần sử dụng biến tạm hoặc sử dụng phép tính xor:

a = a ^ b;
b = a ^ b;
a = a ^ b;

## 2. Linear Search

__Là thuật toán tìm kiếm đơn giản nhất, nó dùng để tìm kiếm một phần tử trong mảng.__

__Nguyên tắc hoạt động như sau:__
1. Duyệt từng phần tử trong mảng từ trái sang phải.
2. Nếu phần tử đang xét trùng với giá trị cần tìm, trả về vị trí của nó.
3. Nếu duyệt hết mảng mà không tìm thấy, trả về kết quả không tồn tại.

```c

int linear_search(int* arr, int n, int target)
{

  for (size_t i = 0; i < n; i++)
    if (arr[i] == target)
        return i;
    else
      return -1;
}

```

+ Thuật toán đơn giản nhưng lại tốn khá nhiều thời gian.
+ Không phù hợp khi sử dụng với số lượng phần tử lớn.

## 3. Binary Search

__Thuật toán tìm kiếm nhị phân (Binary Search) hoạt động bằng cách chia đôi mảng để tìm kiếm, thay vì duyệt tuần tự như Linear Search.__
__Nguyên lý hoạt động:__

1. Sắp xếp mảng (tăng dần hoặc giảm dần).
2. So sánh phần tử ở giữa mảng với giá trị cần tìm.
+ Nếu trùng -> trả về vị trí.
+ Nếu nhỏ hơn -> tiếp tục tìm trong nửa phải.
+ Nếu lớn hơn -> tiếp tục tìm trong nửa trái.
3. Lặp lại bước 2 cho đến khi tìm thấy phần tử hoặc không còn phần tử nào để tìm.

```c
int binary_search(int* arr, int n, int target)
{
  int left = 0;
  int right = n - 1;

  while (left <= right) {
    int middle = left + (right - left) / 2;

    if (arr[middle] == target) {
      return middle;
      }
    else if (arr[middle] < target)
        right = middle + 1;
    else
        left = middle - 1;
  }
  return - 1;
  
}

```

## 4. Binary Search Tree

__Cấu trúc dữ liệu phân cấp (tree) là một cấu trúc dữ liệu phi tuyến tính, trong đó các phần tử (được gọi là nút, hay node) được tổ chức theo một thứ bậc phân cấp. Cây là một trong những cấu trúc dữ liệu quan trọng, được sử dụng rộng rãi trong khoa học máy tính để biểu diễn các quan hệ phân cấp, tìm kiếm, sắp xếp, và lưu trữ.__

- Mỗi nút có tối đa 2 nút con (gọi là cây con trái và cây con phải).
- Dữ liệu trong cây tuân thủ theo quy tắc:
+ Nút con trái chứa giá trị nhỏ hơn nút gốc.
+ Nút con phải chứa giá trị lớn hơn nút gốc.
+ Quy tắc này áp dụng đệ quy cho toàn bộ cây.

