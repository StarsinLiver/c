// 문자열 비교
// 문자나 숫자는 비교 연산자로 비교할 수 있지만, 문자열은 비교 연산자만으로 되지 않는다.
// 문자열의 내용이 같은지 비교하는 'strcmp()' 함수가 더 필요하다. 이 함수는 문자열의 내용이 같으면 0을, 다르면 양수 또는 음수를 반환한다.

// strcmp 함수는 '사전순서(dictionary order)' 에 의거하여 비교하는데, 두 문자열 중에서 왼쪽 문자열이 오른쪽 보다 사전순서로 앞이면 음수, 뒤면 양수를 반환한다.
// 이 점을 이용하면 여러 문자열을 사전순서로 또는 그 역순으로 정렬할 수 있다.

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
  char str[] = "abc";

  printf("true : %d" , strcmp(str , "abc"));
  return 0;
}
