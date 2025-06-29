// 배열

// [형식]
// 타입 배열이름[배열길이]

// [초기화] 남은 공간은 0으로 초기화 됨
// {1,2,3}

// index 
// 변수를 사용할 수 없고 항상 상수만 사용이 가능

// 배열을 선언할 때 괄호 [] 안에 '배열의 길이 (length of array)'를 적어줘야하는데, 배열의 길이는 배열의 요소의 개수, 즉 값을 지정할 수 있는 공간의 개수이다.
// 배열의 길이는 index 처럼 변수를 사용할 수 없고 항상 상수만 가능하다.

// [배열의 크기 size of array]
// 배열의 크기는 '배열이 차지하고 있는 메모리의 크기' 를 말하며 , sizeof 연산자를 통해서 구할 수 있다.

// [공식]
// 배열의 크기 / 배열요소의 크기 = 배열의 길이
// sizeof(arr) / sizeof(int) = 5

// 위를 토대로 define 문에서 사용했던 코드를 다음과 같이 sizeof 연산자로 대신하여 작성이 가능하다.


#define LEN 10
int main(int argc, char const *argv[])
{
  // int length = 10;
  // int arr[length]; // 컴파일 에러

  // const int length = 10;
  // int array[length]; // 컴파일 에러

  int array[LEN];

  // sizeof 사용
  int arr2[sizeof(array) / sizeof(array[0])]; // 컴파일 시에 int arr2[10] 이 됨

  return 0;
}
