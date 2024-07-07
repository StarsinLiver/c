## 구조체 (structure)

### 구조체란?
구조체는 배열보다 발전된 개념으로 종류에 관계없이 '서로 관련된 데이터를 하나로 묶어 놓은 것'이다. 서로 관련된 데이터의 예는 셀 수 없이 많은데, 대표적인 예로는 학생 정보, 책 정보 등이 있다.

정의를 해보자

```c
struct student {
  int no;
  char name[10];
  int kor, math , eng;
};
```

구조체의 정의는 구조체의 구성요소에 대한 정보일 뿐이므로 구조체를 정의한다고 저장공간이 생기는 것은 아니다. 아래와 같이 구조체 변수를 선언해야 비로소 저장공간이 생기며, 구조체 안에 선언된 순서대로 연속적인 저장공간이 마련된다.

> struct student a1; // 구조체 변수 a1을 선언

단 한번의 선언만으로 구조체에 선언된 모든 변수나 배열이 만들어진다니 얼마나 편리한가! 게다가 다음과 같이 배열로 선언할 수도 있다.

```c
struct student sArr[100]; // 구조체 배열 1차원
```

구조체가 없다면, 학생 정보를 적어도 2차원 배열로 다루어야 할 텐데, 구조체를 이용하면 이처럼 한 차원이 낮은 배열로 다룰 수 있다.구조체 배열은 2차원 배열보다 더 다루기 쉽고, 한 학생의 정보가 하나의 구조체 안에 묶여 있기 때문에 다른 학생의 정보와 섞일 염려도 없다. 그리고 배열과 달리 구조체의 구성요소들이 이름을 가지고 있어서 혼동할 염려가 적다.

> sArr[0].kor = 100;

<br/>

## 구조체의 정의와 선언, 초기화
### 구조체의 정의
앞서 설명한 것과 같이 구조체를 사용하려면 먼저 정의를 알아보자

```c
struct 구조체이름 {
  타입 멤버이름;
  타입 멤버이름;
}; // 괄호 뒤에 ';'를 붙임
```

키워드 struct 와 구조체의 이름을 먼저 쓰고 괄호 뒤에 ';'를 붙인다.

구조체는 새로운 타입을 정의한 것일 뿐 아직 값을 저장할 공간이 마련되지 않았다. 왜냐하면 구조체 내의 변수 선언은 각 맴버의 타입과 이름을 나열한 것일 뿐 실제 변수 선언이 아니기 때문이다. 그래서 아래와 같이 구조체를 정의하면 에러가 발생한다.

```c
struct 구조체이름 {
  타입 멤버이름 = 0; // 초기화 불가 --> 에러
  타입 멤버이름;
};
```

### 구조체의 변수의 선언
구조체의 정의는 기존에 없는 타입을 새로 만드는 것이며, 구조체 student 를 정의하면 'struct student'라는 타입이 새로 추가된다. 구조체 타입의 변수를 선언하는 것은 기존의 변수 선언하는 방법과 다르지 않다.

> struct student s1; // 구조체 student 타입의 변수를 선언

구조체 타입의 변수를 선언할 때 매번 struct를 붙이는 것이 거추장스럽다면, 아래와 같이 typedef로 새롭게 정의할 수 있다.

```c
typedef struct student Student; // struct student 를 Student 로 선언

Student a1; // struct student a1; 과 동일
```

typedef 문과 구조체의 정의를 하나로 합치는것도 가능한데 두 코드는 같다.

```c
[ 1 ]
struct student {
  int no;
  char name[10];
  int kor, math , eng;
};

typedef struct student Student;

[ 2 ]
typedef struct student {
  int no;
  char name[10];
  int kor, math , eng;
} Student;
```

그리고 구조체의 정의와 선언 역시 하나로 합치는 것이 가능하다.

```c
[ 1 ]
struct student {
  int no;
  char name[10];
  int kor, math , eng;
};

struct student a1; // 선언

[ 2 ]
struct student {
  int no;
  char name[10];
  int kor, math , eng;
} a1; // 정의와 선언을 동시에
```

구조체의 정의와 선언을 하나로 합치는 경우는 드물고 아래와 같이 구조체의 이름을 생략해서 '이름없는 구조체'를 정의하는 경우에 합친다

```c
struct { // 이름없는 구조체 정의
  int no;
  char name[10];
  int kor, math , eng;
} a1; // 이름이 없으므로 정의와 선언을 같이 할 수 밖에 없음
```

### 구조체의 초기화
선언된 구조체 변수의 저장공간에 접근하려면, '구조체변수이름.멤버이름'의 형식을 사용한다.

```c
struct student a1;

a1.no = 1;
strcpy(s1.name , "KILDONG"); // 맴버의 타입이 문자열 배열인 경우 사용
```

구조체 맴버에 접근할 때 사용하는 '.'는 '맴버 접근 연산자 (member access operator)' 또는 간단히 '맴버 연산자' 라고 하며, 구조체 변수에 이 연산자를 사용해서 각 멤버에 접근이 가능하다

