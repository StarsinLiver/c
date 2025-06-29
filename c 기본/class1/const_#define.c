// #define 을 이용한 상수정의
// 상수를 선언하는 것 보다 더 간단하게 리터럴에 이름을 붙일 수 있는 방법이 있는데 그것은 바로 '#define'을 이용하는 것이다.

// [정의]
// #define 상수이름 리터럴

#define WIDTH 20 // WIDTH 를 20으로 정의 (define) 한다.

int main(int argc, char const *argv[])
{
  printf(WIDTH); // 20 이 출력됨
  return 0;
}

// [추가]
// #include 와 #define 처럼 '#'으로 시작하는 라인은 엄밀히 말하면 C언어의 문장 (statement)이 아니라 '전처리 지시자(preprocessor directive)'이다. 그래서 '#'으로 
// 시작하는 라인의 끝에는 문장의 끝을 의미하는 세미콜론(;)을 붙이지 않는다.

// [전처리기]
// '전처리기(preprocessing)'이란 컴파일 전에 프로그램 코드에 가하는 작업을 말하며, 이 작업을 수행하는 프로그램을 '전처리기(preprocessor)' 라고 한다.

// 그리고 전처리기가 어떠한 작업을 할 것인지 지시하는 것이 바로 '전처리기 지시자(preprocessor directive)' 이며 대표적인 전처리기 지시자로는 '#include' 와 '#define' 이 있다.


// [정리]
// 전처리(preprocessing) : 컴파일 직전에 소스코드에 가하는 작업
// 전처리기 (preprocessor) : 전처리를 하는 프로그램 (컴파일러에 포함)
// 전처리기 지시자 (preprocessor directive) : 전처리 명령어 (#으로 시작하는 라인)

// 전처리기 지시자 '#define'에 의해서 소스코드가 겪는 변화는 '치환(replace)'이다. 즉, 지시자 '#define WIDTH 20' 은 전처리기에게 소스코드에 나타나는 모든 WIDTH를 20으로 
// 치환하라고 지시하는 것이다.

//! 단 문자열에 포함된 경우에는 치환대상에서 제외된다.