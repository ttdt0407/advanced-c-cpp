#include <stdint.h>
#include <stdio.h>

/**********************************************************************
 * Check type of character
 *********************************************************************/

 /* Trả về 1 nếu kí tự c là chữ số hoặc chữ cái, ngược lại trả về 0 */
int my_isalnum(char c)
{
    int result = 0;

    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        result = 1;
    }

    return result;
}

/* Trả về 1 nếu kí tự c là chữ số, ngược lại trả về 0 */
int my_isdigit(char c)
{
    int result = 0;

    if (c >= '0' && c <= '9')
    {
        result = 1;
    }
    return result;
}

/* Trả về 1 nếu kí tự c là chữ cái in thường, ngược lại trả về 0 */
int my_islower(char c)
{
    int result = 0;

    if (c >= 'a' && c <= 'z')
    {
        result = 1;
    }

    return result;
}

/* Trả về 1 nếu kí tự c là chữ cái in hoa, ngược lại trả về 0 */
int my_isupper(char c)
{
    int result = 0;

    if (c >= 'A' && c <= 'Z')
    {
        result = 1;
    }

    return result;
}

/* Trả về 1 nếu kí tự c là chữ cái, ngược lại trả về 0 */
int my_isalpha(char c)
{
    int result = 0;

    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        result = 1;
    }

    return result;
}

/* Trả về mã ASCII của kí tự in thường tương ứng với kí tự c */
int my_tolower(char c)
{
    int result = c;

    if (c >= 'A' && c <= 'Z')
    {
        result += 32;
    }

    return result;
}

/* Trả về mã ascii của kí tự in hoa tương ứng với kí tự c */
int my_toupper(char c)
{
    int result = c;

    if (c >= 'a' && c <= 'z')
    {
        result -= 32;
    }

    return result;
}

/* Trả về 1 nếu kí tự c là dấu cách, ngược lại trả về 0 */
int my_isspace(char c)
{
    int result = 0;

    if ((c == ' ')|| (c  == '\t') || (c == '\n') || (c == '\r') || (c == '\v') || (c == '\f'))
    {
        result = 1;
    }

    return result;
}

/**********************************************************************
 * Function with strings in C
 *********************************************************************/


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

/* So sánh 2 xâu theo thứ tự ASCII */
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