구조체는 간단히 괄호를 이용해서 구조체를 초기화하는 방법도 있다. 물론 괄호 {}안의 값은 구조체에 정의된 멤버의 순서와 일치해야하며, 값을 지정하지 않은 맴버들을 모두 0으로 초기화 된다.

```c
struct student a1 = { 1 , "KILDONG" }; // 나머지 kor , math , eng 은 0으로 초기화
struct student a2 = { 0 }; // 구조체 변수의 모든 맴버를 0으로 초기화
```

구조체는 배열과 달리 대입 연산자만으로도 구조체의 복사가 가능하다 그래서 아래와 같이 구조체 변수로 다른 구조체 변수를 초기화 할 수 있다.

```c
struct student a1 = { 1 , "KILDONG" };
struct student a2 = a1; // a1 의 내용이 a2 에 그대로 복사
```

구조체의 맴버로 배열을 선언할 수 있는데도 구조체만 대입 연산자로 복사를 허용하는 이유는 일반적으로 구조체의 크기가 배열보다 작은 편이기 때문이다. 대입 연산을 제외하면 구조체에 사용할 수 있는 연산자는 거의 없다. 그래서 두 구조체 변수가 같은지 확인하려면 , 각 맴버의 값을 모두 하나씩 비교해야 한다.

```c 
struct point {
  int x , y;
} p1 = { 3 , 5};

struct point2D {
  int x , y;
} p2;

p2 = p1; // ---> 에러 
p2.x = p1.x; // OK!
```

이름없는 구조체에서도 마찬가지이다.

```c
struct {
  int x , y;
} p1 = { 3 , 5};

struct {
  int x , y;
} p2;

p2 = p1; // ---> 에러 
p2.x = p1.x; // OK!
```


### 구조체의 중첩
구조체도 구조체의 멤버가 될 수 있으며, 이렇게 하는 것을 구조체의 중첩이라고 한다.

```c
struct date {
  int year , mon , day;
};

struct userScore {
  char userId[8];
  int score;
  int rank;
  struct date inputData;
  struct date changeData;
};
```

중첩된 구조체 변수의 선언과 초기화를 함께 할때는 다음과 같이 괄호 {}를 중첩하는 것이 보통이며 생략도 가능하다.

```c
struct userScore a1 = {"myId" , 100 , 1 , {2016 , 1 ,31} , {2016 , 2 , 2}}; // 일반적
struct userScore a2 = {"myId" , 100 , 1 , 2016 , 1 , 31 , 2016 , 2 , 2}; // {} 생략 가능
```

접근 시에는 '.' 연산자로 동일하다

```c
struct userScore a1;

a1.inputData.year = 2016;
a1.inputData.mon = 1;
a1.inputData.day = 31;
```

### 구조체의 배열
같은 타입의 구조체 변수들을 하나로 묶어서 배열로 선언할 수 있다. 

```c
struct student stuArr[100]; // 길이가 100인 구조체 배열
Student stuArr[100]; // typedef struct student {} Student;
```

배열 요소의 타입이 구조체라는 것만 제외하면 일반 배열과 다르지 않으므로 그동안 배열을 다뤄왔던 것과 똑같이 하면 된다. 다음은 괄호{}를 이용해서 구조체 배열을 초기화 하는 방법을 보여준다.

```c
struct student stuArr[] = {
  {1 , "KIM" , 100 , 90 , 70}, // stuArr[0]
  {2 , "KIM" , 100 , 90 , 70}, // stuArr[1]
  {3 , "KIM" , 100 , 90 , 70} // stuArr[2]
}
```

구조체 배열을 초기화 하는 것은 마치 2차원 배열을 초기화하는 것과 동일하며, 2ㅏㅊ원 배열에서 그랬던 것 처럼 안쪽 괄호 {}를 생략이 가능하다.

```c
// 괄호 생략 가능
struct student stuArr[] = {
  1 , "KIM" , 100 , 90 , 70, // stuArr[0]
  2 , "KIM" , 100 , 90 , 70, // stuArr[1]
  3 , "KIM" , 100 , 90 , 70 // stuArr[2]
}
```

구조체 배열의 모든 요소의 모든 맴버를 0으로 초기화하고 싶으면, 다음과 같이 간단히 처리가 가능하다.

```c
struct student stuArr[100] = { 0 }; // 구조체 배열의 모든 요소를 0으로 초기화
int arr[10][5] = { 0 }; // 2차원 배열의 모든 요소를 0으로 초기화
```

### 구조체 배열의 길이와 구조체의 크기
구조체 배열의 길이를 구하는 방법도 배열처럼, 구조체 배열 전체의 크기를 배열 요소인 구조체의 크기로 나누면 된다.

```c
const int SIZE = sizeof(stuArr) / sizeof(stuArr[0]);
const int SIZE = sizeof(stuArr) / sizeof(struct student); // 위와 동일
```

구조체의 크기는 이처럼 sizeof 연산자로 구할 수 있으며 상식적으로 구조체의 크기는 모든 맴버의 크기를 더한 것과 같아야 하지만 항상 그런것은 아니다.

