#include"../API/api.h"
#define FRAME_SIZE 128
#define STACK_SIZE 128

char child_stack_1[STACK_SIZE];
char child_frame_1[FRAME_SIZE];

char child_stack_2[STACK_SIZE];
char child_frame_2[FRAME_SIZE];

char child_stack_3[STACK_SIZE];
char child_frame_3[FRAME_SIZE];

char child_stack_4[STACK_SIZE];
char child_frame_4[FRAME_SIZE];

int sum(int a, int b) {
  return a+b;
}

int mul(int a, int b) {
  return a*b;
}

int main() {

  fork(7,1,(void*)sum,child_frame_1,child_stack_1+STACK_SIZE);
  fork(3,1,(void*)sum,child_frame_2,child_stack_2+STACK_SIZE);
  fork(4,2,(void*)mul,child_frame_3,child_stack_3+STACK_SIZE);
  fork(5,1,(void*)mul,child_frame_4,child_stack_4+STACK_SIZE);

  int res1 = wait(child_frame_1);
  int res2 = wait(child_frame_2);
  int res3 = wait(child_frame_3);
  int res4 = wait(child_frame_4);

  putchar(48+(char)res1);
  putchar(48+(char)res2);
  putchar(48+(char)res3);
  putchar(48+(char)res4);

}
