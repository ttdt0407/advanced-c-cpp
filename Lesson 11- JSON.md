# Bài 11: JSON 

## 1. Khái niệm

__Là một định dạng truyền dữ liệu phổ biến trong lập trình và giao tiếp giữa các máy chủ và trình duyệt web, cũng như giữa các hệ thống với nhau.__

+ JSON viết tắt của JavaScript Object Notation.
+ JSON được thiết kế để dễ đọc và dễ viết cho con người cũng như dễ dàng phân tích và tạo ra cho máy tính. Nó sử dụng một cú pháp nhẹ dựa trên cặp key-value.
+ Mỗi đối tượng JSON bao gồm một tập hợp các cặp key - value, trong khi mỗi mảng JSON là một tập hợp các giá trị.
+ Ví dụ tuổi là key thì số tuổi là value.

## 2. Định dạng JSON

+ Key và value luôn được ngăn cách nhau bởi ':', key luôn nằm bên trái và value luôn nằm bên phải.
+ Các cặp key - value ngăn cách nhau bởi dấu phẩy.
+ Key luôn là chuỗi , value có thể là bất kỳ kiểu dữ liệu nào từ số, kí tự, chuỗi, mảng, null hay thậm chí là một object(tập hợp các key-value),v.v.
+ Object được biểu diễn trong '{}'.
+ Số trong JSON luôn là số thực.

### 2.1. Định dạng đối tượng trong JSON (Object)

```json
{
    "name": "John",
    "age": 38,
    "isStudent": false,
    "grades": [2,3,2,1]
}
```
__Các key-value có thể là chuỗi, số, mảng, v.v.__

### 2.2. Định dạng mảng trong JSON (Array)

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

## 3. Cách sử dụng trong C

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


### 3.1. Ví dụ xây dựng dữ liệu JSON dưới dạng mảng

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

### 3.2. Mô phỏng sử dụng JSON dưới dạng Object có chứa mảng 

```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum
{
    JSON_NUM,
    JSON_STR,
    JSON_BOOLEAN,
    JSON_NULL,
    JSON_ARR,
    JSON_OBJECT
} Type;

typedef struct Json_Value
{
    /* data */

    Type type;

    union {
        int num;
        char *str;
        int bool;

        struct {
            int count;
            struct Json_Value *value;

        } array;

        struct {
            int count;
            struct Json_Value *value;
            char **key;
        } object;
    } value;
} Json_Value;


int main (int argc, char *argv[])
{ 
    Json_Value *string;
    
    // Du lieu can truyen co dinh dang sau:
    /*{
    "name": "John",
    "age": 38,
    "isStudent": false,
    "grades": [2,3,2,1]
    }*/

    // Cap phat vung nho ban dau cho bien co kieu Json_Value
    string = (Json_Value *)malloc(sizeof(Json_Value));

    string->type = JSON_OBJECT;
    string->value.object.count = 4;

    // Cap phat bo sung sau khi da biet duoc so luong phan tu
    string->value.object.value = (Json_Value *)malloc(string->value.object.count * sizeof(Json_Value));
    string->value.object.key = (char **)malloc(string->value.object.count * sizeof(Json_Value));

    // Tao cap key-value 1:
    string->value.object.key[0] = "name";
    string->value.object.value[0].type = JSON_STR;
    string->value.object.value[0].value.str = "John";

    // Tao cap key-value 2:
    string->value.object.key[1] = "age";
    string->value.object.value[1].type = JSON_NUM;
    string->value.object.value[1].value.num = 38;

    // Tao cap key value 3
    string->value.object.key[2] = "isStudent";
    string->value.object.value[2].type = JSON_BOOLEAN;
    string->value.object.value[2].value.bool = 1;
    
    // Tao cap key value 4
    string->value.object.key[3] = "grades";
    string->value.object.value[3].type = JSON_ARR;

    // Cap phat dong cho phan tu mang con
    string->value.object.value[3].value.array.count = 4;
    string->value.object.value[3].value.array.value = (Json_Value *)malloc(string->value.object.value[3].value.array.count * sizeof(Json_Value));

    // Cap phat cho phan tu con dau
    string->value.object.value[3].value.array.value[0].type = JSON_NUM;
    string->value.object.value[3].value.array.value[0].value.num = 2;

    // Cap phat cho phan tu con thu 1
    string->value.object.value[3].value.array.value[1].type = JSON_NUM;
    string->value.object.value[3].value.array.value[1].value.num = 3;

    // Cap phat cho phan tu con thu 2
    string->value.object.value[3].value.array.value[2].type = JSON_NUM;
    string->value.object.value[3].value.array.value[2].value.num = 2;

    // Cap phat cho phan tu con cuoi
    string->value.object.value[3].value.array.value[3].type = JSON_NUM;
    string->value.object.value[3].value.array.value[3].value.num = 1;

    return 0;
}
```
### 3.3. Các bước sử dụng JSON

