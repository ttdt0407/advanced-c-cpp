# Bài 14: Array và String

## 14.1. Array

__Array là một cấu trúc dữ liệu cơ bản dùng để lưu trữ các biến cùng kiểu dữ liệu như: integer, char, float, double, pointer, ...__

__Có hai cách để cấp phát array đó là cấp phát tĩnh và cấp phát động.__

### 14.1.1. Static array

__Cú pháp khởi tạo mảng như sau, có nhiều cách để khởi tạo một mảng tĩnh.__

```c
    int A[2] = {0};
```
```c
    int A[] = {1, 2, 3};
```

```c
    int A[3] = {1, 2, 3};
```

```c
    int A[3];

    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
```

+ Kích thước mảng được xác định trong thời điểm biên dịch chương trình (kém linh hoạt hơn so với mảng động).
+ Bộ nhớ sẽ được cấp phát trong suốt runtime.
+ Chỉ số của mảng bắt đầu từ 0 và kết thúc ở length - 1.
+ Các phần tử trong mảng được cấp phát ở vùng nhớ stack nếu scope là local và data hoặc bss segment nếu scope là global.


### 14.1.2. Dynamic array

__Mảng động được cấp phát để gia tăng sự linh hoạt, không cần cố định kích thước như mảng tĩnh.__

__Ta cấp phát mảng ở vùng nhớ heap, khi làm việc với heap, cần sử dụng con trỏ để truy cập (indirectly).__

```c
    /* Cấp phát mảng động gồm 3 phần tử có kiểu dữ liệu integer */
    int *pInt = (int *)malloc(sizeof(int) * 3);

    /* Cấp phát mảng động gồm 3 phần tử có kiểu dữ liệu char */
    int *pChar = (char *)malloc(sizeof(char) * 3);
```

+ Khi làm việc với mảng động ta thường sử dụng một số hàm như: malloc, calloc, realloc, free.
+ Việc sử dụng vùng nhớ heap thường xuyên dễ làm phân mảnh chương trình hoặc rò rỉ bộ nhớ nếu không quản lý tốt.
+ Hàm malloc() trả về con trỏ void nên cần ép kiểu khi gọi.
+ Linh hoạt, có thể resize mảng trong heap.

### 14.1.3. Một số function sử dụng với cấu trúc dữ liệu array

