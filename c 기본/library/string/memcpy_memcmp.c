// 배열의 복사와 비교

// [memcpy] : 배열의 복사
// [memcmp] : 배열의 비교 , 비교결과가 변수에 저장됨


#include <string.h>
int main(int argc, char const *argv[])
{
  
  int arr1[] = {1,2,3};

  int arr2[sizeof(arr1) / sizeof(arr1[0])];

  memcpy(arr2 , arr1 , sizeof(arr1));

  const int LEN = sizeof(arr2) / sizeof(arr2[0]);

  // 복사 출력
  for(int i = 0; i < LEN; i++) {
    printf("%d \n" , arr2[i]);
  }

  // 비교
  int chk = memcmp(arr2 , arr1 , sizeof(arr1)); // 0 참 , 1 거짓

  if(chk == 0)
    printf("참");
  if(chk == 1)
    printf("거짓");

  return 0;
}
