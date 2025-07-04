## 동적 메모리 할당
### 1. 동적 메모리 할당이란?
사용할 저장 공간의 크기가 결정된다는 것과 같은 이야기

```c
int gv_arr[100]; // 정적 할당 , 100 * sizeof(int) == 200byte
static int sv; // 정적 할당 , sizeof(int) = 4byte

int main (void) {
  int lv = 0; // 자동 할당, sizeof(int) = 4byte
  int arr[10]; // 자동 할당 , 10 * sizeof(int) = 40byte
}
```

그러나 실행중에 사용될 메모리의 양을 컴파일시에 예측하여 결정하기 어려운 경우가 있다. 예를 들어 파일을 압축하는 프로그램을 작성할 때, 컴파일 시에는 압축할 파일의 크기를 알 수 없으니, 넉넉히 선언할 수 밖에 없다.

> char fileData[1024 * 1024 * 1024];// 파일의 내용을 저장하기 위한 배열 선언 (1GB)

그러나 이렇게 큰 배열은 스택에 저장하기는 너무 커서 전역적으로 선언해야 하는데, 이렇게 하면 프로그램의 시작부터 종료까지 큰 배열을 메모리에 계속 유지해야 하므로 시스템에 부담이 되고 사용할 수 있는 메모리도 부족해진다.

스택의 크기는 컴파일러마다 다르지만 보통 1MB 이며, 컴파일러의 옵션을 통해 크기를 변경할 수 있다.

```c
#define BIG_SIZE 1024 * 1024 * 1024

char gv_fileData[BIG_SIZE];         // 정적 할당 OK
static char sv_fileData[BIG_SIZE];  // 정적 할당 OK

int main(void) {
  char fileData[BIG_SIZE]; // ---> 에러 , 자동 할당, 스택보다 큰 배열
}
```

이런 문제점들을 해결할 수 있는것이 바로 '동적 메모리 할당 (dynamic memory allocation)' 이다. 동적 메모리 할당은 실행 중에 원하는 기간 동안 필요한 만큼의 메모리를 할당받는 것으로 효율적으로 메모리를 사용할 수 있게 해준다. 

동적으로 메모리를 할당받으려면 malloc()을 사용해야 하며, 이 함수를 호출하면 메모리 할당 요청이 OS에 전달된다. 그러면 OS는 힙(heap)에서 사용중이 아닌 영역을 찾아 할당해준다. 할당받은 메모리는 사용한 후에 free()를 호출해서 반환한다.

```c
int main(void) {
  int* lv;

  lv = malloc(4); // 동적 할당 (4byte)
  return 0;
}
```

### 2. 동적 메모리 할당의 장단점
메모리 할당에는 다음과 같이 3가지 방법이 있는데, 정적 할당과 자동할당은 사용할 메모리의 크기와 할당부터 해제까지의 기간, 즉 저장 기간(storage duration)이 고정적이다.

|종류|할당방법|할당영역|할당시기|해체시기|
|:--:|:--:|:--:|:--:|
|자동 할당|선언|스택|함수 호출|함수종료|
|정적 할당|선언 , static|데이터 영역|프로그램 시작|프로그램 종료|
|동적 할당|함수 호출|힙|malloc()호출|free()호출|

정적으로 할당받은 메모리는 프로그램의 시작부터 종료될 때까지 가장 오랫동안 유지되므로 사용을 최소화해야하며, 함수가 호출되면 자동으로 할당되었다가 함수가 종료되면 자동으로 해제되는 자동할당은 저장기간이 너무 짧고 할당받을 수 있는 메모리의 양도 제한적이다.

반면에 동적할당은 필요한 만큼의 메모리를 원하는 기간동안 사용할 수 있으므로 메모리를 가장 효율적으로 사용할 수 있다.

