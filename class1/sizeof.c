//! 타입의 크기 - sizeof 연산자
// sizeof 는 타입 또는 변수의 크기를 바이트 단위로 알려주는 연산자이다. 이 연산자가 필요한 이유는 각 타입의 크기는 CPU 의 종류에 따라 달라질 수 있기 때문이다.

// [정의]
// sizeof 변수 : 변수의 크기를 byte 단위의 정수로 반환한다.
// sizeof (타입) : 타입의 크기를 byte 단위의 정수로 반환한다.
#include <stdio.h>

int main(int argc, char const *argv[])
{
  int i = 100;


  printf("sizeof i : %d bytes \n" , sizeof i);
  printf("sizeof (char) : %d bytes \n" , sizeof(char));
  printf("sizeof (short) : %d bytes \n" , sizeof(short));
  printf("sizeof (int) : %d bytes \n" , sizeof(int));
  printf("sizeof (long) : %d bytes \n" , sizeof(long));
  printf("sizeof (long long) : %d bytes \n" , sizeof(long long));
  printf("sizeof (float) : %d bytes \n" , sizeof(float));
  printf("sizeof (double) : %d bytes \n" , sizeof(double));
  printf("sizeof (long double) : %d bytes \n" , sizeof(long double));
  return 0;
}

/*
sizeof i : 4 bytes 
sizeof (char) : 1 bytes 
sizeof (short) : 2 bytes 
sizeof (int) : 4 bytes 
sizeof (long) : 4 bytes 
sizeof (long long) : 8 bytes 
sizeof (float) : 4 bytes 
sizeof (double) : 8 bytes 
sizeof (long double) : 16 bytes  
 * 
 */

// 앞서 살펴본것과 같이 sizeof 연산자는 '타입의 크기 (size of type)'를 byte 단위의 정수로 반환한다.
// 피연산자로 타입 뿐만 아니라 변수나 사우 그리고 앞으로 배울 배열과 구조체 등이 가능하며, 이들의 크기, 몇 byte의 메모리 공간을 차지하는 지를 알려준다.
// 타입의 크기는 컴파일 시에 결정되고 실행도중에는 바뀌지 않는 값이기 때문에, 컴파일 단계에서 미리 sizeof 연산을 처리할 수 있다 그렇게 하면 실행 시에 미리 계산된
// 값을 사용하므로 보다 빠른 처리가 가능하다.

// [컴파일 전]
// int size = sizeof(int);

// [컴파일 후]
// int size = 4;