+ Bước 1: Phân tích cú pháp JSON.
+ Bước 2: Hiển thị kết quả sau khi đã phân tích.
+ Bước 3: Giải phóng bộ nhớ.

+ Chuỗi trong chuỗi sẽ gây lỗi cú pháp, cần thêm kí tự '\' vào trước để tránh trình biên dịch không biết được điểm kết thúc chuỗi.

```c
const char *str = "{"
    "\"name\" : \"JOHN\","
    "\"age\" : 38,"
    "\"isStudent\" : true"
"}"

```

+ Nếu các chuỗi không nằm trên 1 hàng thì cần có dấu " để ngăn cách các chuỗi. Trình biên dịch sẽ tự động hiểu là thành một chuỗi liền nhau, và gộp lại thành 1 chuỗi.

```c
// Hai chuỗi nằm trên 2 dòng khác nhau:
const char *str1 = "{ \"abc\" "    
                        "\"anh\"}";
```

## 4. Các hàm sử dụng thường gặp
### 4.1. skip_whitespace

__Chức năng là để bỏ qua các khoảng trắng.__

```c

static void skip_whitespace(const char **json) {
    while (isspace(**json)) {
        (*json)++;
    }
}


```

__Hàm isspace() trong thư viện ctype.h, dùng để kiểm tra khoảng trắng, nếu là khoảng trắng thì trả về 1.__

__Trong trường hợp này thì nếu là khoảng trắng tăng vị trí con trỏ lên 1 đơn vị, lặp lại hành động trên cho tới khi không còn khoảng trắng nữa.__


### 4.2. parse_json

```c
JsonValue *parse_json(const char **json) { 
    while (isspace(**json)) {
        (*json)++;
    }

    switch (**json) {
        case 'n':
            return parse_null(json);
        case 't':
        case 'f':
            return parse_boolean(json);
        case '\"':
            return parse_string(json);
        case '[':
            return parse_array(json);
        case '{':
            return parse_object(json);
        default:
            if (isdigit(**json) || **json == '-') {
                return parse_number(json);
            } else {
                // Lỗi phân tích cú pháp
                return NULL;
            }
    }
}

```

__Là hàm trung tâm dùng để xác định kiểu dữ liệu JSON và gọi đúng hàm con tương ứng để phân tích cú pháp (parse).__

+ Đọc một phần tử JSON và trả về một JsonValue* tương ứng với kiểu của nó.
+ Đầu tiên bỏ qua khoảng trắng trước dữ liệu thực sự.
+ Tiếp theo hàm sẽ nhìn ký tự đầu tiên để quyết định dữ liệu kiểu dữ liệu tương ứng bằng cách gọi hàm.



### 4.3. parse_null

```c
JsonValue *parse_null(const char **json) {
    skip_whitespace(json);
    if (strncmp(*json, "null", 4) == 0) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NULL;
        *json += 4;
        return value;
    }
    return NULL;
}
```

__Phân tích một giá trị "null" trong chuỗi JSON và trả về một con trỏ JsonValue* tương ứng.__

+ Bỏ qua khoảng trắng (nếu có) trước giá trị null.
+ So sánh 4 ký tự đầu tiên trong chuỗi bằng strncmp(), hàm này sẽ trả về kết quả của phép tính s1 - s2.
+ Nếu đúng ký tự null thì cấp phát vùng nhớ động để tạo ra một JsonValue mới.
+ Gán kiểu dữ liệu cho value là JSON_NULL.
+ Di chuyển con trỏ *json về phía trước 4 ký tự, tức là bỏ qua "null" trong chuỗi JSON gốc.
+ Trả về con trỏ value nếu đã phân tích thành công.
+ Nếu không phải "null" thì trả về NULL để báo lỗi hoặc không hợp lệ.


### 4.4. parse_boolean 

```c

JsonValue *parse_boolean(const char **json) {
    skip_whitespace(json);
    JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
    if (strncmp(*json, "true", 4) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = true;
        *json += 4;
    } else if (strncmp(*json, "false", 5) == 0) {
        value->type = JSON_BOOLEAN;
        value->value.boolean = false;
        *json += 5;
    } else {
        free(value);
        return NULL;
    }
    return value;
}

```

__Phân tích một giá trị boolean "true" hoặc "false" trong chuỗi JSON và trả về một con trỏ JsonValue* tương ứng.__

