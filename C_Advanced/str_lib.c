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

/**********************************************************************
 * Function with strings in C
 *********************************************************************/

/**
 * @brief Tính độ dài của chuỗi
 * 
 * @param c Con trỏ đến chuỗi cần tính độ dài
 * @return uint32_t Số lượng ký tự trong chuỗi, không tính ký tự null (\0) ở cuối chuỗi
 */
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