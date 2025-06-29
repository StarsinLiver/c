// unsigned 란?

// 타입 앞에 'unsigned'를 부이면 '부호없는 정수타입' 이 된다
// 한마디로
// int [+30000 ~ -30000] 의 범위라고 가정했을때 unsigned 를 붙이면 [0 ~ +60000] 즉 - 부호가 사라지고 그 범위를 + 가 붙는다.

// [int 의 생략]
// 타입이 'unsigned int' 인 경우, 다음과 같이 'int'를 생략하고 'unsigned'만 적을 수 있다.
// 반대로 signed 도 마찬가지다.

// 사실 long 과 short 도 각각 'short int' 와 'long int' 에서 'int'를 생략한 것이다.


// [limits.h]
// limits.h에는 기본형의 최대값과 최솟값, 예를 들어 INT_MIN(int 의 최솟값) 과 INT_MAX(int 의 최대값) 과 같은 값들이 정의 되어 있따.

int main(int argc, char const *argv[])
{
  unsigned int a = 100000000; // == int a
  unsigned b = 100000000; // == unsigned int b
  signed c = 100000000; // == signed int c

  short int s = 0; // == short a
  long int l = 0; // == long l
  return 0;
}

