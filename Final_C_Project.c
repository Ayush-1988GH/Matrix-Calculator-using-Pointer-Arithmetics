#include <stdio.h>
#include <stdlib.h>

/* TEAM MEMBERS
125EC0012 AYUSH PATEL
125ME0010 SAKSHAM SINGH
125AD0006 SIDDHESH GAHUKAR
125ME0009 PRAVEEN KUMAR
*/

void matrixInput(int *ptr,int m){
    for(int i=0 ;i < m*m ;i++){
        scanf("%d",(ptr + i));
    }
}

int count(int num) {
    int count = 0;
    if (num == 0) return 1;   // 0 has 1 digit
    if (num < 0) {            // to include '-' sign
        count++;              // incrementing count by 1
        num = -num;
    }

    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

void matrixPrint(int *ptr, int m) {

    // Find maximum width
    int maxWidth = 0;
    for (int i = 0; i < m*m; i++) {
        int width = count(*(ptr + i));
        if (width > maxWidth){
            maxWidth = width;
        }
    }

    // Print with alignment
    for (int i = 0; i < m*m; i++){
        printf("%*d ", maxWidth, *(ptr + i));
        if (i%m == m-1){      // to print from next line , use newline before printing the mth element
            printf("\n");
        }
    }
    printf("\n");
}



int matrixAdd(int *ptr1,int *ptr2,int m){
    int mat[m][m];
    int *ptr = &mat[0][0];
    for(int i=0; i< m*m ; i++){
        *(ptr + i)=*(ptr1 + i) + *(ptr2 +i);
    }
    printf("Sum of Matrix :\n");
    matrixPrint(ptr,m);
}

int matrixSub(int *ptr1,int *ptr2,int m){
    int mat[m][m];
    int *ptr = &mat[0][0];
    for(int i=0; i< m*m ; i++){
        *(ptr + i)=*(ptr1 + i) - *(ptr2 +i);
    }
    printf("Difference of Matrix :\n");
    matrixPrint(ptr,m);
}

int matrixPro(int *ptr1,int *ptr2,int m){
    int mat[m][m];
    int *ptr = &mat[0][0];
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            *(ptr + i*m + j)=0;
            for (int k = 0; k < m; k++){
                *(ptr + i*m + j) += ( *(ptr1 + i*m + k)) * (*(ptr2 + k*m + j));
            }
        }
    }
    printf("Product of Matrix :\n");
    matrixPrint(ptr,m);
}

int matrixTrace(int *ptr,int m){
    int trace=0;
    for (int i=0; i<m*m ;i=i+m+1){
        trace += *(ptr+i);
    }
    return trace;
}

int matrixTranspose(int *ptr1,int m){
    int mat[m][m];
    int *ptr= &mat[0][0];
    for(int i=0; i<m ;i++){
        for(int j=0; j<m ;j++){
            *(ptr + i*m +j) = *(ptr1 + j*m +i);
        }
    }
    printf("Transpose of Matrix :\n");
    matrixPrint(ptr,m);
}


int matrixDet(int m, int mat[m][m]) {
    int det = 0;

    if (m == 1){
        return mat[0][0];
    }

    if (m == 2){
        return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    }
    
    int temp[m-1][m-1];
    int sign = 1;
    for (int col=0; col<m ; col++){
        int xi = 0, xj = 0;
        for (int i=1; i<m ; i++){
            xj = 0;
            for (int j=0; j<m; j++){
                if (j == col) continue;
                temp[xi][xj] = mat[i][j];
                xj++;
            }
            xi++;
        }

        det += sign * mat[0][col] * matrixDet(m - 1, temp);
        sign = -sign;
    }

    return det;
}


void copyPtrTo2D(int *ptr, int n, int out[n][n]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            out[i][j] = *(ptr + i*n + j);
}

void getMinor(int n, int mat[n][n], int minor[n-1][n-1], int row, int col) {
    int r = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (i == row) continue;
        c = 0;
        for (int j = 0; j < n; j++) {
            if (j == col) continue;
            minor[r][c++] = mat[i][j];
        }
        r++;
    }
}

