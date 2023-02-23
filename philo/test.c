#include <sys/time.h>
#include <stdio.h>

int main() {
  struct timeval start, end;
  int i = 0 ;
  // record the starting time
  gettimeofday(&start, NULL);

  // do some work here
  // ...
//while(i < 10-1)
//{
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);
  usleep(10000);



 // i++;
//}
  // record the ending time

  gettimeofday(&end, NULL);

  // calculate the elapsed time in microseconds
  int elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

  printf("Elapsed time: %d ms\n", elapsed/1000);

  return 0;
}