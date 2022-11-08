#include"../API/api.h"

char child_stack_1[128] = {1};
char child_frame_1[128] = {1};

char child_stack_2[128] = {1};
char child_frame_2[128] = {1};

char child_stack_3[128] = {1};
char child_frame_3[128] = {1};

char child_stack_4[128] = {1};
char child_frame_4[128] = {1};

int sum(int a, int b) {
  return a+b;
}

int mul(int a, int b) {
  return a*b;
}

int main() {

  fork(7,1,(void*)sum,child_frame_1);
  fork(3,1,(void*)sum,child_frame_2);
  fork(4,2,(void*)mul,child_frame_3);
  fork(5,1,(void*)mul,child_frame_4);

  int res1 = wait(child_frame_1);
  int res2 = wait(child_frame_2);
  int res3 = wait(child_frame_3);
  int res4 = wait(child_frame_4);

  putchar(48+(char)res1);
  putchar(48+(char)res2);
  putchar(48+(char)res3);
  putchar(48+(char)res4);

}
