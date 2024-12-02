#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 정보를 담을 구조체 정의
struct Student {
    char name[50];
    float midterm_score;
    float final_score;
    struct Student* left;
    struct Student* right;
};

// 새로운 학생 노드를 생성하는 함수
struct Student* createStudent(char* name, float midterm_score, float final_score) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->midterm_score = midterm_score;
    newStudent->final_score = final_score;
    newStudent->left = NULL;
    newStudent->right = NULL;
    return newStudent;
}

// 학생을 트리에 삽입하는 함수
struct Student* insertStudent(struct Student* root, struct Student* student) {
    if (root == NULL) {
        return student;
    }
    if (strcmp(student->name, root->name) < 0) {
        root->left = insertStudent(root->left, student);
    } else {
        root->right = insertStudent(root->right, student);
    }
    return root;
}

// 중위 순회를 사용하여 학생 정보를 출력하는 함수
void inorderTraversal(struct Student* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("이름: %s, 중간 점수: %.2f, 기말 점수: %.2f\n", root->name, root->midterm_score, root->final_score);
        inorderTraversal(root->right);
    }
}

int main() {
    int student_count;
    printf("학생 수를 입력하세요: ");
    scanf("%d", &student_count);
    getchar(); // 버퍼 비우기

    struct Student* root = NULL;

    for (int i = 0; i < student_count; i++) {
        char name[50];
        float midterm_score, final_score;

        printf("학생 이름을 입력하세요: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // 개행문자 제거

        printf("중간 점수를 입력하세요: ");
        scanf("%f", &midterm_score);
        getchar(); // 버퍼 비우기

        printf("기말 점수를 입력하세요: ");
        scanf("%f", &final_score);
        getchar(); // 버퍼 비우기

        struct Student* student = createStudent(name, midterm_score, final_score);
        root = insertStudent(root, student);
    }

    printf("\n학생 정보:\n");
    inorderTraversal(root);

    // 메모리 해제
    // 이 단계에서는 노드를 해제하지 않았습니다. 실제 프로덕션 코드에서는 메모리 누수를 방지하기 위해 모든 노드를 해제해야 합니다.
    return 0;
}
