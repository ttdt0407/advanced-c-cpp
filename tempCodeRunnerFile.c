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