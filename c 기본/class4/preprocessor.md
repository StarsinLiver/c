# 전처리기 

## 전처리기 (preprocessor) 란?
소스파일을 컴파일할 때, 본격적인 컴파일을 하기 직전에 소스 파일에 어떠한 작업을 가하는 것을 '전처리(preprocessing)'라 하고 '전처리'를 수행하는 프로그램을 '전처리기' 라고 한다. 전처리기는 비교적 기능이 간단하기 때문에 별도의 프로그램으로 존재하는 경우는 드물로 보통 컴파일러에 포함되어 있다. 그래서 컴파일 할 때, 전처리기를 따로 실행시키지 않아도 컴파일러는 먼저 소스 파일을 전처리한 다음, 그 결과를 가지고 컴파일하기 시작한다.

```
전처리(preprocessing)  : 컴파일 직전에 소스코드에 가하는 작업
전처리기(preprocessor) : 전처리를 하는 프로그램 (컴파일러에 포함)
전처리기 지시자        : 전처리 명령어 (#으로 시작하는 라인)
```

### 전처리기 지시자
전처리기가 해야 할 작업은 '전처리기 지시자 (preprocessor directive)'를 사용해서 소스파일에 명시하며, 소스 파일의 앞부분에 놓는것이 일반적이다.

전처리기 지시자는 '#'로 시작하며, 한 줄 전체가 전처리기 지시자로 인식된다. c언어의 문징이 아니므로 끝에 ';'를 붙이지 않는다. 그러나 주석은 사용할 수 있다.
전처리기가 제일 먼저 하는 작업은 소스파일에서 주석을 제거, 사실은 주석을 '공백(blank)'으로 대체, 하는 것이기 때문이다.

```c
#include <stdio.h>
#define MAX 100
```

지금까지 사용해온 '#include' 와 '#define' 이 대표적인 전처리기 지시자이다. 전처리기는 소스파일에 나타난 순서대로 하나씩 수해오디므로 순서에 유의해야 한다. 일반적으로 include 지시자를 define 지시자보다 위에 놓는다.

|전처리기 지시자| 설명|
|:--:|:--:|
|#include|파일의 내용을 포함시킨다|
|#define|매크로를 정의한다.|
#|undef|매크로 정의를 해제한다|
|#if , #elif|조건이 참이면 (#elif는 else if)|
|#else|조건이 거짓이면|
|#endif|조건 처리의 끝|
|#ifdef|매크로가 정의되어 있다면|
|#ifndef|매크로가 정의되어 있지 않다면|
|#pragma|컴파일러 고유의 전처리 기능을 사용|


## 매크로 정의 - #define
전처리기 지시자 '#define'은 매크로 (macro)를 정의 (define)하는데 사용도니다. 방법은 간단하며 정의할 '매크로의 이름'과 '치환할 내용'을 공백으로 구분해서 적어주면 된다. 그러면 공백이후부터 그 줄의 끝까지의 내용이 매크로로 정의된다.

> #define 매크로 치환내용

매크로의 이름은 대문자로 하는것이 일반적이며 여러 단어로 이루어져있는경우 '_'로 연결한다. 전처리기는 지시자 '#define'을 만나면 소스 파일에서 지정된 매크로를 찾아 치환 내용으로 바꾸는데, 이 과정을 '매크로 확장(macro expansion)'이라 한다.

> #define MAX 32645

전처리기는 소스 파일에 포함된 모든 MAX를 32645로 치환(확장)한다. 단 , 매크로가 부분적으로 일치하거나 문자열에 포함된 경우에는 치환이 불가하다.

매크로로 정의할 수 있는 내용은 숫자뿐만 아니라 문자 또는 문자열 , 식도 가능하다.

```c
#define PI 3.1341
#define NEW_LINE '\n'
#define EMAIL "AAA@DNSKADN.com"
#define SECOND 1
#define MIN 60 * SECOND
#define HOUR 60 * MIN
```

여기서 주의해야할 점은 매크로가 여러 항의 식으로 정의되어 있는경우 반드시 치환 내용 전체를 괄호로 감싸 주어야 한다. 그렇지 않으면 엉뚷한 결과를 얻을 수 있다.

예를 들어, 아래와 같이 초단위의 값을 시간단위로 변환하려고 매크로 상수 HOUR로 나누기를 하면 , "7200 / 60"이 먼저 계산되어 변수 hour 에 2가 아닌 7200이 저장된다.

