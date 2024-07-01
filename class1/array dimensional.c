// 다차원 배열
// 2차원 배열을 선언하는 방법은 1차원 배열과 같다. 다만 괄호 []가 하나 더 들어갈 뿐이다.

// [형식]
// 배열타입 배열이름 [행의길이][열의길이]

// [길이 구하기]
// 행의 길이 = 배열의 크기 / 행의 크기
// 열의 길이 = 행의 크기 / 열의 크기

// 행의 길이 = sizeof(arr) / sizeof(arr[0])
// 열의 길이 = sizeof(arr[0]) / sizeof(arr[0][0])

#include <stdlib.h>

int main(int argc, char const *argv[])
{
  // 일반적
  int arr[3][4] = {{1, 2, 3}, {1, 2, 3, 4}, {1, 2, 3}};

  printf("행의 길이 : %d", sizeof(arr) / sizeof(arr[0]));
  printf("열의 길이 : %d", sizeof(arr[0]) / sizeof(arr[0][0]));

  // 동적 할당
  int rows = 3;
  int cols = 4;

  int **mArr = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    mArr[i] = (int *)malloc(cols * sizeof(int));
  }

  mArr[0][0] = 1;

  printf("mArr : %d", mArr[0][0]);

  // 동적 할당 메모리 해제
  for (int i = 0; i < rows; i++)
  {
    free(mArr[i]);
  }
  free(mArr);
  return 0;
}
