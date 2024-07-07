## 시간 및 날짜 관련 함수
표준 라이브러리는 날짜와 시간을 다루는 데 유용한 함수들도 제공하는 데, 이 함수들을 사용하려면 'time.h'라는 헤더파일을 포함시켜야 한다. 

> time_t time(time_t *timeptr); // 현재 시간을 초 단위의 정수 (time_t)로 반환

이 함수는 '에포크 타입(Epoch time, 1970년 1월 1일 00:00:00 UTC)'을 기준으로 해서 현재까지 경과된 시간을 초단위의 정수로 반환하는데 오류가 발생하면 -1을 반환한다.
UTC는 'Coordinated Universal Time'의 약어로 '세계 협정시'라고 하며, 이전에 사용되던 GMT(Greenwich Mean Time)와 거의 같지만, UTC가 좀 더 정확하다.

반환타입 'time_t'는 부호있는 정수형타입으로 컴파일러마다 다르게 정의될 수 있으며, 현재시간을 초단위로 얻어내는 방법은 다음과 같다.

```c
time_t now;
time(&now);
// time_t now = time(NULL); // time()의 반환값을 저장해도 됨, 위의 두 줄과 동일

printf("now : %d\n" , now); // now = 1460639891
```

위의 코드는 time()을 호출해서 얻은 현재 시간 (초단위)를 변수 now에 저장하고 출력한다.현재 시간을 구한 것 까지는 좋았는데, 초 단위의 값이라 사람이 알아보기 불편하다. 그래서 제공되는 것이 구조체 tm이다.

```c
struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;  // 시간 (0 ~ 23)
  int tm_mday;  // 일 (1 ~ 31)
  int tm_mon;   // 월
  int tm_year;  // 년
  int tm_wday;  // 요일 (day of week) (0 ~ 6) , 0 == 일요일
  int tm_yday;  // 올해의 n번째 일 (day of year) 1월 1일부터 계산, 범위는 0 ~ 365
  int tm_isdst; // 일광절약시간 (daylight saving time) 1 : 사용중 , 0 : 미사용중 , -1 : 사용 불가
}
```

### time_t 를 tm 으로 변환 - localtime() , gmtime()
time_t 타입의 값을 사람이 알아보기 쉬운 구조체 tm 타입으로 변환하려면 다음의 함수들을 사용하면 된다. 이 들은 변환에 실패하면 NULL 을 반환한다

```c
struct tm *localtime(const time_t *time); // 지역시간
struct tm *gmtime(const time_t *time); // GMT기준 시간
```

gmtime()은 '그리니치 표준시'를 기준으로 반환하고, localtime()은 시간대 (time zone)와 일광 절약 시간 (Daylight Saving Time)이 반영된 '현지 시간' 으로 변환하여 반환한다

gmtime()은 서로 시간대가 다른 지역 간의 시간계산에 사용하고, 같은 지역 내에서의 시간 계산의 localtime()을 사용하면 된다.

```c
time_t now = time(NULL);
struct tm *lt = localtime(now);

printf("%4d년 %2d월 %2d일\n" , lt -> tm_year + 1900 , lt -> tm_mon + 1, lt-> tm_mday);
printf("%2d시 %2d분 %2d초\n" , lt -> tm_hour , lt -> tm_min , lt-> tm_sec);
```

한가지 주의할 점은 localtime()과 gmtime()이 하나의 구조체를 공유하기 때문에 변환한 결과를 별도의 구조체에 저장해 두지 않으면 올바른 결과를 얻지 못할 수 있다.

asctime()은 구조체 tm 을 문자열로 변환하여 반환하는 함수이다.

```c
time_t now = time(NULL);
struct tm *lt = localtime(now);
struct tm * gt = gmtime(now);

printf("%s" , asctime(&lt)); // Thu Apr 14 17:51:55 2016
printf("%s" , asctime(&gt)); // Thu Apr 14 17:51:55 2016
```

### tm 을 time_t으로 변환 - mktime()
localtime()과 반대로, 구조체 tm 타입의 변수를 time_t로 변환할 때는 mktime 이라는 함수를 사용한다.

> time_t mktime(struct tm * tmmptr); // tm을 time_t로 변환해서 반환

### 날짜와 시간의 형식화
구조체 tm의 각 필드에 담긴 값을 하나씩 일일이 꺼내서 쓰기는 좀 불편한데 구조체 tm 에 담긴 날짜와 시간을 간단하게 문자열로 만들어서 반환해 주는 함수 asctime 이 제공된다

```c
char* ctime(const time_t *tptr); // *tpr 값이 음수면, NULL을 반환
char* asctime(const sctruct tm *ts); // 구조체 필드값이 유효하지 않으면 실행시 오류발생
```

ctime 도 asctime과 같은 일을 하는데 타입이 time_t이다. 두 함수 반환 문자열에는 개행문자 '\n'이 포함되어 있기 때문에, 출력할 때 개행문자 없이 지시자 '%s'만 적어주었다.

```c
time_t now = time(NULL);
struct tm* ls = localtime(&now);

printf("%s" , asctime(lt)); // Fir Apr 15 18:52:04 2016
printf("%s" , ctime(&now)); // Fir Apr 15 18:52:04 2016
```

asctime() 처럼 간단하게 날짜와 시간을 출력할 수 있는 함수가 두개 더 있다.

```c
char* _strdate(char* str); // 현재 날짜를 mm/dd/yy 형식의 문자열로 반환
char* _strtime(char* str); // 현재 시간을 HH:MM:SS 형식의 문자열로 반환
```

추가로 strftime() 이라는 함수가 추가로 제공되는데 format 을 사용하므로 표는 직접 찾아보자

```c
size_t strftime(char* s ,                // 반환 결과를 저장할 char 배열의 이름
                size_t maxsize,          // 반환 결과의 최대 길이
                const char* format,      // 변환할 형식 (변환 지시자로 구성)
                const struct tm* tptr    // 변환할 구조체 tm
);
```

### 시간차이 계산 - clock() , difftime()
두 날짜 또는 시간의 차이를 구할 때는 difftime() 이라는 함수를 사용하면 된다. 그런데 함수는 반환타입이 double 임에도 불구하고, 반환값이 초단위의 정수이다.

> double difftime(time_t t2 , time_t t1);

정밀한 계산을 하기 위해서는 clock()이라는 함수를 사용하는데 clock 함수는 프로그램이 실행된 직후부터 경과된 시간을 clock_t 타입의 값으로 반환한다.
clock_t 타입은 컴파일러마다 다르게 정의될 수 있으며, 대부분 long 타입으로 정의되어 있다.

> clock_t clock(void); // 프로그램이 시작된 직후부터의 경과 시간을 반환