그러나 효율적으로 메모리를 사용하는 대신 지불해야하는 비용이 있는데, 바로 '성능(performance)'과 메모리 누수 발생 가능성(memory leakage , 메모리를 해제하지 않는 
것) 이다. 동적할당은 메모리를 요청하고 할당받는 과정에서 시간지연이 발생한다. 또한 메모리 누수가 점점 쌓이면 사용할 수 있는 메모리양이 줄어들어 결국 메모리 부족으로 프로그램이 비정상적 종료된다.

정적 할당은 프로그램이 실행될 때 할당받은 공간을 그대로 사용하고, 자동할당 역시 프로그램이 실행될 때 할당받은 스택이라는 공간을 반복해서 재사용하는 것이므로 OS에게 추가로 할당을 요청하지 않고 시간지연도 발생하지 않는다.

기본적으로 자동할당이나 정적 할당을 사용하고, 일시적으로 필요한 메모리는 동적할당을 사용하면 된다. 단, 성능이 중요한 경우에는 동적할당 대신 정적할당을 선택할 수도 있다.


### 3. 동적으로 메모리 할당 받기 - malloc()
앞서 언급처럼 동적으로 메모리를 할당받기 위해서 malloc()이라는 함수를 통해서 OS에게 필요한 크기의 메모리를 요청해야 한다.

```
int i;      // 자동 할당. 지역변수 i 선언
malloc(4);  // 동적 할당. 함수 호출로 4 byte 저장 공간 확보
```

그런데 위의 코드에서 동적 할당으로 확보한 4 byte는 변수 i 와 달리 선언을 하지 않았기 때문에 이름이 없다. 그러면 이름도 없는 저장공간에 어떻게 접근할까? 

포인터를 사용하면 된다. 동적으로 할당받은 저장공간은 오직 포인터를 통해서만 접근이 가능하다.

```c
int *pi = malloc(4); // 동적 할당받은 공간의 주소를 포인터 pi에 저장
*pi = 10;            // 동적할당받은 공간에 값을 저장
```

malloc()의 반환값은 할당받은 메모리의 주소이며, 이 값을 포인터에 저장하여 포인터를 통해 할당받은 메모리를 다루게 된다. 만일 실수로 이 반환값을 잃어버리면 더 이상 메모리 공간을 다룰 수 없을 뿐만 아니라, 해제도 할 수 없으므로 주의하자

> void* malloc(size_t size); // 지정된 크기(byte) 의 메모리를 할당하고 주소를 반환하는 함수

위의 선언에서 알수 있듯 malloc()의 반환값은 타입이 'void*'이므로, 이 값을 어떠한 타입의 포인터에 저장해도 된다. 즉, 할당받은 공간을 어떠한 용도로든 자유롭게 사용할 수 있다.

```c
int* pi = (int*)malloc(4); // 형변환 생략 가능
```

좌변 (int*)과 우변(void*)의 타입이 다르기 때문에 원래는 형변환이 필요하지만 굳이 형변환을 해줄 필요가 없는 이유는 malloc() 함수의 반환값 'void*'가 다른 포인터의 타입으로 자동형변환 되기 때문이다. 그런데도 위의 문장처럼 형변환을 명시적으로 사용하는 이유는 실수를 방지하기 위해서이다.

```c
float* p = malloc(sizeof(int)); // 의도적인것일 수도 있지만 실수 일수도 있다.
```

실수 일 수 있지만 컴파일러는 경고조차 하지 않는다.

만일 요청한 메모리를 할당받지 못하면 malloc()은 NULL 을 반환한다. 그래서 malloc()을 호출한 다음에 아래와 같이 if문으로 반환값을 확인하는 것이 원칙이지만, 메가바이트 이상 단위의 메모리를 요청한 경우가 아니라면 할당에 실패하는 일은 거의 없다.

```c
int* pi = malloc(4);

if(pi == NULL) {
  printf("memory allocation error!");
  exit(1); 
}
```


