// 함수 (function)

// 함수의 유형 중 ..
// 이 함수는 매개변수가 없고 반환타입도 없다. 라는 의미
// void print(void) {}


// [함수의 원형 선언]
// 함수는 선언부(머리) 와 구현부(몸통) 두 부분으로 구성되어 있다.
// C 컴파일러는 소스를 위에서 아래로 단 한번만 읽기 때문에, 함수의 호출이 함수의 정의보다 앞서면 컴파일러는 이 호출이 올바른 것인지 검사할 수 없음
// 컴파일러가 호출된 함수에 대한 정보를 아직 얻지 못했기 때문

#include <stdio.h>
void print(void);

int main(int argc, char const *argv[])
{
  print();
  return 0;
}


void print() {
  printf("hello");
}