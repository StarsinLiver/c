## typedef
 typedef 는 기존의 타입을 새로운 이름으로 정의할 수 있게 해주며, 형식은 다음과 같다.

 typedef 는 '#define'과 달리 전처리기 지시자가 아니므로 끝에 ';'를 붙여야 한다.

```c
 [정의]
 typedef TYPE_NAME NEW_TYPE_NAME; // 끝에 ';'를 붙여야 한다.

 [ 예시 ]
 typedef unsigned char byte; // unsigned char 를 byte 라는 타입으로 정의
 byte b; // unsigned char b 와 동일
```

## 사용 이유
 typedef 를 이용해서 타입에 새로운 이름을 붙여주는 주된 이유는 이식성때문이다. 예를 들어 아래와 같이 작성된 코드가 있을 때,
 이 코드는 32bit 컴파일러에서는 아무런 문제가 없지만 64bit 컴파일러에서는 에러가 발생한다.

```c
unsigned int size = sizeof(int);  32bit 컴파일러는 OK, 64bit 컴파일러는 에러
```

32 bit 컴파일러에서 sizeof 연산의 결과가 부호없는 32bit 정수 (unsigned int) 지만, 64bit 컴파일러에서는 부호없는 64bit 정수이기 때문이다.

위와 같이 작성된 코드를 64bit 용으로 변환하려면 sizeof 연산자의 결과를 저장하는 변수의 타입을 모두 일일이 바꿔주어야 한다.

```c
typedef unsigned int size_t; // 64bit 일때 여기만 바꾸면 된다
size_t size = sizeof(int); // unsigned int 대신 size_t 를 사용
```

그러나 위와 같이 작성된 코드는 64bit 용으로 이식할 때 그저 typedef 문 하나만 변경하면 되므로 간단히 문제가 해결된다. 컴파일러에 따라 달라질 수 있는 타입은 이처럼 
typedef 로 새로운 이름을 정의해서 사용하는 것이 좋다.

typedef 의 또 다른 장점은 복잡한 타입을 간단한 이름으로 바꿀 수 있다.

```c
struct { int x , y; } p1 , p2; // 구조체 타입의 변수 p1 , p2 선언
```

이 복잡한 타입을 typedef 로 새롭게 정의하면 위 코드가 아래와 같이 간결해 진다.

```c
typedef struct { int x , y; } Point;
Point p1 , p2; // Point 타입의 변수 선언
```

한가지 주의할 점은 배열 타입을 typedef 로 정의할 때는 형식이 다르다.

```c 
// typedef int[1000] BigArr; // int[1000] 타입을 BigArr 로 정의 <------ 에러
typedef int BigArr[1000]; // Ok. int[1000] 타입을 BigArr 로 정의

BigArr arr; // int arr[1000] 과 동일
```

## #define 과 typedef 의 차이
위의 두 차이는 뭘까?

```c
#define  size_t unsigned int // size_t 를 unsigned int 로 치환

typedef unsigned int size_t; // unsigned int 를 size_t로 새롭게 정의
```

경우에 따라 '#define'이 typedef 를 대신할 수도 있겠지만 소스파일 전체를 범위로 치환하는 '#define'과 달리 typedef 는 C언어의 문장이므로 소스파일의 일부에만 적용하는 것이 가능하다. 즉, typedef 문장의 위치에 따라 적용범위가 달라진다. 그리고 C언어의 타입은 앞서 살펴본 것과 같이 배열이나 구조체처럼 복잡한 경우가 많아 #define으로 단순히 치환할 수 없는 경우가 있다.
