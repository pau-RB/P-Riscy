#define msz 4

int getchar();
int putchar(int c);

void mxm(int*A,int*B,int*C);

int A[4][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
int B[4][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
int C[4][4] = {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int D[4][4] = {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};


int main() {

  C[0][0] = 0;
  D[0][0] = 0;

  mxm((int*)A,(int*)B,(int*)C);

  for (int i = 0; i < msz; ++i)
    for (int j = 0; j < msz; ++j)
      for (int k = 0; k < msz; ++k)
        D[i][j]+=A[i][k]*B[k][j];

  for (int i = 0; i < msz; ++i)
    for (int j = 0; j < msz; ++j)
      if(C[i][j]!=D[i][j]) {
        putchar(i+48);
        putchar(j+48);
        putchar(C[i][j]/256+48);
        putchar(D[i][j]/256+48);
        return 1;
      }

  putchar('C');

  return 0;
}