## main 함수의 매개변수
main 함수를 살펴보자

```c
int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}
```

두 개의 매개변수 이외에 컴파일러가 허용하는 main 함수의 선언방법이 더 있을 수도 있다 다만 표준에서 허용하는 것은 void 와 int argc, char const *argv[] 이다.

매개변수 타입에서는 '*' 하나를 '[]'를 바꿔쓰는 것을 허용하므로 아래의 두 코드는 동일하다.

```c
int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}

int main(int argc, char const ** argv) // ** 로 동일 코드
{
  /* code */
  return 0;
}
```

콘솔 (도스창)의 '커맨드 라인(command line)'을 통해서도 실행이 가능하다

> C:/work > hello.exe abc 123 "hello world"

프로그램을 실행시키면 먼저 main 함수가 호출되는데 이 때 커맨드 라인에 입력된 내용이 문자열 상수 배열로 구성되어 main 함수의 매개변수로 전달된다.
이 과정을 코드로 표현하면 다음과 같다.

```
char* strArr[] = {"c:\\work\\hello.exe",  "abc" , "123" , "hello world" , NULL};
const int LEN = sizeof (strArr) / sizeof(sizeArr[0]); // 배열의 길이를 계산

int exitCode = main(LEN - 1, strArr); // int main (int argc , char* argv[])를 호출
```

실행한 프로그램의 이름이 배열의 첫번째 요소로 들어가는데 실행파일의 이름뿐만아니라 경로도 같이 들어간다. 그리고 편의를 위해서 NULL 과 LEN 에서 NULL을 제외한 LEN - 1을 제공한다.


## MAIN 함수의 반환값 - 종료코드 (exit code)
main 함수의 반환값에 대해서도 알아보자

한번 main 함수 마지막에 'return 0;' 를 넣어주었는데 , 이 문장은 main 함수의 반환타입이 int 라서 그냥 형식적인 것이 아닌 이 프로그램의 종료 코드 'exit code' 를 반환하기 위한 것이다.
```c
int main(int argc, char const *argv[])
{
  /* code */
  return 0; // 종료 코드 (exit code) 로 사용
}
```

종료 코드는 프로그램이 정상적으로 종료되었는지의 여부를 OS 에 전달하기 위한 값으로 이 값이 0이면 정상종료를 , 그 외의 값은 비정상 종료를 의미한다. 종료 코드는 프로그램마다 다르게 정의될 수 있으며 종료 코드로 프로그램이 비정상 종료된 이유를 확인할 수 있다.

윈도우의 경우 종료 코드가 ERRORLEVEL 이라는 환경변수에 저장되며, 이 환경변수에 저장된 값은 아래와 같은 방법으로 확인이 가능하다.

> C:/work > echo %ERRORLEVEL%

왜 종료 코드를 숫자로 할까? 그 이유는 일괄 작업 파일 (*.bat)을 작성하기 위해 숫자가 더 편리하기 때문이다.

```
@echo off
if &ERRORLEVEL% == 0 goto Ok
if &ERRORLEVEL% == 1 goto Error1
if &ERRORLEVEL% == 2 goto Error2
```
