// Xiaohan Qin
// 521021910604


/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    // version 1:287 misses
    // if (M == 32)
    // {
    //     int i, j, k, l, tmp;
    //     for (i = 0; i < N; i += 8)
    //     {
    //         for (j = 0; j < M; j += 8)
    //         {
    //             for (k = i; k < i + 8; k++)
    //             {
    //                 for (l = j; l < j + 8; l++)
    //                 {
    //                     if (k != l)
    //                     {
    //                         B[l][k] = A[k][l];
    //                     }
    //                     else
    //                     {
    //                         tmp = A[k][l];
    //                     }
    //                 }
    //                 if (i == j)
    //                 {
    //                     B[k][k] = tmp;
    //                 }
    //             }
    //         }
    //     }
    // }

    if (M == 32)
    {
        int i, j, k, l, v1, v2, v3, v4, v5, v6, v7, v8;
        for (i = 0; i < N; i += 8)
        {
            for (j = 0; j < M; j += 8)
            {
                if (i == j)
                {
                    k = i;
                    v1 = A[k][j];v2 = A[k][j + 1];
                    v3 = A[k][j + 2];
                    v4 = A[k][j + 3];
                    v5 = A[k][j + 4];
                    v6 = A[k][j + 5];
                    v7 = A[k][j + 6];
                    v8 = A[k][j + 7];
                    B[k][j] = v1;
                    B[k][j + 1] = v2;
                    B[k][j + 2] = v3;
                    B[k][j + 3] = v4;
                    B[k][j + 4] = v5;
                    B[k][j + 5] = v6;
                    B[k][j + 6] = v7;
                    B[k][j + 7] = v8;

                    v1 = A[k+1][j];
                    v2 = A[k+1][j + 1];
                    v3 = A[k+1][j + 2];
                    v4 = A[k+1][j + 3];
                    v5 = A[k+1][j + 4];
                    v6 = A[k+1][j + 5];
                    v7 = A[k+1][j + 6];
                    v8 = A[k+1][j + 7];
                    B[k+1][j] = B[k][j+1];
                    B[k][j + 1] = v1;
                    B[k+1][j + 1] = v2;
                    B[k+1][j + 2] = v3;
                    B[k+1][j + 3] = v4;
                    B[k+1][j + 4] = v5;
                    B[k+1][j + 5] = v6;
                    B[k+1][j + 6] = v7;
                    B[k+1][j + 7] = v8;

                    v1 = A[k+2][j];
                    v2 = A[k+2][j + 1];
                    v3 = A[k+2][j + 2];
                    v4 = A[k+2][j + 3];
                    v5 = A[k+2][j + 4];
                    v6 = A[k+2][j + 5];
                    v7 = A[k+2][j + 6];
                    v8 = A[k+2][j + 7];
                    B[k+2][j] = B[k][j+2];
                    B[k+2][j+1] = B[k+1][j+2];
                    B[k][j + 2] = v1;
                    B[k+1][j + 2] = v2;
                    B[k+2][j + 2] = v3;
                    B[k+2][j + 3] = v4;
                    B[k+2][j + 4] = v5;
                    B[k+2][j + 5] = v6;
                    B[k+2][j + 6] = v7;
                    B[k+2][j + 7] = v8;

                    v1 = A[k+3][j];
                    v2 = A[k+3][j + 1];
                    v3 = A[k+3][j + 2];
                    v4 = A[k+3][j + 3];
                    v5 = A[k+3][j + 4];
                    v6 = A[k+3][j + 5];
                    v7 = A[k+3][j + 6];
                    v8 = A[k+3][j + 7];
                    B[k+3][j] = B[k][j+3];
                    B[k+3][j+1] = B[k+1][j+3];
                    B[k+3][j+2] = B[k+2][j+3];
                    B[k][j + 3] = v1;
                    B[k+1][j + 3] = v2;
                    B[k+2][j + 3] = v3;
                    B[k+3][j + 3] = v4;
                    B[k+3][j + 4] = v5;
                    B[k+3][j + 5] = v6;
                    B[k+3][j + 6] = v7;
                    B[k+3][j + 7] = v8;

                    v1 = A[k+4][j];
                    v2 = A[k+4][j + 1];
                    v3 = A[k+4][j + 2];
                    v4 = A[k+4][j + 3];
                    v5 = A[k+4][j + 4];
                    v6 = A[k+4][j + 5];
                    v7 = A[k+4][j + 6];
                    v8 = A[k+4][j + 7];
                    B[k+4][j] = B[k][j+4];
                    B[k+4][j+1] = B[k+1][j+4];
                    B[k+4][j+2] = B[k+2][j+4];
                    B[k+4][j+3] = B[k+3][j+4];
                    B[k][j + 4] = v1;
                    B[k+1][j + 4] = v2;
                    B[k+2][j + 4] = v3;
                    B[k+3][j + 4] = v4;
                    B[k+4][j + 4] = v5;
                    B[k+4][j + 5] = v6;
                    B[k+4][j + 6] = v7;
                    B[k+4][j + 7] = v8;

                    v1 = A[k+5][j];
                    v2 = A[k+5][j + 1];
                    v3 = A[k+5][j + 2];
                    v4 = A[k+5][j + 3];
                    v5 = A[k+5][j + 4];
                    v6 = A[k+5][j + 5];
                    v7 = A[k+5][j + 6];
                    v8 = A[k+5][j + 7];
                    B[k+5][j] = B[k][j+5];
                    B[k+5][j+1] = B[k+1][j+5];
                    B[k+5][j+2] = B[k+2][j+5];
                    B[k+5][j+3] = B[k+3][j+5];
                    B[k+5][j+4] = B[k+4][j+5];
                    B[k][j + 5] = v1;
                    B[k+1][j + 5] = v2;
                    B[k+2][j + 5] = v3;
                    B[k+3][j + 5] = v4;
                    B[k+4][j + 5] = v5;
                    B[k+5][j + 5] = v6;
                    B[k+5][j + 6] = v7;
                    B[k+5][j + 7] = v8;

                    v1 = A[k+6][j];
                    v2 = A[k+6][j + 1];
                    v3 = A[k+6][j + 2];
                    v4 = A[k+6][j + 3];
                    v5 = A[k+6][j + 4];
                    v6 = A[k+6][j + 5];
                    v7 = A[k+6][j + 6];
                    v8 = A[k+6][j + 7];
                    B[k+6][j] = B[k][j+6];
                    B[k+6][j+1] = B[k+1][j+6];
                    B[k+6][j+2] = B[k+2][j+6];
                    B[k+6][j+3] = B[k+3][j+6];
                    B[k+6][j+4] = B[k+4][j+6];
                    B[k+6][j+5] = B[k+5][j+6];
                    B[k][j + 6] = v1;
                    B[k+1][j + 6] = v2;
                    B[k+2][j + 6] = v3;
                    B[k+3][j + 6] = v4;
                    B[k+4][j + 6] = v5;
                    B[k+5][j + 6] = v6;
                    B[k+6][j + 6] = v7;
                    B[k+6][j + 7] = v8;

                    v1 = A[k+7][j];
                    v2 = A[k+7][j + 1];
                    v3 = A[k+7][j + 2];
                    v4 = A[k+7][j + 3];
                    v5 = A[k+7][j + 4];
                    v6 = A[k+7][j + 5];
                    v7 = A[k+7][j + 6];
                    v8 = A[k+7][j + 7];
                    B[k+7][j] = B[k][j+7];
                    B[k+7][j+1] = B[k+1][j+7];
                    B[k+7][j+2] = B[k+2][j+7];
                    B[k+7][j+3] = B[k+3][j+7];
                    B[k+7][j+4] = B[k+4][j+7];
                    B[k+7][j+5] = B[k+5][j+7];
                    B[k+7][j+6] = B[k+6][j+7];
                    B[k][j + 7] = v1;
                    B[k+1][j + 7] = v2;
                    B[k+2][j + 7] = v3;
                    B[k+3][j + 7] = v4;
                    B[k+4][j + 7] = v5;
                    B[k+5][j + 7] = v6;
                    B[k+6][j + 7] = v7;
                    B[k+7][j + 7] = v8;
                }
                else
                {
                    for (k=i; k<i+8; k++)
                        for (l=j; l<j+8; l++)
                            B[l][k] = A[k][l];
                }
            }
        }
    }

    if (M == 64)
    {
        int i, j, k, l, v1, v2, v3, v4, v5, v6, v7, v8;
        
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

