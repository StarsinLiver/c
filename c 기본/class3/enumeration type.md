# 열거형

## 열거형의 정의와 선언
열거형을 정의할 때는 키워드 enum을 사용하여 구조체처럼 괄호 {} 안에 쉼표를 구분자로 해서 상수를 나열하면 되며, 이 상수들을 열거형 상수 (enumeration constant)라고 한다.

> enum 열거형이름 { 상수1, 상수2 ,... } // 열거형 이름은 생략 가능

열거형 상수의 이름은 대문자로 하는 것이 일반적이며, 같은 열거형 타입 내에서 뿐만아니라 다른 열거형 타입의 상수와 이름이 중복되면 안된다.

```c
enum direction {LEFT, RIGHT , UP , DOWN};
enum button {UP , DOWN}; // ----> 에러 direction 의 DOWN 과 중복
```

열거형 상수의 값은 직접 지정해 줄 수 있으며, 값이 저장되지 않은 상수는 바로 왼쪽 옆에 있는 상수 보다 1이 큰 값을 갖게 되며, 제일 왼쪽에 있으면 0이 된다. 따라서 두 문장은 같은 의미이다.

```c
enum direction {LEN , RIGHT = 3, UP , DOWN};
enum direction {LEN = 0 , RIGHT = 3, UP = 4 , DOWN = 5}; // 위와 동일한 문장 이다.
```

각 열거형 상수의 값이 꼭 연속적이어야 하는 것은 아니며, 아래와 같이 다른 열거형 상수의 값을 이용해서 값을 지정할 수도 있다. 그러면 상수 LEFT의 값만 변경해도 나머지 상수의 값이 자동적으로 변경되는 결과를 얻을 수 있다.

```c
enum direction {LEFT = 10 , RIGHT = LEFT + 10 , UP = RIGHT + 10 , DOWN = UP + 10};
enum direction {LEFT = 10 , RIGHT = 20 , UP = 30 , DOWN = 40}; // 위와 동일한 문장 이다.
```

열거형을 선언하는 방법은 다음과 같다

> enum direction dir; // 열거형 direction 타입의 변수 dir 을 선언

구조체처럼 열거형도 정의와 선언을 동시에 할 수 있으며, 위 두 문장은 다음과 같이 한 문장으로 쓸 수 있다.

> enum direction {LEFT, RIGHT , UP , DOWN} dir; // 열거형의 정의와 선언을 동시에

또한 열거형의 이름을 생략할 수 있으며, 이름없는 열거형은 한번만 사용할 수 있다.

> enum {LEFT, RIGHT , UP , DOWN} dir;

아니면 typedef 를 이용해서 다음과 같이 정의할 수 있다.

```c
typedef enum {
  LEFT , RIGHT , UP , DOWN // LEFT = 0 , RIGHT = 1, UP = 2, DOWN = 3
} Direction;

Direction dir = LEFT; // 0;과 동일
```

변수 dir 의 타입이 열거형 direction 이라는 것은 변수 dir 이 열거형 direction 에 정의된 상수의 값만 가져야 한다는 것을 의미한다. 그러나 다른 정수값이 저장되어도 아무런 문제가 없다.

> Direction dir = 300; // OK! 아무 문제가 없다.

이처럼 컴파일러가 열거형 변수에 열거형 상수가 아닌 값이 저장되는 것을 확인하지 않기 때문에 열거형 변수가 올바른 값을 갖도록 하는것은 전적으로 프로그래머의 책임이다.

그러면 변수의 타입을 INT로 하면 될텐데 굳이 열거형으로 하는 이유는 무엇일까? 비록 컴파일러가 열거형 변수의 값을 체크해주지는 못하더라도 프로그래머가 해당 변수에 어떤 값들이 저장되어야 하는지 알고 그에 맞게 처러할 수 있기 때문이다.

```c
void go (Direction dir , int n); // dir 방향으로 n 만큼 이동하는 함수
void go (int dir , int n);       // dir 방향으로 n 만큼 이동하는 함수
```

```c
#include <stdio.h>

typedef enum direction
{
  LEFT,
  RIGHT,
  UP,
  DOWN
} Direction;

typedef struct
{
  int x;
  int y;
} Point;

char *dirName[] = {"LEFT", "RIGHT", "UP", "DOWN"};

void go(Point *p, Direction dir, int n);

int main(int argc, char const *argv[])
{
  Point p = {0};
  int i;

  for (i = LEFT; i <= DOWN; i++)
    printf("%s : %d \n", dirName[i], i);

  go(&p, DOWN, 5);
  go(&p, RIGHT, 10);
  go(&p, UP, 2);
  go(&p, LEFT, 1);
  return 0;
}

void go(Point *p, Direction dir, int n)
{
  printf("[%-5s , %2d]", dirName[dir], n);
  printf("(%2d , %2d) ->", p->x, p->y);

  switch (dir)
  {
  case LEFT:
    p->x += -n;
    break;
  case RIGHT:
    p->x += n;
    break;
  case UP:
    p->y += -n;
    break;
  case DOWN:
    p->y += n;
    break;
  }

  printf("(%2d , %2d) \n", p->x, p->y);
}

/*
LEFT : 0 
RIGHT : 1
UP : 2
DOWN : 3
[DOWN  ,  5]( 0 ,  0) ->( 0 ,  5)
[RIGHT , 10]( 0 ,  5) ->(10 ,  5)
[UP    ,  2](10 ,  5) ->(10 ,  3)
[LEFT  ,  1](10 ,  3) ->( 9 ,  3)
*/
```