### 동적 할당받은 메모리를 배열처럼 쓰기
앞서 변수로 동적 할당의 예를 들었지만, 동적으로 할당받은 공간은 주로 배열에 쓰인다. 그리고 이 공간을 배열로 사용하는 것은 배열을 포인터로 다루는 것과 완전히 동일하다.

```c
int* pArr = malloc(sizeof(int) * 10); // === int arr[10] === sizeof(int) * 10

pArr[0] = 100;
```

힙도 스택처럼 초기화 없이 덮어쓰기만 하므로 malloc()을 통해 할당받은 메모리는 이전 데이터(쓰기레기 값)가 그대로 남아있다. 초기화가 필요하면, memset()으로 초기화해야한다.

```c
int* pi = malloc(100);

memset(pi , 0 , 100); // 동적 할당받은 메모리를 0으로 모두 채움
```


### 프로세스의 주소 공간
프로그램을 실행하면, 프로그램이 메모리에 올라가면서 '프로세스(실행 중인 프로그램)'가 되는데 32 bit OS의 각 프로세스는 4GB(0x0 ~ 0xFFFFFFFF) 의 주소 공간을 갖게 된다.

> 프로세스 주소 공간 (4GB) = 사용자 주소 공간 (2GB) + 시스템 주소 공간 (2GB)    [ 32 bit OS ]

이 중에서 절반인 2GB 는 OS를 위한 것이므로 실제사용할 수 있는 공간은 나머지 2GB 뿐이며, 이 공간에 코드 영역, 데이터 영역, 스택, 힙이 만들어진다

데이터 영역은 전역변수와 정적변수가 생성되는 영역으로 그 크기가 컴파일 시에 저장되어 프로그램의 종료시까지 유지된다. 스택과 힙의 기본 크기는 1MB 로 같지만, 스택은 처음 할당된 크기가 프로그램 종료될 때까지 고정적이고, 힙은 동적 할당되는 메모리의 양에 따라 크기가 계속 달라진다.

|영역|기본크기|최대크기|메모리 관리|
|:--:|:--:|:--:|:--:|
|스택|초기값 (1MB)|초기값 (1MB)|x|
|힙|초기값 (1MB)|약 2GB|o|


### 동적 메모리 할당의 해제 - free()
지금까지 malloc()을 통해 메모리를 할당받아서 사용만 했는데 원래 동적으로 할당받은 메모리는 사용한 후에 반드시 할당을 해제해야 한다. 해제하지 않으면 '메모리 누수'가 발생한다.

```c
int* pArr = malloc(100 * sizeof(int));

free(pArr); // 메모리 해제
```

이 함수의 선언부는 다음과 같으며 매개변수로 해제하고자 하는 동적할당 영역의 주소를 지정하기만 하면 된다. 동적으로 할당받은 메모리의 주소가 아니면, 실행시에 에러가 발생하고, 매개변수의 값이 NULL 이면 아무일도 하지 않는다.

> void free(void* ptr); // 동적 할당받은 메모리 해제

OS는 해당 주소에 할당된 영역의 크기를 알고 있기 때문에, 해제할 영역의 주소만 알려주면 나머지는 OS가 알아서 처리한다. 참고로 동적으로 할당된 메모리의 양을 주소로 알아 낼 수 있는 _msize()라는 함수가 있는데, 표준은 아니지만 대부분의 컴파일러에서 사용이 가능하다

> size_t _msize(void* memblock); // 동적으로 할당된 메모리의 크기를 반환


### 댕글링 포인터
만일 아래의 코드와 같이 free()로 메모리를 해제한 후 해당 메모리에 접근한다면 어떻게 될까

```c
int* pArr = malloc(100 * sizeof(int));

free(pArr); // 메모리 해제

pArr[0] = 10; // 가능
```

놀랍게도 이미 할당이 해제된 메모리에 값을 저장하는 데도 에러가 발생하지 않는다. 그러나 나중에 이 영역이 다른 용도로 할당되어 사용될 수 있으므로 이런식으로 코드를 작성하면 안된다.