```c
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    ERROR_INVALID,
    ERROR_OK,
    ERROR_NOTFOUND
} Error_status_t;

typedef struct _Array
{
    int *A;
    int size;
    int length;
} Array_t;

void display(Array_t arr)
{
    printf("Elements of array: ");

    for (int i = 0; i < arr.length; i++)
    {
        printf("%d ", arr.A[i]);
    }
    printf("\n");
}

int append(Array_t *arr, int val)
{
    int result = ERROR_OK;
    if (arr->length < arr->size)
    {
        arr->A[arr->length++] = val;
    }
    else
    {
        result = ERROR_INVALID;
    }

    return result;
}

int insert(Array_t *arr, int val, int index)
{
    int result = ERROR_OK;
    if (index >= 0 && index < arr->length)
    {
        for (int i = arr->length; i > index; i--)
        {
            arr->A[i] = arr->A[i - 1];
        }
        arr->A[index] = val;
        arr->length++;
    }
    else
    {
        result = ERROR_INVALID;
    }

    return result;
}

int delete(Array_t *arr, int index)
{
    int result = ERROR_OK;
    if (index >= 0 && index < arr->length)
    {
        arr->A[index] = 0;
        for (int i = index; i < arr->length - 1; i++)
        {
            arr->A[i] = arr->A[i + 1];
        }
        arr->length--;
    }
    else
    {
        result = ERROR_INVALID;
    }

    return result;
}

int swap(int *src, int *dst)
{
    int result = ERROR_OK;

    if ((src != NULL) && (dst != NULL))
    {
        int temp = *src;
        *src = *dst;
        *dst = *src;
    }
    else
    {
        result = ERROR_INVALID;
    }

    return result;
}

int linear_search(Array_t *arr, int val)
{
    int result = ERROR_NOTFOUND;

    for (int i = 0; i < arr->length; i++)
    {
        if (val == arr->A[i])
        {
            result = i;
        }
    }

    return result;
}

int binary_search(Array_t *arr, int val)
{
    int result = ERROR_NOTFOUND;
    int l = 0;
    int h = arr->length - 1;

    while (l <= h)
    {
        int m = (h - l) / 2 + l;
        if (arr->A[m] == val)
        {
            result = m;
        }
        else if (arr->A[m] < val)
        {
            l = m + 1;
        }
        else
        {
            h = m - 1;
        }
    }

    return result;
}

int get(Array_t *arr, int index)
{
    if (index >= 0 && index < arr->length)
    {
        return arr->A[index];
    }

    return ERROR_NOTFOUND;
}

int set(Array_t *arr, int val, int index)
{
    int result = ERROR_OK;

    if (index >= 0 && index < arr->length)
    {
        arr->A[index] = val;
    }
    else
    {
        result = ERROR_INVALID;
    }

    return result;
}

void reverse(Array_t *arr)
{
    for (int i = 0; i < arr->length / 2; i++)
    {
        swap(&arr->A[i], &arr->A[arr->length - i]);
    }
}


Array_t *merge(Array_t *arr1, Array_t *arr2)
{
    int k = 0;
    int i = 0;
    int j = 0;

    Array_t *pStruct = (Array_t *)malloc(sizeof(Array_t));

    while((i < arr1->length) && (j < arr2->length))
    {
        if (arr1->A[i] < arr2->A[j])
        {
            pStruct->A[k++] = arr1->A[i++];
        }
        else
        {
            pStruct->A[k++] = arr2->A[j++];
        }
    }

    while(i < arr1->length)
    {
        pStruct->A[k++] = arr1->A[i++];
    }

    while (j < arr2->length)
    {
        pStruct->A[k++] = arr2->A[j++];
    }

    pStruct->length = arr1->length + arr2->length;
}

```

## 14.2. String

__String được biểu diễn dưới dạng cấu trúc dữ liệu array, có kí tự NULL ở cuối để đánh dấu kết thúc chuỗi.__

+ str trong ví dụ dưới là con trỏ đến chuỗi hằng (nằm ở phân vùng text), ta chỉ có thể đọc các kí tự chứ không thể thay đổi giá trị của chúng.

```c

    char *str = "Hello";
```

+ Cách khởi tạo chuỗi dưới đây thì có thể đọc và thay đổi giá trị của chuỗi hoặc của từng phần tử trong chuỗi.

```c
    char A[] = "Hello";
    char A[] = {'H', 'e', 'l', 'l', 'o', '\0'};
```
+ Nếu dùng dấu nháy kép thì mặc định trình biên dịch sẽ thêm vào cuối chuỗi một kí tự null, còn nếu khai báo trong dấu ngoặc đơn như hàng dưới thì ta cần phải thêm kí tự null thủ công.


### 14.2.1. Tự triển khai thư viện string.h cơ bản

