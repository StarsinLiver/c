# 표준 라이브러리

## 문자 입출력 함수

### getc() 와 getchar()
getc()는 파일에서 문자 하나를 입력핟기 위한 함수인데, 화면(키보드)를 통해 입력받을 때도 사용할 수 있다.

> int ch = getc(stdin); // 화면에서 문자 하나를 입력받아서 ch 에 저장

'stdin' 은 '표준 입력(standard input)' 즉, 화면(키보드)을 통한 입력을 의미하며, 위 문장은 getc()를 이용해서 화면으로부터 문자 하나를 입력받아서 변수 ch에 저장한다. 이 함수는 작업도중에 오류가 발생하거나 더 이상 일겅올 문자가 없으면 '-1'을 반환한다.

그래서 반환타입이 char 가 아닌 int 이며, 반환된 값을 저장할 변수 ch의 타입도 int 인 것이다.

getc(stdin)을 간략한 것이 getchar()이며 , 위의 문장은 아래와 같이 쓸수 있다.

> int ch = getchar(); // getchar()는 getc(stdin)과 동일

### getch()와 getche()
getch()와 getche() 역시 화면으로부터 하나의 문자를 입력받는데 사용되는데, getch()는 입력받은 문자를 화면에 출력하지 않고 , getche()를 출력한다는 차이가 있다. 테트리스와  같은 게임을 할 때는 입력한 문자가 화면에 나타나지 않아야 하므로 getche()보다 getch()가 적합하다.

또한, getc()와 달리 getch()와 getche()는 표준 라이브러리에 포함되지 않는다. 그러나 윈도우에서는 대부분의 컴파일러가 지원한다.

|입력함수|설명|버퍼|헤더파일|
|:--:|:--:|:--:|:--:|
|getc()|지정된 파일에서 문자 하나를 입력받음. fgetc()와 동일| O | stdio.h|
|getchar()|화면에서 문자 하나를 입력받음. getc(stdin) 과 동일| O | stdio.h|
|getch()|화면에서 문자 하나를 입력받음.| x |conio.h|
|getche()|화면에서 문자 하나를 입력받고 출력 (echo).| x |conio.h|

getc()와 getch()의 또 다른 차이는 버퍼의 사용여부인데, 버퍼를 사용한 다는 것은 입력한 내용을 delete 키나 backspace 키로 수정할 수 있고 enter키를 눌러야 일력이 끝난다. 그 다음에 getc()가 버퍼로 부터 문자 하나를 읽어온다. 

반면 버퍼를 사용하지 않는 입력은 키를 누르는 즉시 입력이 끝나버리므로 수정할 기회가 없다.

버퍼를 사용하는 입력은 입력한 내용을 수정할 수 있는 장점이 있으나. 문자를 입력한 후에 누른 Enter키("\n")도 버퍼에 남는다.

```c
int ch;

while(ch = getchar()) {
  printf("%c\n" , ch);

  getchar(); // getchar()을 한번 더 호출해서 버퍼에서 '\n'을 제거
}
```

반대로 문자를 출력하는데 사용하는 함수는 다음과 같다.

```c
int putc(int ch , FILE* fp); // stdio.h
int putchar(int ch);         // stdio.h
int putch(int ch);           // conio.h
```

이 함수들은 문자 출력 전용이므로 printf()보다 사용하기 편리하고 간단하지만, 문자를 출력하고 개행을 하지 않으므로 개행이 필요할 때는 다음과 같이 한다.

```c
putchar('a'); // putc('a' , stdin)과 동일
putchar('\n'); // puts("")와 동일
```