/* Cofactor matrix */
void matrixCofactor(int n, int mat[n][n], int co[n][n]) {
    int minor[n-1][n-1];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            getMinor(n, mat, minor, i, j);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            co[i][j] = sign * matrixDet(n-1, minor);
        }
    }
}

/* Adjoint Matrix (= transpose of cofactor matrix) */
void matrixAdjoint(int n, int mat[n][n], int adj[n][n]) {
    int co[n][n];
    matrixCofactor(n, mat, co);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            adj[j][i] = co[i][j];
        }
    }
}

/* Inverse Matrix */
void printInverse(int n, int mat[n][n]) {
    float det = matrixDet(n, mat);
    if (det == 0) {
        printf("Matrix is singular , determinant = 0 : Inverse does not exist...\n\n");
        return;
    }
    int adj[n][n];
    matrixAdjoint(n, mat, adj);
    printf("Inverse of Matrix :\n");
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("%.2f ", (float)adj[i][j] / det);
        }
        printf("\n");
    }
    printf("\n");
}


/* MATRIX TYPE CHECKER */

/* Check null matrix (all zeros) */
int isNullMatrix(int n, int mat[n][n]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (mat[i][j] != 0) return 0;
    return 1;
}

/* Check identity matrix */
int isIdentity(int n, int mat[n][n]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++) {
            if (i == j && mat[i][j] != 1) return 0;
            if (i != j && mat[i][j] != 0) return 0;
        }
    return 1;
}

/* Check diagonal (non-zero allowed only on diagonal) */
int isDiagonal(int n, int mat[n][n]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (i != j && mat[i][j] != 0) return 0;
    return 1;
}

/* Symmetric: A = A^T */
int isSymmetric(int n, int mat[n][n]) {
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (mat[i][j] != mat[j][i]) return 0;
    return 1;
}

/* Skew-symmetric: A^T = -A (diagonal must be zero) */
int isSkewSymmetric(int n, int mat[n][n]) {
    for (int i=0;i<n;i++)
        if (mat[i][i] != 0) return 0;
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (mat[i][j] != -mat[j][i]) return 0;
    return 1;
}

void identifyMatrixTypes(int n, int mat[n][n]) {
    printf("\nMatrix Type Classification:\n");
    if (isNullMatrix(n, mat))    printf("Null matrix\n");
    if (isIdentity(n, mat))      printf("Identity matrix\n");
    if (isDiagonal(n, mat))      printf("Diagonal matrix\n");
    if (isSymmetric(n, mat))     printf("Symmetric matrix\n");
    if (isSkewSymmetric(n, mat)) printf("Skew-symmetric matrix\n");
    if (!(isNullMatrix(n, mat) || isIdentity(n, mat) || isDiagonal(n, mat) || isSymmetric(n, mat) || isSkewSymmetric(n, mat))) printf("Normal Matrix\n");
    printf("\n");
}

/* MENU - UI */

void printMenu() {
    printf("\n");
    printf("+------------------------------------------------+\n");
    printf("|                MATRIX  TOOLKIT                 |\n");
    printf("+------------------------------------------------+\n");
    printf("| 1.  Input Matrix 1                             |\n");
    printf("| 2.  Input Matrix 2                             |\n");
    printf("| 3.  Input Matrix 3                             |\n");
    printf("| 4.  Print Matrix                               |\n");
    printf("| 5.  Matrix Addition                            |\n");
    printf("| 6.  Matrix Subtraction                         |\n");
    printf("| 7.  Matrix Multiplication                      |\n");
    printf("| 8.  Determinant                                |\n");
    printf("| 9.  Transpose                                  |\n");
    printf("| 10. Adjoint                                    |\n");
    printf("| 11. Inverse                                    |\n");
    printf("| 12. Identify Matrix                            |\n");
    printf("| 13. Trace                                      |\n");
    printf("+------------------------------------------------+\n");
    printf("| 0.  Exit Program                               |\n");
    printf("+------------------------------------------------+\n");
    printf("\n");
    printf("Enter your choice : ");
}

