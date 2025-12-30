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




