#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void result(int time1, int time2, char text1[], char text2[], char text3[], int total_error)
{
    int time_tmp;
    float typing_speed;
    time_tmp = time2 - time1; // 연산자 '-' 추가
    printf("total time: %d sec\n", time_tmp);
    typing_speed = (((strlen(text1) + strlen(text2) + strlen(text3)) - total_error) / (float)time_tmp) * 60; // 연산자 '-'와 형 변환 추가
    printf("분당 타수: %.2f 타\n", typing_speed); // %.2f로 포맷 수정
}

int main()
{
    int first_word_descriptor, second_word_descriptor, third_word_descriptor;
    int first_word_read, first_word_count = 0, first_word_error = 0;
    int second_word_read, second_word_count = 0, second_word_error = 0;
    int third_word_read, third_word_count = 0, third_word_error = 0;
    int total_error = 0; // 변수명 오타 수정
    char first_word, first_word_text[] = "System Programming";
    char second_word, second_word_text[] = "typing test program";
    char third_word, third_word_text[] = "league of legends";
    struct termios init_attr, new_attr;
    time_t time1, time2;

    first_word_descriptor = open(ttyname(fileno(stdin)), O_RDWR);
    tcgetattr(first_word_descriptor, &init_attr);
    new_attr = init_attr; // '=' 추가
    new_attr.c_lflag &= ~ICANON; // '~' 추가
    new_attr.c_lflag &= ~ECHO;   // '~' 추가
    new_attr.c_cc[VMIN] = 1;
    new_attr.c_cc[VTIME] = 0;
    if (tcsetattr(first_word_descriptor, TCSANOW, &new_attr) != 0) { // 조건 수정 및 블록 닫힘 수정
        fprintf(stderr, "터미널 속성을 실행할 수 없음.\n");
        return 1;
    }

    printf("타자 검정 프로그램 입니다.\n\n");
    time(&time1);
    printf("다음 문장을 그대로 입력하세요.\n\n%s\n", first_word_text);

    while ((first_word_read = read(first_word_descriptor, &first_word, 1)) > 0 && first_word != '\n') { // 반복문 조건 수정
        if (first_word == first_word_text[first_word_count++]) {
            write(first_word_descriptor, &first_word, 1);
        } else {
            write(first_word_descriptor, "*", 1);
            first_word_error++; // 변수명 수정
        }
    }
    tcsetattr(first_word_descriptor, TCSANOW, &init_attr);
    close(first_word_descriptor);

    second_word_descriptor = open(ttyname(fileno(stdin)), O_RDWR);
    tcgetattr(second_word_descriptor, &init_attr);
    new_attr = init_attr;
    new_attr.c_lflag &= ~ICANON;
    new_attr.c_lflag &= ~ECHO;
    new_attr.c_cc[VMIN] = 1;
    new_attr.c_cc[VTIME] = 0;
    if (tcsetattr(second_word_descriptor, TCSANOW, &new_attr) != 0) {
        fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
        return 1;
    }

    printf("\n\n%s\n", second_word_text);

    while ((second_word_read = read(second_word_descriptor, &second_word, 1)) > 0 && second_word != '\n') {
        if (second_word == second_word_text[second_word_count++]) {
            write(second_word_descriptor, &second_word, 1);
        } else {
            write(second_word_descriptor, "*", 1);
            second_word_error++;
        }
    }
    tcsetattr(second_word_descriptor, TCSANOW, &init_attr);
    close(second_word_descriptor);

    third_word_descriptor = open(ttyname(fileno(stdin)), O_RDWR);
    tcgetattr(third_word_descriptor, &init_attr);
    new_attr = init_attr;
    new_attr.c_lflag &= ~ICANON;
    new_attr.c_lflag &= ~ECHO;
    new_attr.c_cc[VMIN] = 1;
    new_attr.c_cc[VTIME] = 0;
    if (tcsetattr(third_word_descriptor, TCSANOW, &new_attr) != 0) {
        fprintf(stderr, "터미널 속성을 설정할 수 없음.\n");
        return 1;
    }

    printf("\n\n%s\n", third_word_text);

    while ((third_word_read = read(third_word_descriptor, &third_word, 1)) > 0 && third_word != '\n') {
        if (third_word == third_word_text[third_word_count++]) {
            write(third_word_descriptor, &third_word, 1);
        } else {
            write(third_word_descriptor, "*", 1);
            third_word_error++;
        }
    }
    tcsetattr(third_word_descriptor, TCSANOW, &init_attr);
    close(third_word_descriptor);

    total_error = first_word_error + second_word_error + third_word_error; // 변수명 수정
    printf("\n\n타이핑 오류 횟수는 %d\n", total_error);
    time(&time2);
    result(time1, time2, first_word_text, second_word_text, third_word_text, total_error);

    return 0;
}
