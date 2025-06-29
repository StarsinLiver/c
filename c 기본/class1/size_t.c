// sizeof 의 결과 타입 : size_t
// 엄밀히 예기하면 sizeof 연산의 결과 타입은 'size_t' 이다.
// size_t 는 보통 'unsigned int'와 동일한 타입으로 정의되어 있지만 컴파일러마다 타입의 크기가 다를 수 있으므로 '이식성(portability)'을 높이기 위해 별도의 
// 타입으로 정의해 놓은 것이다. 만일 sizeof 의 연산결과 타입이 'unsigned long long'인 시스템에서는 size_t 가 정의된 부분만 수정하면 된다.

#include <stdio.h>

int main(int argc, char const *argv[])
{
  size_t size = sizeof(int); // 이식성이 높은 코드
  unsigned int_ssize = sizeof(int); // 이식성이 낮은 코드

  // 코드
  int i ;
  size_t i_size = sizeof i;
  size_t int_size = sizeof(int);

  printf("i_size : %d\n" , i_size);
  printf("int_size : %d\n" , int_size);

  printf("sizeof(1.0f) : %d\n" , sizeof(1.0f)); // 1.0f 는 float 타입
  printf("sizeof(1.0) : %d\n" , sizeof(1.0)); // 1.0 은 double 타입
  printf("sizeof(65) : %d\n" , sizeof(65)); // 65 는 int 타입
  printf("sizeof('A') : %d\n" , sizeof('A')); // 'A' 는 char 타입
  printf("sizeof(char) : %d\n" , sizeof(char)); 
  return 0;
}

/*
i_size : 4
int_size : 4
sizeof(1.0f) : 4
sizeof(1.0) : 8
sizeof(65) : 4
sizeof('A') : 4
sizeof(char) : 1
*/

// [부호 연산자] + -
// 부호 연산자 '-'는 피연산자의 부호를 반대로 변경한 결과를 반환한다. 피연산자가 음수면 양수, 양수면 음수가 연산의 결과가 된다. 부호 연산자 '+'는 하는 일이 없으며,
// 쓰이는 경우도 거의 없다. 부호 연산자 '-'가 있으니까 형식적으로 '+'를 추가해 놓은 것 뿐이다.

// 증감연산자와 달리 부호 연산자는 일반 산술 변환이 적용되므로, 피연산자의 타입이 short 처럼 int 보다 작은 타입이라면, int 로 자동 형변환 된다. 그래서
// 식 '+s'의 결과 타입은 short 가 아닌 int 이고, 'sizeof(+s)' 의 결과는 int 의 크기인 4가 된다

// int s = 10
// sizeof(+s) -> sizeof(+int) -> sizeof(int) -> 4

// 부호 연산자 '+' 가 피연산자와 같은 값을 연산결과로 반환하지만, 연산결과의 타입은 피연산자의 타입과 다를 수 있다는 것을 알 수 있다.
// sizeof(++s) -> sizeof(short) -> 2



