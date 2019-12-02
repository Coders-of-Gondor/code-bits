#include <stdlib.h>
#include <stdio.h>

typedef struct matrix {
  unsigned rows;
  unsigned cols;
  double *data;
} matrix_t;

matrix_t m_ctor(unsigned int r, unsigned int c);
void m_dtor(matrix_t *m);
void m_init(matrix_t *m);
void m_set_item(matrix_t *m, unsigned int r, unsigned int c, double v);
double m_get_item(matrix_t *m, unsigned int r, unsigned int c);
double *m_item(matrix_t *m, unsigned int r, unsigned int c);
void m_print(matrix_t *m);
void m_mult_const(matrix_t *dest, double k);
int m_add(matrix_t *dest, matrix_t *src);
int m_mult(matrix_t *dest, matrix_t *sr1, matrix_t *src2);

int main(void)
{
  matrix_t m = m_ctor(2, 2);
  m_init(&m);
  m_print(&m);
  printf("\n");

  double val = m_get_item(&m, 3, 2);
  printf("%g\n", val);
  m_set_item(&m, 3, 2, 42);
  val = m_get_item(&m, 3, 2);
  printf("%g\n", val);
  printf("\n");

  m_mult_const(&m, 42);
  m_print(&m);
  printf("\n");

  matrix_t m2 = m_ctor(9, 7);
  matrix_t m3 = m_ctor(2, 2);
  m_init(&m3);
  m_add(&m, &m2);
  m_add(&m, &m3);
  m_print(&m);
  printf("\n");

  matrix_t m4 = m_ctor(2, 2);
  m_init(&m4);
  printf("M3\n");
  m_print(&m3);
  printf("M4\n");
  m_print(&m4);
  if (m_mult(&m, &m3, &m4)) {
    printf("RESULT\n");
    m_print(&m);
  }

  m_dtor(&m);
  m_dtor(&m2);
  m_dtor(&m3);
  return 0;
}

matrix_t m_ctor(unsigned int r, unsigned int c)
{
  matrix_t m = { .rows = r, .cols = c, .data = malloc(r * c * sizeof(double)) };
  return m;
}

void m_dtor(matrix_t *m)
{
  free(m->data);
}

void m_init(matrix_t *m)
{
  unsigned int v = 1;
  for (unsigned int r = 0; r < m->rows; r++)
  {
    for (unsigned int c = 0; c < m->cols; c++)
    {
      m->data[r * m->cols + c] = v;
      v++;
    }
  }
}

void m_set_item(matrix_t *m, unsigned int r, unsigned int c, double v)
{
  m->data[(r - 1) * m->cols + (c - 1)] = v;
}

double m_get_item(matrix_t *m, unsigned int r, unsigned int c)
{
  return m->data[(r - 1) * m->cols + (c -1)];
}

double *m_item(matrix_t *m, unsigned int r, unsigned int c)
{
  return 0;
}

void m_print(matrix_t *m)
{
  for (unsigned int r = 0; r < m->rows; r++)
  {
    for (unsigned int c = 0; c < m->cols; c++)
    {
      printf("%g ", m->data[r * m->cols + c]);
    }
    printf("\n");
  }
}

void m_mult_const(matrix_t *dest, double k)
{
  for (unsigned int r = 0; r < dest->rows; r++)
  {
    for (unsigned int c = 0; c < dest->cols; c++)
    {
      dest->data[r * dest->cols + c] *= k;
    }
  }
}

int m_add(matrix_t *dest, matrix_t *src)
{
  // Check the size of matrixes
  if (dest->rows != src->rows || dest->cols != src->cols)
  {
    fprintf(stderr, "The matrixes are not of the same size\n");
    return 0;
  }
  
  for (unsigned int r = 0; r < dest->rows; r++) 
  {
    for (unsigned int c = 0; c < dest->cols; c++)
    {
      dest->data[r * dest->cols + c] += src->data[r * src->cols + c];
    }
  }

  return 1;
}

int m_mult(matrix_t *dest, matrix_t *src1, matrix_t *src2)
{
  if (src1->rows != src2->cols || src1->cols != src2->rows || dest->cols != src1->rows || dest->rows != src2->cols)
  {
    fprintf(stderr, "The matrixes are not of a proper size\n");
    return 0;
  }

  int v;

  for (unsigned int r = 0; r < src1->rows; r++)
  {
    for (unsigned int c = 0; c < src1->cols; c++)
    {
      //printf("%g ", src1->data[r * src1->cols + c]);
      dest->data[r * dest->cols + c] += src1->data[r * src1->cols + c] * src2->data[c * dest->rows + r];
    }
  }

  return 1;
}
