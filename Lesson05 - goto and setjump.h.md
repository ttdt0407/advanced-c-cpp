# Bài 6: goto - setjump.h

## 6.1. goto

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

