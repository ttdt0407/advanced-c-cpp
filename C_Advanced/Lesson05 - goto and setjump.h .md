# Bài 5: goto - setjump.h

## 5.1. goto

__Là lệnh điều khiển luồng chương trình, cho phép nhảy đến một nhãn (label) bất kỳ trong cùng một hàm__

```c

goto ten_nhan;
...
ten_nhan:
// đoạn mã

```

+ goto giúp bỏ qua hoặc lặp lại một đoạn mã nhất định, thường dùng để thoát khỏi nhiều vòng lặp lồng nhau hoặc xử lý lỗi.
+ Chương trình sau thay thế cho vòng lặp while

```c

int i = 0;
start:

if (i >= 5)
    goto end;

printf("%d\n");
i++;
goto start;

end:
    printf("THE END\n");

```

+ goto không thể nhảy ra ngoài hàm hiện tại.

+ Việc sử dụng goto làm mã nguồn có thể trở nên khó đọc, khó bảo trì, khó debug, dễ gây lỗi.

```c

// chương trình đèn giao thông



#include <stdio.h>


void delay(int second)
{
    int count = 0;
    while(count < 6000000 * second)
    {
        count++;
    }
}


typedef enum 
{
    RED;
    GREEN;
    YELLOW;
} trafficLightState;



int main(int argc, char* argv[])
{

    trafficLightState state = RED;


    while(1)
    {
        switch(state)
        {
            case RED:
                printf("RED\n");
                state = YELLOW;
                delay(50);
                go to skip_sleep;
            case GREEN:
                printf("GREEN\n");
                state = RED;
                delay(50);
                go to skip_sleep;
            case YELLOW:
                printf("YELLOW\n");
                state = GREEN;
                delay(5);
                go to skip_sleep;

            skip_sleep:;
        }

    }
    return 0;
}

```

__Đây là một chương trình mô phỏng LED - 7 đoạn, điều khiển việc hiển thị bằng nút bấm theo quy luật : Bấm số lần lẻ phím bất kỳ hiển thị, bấm số lần chẵn dừng, bấm phím q hoặc Q sẽ kết thúc chương trình__

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <conio.h>
#include <unistd.h>
#include <stdbool.h>



char str1[] = "HI";
char str2[] = "DINH";
char str3[] = "TIEN";



uint8_t letter_h[8][8] = {
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1}
};

 uint8_t letter_i[8][8] = {
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {1,1,1,1,1,1,1,1}
};

 uint8_t letter_d[8][8] = {
    {1,1,1,1,1,1,0,0},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,1,1},
    {1,1,1,1,1,1,0,0}
};

 uint8_t letter_n[8][8] = {
    {1,0,0,0,0,0,0,1},
    {1,1,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,0,1,0,0,0,1},
    {1,0,0,0,1,0,0,1},
    {1,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,1}
};

 uint8_t letter_t[8][8] = {
    {1,1,1,1,1,1,1,1},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,1,0,0,0}
};

 uint8_t letter_e[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1}
};
    
typedef enum {
    FIRST_STRING,
    SECOND_STRING,
    THIRD_STRING
} string;


int count = 0;
bool running = 1;

uint8_t is_button_pressed()
{

    if (kbhit())
    {
        char ch = getch();
        count++;
        if (ch == 'q' || ch == 'Q') 
        running = 0;
        else if (count % 2 == 0)
            return 0;
        else if (count % 2 != 0) return 1;
    }
    return 0;
}

void print_string( const uint8_t matrix[8][8])
{
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            printf(matrix[i][j] ? "*" : " ");
        }
        printf("\n");
    }
    printf("\n");
}

void delay(int time)
{
    sleep(time);
}

int main(int argc , char* argv[])
{

    string type = FIRST_STRING;
    while(running)
    {
        switch(type)
        {
            case FIRST_STRING:
            for (size_t i = 0; i < sizeof(str1) - 1; i++)
            {
                if (str1[i] == 'H')
                {
                    print_string(letter_h);
                }
                else if (str1[i] == 'I')
                    print_string(letter_i);
                
                if (is_button_pressed())
                    while(!is_button_pressed());
                if (is_button_pressed() == 2)
                        goto exit_prog;

                
            }
            printf("\n");
            delay(1);
            goto exit_loop;

            case SECOND_STRING:
                for (size_t i = 0; i <sizeof(str2) - 1; i++)
                {
                    if (str2[i] == 'D')
                        print_string(letter_d);
                    else if (str2[i] == 'I')
                        print_string(letter_i);
                    else if (str2[i] == 'N')
                        print_string(letter_n);
                    else if (str2[i] == 'H')
                        print_string(letter_h);
                    
                    if (is_button_pressed())
                        while(!is_button_pressed());
                    if (is_button_pressed() == 2)
                        goto exit_prog;
                
                }
                printf("\n");
                delay(1);
                goto exit_loop;

            case THIRD_STRING:
                for (size_t i = 0; i <sizeof(str3) - 1; i++)
                {
                    if (str3[i] == 'T')
                        print_string(letter_t);
                    else if (str3[i] == 'I')
                        print_string(letter_i);
                    else if (str3[i] == 'E')
                        print_string(letter_e);
                    else if (str3[i] == 'N')
                        print_string(letter_n);
                    
                    if (is_button_pressed())
                        while(!is_button_pressed());
                    if (is_button_pressed() == 2)
                        goto exit_prog;
                }
                printf("\n");
                delay(1);
                goto exit_loop;
            
        }



        exit_loop:
            if (type == FIRST_STRING) type = SECOND_STRING;
            else if (type == SECOND_STRING) type = THIRD_STRING;
            else if (type == THIRD_STRING) type = FIRST_STRING;

    }


    exit_prog:;
    return 0;
}