```c
struct student {
  int no;               // sizeof (int) = 4
  char name[10];        // sizeof (char[10]) = 10
  int kor , math ,eng;  // sizeof(int) * 3 = 12
};                      // 합계 : 26
```

위의 계산에서 알 수 있듯이 모든 맴버의 크기를 더하면 26이나 sizeof 연산자로 구조체 student 의 크기를 출력하면 28이다.

> printf("%d" , sizeof(struct student)); // 28


왜냐하면 시스템의 '정렬 제한(align requirement)' 에 의해 구조체의 맴버 사이에 빈 공간이 생겼기 때문이다. 이 빈 공간을 패딩(padding)또는 홀(hole)이라고 하는데, 아래의 2byte 공간이 바로 패딩이다.

```c
구조체 : struct student

int no : 4byte
char name[10] :10byte
int kor : 4byte

[ 2byte padding or hole ]

int math : 4byte
int eng : 4byte
```

정렬 제한은 데이터가 저장될 수 있는 주소에 제한을 두는 것을 말한다. 정렬 제한은 타입마다 다를 수 있으며, int 와 같이 4 byte 크기의 구조체 멤버는 주소가 4의 배수인 곳에만 저장되도록 배치한다는 것이 정렬 제한의 한 예이다.

위의 박스에서 int 타입의 맴버는 정렬 제한에 의해 모두 4의 배수인 곳에 배치되어 있므려 중간에 빈 공간이 생겼다. 이러한 빈 공간 (패딩)은 구조체 맴버의 순서에 따라 크기와 위치가 달라지므로 구조체 맴버의 순서를 적절히 바꾸면 구조체의 크기를 줄일 수도 있다.

정렬 제한을 두는 이유는 보다 효율적으로 메모리에 접근하기 위해서인데 컴파일러가 알아서 처리하므로 우리는 전혀 신경쓰지 않아도 된다. 그저 구조체 맴버의 사이나 끝에 정렬 제한에 의해 빈공간이 생길 수 있다는 정도만 알아두자

<br/>

### 구조체와 포인터
구조체 변수 역시 포인터로 다룰 수 있으며, 다루는 방법은 그동안 배운대로이다. 구조체 변수 s와 이를 가리키는 포인터 p의 선언과 초기화는 다음과 같다

```c
struct student {
  int no;
  char name[10];
  int kor , math , eng;
};
struct student s = { 1, "홍길동" , 100 , 100 ,100 }
struct student *p = &s; // 구조체 변수 s의 주소를 포인터 p에 저장
```

그리고 구조체 포인터 p에 '*' 연산을 하면 구조체를 결과로 얻는다.

> struct student tmp = *p; // 포인터 p가 가리키는 구조체를 tmp 에 저장

포인터로 구조체의 멤버에 접근할 때는 '*' 연산자와 '.'연산자를 같이 사용한다.

> (*p).kor = 90; // s.kor = 90;


'*' 연산자가 '.' 연산자보다 우선순위가 낮기 때문에 괄호를 사용하지 않으면 연산자 '*'의 피연산자는 'p'가 아니라 'p.kor'가 된다.

> *p.kor == *(p.kor)

포인터로 구조체의 멤버에 접근하려면, 두 개의 연산자에 괄호까지 사용해야 하니 좀 불편하다. 이 불편함을 덜어주기 위해 '->' 연산자가 제공된다. 이 연산자는 화살표 처럼 생겼는데, '포인터가 가리키는 구조체의 멤버'에 저장된 값을 반환한다.

```c
(*포인터).멤버 == 포인터 -> 멤버

(*p).kor == p -> kor;
```

그래서 구조체 변수 s와 이를 가리키는 포인터 p 가 있을때 세문장은 같은 의미이다.

```c
s.kor = 90;
(*p).kor.kor = 90;
p -> kor = 90;
```

그리고 구조체에 사용되는 연산자인 '.' 과 '->' 포인터에 사용되는 연산자인 '*' 와 '&' 보다 우선순위가 높다는 것을 기억하자.

```c
*p.no == *(p.no)
*p -> no == *(p -> no)
```

### 구조체 배열의 포인터
구조체 배열을 가리키는 포인터의 타입은 구조체의 타입에 '*' 을 붙인 것이어야 한다.

```c
struct student stuArr[4];     // 길이가 4인 구조체 배열
struct student* pArr = stuArr; // 구조체 배열을 가리키는 포인터
```


### 자기 참조 구조체
구조체가 자기 자신을 중첩할 수는 없다. 다만, 자기 자신과 같은 구조체를 가리키는 포인터를 맴버로 가질 수 있다.

```c
struct people {
  char name[10];
  struct people mother; // ---> 에러
  struct people *father; // OK!!
}
```

구조체 people 은 한 사람의 정보를 다루기 위해 정의한 것으로, 같은 타입의 구조체를 가리키기 위한 포인터 father를 멤버로 가지고 있다. 이 포인터는 자신의 아버지에 대한 정보를 담고 있는 구조체 변수의 주소를 저장해야할 것이다.