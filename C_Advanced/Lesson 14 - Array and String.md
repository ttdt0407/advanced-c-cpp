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

```