```

## 5.2. Thư viện setjmp.h

### 5.2.1. Hàm setjmp và longjmp trong thư viện setjmp.h
__Là một thư viện cung cấp 2 hàm chính là setjmp và longjmp__

+ Đây là một cơ chế nhảy không cục bộ non-local jump, cho phép bạn nhảy từ một hàm về một vị trí trước đó trong call stack, tương tự như goto nhưng xuyên qua được nhiều hàm.
+ Cả hai hàm này đều được sử dụng để thực hiện xử lý ngoại lệ trong C dù không phải là một cách tiêu biểu.
+ 2 hàm như sau:

```c
setjmp(jmp_buf env);
longjmp(jmp_buf env, int value);
```

+ Kiểu dữ liệu jmp_buf lưu trữ trạng thái thực thi của chương trình tại thời điểm mình gọi thằng setjmp ra. Dữ liệu đó chính là thanh ghi PC hoặc một số thanh ghi khác nữa.

__Hàm setjmp(jmp_buf env) có chức năng đánh dấu vị trí có thể quay lại bằng longjmp sau này:__
+ Giá  trị trả về của hàm setjmp(jmp_buf env) là một giá trị số nguyên, bằng 0 ở lần gọi đầu tiên.
+ Trả về một giá trị khác 0 ở lần gọi tiếp theo phụ thuộc vào hàm tham số của hàm longjmp(jmp_buf env, int value).


__Hàm longjmp(jmp_buf env, int value) nhảy về vị trí hiện tại của setjmp và tiếp tục thực thi từ đó__
+ Biến env là biến trong hàm setjmp dùng để đọc dữ liệu vị trí, nhờ đó longjmp quay về được.
+ Tham số value là giá trị tự truyền, nó chính là giá trị mà setjmp trả về từ lần gọi khác lần gọi đầu tiên.
+ Lưu ý biến jmp_buf env cần được khởi tạo global để có thể truy xuất được trong cả setjmp() và longjmp().

```c

#include <stdio.h>
#include <setjmp.h>


jmp_buf env;

int exception = 0;


void func_2()
{
    printf("This is function 2\n");
    longjmp(env,2);
}

void func_3()
{
    printf("This is function 3\n");
    longjmp(env,3);
}

void func_1()
{
    exception = setjmp(env);
    if (exception == 0)
    {
        printf("This is function 1\n");
        printf("exception = %d\n", exception);
        func_2();
    }
    else if(exception == 2)
    {
        printf("exception = %d\n", exception);
        func_3();      
    }
    else if(exception == 3)
    {
        printf("exception = %d\n", exception);
    } 
}

int main(int argc, char *argv[])
{
    func_1();        
    return 0;
}

```

### 5.2.2. Xử lý ngoại lệ (Exception Handling)

__Xử lý ngoại lệ (exception handling) là một cơ chế trong lập trình giúp phát hiện và xử lý các lỗi hoặc tình huống bất thường xảy ra trong quá trình thực thi chương trình, giúp chương trình hoạt động ổn định và không bị dừng đột ngột.__

#### 5.2.2.1. Ngoại lệ là gì

__Ngoại lệ là những lỗi hoặc sự kiện không mong muốn xảy ra trong quá trình thực thi (runtime errors). Ví dụ như:__

+ Chia một số cho 0.
+ Truy cập mảng ngoài phạm vi.
+ Truy xuất con trỏ NULL.
+ Lỗi khi mở hoặc tập tin không tồn tại.
+ Lỗi cấp phát bộ nhớ.

#### 5.2.2.2. Cơ chế xử lý ngoại lệ

__Cơ chế xử lý ngoại lệ giúp chương trình phản ứng kịp thời với các lỗi mà không làm gián đoạn toàn bộ chương trình, không làm chương trình bị crash__

__Hầu hết các ngôn ngữ lập trình bậc cao như: C++, java, python,... đều hỗ trợ xử lý ngoại lệ thông qua từ khoá chính như:__

+ try: định nghĩa một khối lệnh có thể phát sinh ra lỗi.
+ catch: xử lý ngoại lệ nếu có lỗi xảy ra.
+ throw: ném ra một ngoại lệ khi xảy ra lỗi.

```c
    try
    {
        // khối lệnh có thể phát sinh lỗi
    }
    catch (loai_ngoai_le_1)
    {
        // Xử lý ngoại lệ loại 1
    }
    catch(loai_ngoai_le_2)
    {
        // Xử lý ngoại lệ loại 2
    }

```

```c
#include <stdio.h>
#include <setjmp.h>

#define TRY if((exception = setjmp(env)) == 0) 
#define CATCH(x) else if (exception == x)
#define THROW(x) longjmp(env,x)

typedef enum
{
    NO_ERROR,
    NO_EXIST,
    DEVIDE_BY_ZERO,
} error_codes;

jmp_buf env;
int exception = 0;


double divide(int a, int b)
{

    if (a == 0 && b == 0)
        THROW(NO_EXIST);
    else if (b == 0)
        THROW(DIVIDE_BY_ZERO);
    
    return (double) a / b;
}

int main(int argc, char *argv[])
{
    exception = NO_ERROR;
    
    TRY
        printf("Ket qua: %.2lf\n", divide(2,2));
    CATCH(NO_EXIST)
        printf("Khong hop le\n");
    CATCH(DIVIDE_BY_ZERO)
        printf("Khong chia duoc cho 0\n");


    return 0;
}
```

__Bản chất của TRY-CATCH_THROW là sử dụng cho mục đích debug.__
+ Chương trình vẫn sẽ tiếp tục dù có lỗi hay không, khác với assert sẽ gây dừng hẳn chương trình.
+ Tách biệt logic gỡ lỗi và logic của chương trình chính.