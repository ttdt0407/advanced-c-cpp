# Bài 3: Bitmask 
__Là một kỹ thuật sử dụng các bit để lưu trữ và thao tác với các cờ (flags) hoặc trạng thái. Có thể sử dụng bitmask để đặt, xoá, và kiểm tra trạng thái của các bit cụ thể trong một từ__
+ Dùng để tối ưu hoá bộ nhớ
+ Thực hiện các phép toán logic trên một cụm bit
+ Quản lý các trạng thái, quyền truy cập hoặc các thuộc tính

<p align = "center">
<img src = "https://forum-kobotoolbox-org.s3.dualstack.us-east-1.amazonaws.com/original/2X/4/4b86614216a50a78b4dff109184c99f671972c90.png" width = "500" height = "350">


Có nhiều kiểu dữ liệu giúp tối ưu bộ nhớ và linh hoạt khi chuyển đổi giữa các hệ thống như:
int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,...

## 3.1 Phép dịch bit trái và dịch bit phải

+ Phép dịch trái
``` bash

int x = 4; // 0b00000100;
x = x << 2;  // 0b00010000;
```

+ Phép dịch phải
``` bash

int x = 3; // 0b00000011;
x = x >> 2; // 0b00000000;
```
# 3.1 Bật bit sử dụng phép OR

``` bash
#include <stdio.h>
#include <stdint.h>


#define FEATURE1 1 << 0
#define FEATURE2 1 << 1
#define FEATURE3 1 << 2
#define FEATURE4 1 << 3
#define FEATURE5 1 << 4
#define FEATURE6 1 << 5
#define FEATURE7 1 << 6
#define FEATURE8 1 << 7

uint8_t user1;


void enableFeature(uint8_t *options, uint8_t feature)
{
    *options |= feature;   // sử dụng con trỏ để giải tham chiếu, thay đổi các bit của biến
}

```

# 3.2 Tắt bit sử dụng phép AND và NOR
``` bash

void disableFeature(uint8_t *options, uint8_t feature)
{
    *options &= ~feature;   // sử dụng con trỏ để giải tham chiếu, thay đổi các bit của biến
}

```

# 3.3 Đọc bit đang bật hay tắt

``` bash

int8_t isFeatureDisabled(uint8_t options, uint8_t feature)
{
    return ((options & feature) != 0) ? 1 : 0;  // kiểm tra xem bit thứ n đang bật hay tắt

}

```

__Chương trình sử dụng đầy đủ 3 tính năng trên__
```bash

#include <stdio.h>
#include <stdint.h>


#define FEATURE1 1 << 0
#define FEATURE2 1 << 1
#define FEATURE3 1 << 2
#define FEATURE4 1 << 3
#define FEATURE5 1 << 4
#define FEATURE6 1 << 5
#define FEATURE7 1 << 6
#define FEATURE8 1 << 7

uint8_t user1;


void enableFeature(uint8_t *options, uint8_t feature)
{
    *options |= feature;
}

void disableFeature(uint8_t *options, uint8_t feature)
{
    *options &= ~feature;
}

uint8_t isFeatureDisabled(uint8_t options, uint8_t feature)
{
    return (options & feature) != 0;
}

void listSelectedFeatures(uint8_t options)
{
    const char *featureName[] = {
        "FEATURE1", "FEATURE2", "FEATURE3", "FEATURE4", "FEATURE5", "FEATURE6", "FEATURE7", "FEATURE8"};

    for (int i = 0; i < sizeof(featureName) / sizeof(const char *); i++)
    {
        if ((options >> i) & 1)
            printf("%s\n", featureName[i]);
    }
}


int main(int argc, const char *argv[])
{
    uint8_t options = 0;

    enableFeature(&options, FEATURE1 | FEATURE3 | FEATURE5); // có thể bật nhiều tính năng bằng toán tử '|'

    disableFeature(&options, FEATURE1);

    listSelectedFeatures(options);  // liệt kê các tính năng đang bật
    return 0;
}

```

