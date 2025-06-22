# Bài 11: JSON 

## Khái niệm

__Là một định dạng truyền dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống với nhau.__

+ JSON viết tắt của JavaScript Object Notation.
+ JSON được thiết kế để dễ đọc và dễ viết cho con người cũng như dễ dàng phân tích và tạo ra cho máy tính. Nó sử dụng một cú pháp nhẹ dựa trên cặp key-value.
+ Mỗi đối tượng JSON bao gồm một tập hợp các cặp key - value, trong khi mỗi mảng JSON là một tập hợp các giá trị.
+ Ví dụ tuổi là key thì số tuổi là value.

## Định dạng JSON

+ Key và value luôn được ngăn cách nhau bởi ':', key luôn nằm bên trái và value luôn nằm bên phải.
+ Các cặp key - value ngăn cách nhau bởi dấu phẩy.
+ Key luôn là chuỗi , value có thể là bất kỳ kiểu dữ liệu nào từ số, kí tự, chuỗi, mảng, null hay thậm chí là một object(tập hợp các key-value),v.v.
+ Object được biểu diễn trong '{}'.
+ Số trong JSON luôn là số thực.

### Định dạng đối tượng trong JSON (Object)

```json
{
    "name": "John",
    "age": 38,
    "isStudent": false,
    "grades": [2,3,2,1]
}
```
__Các key-value có thể là chuỗi, số, mảng, v.v.__

### Định dạng mảng trong JSON (Array)

```json
[
    {
        "name": "John Dare",
        "age": 32,
        "city": "New York",
        "occupation": "Software Engineer",
        "isStudent": false
    },
    {
        "name": "Jane Smith",
        "age": null,
        "city": "Los Angeles",
        "contact": {
            "email": "jame.smith@example.com",
            "phone": "555-1234"
        }
    },
    {
        "name": "Bob Johnson",
        "age": 35,
        "city": "Chicago"
    },
    20, 3.14, "hello world", true, null, [80.70,90]
]

```

___Mảng JSON không bị ràng buộc về kiểu dữ liệu, mỗi phần tử đều có thể khác nhau về kiểu dữ liệu.__
