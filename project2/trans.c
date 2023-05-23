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

static int min(int x, int y) 
{
    return x > y ? y : x;
}

void trans_32x32(int M, int N, int A[N][M], int B[M][N])            //transpose function for 32x32 matrix
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
    int i, j, k, l, v1, v2, v3, v4, v5, v6, v7, v8;             //use 8 variables to store the values
    for (i = 0; i < N; i += 8)
    {
        for (j = 0; j < M; j += 8)
        {
            for (int k=i, l=j; k<i+8; k++, l++)
            {
                v1 = A[k][j];
                v2 = A[k][j+1];
                v3 = A[k][j+2];
                v4 = A[k][j+3];
                v5 = A[k][j+4];
                v6 = A[k][j+5];
                v7 = A[k][j+6];
                v8 = A[k][j+7];
                B[l][i] = v1;
                B[l][i+1] = v2;
                B[l][i+2] = v3;
                B[l][i+3] = v4;
                B[l][i+4] = v5;
                B[l][i+5] = v6;
                B[l][i+6] = v7;
                B[l][i+7] = v8;
            }
            for (k=0; k<8; k++)                                 //lazy transposition, copy first then transpose
            {
                for (l=k+1; l<8; l++)
                {
                    v1 = B[j+k][i+l];
                    B[j+k][i+l] = B[j+l][i+k];
                    B[j+l][i+k] = v1;
                }
            }
        }
    }
}

void trans_64x64(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, tmp, v1, v2, v3, v4, v5, v6, v7, v8;
    for (i = 0; i < N; i += 8) 
        for (j = 0; j < M; j += 8) 
        {
            for (k = 0; k < 4; k++) 
            {
                // A top left
                v1 = A[k + i][j];
                v2 = A[k + i][j + 1];
                v3 = A[k + i][j + 2];
                v4 = A[k + i][j + 3];

                // copy
                // A top right
                v5 = A[k + i][j + 4];
                v6 = A[k + i][j + 5];
                v7 = A[k + i][j + 6];
                v8 = A[k + i][j + 7];

                // copy to B
                B[j + k][i + 0] = v1;
                B[j + k][i + 1] = v2;
                B[j + k][i + 2] = v3;
                B[j + k][i + 3] = v4;
                B[j + k][i + 4] = v5;
                B[j + k][i + 5] = v6;
                B[j + k][i + 6] = v7;
                B[j + k][i + 7] = v8;
            }
            // then transpose
            for (k = 0; k < 4; k++) 
            {
                for (v1 = k + 1; v1 < 4; v1++) 
                {
                    tmp = B[j + k][i + v1], B[j + k][i + v1] = B[j + v1][i + k],
                    B[j + v1][i + k] = tmp;
                    tmp = B[j + k][i + 4 + v1],
                    B[j + k][i + 4 + v1] = B[j + v1][i + 4 + k],
                    B[j + v1][i + 4 + k] = tmp;
                }
            }
            // A bottom left and right
            for (k = 0; k < 4; k++) 
            {
                // step 1 2
                v1 = A[i + 4][j + k], v5 = A[i + 4][j + k + 4];
                v2 = A[i + 5][j + k], v6 = A[i + 5][j + k + 4];
                v3 = A[i + 6][j + k], v7 = A[i + 6][j + k + 4];
                v4 = A[i + 7][j + k], v8 = A[i + 7][j + k + 4];
                // step 3
                tmp = B[j + k][i + 4], B[j + k][i + 4] = v1, v1 = tmp;
                tmp = B[j + k][i + 5], B[j + k][i + 5] = v2, v2 = tmp;
                tmp = B[j + k][i + 6], B[j + k][i + 6] = v3, v3 = tmp;
                tmp = B[j + k][i + 7], B[j + k][i + 7] = v4, v4 = tmp;
                // step 4
                B[j + k + 4][i + 0] = v1, B[j + k + 4][i + 4 + 0] = v5;
                B[j + k + 4][i + 1] = v2, B[j + k + 4][i + 4 + 1] = v6;
                B[j + k + 4][i + 2] = v3, B[j + k + 4][i + 4 + 2] = v7;
                B[j + k + 4][i + 3] = v4, B[j + k + 4][i + 4 + 3] = v8;
            }
        }
}

void trans_61x67(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, k, s, v1, v2, v3, v4, v5, v6, v7, v8;
    for (i = 0; i < N; i += 8) 
    for (j = 0; j < M; j += 1)                                  //After test, I choose 1 as the best step 1: 1758
    {                                                           //10: 1775
        if (i + 8 <= N && j + 1 <= M)                           //15: 1777
        {                                                       //20: 1776
            for (s = j; s < j + 1; s++)                         //30: 1799
            {
                v1 = A[i][s];
                v2 = A[i + 1][s];
                v3 = A[i + 2][s];
                v4 = A[i + 3][s];
                v5 = A[i + 4][s];
                v6 = A[i + 5][s];
                v7 = A[i + 6][s];
                v8 = A[i + 7][s];
                B[s][i + 0] = v1;
                B[s][i + 1] = v2;
                B[s][i + 2] = v3;
                B[s][i + 3] = v4;
                B[s][i + 4] = v5;
                B[s][i + 5] = v6;
                B[s][i + 6] = v7;
                B[s][i + 7] = v8;
            }
        } 
        else 
        {
            for (k = i; k < min(i + 8, N); k++) 
            {
                for (s = j; s < min(j + 1, M); s++) 
                {
                    B[s][k] = A[k][s];
                }
            }
        }
    }
}



void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32)
    {
        trans_32x32(M, N, A, B);
    }
    if (M == 64)
    {
        trans_64x64(M, N, A, B);
    }
    if (M == 61)
    {
        trans_61x67(M, N, A, B);
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

