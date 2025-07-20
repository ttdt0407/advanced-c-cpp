# Bài 13: Makefile

## 1. Makefile trong C/C++

- Là một tệp văn bản chứa các chỉ thị để xây dựng (build) một dự án lập trình, thường được sử dụng trong các ngôn ngữ lập trình như C/C++.
- Makefile giúp tự động hóa quá trình biên dịch và liên kết các tệp nguồn thành một chương trình thực thi duy nhất.
- Makefile định nghĩa các rules, variables và commands để xây dựng từng phần của dự án, giúp tiết kiệm thời gian và tránh lỗi khi phải thực hiện các lệnh biên dịch bằng tay.
- Makefile sử dụng tool make để đọc và thực thi các quy tắc trong đó. Nó tự động quản lý việc biên dịch, kiểm tra sự thay đổi của file, và chỉ biên dịch lại những phần cần thiết.
- Các cách tạo makefile
+ Makefile
+ makefile

## 2. Nội dung chi tiết của Makefile

__Trong thư mục project, bạn sẽ tạo một tệp có tên Makefile với nội dung như sau:__

```makefile
# Tên của chương trình
TARGET = myprogram

# Thư mục chứa header và source files
HEADER_DIR = Header
SOURCE_DIR = Source

# Các tệp nguồn và tệp object tương ứng
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

# Trình biên dịch và các cờ
CC = g++
CFLAGS = -I$(HEADER_DIR) -Wall -Wextra

# Quy tắc đầu tiên là quy tắc mặc định sẽ được thực thi
all: $(TARGET)

# Quy tắc để tạo ra tệp thực thi
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

# Quy tắc để biên dịch các tệp .cpp thành .o
$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc để làm sạch thư mục build
clean:
	rm -f $(SOURCE_DIR)/*.o $(TARGET)

# Quy tắc giả (phony target)
.PHONY: all clean

```

# 3. Giải thích chi tiết Makefile

## 3.1. Biến TARGET
__Đây là tên file thực thi chương trình bạn muốn tạo ra. Trong ví dụ này, chương trình sẽ có tên là myprogram.__

## 3.2. Biến HEADER_DIR và SOURCE_DIR
- Chỉ định thư mục chứa các tệp header và source.
- HEADER_DIR là thư mục chứa các tệp header (.h).
- SOURCE_DIR là thư mục chứa các tệp nguồn (.c/.cpp).

## 3.3. Biến SOURCES và OBJECTS

- wildcard sẽ tìm tất cả các biến có chưa các tệp có .c trong thư mục Source và lưu trữ chúng trong biến SOURCES.
- $(SOURCES:.c=.o) sẽ thay thế đuôi .c bằng .o trong danh sách SOURCES và lưu trữ chúng trong biến OBJECTS.

## 3.4. Biến CC và CFLAGS
- Chỉ định trình biên dịch (gcc) và các cờ biên dịch.
- -I$(HEADER_DIR) để chỉ định thư mục chứa các tệp header.
- -Wall và -Wextra để bật các cảnh báo bổ sung trong quá trình biên dịch.

## 3.5. Quy tắc all
- Quy tắc mặc định sẽ được thực thi khi bạn chỉ gõ make trong dòng lệnh.
- Quy tắc này xây dựng chương trình từ các tệp object.

## 3.6. Quy tắc $(TARGET)
- Quy tắc này tạo ra tệp thực thi từ các tệp object.
- $@ đại diện cho tên của mục tiêu hiện tại (trong trường hợp này là myprogram).
- $^ đại diện cho danh sách tất cả các dependency (hay là các tệp object).


## 3.7. Quy tắc $(SOURCE_DIR)/ %.o
- Quy tắc này biên dịch từng tệp .c thành .o.
- $(CC) $(CFLAGS) -c -o $@ $< sẽ biên dịch từng tệp trong folder Source thành tệp .o
- $@ đại diện cho tên của tệp đích (tệp .o).
- $< đại diện cho tên của tệp nguồn (tệp .c).

## 3.8 Quy tắc clean
- Quy tắc này xóa các tệp .o và tệp thực thi, làm sạch thư mục build.

## 3.9. Quy tấc .PHONY
- Chỉ định rằng các quy tắc all và clean không phải là tên của tệp, chỉ là cá quy tắc giả