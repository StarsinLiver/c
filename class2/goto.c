// goto 문

// goto 문은 실행흐름을 지정된 곳으로 이동시킨다. break 문과 continue 은 swich 문이나 반복문 내에서만 사용가능하다는 조건이 있으나 goto 문은 함수의 블럭 안이라면
// 어디서든 사용이 가능하다.

// [형식]
// goto 레이블 이름; // 지정된 레이블로 이동

// [레이블]
// 레이블이름 :

// goto 문으로 이동할 곳의 위치는 '레이블(label)' 로 지정한다.

#include <string.h>

int main(int argc, char const *argv[])
{

  char str[] = "a";

  if (strcmp(str, "a") == 0)
    goto a;
  if (strcmp(str, "b") == 0)
    goto b;

a:
  printf("a");
  exit(1);
b:
  printf("b");
  exit(1);
  return 0;
}