```c
hour = 7200 / HOUR;
hour = 7200 / 60 * 60;
hour = 7200;
```

그래서 아래와 같이 식 전체를 괄호로 감싸주어야 올바른 결과를 얻을 수 있다.

```c
#define MIN (60 * SECOND)
#define HOUR (60 * MIN)
```

매크로로 정의할 내용이 길 때는 '\'를 쓰면 여러 줄에 나누어 적을 수 있다.

```c
#define LONG_MSG "this is " \
                  "a very very " \
                  "long message."
```

한줄로 쓰면 다음과 같다.

> #define LONG_MSG "this is " "a very very " "long message."

연속적으로 나열된 문자열 상수들은 하나로 결합된다.

> #define LONG_MSG "this is a very very long message."

반대로 아래와 같이 정의할 매크로의 내용이 아예없을 수도 있다. 매크로를 정의하긴 했지만 내용이 없으므로 치환되지 않는다

> #define DEBUG // 매크로 DEBUG를 정의했지만 내용이 없다.

<br/>

### 매크로 정의 해제 #undef
'#define'과 반대로 '#undef'는 이미 정의된 매크로를 취소한다. 주로 매크로의 정의를 변경할 때 사용된다.

```c
#define MAX 100
...
#undef MAX        // 매크로 정의 해제
#define MAX 200   // 매크로 재정의
```

매크로를 재정의할 때는 , #undef로 정의를 취소하고 다시 #define으로 정의해야 하는데 다르면 #undef를 사용하지 않고도 재정의가 가능하다.

```c
#include <stdio.h>

#define MAX 100

int main(int argc, char const *argv[])
{
  printf("%d \n" , MAX);

  #undef MAX
  #define MAX 200

  printf("%d \n" , MAX);
  return 0;
}

/*
100 
200
*/
```

### 매크로 함수
전처리기 지시자 '#define'으로 단순한 치환 뿐만아니라 함수처럼 매개변수를 갖는 매크로를 정의하는 것도 가능한데, 이러한 매크로를 '매크로 함수 (function0like macro)'라고 한다. 매크로 함수 역시 매크로처럼 정의된 내용으로 치환될 뿐이지만, 매개변수를 가질수 있으므로 활용도가 높다

> #define 매크로 ( 매개변수 , 매개변수2 , ... )  치환내용

매크로의 이름 다음에 함수처럼 괄호를 붙이고 그 안에 매개변수를 쉼표 ','로 구분하여 나열한다. 함수와 달리 매크로 함수의 매개변수는 타입없이 이름만 적는다. 그리고 이 매개변수로 치환될 내용을 착성하면 된다. 이때 주의할 점은 매크로의 이름과 괄호 '(' 사이에 공백이 있어서는 안된다. 공백이 있으면, 매크로 함수가 아닌 단순 매크로를 정의한 것이 되기 때문이다. 단, 매개변수를 나열하는 괄호 ()안의 공백은 허용된다.

> #define max(x,y) x > y ? x : y

위에 정의한 매크로 함수 max 를 정의했다. 매크로 함수의 이름 'max' 와 괄호 '(' 사이에 공백이 없을음 확인하자 매크로 함수를 호출하는 방법은 함수 호출과 동일하다

```c
int result = max(3 ,5);
```

[ 여러 문장으로 이루어진 경우 ]

간혹 아래와 같이 여러문장으로 이루어진 매크로 함수를 정의해야 할 수도 있다. 

> #define swap(a , b , tmp) tmp = a; a = b; b = tmp

이 매크로 함수는 두 매개변수 a와 b의 값을 바꾸는 일을 하도록 작성되었다. 이 매크로 함수가 if 문과 결합된다면 어떻게 될까?

```c
[ 1 ] - 매크로 사용
if(a > b)
  swap(a , b , tmp);

[ 2 ] - 전처리 후
if (a > b)
  tmp = a; a = b; b = tmp;
```

[ 2 ]의 코드에서 알 수 있듯이 의도한 바와 달리 한 문장만 if 문에 속한것으로 간주된다. 이러한 문제를 피하려면 괄호()를 사용해서 문장들을 하나로 묶어야 한다.

> #define swap(a , b , tmp) {tmp = a; a = b; b = tmp}

그러나 여전히 문제가 있다. 아래의 왼쪽과 같이 불럭이 생략된 if-else 문의 경우 매크로 함수가 치환되고 나면 블럭{} 뒤에 남는 ';'에 의해 if문이 끝나게 된다.