+ Đầu tiên hàm bỏ qua các ký tự trắng (space, tab, newline, ...) trước khi đọc dữ liệu.
+ Cấp phát động vùng nhớ cho một JsonValue mới để lưu boolean.
+ Trường hợp "true" hoặc "false" thì cấp phát và gán kiểu tương ứng.
+ Cuối cùng tăng giá trị con trỏ.
+ Nếu không phải "true" hoặc "false" free vùng nhớ động và trả về NULL.
+ Cuối cùng trả về con trỏ tới JsonValue đã điền thông tin boolean.


### 4.5. parse_number

```c

JsonValue *parse_number(const char **json) {
    skip_whitespace(json);
    char *end;
    double num = strtod(*json, &end);
    if (end != *json) {
        JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
        value->type = JSON_NUMBER;
        value->value.number = num;
        *json = end;
        return value;
    }
    return NULL;
}

```

__Phân tích một số thực trong chuỗi JSON, lưu vào struct JsonValue và trả về con trỏ JsonValue*.__

+ Vì các số trong chuỗi JSON đều dưới dạng kí tự nên sử dụng strtod() để chuyển đổi thành số. Tham số đầu tiên truyền vào là con trỏ cấp 1 mang vị trí bắt đầu của kí tự số, tham số thứ hai là địa chỉ của con trỏ cấp 1, trả về vị trí kết thúc kí tự số.
+ Nếu thỏa điều kiện con trỏ end khác với con trỏ đến vị trí bắt đầu kí tự số thì hợp lệ.
+ Bắt đầu cấp phát động cho giá trị và gán kiểu là JSON_NUMBER.
+ Gán giá trị sau đó cập nhật vị trí con trỏ.
+ Trả về giá trị JsonValue*.


### 4.6. parse_string

```c

JsonValue *parse_string(const char **json) {
    skip_whitespace(json);


    if (**json == '\"') {
        (*json)++;
        const char *start = *json;
        while (**json != '\"' && **json != '\0') {
            (*json)++;
        }
        if (**json == '\"') {
            size_t length = *json - start; // 3
            char *str = (char *) malloc((length + 1) * sizeof(char));
            strncpy(str, start, length);
            str[length] = '\0';

            JsonValue *value = (JsonValue *) malloc(sizeof(JsonValue));
            value->type = JSON_STRING;
            value->value.string = str;
            (*json)++;
            return value;
        }
    }
    return NULL;
}

```
__Phân tích một chuỗi JSON kiểu ("...") và lưu vào JsonValue.__

+ Bỏ qua khoảng trắng.
+ Kiểm tra điều kiện xem kí tự tại vị trí hiện tại có phải là dấu " không trước khi bắt đầu xử lý chuỗi JSON.
+ Đánh dấu vị trí bắt đầu chuỗi.
+ Duyệt tới dấu kết thúc chuỗi.
+ Tạo bản sao dữ liệu (chuỗi) : cấp phát chuỗi mới trong heap, sao chép "length" kí tự kể từ "start".
+ Thêm kí tự null vào cuối chuỗi.
+ Tạo JsonValue: cấp phát động, gán kiểu, gán giá trị, tăng con trỏ lên 1 đơn vị.
+ Trả về giá trị value.
+ Trả về null nếu gặp lỗi.

### 4.7. parse_array

```c
JsonValue *parse_array(const char **json) {
    skip_whitespace(json);
    if (**json == '[') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *array_value = (JsonValue *)malloc(sizeof(JsonValue));
        array_value->type = JSON_ARRAY;
        array_value->value.array.count = 0;
        array_value->value.array.values = NULL;

        /*
        double arr[2] = {};
        arr[0] = 30;
        arr[1] = 70;
        */

        while (**json != ']' && **json != '\0') {
            JsonValue *element = parse_json(json); // 70
            if (element) {
                array_value->value.array.count++;
                array_value->value.array.values = (JsonValue *)realloc(array_value->value.array.values, array_value->value.array.count * sizeof(JsonValue));
                array_value->value.array.values[array_value->value.array.count - 1] = *element;
                free(element);
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        
        if (**json == ']') {
            (*json)++;
            return array_value;
        } else {
            free_json_value(array_value);
            return NULL;
        }
    }
    return NULL;
}

```

__Phân tích cú pháp (parse) mảng JSON từ chuỗi đầu vào.__

+ Bỏ qua kí tự trắng như dấu cách, xuống dòng,...
+ Kiểm tra dấu hiệu bắt đầu của mảng.
+ Cấp phát đối tượng JsonValue, tạm thời gián số lượng phần tử trong mảng bằng 0 và đệ quy JsonValue gán cho null.
+ Sử dụng vòng lặp cho đến khi nào gặp kí tự null hoặc kí tự ']' báo hiệu kết thúc.
+ Tạo một biến element kiểu JsonValue* để lưu trữ từng phần tử trong mảng.
+ Realloc lại vùng nhớ động để cập nhật thêm số lượng phần tử mới.
+ Xong xuôi thì xử lý dấu phẩy sau đó kết thúc mảng.
+ Nếu có lỗi thì giải phóng bộ nhớ và trả về.

