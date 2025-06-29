// 문자 상수로는 하나의 문자밖에 표현할 수 없으므로 '둘 이상의 문자(문자열 , string)'을 표현할 방법이 필요하다.

// 둘 이상의 문자를 표현할 때는 큰따옴표를 사용하며 이것을 '문자열 리터럴 (문자열 상수)' 라고 한다.

// [확장열 (escape sequence)]
// 이스케이프 문자요.

// [#define 전처리]
// 앞서 전처리기 지시자 'define' 은 큰따옴표 (문자열 상수) 내의 내용은 치한하자 못한다고 했지만 방법은 있다.

#include <stdio.h>
#define EMAIL "ask@me.com"

int main(int argc, char const *argv[])
{
  char str[] = "abcd";

  // define 전처리
  printf("hello my email : %s", EMAIL);

  return 0;
}

/*
hello my email : ask@me.com
*/