이 문제를 해결하려면 블럭 {} 대신 while 문을 사용해야 한다.

> #define swap(a , b , tmp) do {tmp = a; a = b; b = tmp} while(0)

위의 do-while문은 조건식이 0(거짓) 이므로 블럭 {}내의 문장이 단 한번만 수행된다.


<br/>

## # 연산자
이 연산자는 매크로 함수에서만 사용할 수 있는 특수한 것으로 프로그램의 디버깅이나 테스트에서 유용하게 사용된다. 만일 아래와 같이 매개변수의 값을 출력하는 매크로 함수를 정의했다고 가정하자

> #define print_int(x) printf("x : %d\n" , x)

그리고 매크로 함수를 호출하면

```c
int x = 5, y = 7;

print_int(x); // x = 5
print_int(y); // x = 7
```

아쉽게도 큰 따옴표 안의 x는 치환되지 않기 때문에 'y=7'이 아닌 'x=5'가 출력된다. 매크로 함수의 매개변수가 y일때는 x대신 y로 출력하게 할 수 없을까? 이럴 때 사용하는 것이 '#' 연산자이다.

> #define print_int(x) printf(#x" : %d \n" , x);

이제 호출하면 다음과 같다.

```c
int x = 5, y = 7;

print_int(x); // x = 5
print_int(y); // y = 7
```

이 매크로 함수는 변수뿐만 아니라 식일때 더욱 유용하다

<br/>

## ## 연산자
이 연산자도 #연산자처럼 매크로 함수에서만 사용할 수 있으며, 두 피연산자를 하나로 결합하는 일을 한다. 예를 들어 매크로 함수 getCurrency()가 다음과 같이 정의되어 있을때 ## 연산자는 'CURRNECY_'와 매개변수 na를 결합한다.

> #define getCurrency(na) CURRENCY_ ## na // CURRENCY_na

그래서 이 매크로 함수를 getCurrency(KR)와 같이 호출하면 다음과 같다.

```c
printf("%s \n" , getCurrentcy(KR)); // CURRENCY_KR
```

이처럼 ## 연산자는 동적으로 명칭(식별자)를 만들어 낼 수 있으므로 일정한 규칙(접두사 , 접미사)에 의해 만들어진 명칭을 사용하는 프로그램에서 규칙이 변경되었을 때 식별자를 일일이 손수 고쳐주지 않아도 된다.

```c
#include <stdio.h>

#define CURRENCY_KR "won"
#define CURRENCY_kr CURRENCY_KR
#define CURRENCY_US "dollar"
#define CURRENCY_us CURRENCY_us

#define DATE_FORMAT_KR "YYYY/MM/DD"
#define DATE_FORMAT_US "MM/DD/YY"

#define call(fn , na) get_ ## fn ## _ ## na 
#define getCurrency(na) CURRENCY_ ## na

void get_dateFormat_kr(void) {
  printf("get_dateFormat_kr() : %s \n" , DATE_FORMAT_KR);
}

void get_dateFormat_us(void) {
  printf("get_dateFormat_us() : %s \n" , DATE_FORMAT_US);
}

int main(int argc, char const *argv[])
{
  call(dateFormat , kr)(); // get_dateFormat_kr();
  call(dateFormat , us)(); // getdateFormat_us();

  printf("currency of %s : %s \n" , "KR" , getCurrency(KR));
  printf("currency of %s : %s \n" , "US" , getCurrency(US));
  return 0;
}

/*
get_dateFormat_kr() : YYYY/MM/DD 
get_dateFormat_us() : MM/DD/YY
currency of KR : won
currency of US : dollar
*/
```

<br/>

## 내장 매크로
프로그래머의 편의를 위해 컴파일러가 다음과 같은 매크로를 기본적으로 제공한다.

|내장 매크로|설명|
|:--:|:--:|
|__TIMESTAMP__|소스 파일이 마지막으로 수정된 날짜와 시간으로 치환|
|__DATE__|현재의 날짜(월일년)로 치환된다|
|__TIME__|현재의 시간(hh:mm:ss)으로 치환된다.|
|__FILE__|소스 파일이름으로 치환된다. (경로와 확장자 포함)|
|__LINE__|소스 파일의 몇번재 줄(line)인지 알려준다.|
|__STDC__|표준 C를 따를 때는 1, 아닌 때는 정의되지 않는다|

