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
__Mảng JSON không bị ràng buộc về kiểu dữ liệu, mỗi phần tử đều có thể khác nhau về kiểu dữ liệu.__
__Sự khác biệt chủ yếu giữa JSON và struct hay union là ở chỗ, JSON linh hoạt hơn trong việc lưu trữ dữ liệu, dùng để trao đổi dữ liệu giữa nhiều hệ thống, dễ đọc dễ, xử lý.__

## Cách sử dụng trong C

__Ta sử dụng enum để có thể liệt kê ra các kiểu dữ liệu có thể nhận: số, chuỗi, đúng/sai, đối tượng json hay mảng json.__

```c
typedef enum
{
    JSON_BOOLEAN,
    JSON_NUMBER,
    JSON_STRING,
    JSON_OBJECT,
    JSON_ARRAY
} JsonType;
```

__Sử dụng cấu trúc dữ liệu struct để lưu trữ dữ liệu JSON, lồng union ở bên trong.__

```c
typedef struct Json_value
{
    JsonType type;
    union 
    {
        int boolean; // true/false
        int num;     // gia tri so thuc
        char *string;

        struct {
            struct Json_value *value;  // de quy de xac dinh dac diem tung phan tu
            size_t count;    // dem so luong phan tu
        } array;

        struct 
        {
            struct Json_value *value;
            char **key;    // la mot con tro den cac chuoi, hay la mang cac chuoi.
            size_t count;
        } object;
    } value;

} Json_value;
```

+ Sử dụng union để tiết kiệm vùng nhớ.


__Ví dụ xây dựng dữ liệu JSON dưới dạng mảng.__

```c
int main (void)
{   
    // Json: [50.345, true, [50,"abc"]]

    // Cấp phát động vùng nhớ để lưu trữ tạm thời trước khi biết chính xác size
    Json_value *json_str = (Json_value*) malloc(sizeof(Json_value));
    json_str->type = JSON_ARRAY;
    json_str->value.array.count = 3;

    // Cấp phát bổ sung vùng nhớ cho các phần tử trong mảng
    json_str->value.array.value = (Json_value *)malloc(sizeof(Json_value) * json_str->value.array.count);

    // Lặp lại tương tự với các phần tử trong mảng
    
    // Phần tử thứ 0
    json_str->value.array.value[0].type = JSON_NUM;
    json_str->value.array.value[0].value.num = 50.345;

    // Phần tử thứ 1
    json_str->value.array.value[1].type = JSON_BOOLEAN;
    json_str->value.array.value[1].value.boolean = 1;

    // Phần tử thứ 2 là mảng chứa 2 phần tử con
    json_str->value.array.value[2].type = JSON_ARRAY;
    json_str->value.array.value[2].value.array.count = 2;

    // Cấp phát vùng nhớ cho mảng chứa 2 phần tử con
    json_str->value.array.value[2].value.array.value = (Json_value *)malloc(json_str->value.array.value[2].value.array.count * sizeof(Json_value));

    // Phần tử con thứ 0 trong mảng (phần tử thứ 2.0)
    json_str->value.array.value[2].value.array.value[0].type = JSON_NUM;
    json_str->value.array.value[2].value.array.value[0].value.num = 50; 

    // phần tử con thứ 1 trong mảng (phần tử thứ 2.1)
    json_str->value.array.value[2].value.array.value[1].type = JSON_STRING;
    json_str->value.array.value[2].value.array.value[1].value.string = "abc";

    return 0;
}
```