```c
#include <stdint.h>
#include <stdio.h>

/**
 * @brief Kiểm tra xem ký tự có phải là chữ cái hoặc chữ số không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là chữ cái (a-z, A-Z) hoặc chữ số (0-9), ngược lại trả về 0
 */
int my_isalnum(char c)
{
    int result = 0;

    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        result = 1;
    }

    return result;
}

/**
 * @brief Kiểm tra xem ký tự có phải là chữ số không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là chữ số (0-9), ngược lại trả về 0
 */
int my_isdigit(char c)
{
    int result = 0;

    if (c >= '0' && c <= '9')
    {
        result = 1;
    }
    return result;
}

/**
 * @brief Kiểm tra xem ký tự có phải là chữ cái in thường không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là chữ cái in thường (a-z), ngược lại trả về 0
 */
int my_islower(char c)
{
    int result = 0;

    if (c >= 'a' && c <= 'z')
    {
        result = 1;
    }

    return result;
}

/**
 * @brief Kiểm tra xem ký tự có phải là chữ cái in hoa không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là chữ cái in hoa (A-Z), ngược lại trả về 0
 */
int my_isupper(char c)
{
    int result = 0;

    if (c >= 'A' && c <= 'Z')
    {
        result = 1;
    }

    return result;
}

/**
 * @brief Kiểm tra xem ký tự có phải là chữ cái không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là chữ cái (a-z, A-Z), ngược lại trả về 0
 */
int my_isalpha(char c)
{
    int result = 0;

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        result = 1;
    }

    return result;
}

/**
 * @brief Chuyển đổi ký tự in hoa thành ký tự in thường
 * 
 * @param c Ký tự cần chuyển đổi
 * @return int Trả về mã ASCII của ký tự in thường tương ứng với c, nếu c không phải chữ in hoa thì trả về c
 */
int my_tolower(char c)
{
    int result = c;

    if (c >= 'A' && c <= 'Z')
    {
        result += 32;
    }

    return result;
}

/**
 * @brief Chuyển đổi ký tự in thường thành ký tự in hoa
 * 
 * @param c Ký tự cần chuyển đổi
 * @return int Trả về mã ASCII của ký tự in hoa tương ứng với c, nếu c không phải chữ in thường thì trả về c
 */
int my_toupper(char c)
{
    int result = c;

    if (c >= 'a' && c <= 'z')
    {
        result -= 32;
    }

    return result;
}

/**
 * @brief Kiểm tra xem ký tự có phải là ký tự khoảng trắng không
 * 
 * @param c Ký tự cần kiểm tra
 * @return int Trả về 1 nếu c là ký tự khoảng trắng (dấu cách, tab, xuống dòng, v.v.), ngược lại trả về 0
 */
int my_isspace(char c)
{
    int result = 0;

    if ((c == ' ')|| (c  == '\t') || (c == '\n') || (c == '\r') || (c == '\v') || (c == '\f'))
    {
        result = 1;
    }

    return result;
}

 /* Sử dụng để trả về số lượng ký tự trong xâu, không tính kí tự null ở cuối xâu */
uint32_t my_strlen(char *c)
{
    int index = 0;

    while(c[index] != '\0')
    {
        index++;
    }

    return index;
}

/**
 * @brief So sánh hai chuỗi theo thứ tự từ điển (ASCII)
 * 
 * @param s Con trỏ đến chuỗi thứ nhất
 * @param t Con trỏ đến chuỗi thứ hai
 * @return int Trả về giá trị âm nếu s < t, 0 nếu s == t, giá trị dương nếu s > t
 */
int my_strcmp(char *s, char *t)
{
    int index = 0;

    while (s[index] != '\0' && t[index] != '\0')
    {
        if (s[index] != t[index])
        {
            return s[index] - t[index];
        }
        ++index;
    }

    return s[index] - t[index];
}

/**
 * @brief So sánh tối đa n ký tự đầu tiên của hai chuỗi
 * 
 * @param s Con trỏ đến chuỗi thứ nhất
 * @param t Con trỏ đến chuỗi thứ hai
 * @param n Số lượng ký tự tối đa cần so sánh
 * @return int Trả về giá trị âm nếu s < t, 0 nếu s == t, giá trị dương nếu s > t
 */
int my_strncmp(char *s, char *t , size_t n)
{
    int index = 0;


    while((index < n) && (s[index] != '\0') && (t[index] != '\0'))
    {
        if (s[index] != t[index])
        {
            return s[index] - t[index];
        }
        index++;
    }

    if (index == n)
    {
        return 0;
    }

    return s[index] - t[index];
}

/**
 * @brief So sánh hai chuỗi không phân biệt chữ hoa chữ thường
 * 
 * @param s Con trỏ đến chuỗi thứ nhất
 * @param t Con trỏ đến chuỗi thứ hai
 * @return int Trả về giá trị âm nếu s < t, 0 nếu s == t, giá trị dương nếu s > t (không phân biệt hoa thường)
 */
int my_strcmpi(char *s, char *t)
{
    int index = 0;

    while(s[index] != '\0' && t[index] != '\0')
    {
        char cs = my_tolower(s[index]);
        char ct = my_tolower(t[index]);

        if (cs != ct)
        {
            return cs - ct;
        }
        ++index;
    }

    return my_tolower(s[index]) - my_tolower(t[index]);
}

/**
 * @brief Sao chép chuỗi nguồn vào chuỗi đích
 * 
 * @param dest Con trỏ đến chuỗi đích (nơi lưu kết quả)
 * @param source Con trỏ đến chuỗi nguồn cần sao chép
 * @return char* Con trỏ đến chuỗi đích
 */
char *my_strcpy(char *dest, char *source)
{
    int src_index = 0;

    while(source[src_index] != '\0')
    {
        dest[src_index] = source[src_index];
        src_index++;
    }

    dest[src_index] = '\0';
    return dest;
}

/**
 * @brief Sao chép tối đa n ký tự từ chuỗi nguồn vào chuỗi đích
 * 
 * @param dest Con trỏ đến chuỗi đích (nơi lưu kết quả)
 * @param source Con trỏ đến chuỗi nguồn cần sao chép
 * @param n Số lượng ký tự tối đa cần sao chép
 * @return char* Con trỏ đến chuỗi đích
 */
char *my_strncpy(char *dest, char *source, size_t n)
{
    int src_index = 0;

    while (source[src_index] != '\0' && src_index < n)
    {
        dest[src_index] = source[src_index];
        src_index++;
    }

    while(src_index < n)
    {
        dest[src_index++] = '\0';
    }
    return dest;
}

/**
 * @brief Nối chuỗi nguồn vào cuối chuỗi đích
 * 
 * @param dest Con trỏ đến chuỗi đích
 * @param src Con trỏ đến chuỗi nguồn cần nối
 * @return char* Con trỏ đến chuỗi đích sau khi nối
 */
char* my_strcat(char *dest, char *src)
{
    int dst_index = 0;
    int src_index = 0;

    while(dest[dst_index] != '\0')
    {
        dst_index++;
    }

    while(src[src_index] != '\0')
    {
        dest[dst_index++] = src[src_index++];
    }

    dest[dst_index] = '\0';

    return dest;
}

/**
 * @brief Nối tối đa n ký tự từ chuỗi nguồn vào cuối chuỗi đích
 * 
 * @param dest Con trỏ đến chuỗi đích
 * @param source Con trỏ đến chuỗi nguồn cần nối
 * @param n Số lượng ký tự tối đa cần nối
 * @return char* Con trỏ đến chuỗi đích sau khi nối
 */
char *my_strncat(char *dest, char *source, size_t n)
{
    int dst_index = 0;
    int src_index = 0;

    while(dest[dst_index] != '\0')
    {
        dst_index++;
    }

    while(source[src_index] != '\0' && src_index < n)
    {
        dest[dst_index++] = source[src_index++];
    }

    dest[dst_index] = '\0';

    return dest;
}

/**
 * @brief Tìm kiếm chuỗi con đầu tiên trong chuỗi chính
 * 
 * @param s Con trỏ đến chuỗi chính
 * @param t Con trỏ đến chuỗi con cần tìm
 * @return char* Con trỏ đến vị trí đầu tiên của chuỗi con trong chuỗi chính, hoặc NULL nếu không tìm thấy
 */
char *my_strstr(char *s, char *t)
{
    int len1 = my_strlen(s);
    int len2 = my_strlen(t);
    size_t i;

    for (i = 0; i <= len1 - len2; i++)
    {
        int check = 1;

        if (s[i] == t[0])
        {
            for (int j = 0; j < len2; j++)
            {
                if (s[i + j] != t[j])
                {
                    check = 0;
                    break;
                }
            }
            if (1 == check)
            {
                return &s[i];
            }
        }
    }

    return NULL;
}
```