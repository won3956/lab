use std::io::{self, Write};

// 행렬의 크기를 입력받아서 행렬을 저장하는 함수
fn input_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut matrix = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            let mut input = String::new();
            print!("행렬의 {}행 {}열 원소 입력: ", i + 1, j + 1);
            io::stdout().flush().unwrap();
            io::stdin().read_line(&mut input).unwrap();
            let element: i32 = input.trim().parse().unwrap();
            matrix[i][j] = element;
        }
    }
    matrix
}

// 두 행렬을 더하는 함수
fn add_matrices(matrix1: &Vec<Vec<i32>>, matrix2: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let rows = matrix1.len();
    let cols = matrix1[0].len();
    let mut result = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    result
}

// 행렬을 출력하는 함수
fn print_matrix(matrix: &Vec<Vec<i32>>) {
    let rows = matrix.len();
    let cols = matrix[0].len();
    for i in 0..rows {
        for j in 0..cols {
            print!("{} ", matrix[i][j]);
        }
        println!();
    }
}

fn main() {
    // 행렬의 크기 입력 받기
    let mut input = String::new();
    print!("행렬의 행 수를 입력하세요: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut input).unwrap();
    let rows: usize = input.trim().parse().unwrap();

    input.clear();
    print!("행렬의 열 수를 입력하세요: ");
    io::stdout().flush().unwrap();
    io::stdin().read_line(&mut input).unwrap();
    let cols: usize = input.trim().parse().unwrap();

    // 행렬 입력
    let matrix1 = input_matrix(rows, cols);
    let matrix2 = input_matrix(rows, cols);

    // 두 행렬 더하기
    let result_matrix = add_matrices(&matrix1, &matrix2);

    // 결과 출력
    println!("덧셈 결과:");
    print_matrix(&result_matrix);
}
