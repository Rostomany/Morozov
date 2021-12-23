#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void TransposedMatrix(float** transp_inv_matrix, float** inv_matrix, int size_matrix)
{
    for (int i = 0; i < size_matrix; ++i)
    {
        for (int j = 0; j < size_matrix; ++j)
        {
            transp_inv_matrix[j][i] = inv_matrix[i][j];
        }
    }
}

void DeleteElement(float** matrix, int size_matrix, float** alg_ñompl, int row, int column)
{
    int i2 = 0;
    int j2 = 0;
    for (int i1 = 0; i1 < size_matrix; ++i1)
    {
        if (i1 != row)
        {
            for (int j1 = 0; j1 < size_matrix; ++j1)
                if (j1 != column)
                {
                    alg_ñompl[i2][j2] = matrix[i1][j1];
                    ++j2;
                }
            ++i2;
            j2 = 0;
        }
    }
}


float Determinant(float** matrix, int size_matrix)
{
    float x = 0;
    int k = 1;

    if (size_matrix == 1)
        x = matrix[0][0];
    if (size_matrix == 2)
        x = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    else
        for (int i = 0; i < size_matrix; ++i)
        {
            int new_size_matrix = size_matrix - 1;
            float** alg_ñompl = (float**)malloc(new_size_matrix * sizeof(float*));
            if (alg_ñompl == NULL)
                exit(EXIT_FAILURE);
            for (int j = 0; j < new_size_matrix; j++)
            {
                alg_ñompl[j] = (float*)malloc(new_size_matrix * sizeof(float));
                if (alg_ñompl[j] == NULL)
                    exit(EXIT_FAILURE);
            }

            DeleteElement(matrix, size_matrix, alg_ñompl, 0, i);
            x += k * matrix[0][i] * Determinant(alg_ñompl, new_size_matrix);
            k = -k;
            free(alg_ñompl);
        }
    return x;
}


void Ex1()
{
    //==============input==============//

    int size_matrix = 0;
    printf("Enter the size of the square matrix, pls.\n");
    scanf_s("%i", &size_matrix);
    if (size_matrix < 1)
    {
        printf("You didn't create a matrix.");
        exit(1);
    }

    float** matrix = (float**)malloc(size_matrix * sizeof(float*));
    float** inv_matrix = (float**)malloc(size_matrix * sizeof(float*));
    float** transp_inv_matrix = (float**)malloc(size_matrix * sizeof(float*));
    for (int i = 0; i < size_matrix; ++i)
    {
        matrix[i] = (float*)malloc(size_matrix * sizeof(float));
        inv_matrix[i] = (float*)malloc(size_matrix * sizeof(float));
        transp_inv_matrix[i] = (float*)malloc(size_matrix * sizeof(float));
    }
    for (int i = 0; i < size_matrix; ++i)
    {
        for (int j = 0; j < size_matrix; ++j)
        {
            printf("[%d][%d] element of the matrix = ", i + 1, j + 1);
            scanf_s("%f", &matrix[i][j]);
        }
        printf("\n");
    }

    //==================Ex1==================//

    float det = Determinant(matrix, size_matrix);
    printf("Determinant of the matrix: %f\n\n", det);

    if (det == 0)
    {
        printf("Matrix with determinant = 0 has no inverse matrix.\n");
        exit(1);
    }

    int h = 0;

    for (int i = 0; i < size_matrix; ++i)
    {
        for (int j = 0; j < size_matrix; ++j)
        {
            int new_size_matrix = size_matrix - 1;
            float** minor = (float**)malloc(new_size_matrix * sizeof(float*));
            for (int s = 0; s < new_size_matrix; ++s)
                minor[s] = (float*)malloc(new_size_matrix * sizeof(float));

            DeleteElement(matrix, size_matrix, minor, i, j);

            if ((i + j + 2) % 2 == 1)
                h = -1;
            else
                h = 1;

            inv_matrix[i][j] = h * Determinant(minor, new_size_matrix) / det;
        }

    }

    TransposedMatrix(transp_inv_matrix, inv_matrix, size_matrix);

    printf("Inverse matrix:\n");

    for (int i = 0; i < size_matrix; i++)
    {
        for (int j = 0; j < size_matrix; j++)
        {
            printf("%10f\t", transp_inv_matrix[i][j]);
        }
        printf("\n");
    }

    //============================================//
}


void Ex2()
{
    //==============input==============//

    int num_of_variables;
    int num_of_equations;
    printf("Number of variables = ");
    scanf_s("%d", &num_of_variables);
    printf("\nNumber of equations = ");
    scanf_s("%d", &num_of_equations);

    if (num_of_variables < 1 || num_of_equations < 1)
    {
        printf("You didn't create a system of equations.");
        exit(1);
    }

    if (num_of_variables != num_of_equations)
    {
        printf("\nThe system of equations cannot be solved by the Carnmer method, \
since the matrix of this equation has no determinant.\n");
        exit(1);
    }

    float** matrix = (float**)malloc(num_of_variables * sizeof(float*));
    if (matrix == NULL)
        exit(EXIT_FAILURE);
    float** matrix2 = (float**)malloc(num_of_variables * sizeof(float*));
    if (matrix2 == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < num_of_variables; ++i)
    {
        matrix[i] = (float*)malloc(num_of_variables * sizeof(float));
        if (matrix[i] == NULL)
            exit(EXIT_FAILURE);
        matrix2[i] = (float*)malloc(num_of_variables * sizeof(float));
        if (matrix2[i] == NULL)
            exit(EXIT_FAILURE);
    }
    float* free = (float*)malloc(num_of_variables * sizeof(float));
    if (free == NULL)
        exit(EXIT_FAILURE);
    
    for (int i = 0; i < num_of_variables; ++i)
    {
        for (int j = 0; j < num_of_variables; ++j)
        {
            printf("[%d][%d] element of the matrix = ", i + 1, j + 1);
            scanf_s("%f", &matrix[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < num_of_variables; ++i)
    {
        printf("[%d] free term of the system of equations = ", i + 1);
        scanf_s("%f", &free[i]);
    }

    //==================Ex2==================//

    float det = Determinant(matrix, num_of_variables);
    printf("\nDeterminant of the matrix: %f\n", det);
    printf("Answers:\n");
    float det2;
    float x;
    
    if (det == 0)
    {
        printf("\nA Zero determinant matrix cannot be solved by the Cranmer method.\n");
        exit(1);
    }
    for (int b = 0; b < num_of_variables; ++b)
    {
        for (int i = 0; i < num_of_variables; ++i)
        {
            for (int j = 0; j < num_of_variables; ++j)
            {
                matrix2[i][j] = matrix[i][j];
            }
        }
        for (int u = 0; u < num_of_variables; ++u)
        {
            matrix2[u][b] = free[u];
        }
        det2 = Determinant(matrix2, num_of_variables);
        x = det2 / det;
        printf("x%d = %f\n", b + 1, x);
    }

}


int main()
{
    Ex1();
    Ex2();
    return 0;
}