/* Helper to ask user which matrix (1..3). Returns chosen matrix index or -1 */
int chooseMatrixPrompt() {
    int id;
    printf("Choose matrix (1, 2 or 3): ");
    scanf("%d", &id);
    if (id < 1 || id > 3) {
        printf("Invalid selection. Please choose 1, 2 or 3.\n");
        return -1;
    }
    return id;
}

/* # MAIN */
int main() {
    int n;
    for(int i=0;i<60;i++) printf(" ");
    printf(" || MATRIX CALCULATOR || ");
    printf("\nWelcome to Matrix Calculator :) \n\n"); 
    printf("Enter order of square matrices (n): ");
    if (scanf("%d", &n) != 1 || n <= 0 ) {
        printf("Invalid matrix size...\n");
        return 0;
    }
    if(n>10) {
        printf("Too large Matrix Size !");
        return 0;
    } 
    /* allocate three matrices of the same size */
    int mat1[n][n], mat2[n][n], mat3[n][n];
    int *ptr1 = &mat1[0][0];
    int *ptr2 = &mat2[0][0];
    int *ptr3 = &mat3[0][0];

    /* keep track which matrices have been filled by user */
    int filled1 = 0, filled2 = 0, filled3 = 0;

    int choice;
    while (1) {
        printMenu();

        if (scanf("%d", &choice) != 1) {
            /* clear bad input and continue */
            while (getchar() != '\n');
            printf("Invalid input. Try again.\n");
            continue;
        }
        if (choice == 0) {
            printf("Exiting Matrix Calculator !! Goodbye :) \n");
            break;
        }

        switch (choice) {

            case 1:
                printf("Enter elements of Matrix 1 (%d numbers):\n", n*n);
                matrixInput(ptr1, n);
                filled1 = 1;
                printf("Matrix 1 recorded.\n");
                break;

            case 2:
                printf("Enter elements of Matrix 2 (%d numbers):\n", n*n);
                matrixInput(ptr2, n);
                filled2 = 1;
                printf("Matrix 2 recorded.\n");
                break;

            case 3:
                printf("Enter elements of Matrix 3 (%d numbers):\n", n*n);
                matrixInput(ptr3, n);
                filled3 = 1;
                printf("Matrix 3 recorded.\n");
                break;

            case 4: { /* Print matrix - ask which one to print */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if (id == 1 && !filled1) { printf("Matrix 1 not entered yet.\n"); break; }
                if (id == 2 && !filled2) { printf("Matrix 2 not entered yet.\n"); break; }
                if (id == 3 && !filled3) { printf("Matrix 3 not entered yet.\n"); break; }

                printf("Matrix %d:\n", id);
                if (id == 1) matrixPrint(ptr1, n);
                if (id == 2) matrixPrint(ptr2, n);
                if (id == 3) matrixPrint(ptr3, n);
                break;
            }

            case 5: /* Addition */
                if (filled1 + filled2 + filled3 < 2) {
                    printf("Error: At least two matrices must be entered to perform addition.\n");
                    break;
                }
                /* ask which two to add (simple approach: ask indices) */
                {
                    int a, b;
                    printf("Add which matrices? Enter 2 matrices (m1 + m2): ");
                    scanf("%d %d", &a, &b);
                    if (a<1||a>3||b<1||b>3) { printf("Invalid matrix indices.\n"); break; }
                    int *A = (a==1?ptr1: (a==2?ptr2:ptr3));
                    int *B = (b==1?ptr1: (b==2?ptr2:ptr3));
                    int filledA = (a==1?filled1:(a==2?filled2:filled3));
                    int filledB = (b==1?filled1:(b==2?filled2:filled3));
                    if (!filledA || !filledB) { printf("Error: One or both selected matrices are not entered yet.\n"); break; }
                    matrixAdd(A, B, n);
                }
                break;

            case 6: /* Subtraction */
                if (filled1 + filled2 + filled3 < 2) {
                    printf("Error: At least two matrices must be entered to perform subtraction.\n");
                    break;
                }
                {
                    int a, b;
                    printf("Subtract which matrices? Enter 2 matrices (m1 - m2): ");
                    scanf("%d %d", &a, &b);
                    if (a<1||a>3||b<1||b>3) { printf("Invalid matrix indices.\n"); break; }
                    int *A = (a==1?ptr1: (a==2?ptr2:ptr3));
                    int *B = (b==1?ptr1: (b==2?ptr2:ptr3));
                    int filledA = (a==1?filled1:(a==2?filled2:filled3));
                    int filledB = (b==1?filled1:(b==2?filled2:filled3));
                    if (!filledA || !filledB) { printf("Error: One or both selected matrices are not entered yet.\n"); break; }
                    matrixSub(A, B, n);
                }
                break;

            case 7: /* Multiplication */
                if (filled1 + filled2 + filled3 < 2) {
                    printf("Error: At least two matrices must be entered to perform multiplication.\n");
                    break;
                }
                {
                    int a,b;
                    printf("Multiply which matrices? Enter 2 matrices (m1 * m2): ");
                    scanf("%d %d", &a, &b);
                    if (a<1||a>3||b<1||b>3) { printf("Invalid matrix indices.\n"); break; }
                    int *A = ( a==1 ? ptr1: (a==2 ? ptr2 : ptr3));
                    int *B = ( b==1 ? ptr1: (b==2 ? ptr2 : ptr3));
                    int filledA = (a==1 ? filled1 : (a==2 ? filled2 : filled3));
                    int filledB = (b==1 ? filled1 : (b==2 ? filled2 : filled3));
                    if (!filledA || !filledB) { printf("Error: One or both selected matrices are not entered yet.\n"); break; }
                    matrixPro(A, B, n);
                }
                break;

            case 8: { /* Determinant */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                if (id == 1) {
                    int det = matrixDet(n, mat1);
                    printf("Determinant of Matrix 1 = %d\n", det);
                } else if (id == 2) {
                    int det = matrixDet(n, mat2);
                    printf("Determinant of Matrix 2 = %d\n", det);
                } else {
                    int det = matrixDet(n, mat3);
                    printf("Determinant of Matrix 3 = %d\n", det);
                }
                break;
            }

            case 9: { /* Transpose */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                if (id == 1) matrixTranspose(ptr1, n);
                else if (id == 2) matrixTranspose(ptr2, n);
                else matrixTranspose(ptr3, n);
                break;
            }

            case 10: { /* Adjoint */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                /* copy selected matrix into 2D int array and compute adjoint */
                int src[n][n], adj[n][n];
                if (id==1) copyPtrTo2D(ptr1, n, src);
                else if (id==2) copyPtrTo2D(ptr2, n, src);
                else copyPtrTo2D(ptr3, n, src);

                matrixAdjoint(n, src, adj);
                printf("Adjoint Matrix:\n");
                matrixPrint(&adj[0][0], n);
                break;
            }

            case 11: { /* Inverse */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                int src[n][n];
                if (id==1) copyPtrTo2D(ptr1, n, src);
                else if (id==2) copyPtrTo2D(ptr2, n, src);
                else copyPtrTo2D(ptr3, n, src);

                printInverse(n, src);
                break;
            }

            case 12: { /* Identify matrix types */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                int src[n][n];
                if (id==1) copyPtrTo2D(ptr1, n, src);
                else if (id==2) copyPtrTo2D(ptr2, n, src);
                else copyPtrTo2D(ptr3, n, src);

                identifyMatrixTypes(n, src);
                break;
            }

            case 13: { /* Trace */
                int id = chooseMatrixPrompt();
                if (id == -1) break;
                if ((id==1 && !filled1) || (id==2 && !filled2) || (id==3 && !filled3)) {
                    printf("Selected matrix not yet entered.\n"); break;
                }
                int tr;
                if (id==1) tr = matrixTrace(ptr1, n);
                else if (id==2) tr = matrixTrace(ptr2, n);
                else tr = matrixTrace(ptr3, n);
                printf("Trace = %d\n", tr);
                break;
            }

            default:
                printf("Invalid choice. Please pick a valid menu number.\n");
                break;
        }
    }

    return 0;
}