주로 디버깅, 테스트에 유용한 것들이며 다음의 예제를 보는것으로 끝난다.

```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
  printf("최근 수정 시간 : %s \n" , __TIMESTAMP__);
  printf("컴파일된 날짜 : %s \n" , __DATE__);
  printf("컴파일된 시간 : %s \n" , __TIME__);
  printf("파일이름 : %s \n" , __FILE__);
  printf("라인 번호 : %d \n" , __LINE__);
  return 0;
}

/*
최근 수정 시간 : Sun Jul 07 14:34:56 2024 
컴파일된 날짜 : Jul  7 2024
컴파일된 시간 : 14:35:14
파일이름 : C:\ALL_WORKSPACE\0_GIT\c\main.c
라인 번호 : 9
*/
```

<br/>

## 조건부 컴파일
전처리기 지시자로 조건에 따라 소스 코드의 일부를 포함시키거나 제외시키는 것이 가능한데, 이것을 '조건부 컴파일(conditional compilation)'이라 한다. 조건부 컴파일에 사용되는 기본적인 전처리기 지시자로는 '#if'와 '#endif'가 있으며 다음과 같은 형식으로 사용된다.

```c
#if 조건식
  // 조건식이 참일 경우 컴파일될 문자들을 넣는다.

#endif
```

조건식이 참인 경우에만 '#if'와 '#endif'사이의 문장들이 컴파일 된다. 거짓인 경우, 이 문장들은 컴파일 대상에서 제외된다. 마치 소스 파일에 존재하지 않는 것처럼 다뤄진다.

지시자 '#else' 와 '#elif'를 사용하면, if-else 문처럼 형식으로 구성이 가능하며 if 문처럼 중첩도 가능하다

```c
#if 조건식1
  // 조건식1이 참일 경우 컴파일될 문장
#elif 조건식2
  // 조건식2이 참일 경우 컴파일될 문장
#else
  // 조건식 1과 2가 거짓일 경우
#endif
```

다만 조건식에 사용할 수 있는 상수와 연산자는 if 문에 비해 제한적인데, 상수는 정수(문자상수 포함)만 가능하며, 연산자는 대부분 사용가능하지만 형변환 , 증감, 대입 연산자 등을 사용할 수 없다.

```c
#if DEBUG                            // 매크로 DEBUG 의 값이 0이 아니면, 참
#if DEBUG == 1                       // 매크로 DEBUG의 값이 1이면 참
#if MODE!=DEBUG                      // 매크로 MODE와 DEBUG의 값이 다르면 참
#if (10 <= VERSION && VERSION <= 30) // 논리 연산자 , 비교연산자

#if OS_VERSION > 3.1                 // ---> 에러 실수는 조건식에 사용 불가
#if (OS_NAME == "WINDOWS 8")         // ---> 에러  문자열은 조건식에 사용불가
```

그리고 주석 대신에 #if#endif 를 사용할 수도 있는데 주석 '/**/'은 줄첩할 수 없기 때문에 중첩 가능한 #if~#endif를 사용하는 것이 더 편리할 때가 있다.
다음의 경우 조건식이 0(거짓)이므로 #if 와 #endif 사이의 문장들이 컴파일에서 제외되어 주석 처리한 것과 같은 효과를 얻는다.

```c
#if 0 // 조건식이 0 (거짓)

  // 주석 처리됨

#endif
```

이 주석을 해제하려면 조건식을 0에서 1로 바꾸기만 하면 된다.

<br/>

## defined 연산자
매크로가 정의되었는지 확인하는 연산자이다. 전처리기 지시자 #if 와 #elif 의 조건식에 사용되며, 지정된 매크로가 정의되어 있으면 1, 아니면 0을 반환한다. 괄호는 생략해도 된다

```c
#if defined(MAX) // 매크로 MAX 가 정의되어 있으면 1
#if !defined(MAX) // 매크로 MAX가 정의되어 있지 않으면 0
```

define 연산자를 사용하지 않고 매크로 이름만으로 조건식을 작성해도 매크로가 정의되어 있는지 확인할 수 있는 것 처럼 보인다.

```c
#if MAX // 매크로 MAX 가 정의되어 있으면 참 , 그렇지 않으면 거짓
```

그러나 매크로가 정의되어 있으도 값이 0이면, 0을 결과로 얻기에 반드시 define 연산자를 사용해야 매크로의 정의 여부를 정확히 알 수 있다

