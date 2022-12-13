#ifndef API_H
#define API_H

void fork(int a0, int a1, int a2, int a3, int a4, void *child_func, char *child_frame, char *child_stack);

int wait(char *child_frame);

#endif