그래서 생각해낸 방법이 메모리를 해제한 직후에 해당 메모리를 가리키던 포인터를 모두 NULL로 초기화하는 것이다. 그렇게 하면 위와 같은 코드를 작성하더라도 에러가 발생하여 잘못된 부분을 쉽게 발견할 수 있다.

```c
int* pArr = malloc(100 * sizeof(int));

free(pArr); // 메모리 해제
pArr = NULL;
pArr[0] = 10; // 에러
```

할당이 해제된 메로리를 가리키는 포인터를 '댕글링 포인터 (dangling pointer)'라고 하며, 메모리를 해제한 후에 포인터를 NULL로 초기화해서 댕글링 포인터가 하나도 남지 않게 해야한다.

혹시라도 포인터를 널로 초기화하는 것을 잊을까봐 아래와 같이 매크로 함수 safeFree()를 정의해서 free()대신 사용하기도 한다.

> #define safeFree(p) if (p) {free(p); p = NULL;} // 메크로 함수 safeFree()를 정의

이 매크로 함수는 p 가 NULL인지 확인하고 널이 아니면 메모리를 해제하고 p를 NULL로 초기화 한다.

```c
#define safeFree(p) if (p) {free(p); p = NULL;} 

int* pArr = malloc(100 * sizeof(int));
safeFree(pArr);
```

<br/>
<br/>

## 3. calloc() 과 realloc()
### calloc()
동적 메로리 할당을 요청하는 함수는 malloc()외에도 calloc()과 realloc()이 있다. calloc()에 대해서 먼저 알아보자 

> void *calloc(size_t n , size_t size); // n * size byte의 메모리를 동적할당

이 함수는 malloc()과 달리 매개변수가 2개이다. malloc()은 할당받을 메모리의 크기만 지정하면 되는데, calloc()은 타입의 크기와 개수를 따로 받는다. 아래의 두 문장은 같은 메모리 할당이다.

```c
iArr = malloc(100 * sizeof(int));
iArr2 = calloc(100 , sizeof(int));
```

또 다른 차이는 초기화에 있다. malloc()으로 할당받은 메모리는 자동으로 초기화되지 않으므로 이전에 저장된 쓰레기 값이 들어있지만, calloc()으로 할당받은 메모리는 모두 0으로 자동 초기화 된다 따라서 아래의 두 코드는 동일하다.

```c
[ 1 ]
iArr = malloc(100 * sizeof(int));
memset(iArr , 0 , 100 * sizeof(int))

[ 2 ]
iArr2 = calloc(100 , sizeof(int));
```

calloc()에는 초기화를 하는 과정이 포함되어 있기때문에 malloc()이 아주 조금이라도 더 빠를 수 밖에 없다. 기본적으로 malloc()을 사용하고, 초기화가 필요한 경우에만 calloc()을 사용하자

### realloc()
동적 할당받은 메모리가 부족하게 된 경우에는 어떻게 해야 할까? 아래와 같이 malloc()을 한번 더 호출해서 추가로 메모리를 할당받는 것은 어떠할까?

```c
int* arr = malloc(10 * sizeof(int));
int* arr2 = malloc(10 * sizeof(int)); // 10개의 int 값을 저장할 수 있는 공간 추가
```

연속적으로 동작 할당을 받더라도 이 두 메모리의 주소가 연속적이라는 보장이 없기 때문에 사용하는데 어려움이 있다. 더 나은 방법은 앞서 배운것 처럼 보다 큰 크기의 메모리를 새로 할당받은 다음에 기존 내용을 복사하는 것이다.

```c
int* arr = malloc(10 * sizeof(int));

int* tmp = malloc(20 * sizeof(int));
memcpy(tmp , arr , 10 * sizeof(int));

free(arr);
arr = tmp;
```

