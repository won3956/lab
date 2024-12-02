#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    int student_count;
    cout << "학생 수를 입력하세요: ";
    cin >> student_count;
    cin.ignore(); // 버퍼 비우기

    map<string, pair<float, float>> students;

    for (int i = 0; i < student_count; i++) {
        string name;
        float midterm_score, final_score;

        cout << "학생 이름을 입력하세요: ";
        getline(cin, name);

        cout << "중간 점수를 입력하세요: ";
        cin >> midterm_score;
        cin.ignore(); // 버퍼 비우기

        cout << "기말 점수를 입력하세요: ";
        cin >> final_score;
        cin.ignore(); // 버퍼 비우기

        students[name] = make_pair(midterm_score, final_score);
    }

    cout << "\n학생 정보:\n";
    for (const auto& student : students) {
        cout << "이름: " << student.first
             << ", 중간 점수: " << student.second.first
             << ", 기말 점수: " << student.second.second << endl;
    }

    return 0;
}
