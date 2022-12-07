#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

void getMatrix(char *filename, int *n, int *m, int ***matrix, bool ***checkMatrix) {
    FILE *fptr;
    fptr = fopen(filename, "r");

    //Lấy giá trị cho n, m
    fscanf(fptr, "%d", n);
    fscanf(fptr, "%d", m); 

    //Khai báo 1 mảng động 2 chiều
    int **a = (int **)malloc(*n * sizeof(int *));
    for (int i = 0; i < *n; i++)
        a[i] = (int *)malloc(*m * sizeof(int));

    //Lấy giá trị cho mảng 2 chiều
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            fscanf(fptr, "%d", &a[i][j]);
    
    //Gán cho ma trận a cho matrix
    *matrix = a;

    //Khai báo và tạo giá trị true cho checkMatrix
    bool **b = (bool **)malloc(*n * sizeof(bool *));
    for (int i = 0; i < *n; i++)
        b[i] = (bool *)malloc(*m * sizeof(bool));
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *m; j++)
            if (a[i][j] == 1)
                b[i][j] = true;
            else
                b[i][j] = false;
    *checkMatrix = b;
    
    fclose(fptr);
}

void coutMatrix1(char *filename, char *x, int n, int m, int **matrix) {
    FILE *fptr;
    fptr = fopen(filename, x);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(fptr, "%d ", matrix[i][j]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

void coutMatrix2(char *filename, char *x, int n, int m, int **matrix, bool **checkMatrix) {
    FILE *fptr;
    fptr = fopen(filename, x);
    fprintf(fptr, "\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (checkMatrix[i][j] == false && matrix[i][j] == 1) {
                fprintf(fptr, "%c ", '*');
            } else {
                fprintf(fptr, "0 ");
            }
        }
        fprintf(fptr, "\n");
    }
}

void result(int n, int m, int **matrix, bool **checkMatrix, int x, int y, int a, int b) {
    //Thoát nếu đã tới vị trí (n-1, m-1)
    if (x == n-1 && y == m-1) {
        checkMatrix[x][y] = false;
        coutMatrix2("output.txt", "a", n, m, matrix, checkMatrix);
        return;
    }

    //Đánh dấu vị trí là đã đi qua
    checkMatrix[x][y] = false;
    
    //Đi xuống
    if (x-1>=0)
        if (checkMatrix[x-1][y] && x-1 != a && y != b) 
            result(n, m, matrix, checkMatrix, x-1, y, x, y); 
        
    //Đi sang phải
    if (y+1<m)
        if (checkMatrix[x][y+1] && x != a && y+1 != b) 
            result(n, m, matrix, checkMatrix, x, y+1, x, y);

    //Đi sang trái
    if (y-1>=0)
        if (checkMatrix[x][y-1] && x != a && y-1 != b) 
            result(n, m, matrix, checkMatrix, x, y-1, x, y);

    //Đi lên
    if (x+1<n)
        if (checkMatrix[x+1][y] && x+1 != a && y != b) 
            result(n, m, matrix, checkMatrix, x+1, y, x, y);

    //Trả lại vị trí nếu không có cách đi nào thỏa mãn
    checkMatrix[x][y] = true;
}

int main() {
    //Lấy giá trị
    int n, m;
    int **matrix;
    bool **checkMatrix;
    getMatrix("input.txt", &n, &m, &matrix, &checkMatrix);

    //Xuất ma trận ban đầu
    coutMatrix1("output.txt", "w", n, m, matrix);

    result(n, m, matrix, checkMatrix, 0, 0, -1, -1);
    return 0;
}