기존 공간이 부족해지면, 이처럼 다소 복잡한 과정을 거쳐야하는데 좀 더 간단한 방법은 없을까? 이럴때 사용하면 좋은 것이 바로 realloc()이다. 이 함수를 이용하면 기존의 메모리의 크기를 늘릴 수 있고 줄일 수도 있다.

> void *realloc(void *memblock , size_t newSize);

첫번째 매개변수로 동적 할당받은 메모리의 주소를, 두번째 매개변수로 변경하고자 하는 메모리의 크기를 넣어주면 된다. 만일 첫번째 매개변수의 값이 NULL 이라면, malloc()처럼 동작하고, newSize의 값이 0이면 free()처럼 동작하여 해당 메모리는 해제된다. 아래 왼쪽의 코드를 realloc()을 사용해서 변경하면 오른쪽 같이 더 간단해진다.

```c
strArr = malloc(sizeof (char*) * len);

strArr = realloc(strArr , sizeof(char*) * len * 2); // 4 byte (32 bit OS) * len * 2 으로 메모리 늘리기
```

realloc()으로 동적할당 받은 메모리의 크기를 축소할 때는 별 문제가 없지만, 확대시에는 확장할 공간이 이미 사용중이면, 새로운 공간을 할당받고 기존의 내용을 복사한다.
이 때는 기존의 주소가 아닌 새로 할당받은 공간의 주소가 반환되므로 항상 realloc()을 호출한 결과로 기존의 주소를 저장하고 있는 모든 포인터의 값을 대체해야한다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(char *str);
void printArr(void);

char **strArr; // 문자열 배열 포인터
int len = 2;   // 문자열 배열의 길이
int pos = 0;   // 문자열을 저장할 위치 (index)

int main(int argc, char const *argv[])
{
  char input[50];
  int i;

  strArr = malloc(sizeof(char *) * len); // 2차원배열 2행 할당

  printf("저장할 단어를 입력하세요. (ENTER : 종료)\n");
  printf(">");

  while (strlen(gets(input)))
  {
    add(input);
    printf(">");
  }

  for (i = 0; i < pos; i++)
  {
    free(strArr[i]);
  }

  free(strArr); // 배열의 메모리를 해제

  return 0;
}

void add(char* str) {
  char* tmp = malloc(sizeof(char) * (strlen(str) + 1)); // 널문자 저장할 공간

  if(pos >= len) {
    strArr = realloc(strArr, sizeof(char*) * len * 2);
    len *= 2;
  }

  strcpy(tmp , str);
  strArr[pos++] = tmp;

  printArr();
}

void printArr(void) {
  int i;

  printf("strArr = %p [" , strArr);
  
  for(i = 0; i < pos; i++) 
    printf("%s, " , strArr[i]);
    
  printf("] len : %d \n" , len);
}

/*
저장할 단어를 입력하세요. (ENTER : 종료)
>aa
strArr = 00000000009A3C60 [aa, ] len : 2 
>bb
strArr = 00000000009A3C60 [aa, bb, ] len : 2 
>cc
strArr = 00000000009A4D90 [aa, bb, cc, ] len : 4 
>dd
strArr = 00000000009A4D90 [aa, bb, cc, dd, ] len : 4 
>aa
strArr = 00000000009A4E20 [aa, bb, cc, dd, aa, ] len : 8
>bb
strArr = 00000000009A4E20 [aa, bb, cc, dd, aa, bb, ] len : 8
>gg
strArr = 00000000009A4E20 [aa, bb, cc, dd, aa, bb, gg, ] len : 8
>bb
strArr = 00000000009A4E20 [aa, bb, cc, dd, aa, bb, gg, bb, ] len : 8
>ff
strArr = 00000000009A4F50 [aa, bb, cc, dd, aa, bb, gg, bb, ff, ] len : 16
>cc
strArr = 00000000009A4F50 [aa, bb, cc, dd, aa, bb, gg, bb, ff, cc, ] len : 16
*/
```