```c
#define MAX 0

#if MAX // 조건식이 0 (거짓)
#if defined(MAX) // 조건식이 1 (참)
```

<br/>

## #ifdef 와 #ifndef
연산자 defined는 빈번히 사용되므로, 이 연산자와 지시자 #if 가 결합된 #ifdef라는 지시자가 제공된다. #ifndef는 #ifdef 와 논리부정 연산자 '!' 를 결합한 것으로 #ifdef와 반대의 의미이다.

```c
[ 1 ] - #ifdef
#if defined(DEBUG) == #ifdef DEBUG

[ 2 ] - #ifndef
#if !defined(DEBUG) == #ifndef DEBUG
```

예시로 보자

```c
#include <stdio.h>

#define DEBUG
#define print_int(x) printf(#x" : %d\n" , x)

#if 1
int main(int argc, char const *argv[])
{
  int x = 10;

#ifdef DEBUG
  print_int(x);
#endif

  return 0;
}

#else 
int main(int argc, char const *argv[])
{
  printf("여기는 주석일 수 있습니다")
  return 0;
}
#endif

/*
x : 10
*/
```

<br/>

## include 
전처리기는 지시자 include 위치에 지정된 파일의 내용을 그대로 포함시킨다. 대부분의 경우 헤더 파일 (*.h)을 소스 파일에 포함시키기 위해 사용하지만, 반드시 헤더파일이어야 하는 것은 아니다. 그래서 include 순서에 유의해야 한다.

표준라이브러리의 헤더를 제일 위에 놓고 그 다음에 사용자 정의 헤더를 놓는 것이 일반적이다. 지시자 define 이 include 보다 위쪽에 있으면 include 가 지정한 파일의 내용에도 영향을 미치기 때문에 define 은 include 보다 아래에 놓는다.

```c
#include <stdio.h> // 표준 라이브러리
#include "user.h" // 사용자 라이브러리

#define SIZE 100
```

### 헤더 파일의 중복 방지
앞서 설명한 것과 같이 헤더 파일은 중첩이 가능하기 때문에 실수로 동일한 헤더 파일이 중복해서 포함될 수 있다 이러한 일이 일어나는 것을 방지하기 위해 다음과 같이 '조건부 컴파일'을 한다

```c
[ user.h ]
#ifndef _USER_H // _USER_H 가 정의되어 있지 않으면, #endif 까지 수행
#define _USER_H // _USER_H 를 정의

...

#endif
```

만일 user.h 가 처음으로 소스파일에 포함되는 경우에는 _USER_H 가 정의 되어 있지 않을 것이므로 #ifndef 와 #endif 사이에 속한 문장들이 컴파일 될 것이다. 그러나 이 헤더 파일이 두 번 이상 포함된 경우에는 '#define _USER_H' 에 의해 #ifndef의 조건식이 거짓이 되어 컴파일 되지 않는다.


<br/>

## pragma
지금까지 소개한 전처리기 지시자 외에 컴파일러마다 자신만의 전처리 기능이 필요할 때 pragma 지시자를 사용한다. 각 컴파일러는 필요에 따라 다양한 전처리 작업을 정의해 놓고 pragma 지시자를 통해 전처리 작업을 수행할 수 있게 한다. 그래서 특정 컴파일러를 위해 만들어진 전처리 기능은 다른 컴파일러에서 무시되거나 다른 의미로 해석되어 오동작 할 수 있으므로 pragma 지시자를 사용하기 전에 컴파일러가 지원하는 지 확인해야한다.

```c
#pragma once  // 헤더 파일이 중복되어 포함되지 않게 한다.
#pragma warning(disable : 2996) // 4996번 경고 메시지가 나타나지 않게 한다.
```

Visual Studio 2015에서는 #ifndef 로 저건부 컴파일 대신 '#pragma once'를 사용해서 간단히 헤더 파일의 중복을 방지할 수 있다. 그러나 이 기능이 모든 컴파일러에서 동작한다는 보장이 없기에 가능하면 #ifndef를 사용하는 것이 좋다

특정 경고 메시지가 나타나지 않도록 할때 '#pragma warning'을 사용하는데 , 4996번 은 대체 함수의 사용을 권유하는 경고 메시지이다.

보다 자세한 내용은 https://msdn.microsoft.com/ko-kr/library/d9x1s805.aspx 를 참조하자