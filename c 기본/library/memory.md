## 메모리 관련 함수
메모리와 관련된 함수들의 목록은 다음과 같다 대부분 문자열 관련함수와 비슷하므로 이해하기 쉬울것이다. 이 함수들은 문자열과 관련이 많아서 'string.h'에 포함되어 있다.

|함수|설명|
|:--:|:--:|
|void *memchr(void* p , int ch , size_t n)| 주소 p로부터 n 바이트 내에 ch 가 있으면 그 주소를 반환 못찾으면 NULL을 반환|
|int memcmp(void* p1 , void* p2 , size_t n)| 주소 p1 으로부터 n 바이트와 p2 부터 n 바이트를 비교 같으면 0을 다르면 양수 또는 음수|
|void* memcpy(void *dst , void* src , size_t n)| src에서 dst로 n 바이트를 복사 후 ,dst의 주소를 반환|
|void* memmove(void *dst , void *src , size_t n)|src에서 dst로 n 바이트를 이동후 , dst 의 주소를 반환|
|void* memset(void *p , int ch, size_t n)| ch(1 byte)를 주소 p부터 n 개씩 채워 넣는다.|


원래 memmove()는 같은 대상 내에서 데이터를 복사할 때, memcpy()는 서로 다른 대상 간의 복사에 사용하려고 만들어졌으나 대부분의 컴파일러에서 이 두 함수는 차이가 없다

```c
char src[10] = "123456789";

memmove(src + 3 , src , 3); // 123123789 
memcpy(src+3 , src , 3); // 123123789

// 두 함수가 차이가 없다
```

메모리 관련 함수는 바이트 단위 조작을 하는 데, 왜 memset 과 memchr는 두번째 매개변수 타입이 int 일까?

그 이유는 문자 상수와 16진 정수 상수의 타입이 int 이기때문이다. 예를 들어 0x100번지 부터 10바이트를 문자 상수 'A' 또는 0xFF로 채우려면 아래와 같이 문장을 작성한다.

```c
memset(0x100 , 'A' , 10); // 0x100번지 부터 10 byte를 'A'로 채운다.
memset(0x100 , 0xFF , 10); // 0x100번지 부터 10 byte를 0xFF 로 채운다.
```