### 4.8.parse_object

```c
JsonValue *parse_object(const char **json) {
    skip_whitespace(json);
    if (**json == '{') {
        (*json)++;
        skip_whitespace(json);

        JsonValue *object_value = (JsonValue *)malloc(sizeof(JsonValue));
        object_value->type = JSON_OBJECT;
        object_value->value.object.count = 0;
        object_value->value.object.keys = NULL;
        object_value->value.object.values = NULL;

        while (**json != '}' && **json != '\0') {
            JsonValue *key = parse_string(json);
            if (key) {
                skip_whitespace(json);
                if (**json == ':') {
                    (*json)++;
                    JsonValue *value = parse_json(json);
                    if (value) {
                        object_value->value.object.count++;
                        object_value->value.object.keys = (char **)realloc(object_value->value.object.keys, object_value->value.object.count * sizeof(char *));
                        object_value->value.object.keys[object_value->value.object.count - 1] = key->value.string;

                        object_value->value.object.values = (JsonValue *)realloc(object_value->value.object.values, object_value->value.object.count * sizeof(JsonValue));
                        object_value->value.object.values[object_value->value.object.count - 1] = *value;
                        free(value);
                    } else {
                        free_json_value(key);
                        break;
                    }
                } else {
                    free_json_value(key);
                    break;
                }
            } else {
                break;
            }
            skip_whitespace(json);
            if (**json == ',') {
                (*json)++;
            }
        }
        if (**json == '}') {
            (*json)++;
            return object_value;
        } else {
            free_json_value(object_value);
            return NULL;
        }
    }
    return NULL;
}
```

__Phân tích cú pháp một đối tượng JSON.__

+ Bỏ qua khoảng trắng.
+ Nếu là kí tự '{' thì tăng giá trị con trỏ lên 1 đơn vị và tiếp tục bỏ qua khoảng trắng.
+ Cấp phát bộ nhớ để lưu trữ cho JsonValue. Ban đầu object trống (chưa có key-value nào).
+ Dùng vòng lặp xử lý từng cặp "key":value.
+ Tạo JsonValue*key và phân tích đó phải là chuỗi.
+ Bỏ qua khoảng trắng.
+ Nếu gặp kí tự ':' thì tiếp tục cập nhật giá trị con trỏ.
+ JsonValue* value phân tích giá trị tương ứng với key.
+ Nếu đó là giá trị có nghĩa thì cấp phát vùng nhớ cho keys và values.
+ Lưu key và value.
+ free(key) không được vì ta dùng key->value.string làm key.
+ Nếu lỗi thì free_json_value(key).
+ Nếu găp kí tự ',' thì bỏ qua và tiếp tục.
+ Khi gặp '}' thì kết thúc object.
+ Nếu sai cú pháp thì free toàn bộ và trả về NULL.


### 4.9. free_json_value

```c
void free_json_value(JsonValue *json_value) {
    if (json_value == NULL) {
        return;
    }
    switch (json_value->type) {
        case JSON_STRING:
            free(json_value->value.string);
            break;

        case JSON_ARRAY:
            for (size_t i = 0; i < json_value->value.array.count; i++) {
                free_json_value(&json_value->value.array.values[i]);
            }
            free(json_value->value.array.values);
            break;

        case JSON_OBJECT:
            for (size_t i = 0; i < json_value->value.object.count; i++) {
                free(json_value->value.object.keys[i]);
                free_json_value(&json_value->value.object.values[i]);
            }
            free(json_value->value.object.keys);
            free(json_value->value.object.values);
            break;

        default:
            break;
    }
}
```

__Đệ quy đi qua toàn bộ cây JSON (gồm các object, array, string, ...) và giải phóng tất cả vùng nhớ đã cáp phát động trước đó.__

+ Nếu json_value rỗng, thoát luôn.
+ Trường hợp nếu là JSON_STRING thì ta chỉ cần free nó.

+ Trường hợp đó là JSON_ARRAY thì ta dùng vòng lặp đi qua từng phần tử trong mảng.
+ Dùng đệ quy để free từng phần tử (&value[i]).
+ Sau đó free mảng con trỏ values.

+ Còn nếu đó là JSON_OBJECT thì ta cũng vòng lặp đi qua các phần tử trong object, mỗi lần lặp ta giải phóng key và value cùng lúc.
+ Sau đó thì giải phóng nốt mảng của key và value.



