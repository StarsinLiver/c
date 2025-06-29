# 파일 입출력

<br/>

## 파일 열기와 닫기
파일을 열고, 읽기 , 쓰기 , 닫기 과정은 메모리를 동적으로 할당받아 사용한 후에 해제하는 것과 비슷한데, 동적 메모리의 관리처럼 파일의 관리 역시 OS의 책임이므로 파일과 관련된 작업은 항상 OS를 통해야 하기 때문이다. 메모리를 할당받아 사용하려고 malloc()을 호출했던것 처럼 파일을 사용하려면 fopen()을 호출해야 한다.

> FILE* fopen(char* filename , char *mode); // 파일을 지정된 모드로 연다

fopen()으로 파일을 열려면 파일이름과 모드를 지정해야 한다.

```c
FILE* fp = fopen("aaa.txt" , "r");

if(fp == NULL) {
  exit(1)
}
```

fopen()으로 파일을 연다는 것은 OS에게 해당 파일을 사용할 수 있게 준비해달라고 요청하는 것이며, OS는 요청받은 파일의 존재와 권한 상태 등을 확인한 후에 파일이 사용될 수 있도록 준비한다. 이 과정에서 문제가 발생하면 fopen()은 NULL을 반환하며, 문제가 없으면 FILE 타입의 구조체 변수의 주소를 반환한다. 이 주소는 앞으로 배울 파일 처리와 관련된 함수들을 호출하는데 사용된다.

일반적으로 구조체 FILE 은 아래와 같이 정의되어 있으며, 컴파일러 마다 다를 수 있다.

```c
struct _iobuf {
  char *_ptr;   // 현재 위치 범위는 0  ~ bufsiz-1
  int _cnt;     // 버퍼에서 남아있는 byte의 수 범위는 0 ~ bufsiz - 1
  char *_base;  // 버퍼의 주소
  int _flag;    // 상태 플래그 - 파일모드 , 에러발생, 파일 끝 (EOF)의 정보 제공
  int _file;    // 파일 식별자 (file descriptor)
  int _charbuf; 
  int _bufsiz;  // 버퍼의 크기
  char *_tmpfname;  // 임시 파일의 이름
};

typedef struct _iobuf FILE; // 구조체 _iobuf 를 FILE 로 정의
```

<br/>

## fopen()의 모드
[ 일반 모드 ]
|파일 처리모드|파일이 있으면|파일이 없으면|
|:--:|:--:|:--:|
|r|read|error|
|w|write (덮어쓰기)|NEW FILE|
|a [append]|write (이어쓰기)|NEW FILE|

<br/>

[ 수정 모드 ]
|파일 처리모드|파일이 있으면|파일이 없으면|
|:--:|:--:|:--:|
|r+|read + write (덮어쓰기)|error|
|w+|read + write (덮어쓰기)|NEW FILE|
|a+ [append]|read + write (이어쓰기)|NEW FILE|

<br/>

## 열린 파일 닫기
파일을 열어서 작업을 모두 수행한 후에는 파일을 닫아야 하는데 , 이때 사용하는 함수가 바로 fclose()이다.

> int fclose(FILE* fp); // 지정된 파일 (fp)를 닫는다 성공시 0 , 실패시 EOF 반환

EOF는 -1 로 정의되어 잇으며, 원래는 '파일의 끝'을 의마하지만 몇몇 파일 입출력 관련 함수에서 에러가 발생했다는 것을 알린다.

> #define EOF (-1)

예를 들어 파일의 내용을 읽어 오는 fread()라는 함수가 EOF 를 반환했다면 파일의 끝에 도달하여 더 이상 읽을 내용이 없거나 파일을 읽는 중에 에러가 발생한 것이다. 이를 구별하려면 feof() 또는 ferror()을 호출해야 한다

```c
int feof(FILE *fp);       // 반환값이 0이 아니면, 파일의 끝에 도달
int ferror(FILE* fp);     // 반환값이 0이 아니면 에러가 발생
VOID CLEARERR(FILE* fp);  // 에러 발생 여부를 초기화

if(feof(fp))
  printf("파일의 끝")
else if (ferror(fp)) 
  printf("에러")

clearerr(fp); // 에러 상태 초기화
```

한번 에러가 발생하면 에러 발생 상태가 계속 유지되므로 clearerr()로 에러 상태를 초기화해야한다. 그렇지 않으면 이후에 에러가 발생하지 않아도 ferror()의 호출결과는 에러가 발생한 것으로 나온다.

파일을 열고 닫지 않으면 구조체 FILE과 버퍼로 사용하던 공간 등 해당 파일이 사용하던 메모리가 반환되지 않아 메모리 누수가 발생한다. 게다가 OS는 성능상의 문제로 동시에 열 수 있는 파일의 개수를 제한하고 있으므로 파일을 너무 많이 열고 닫지 않으면 다른 프로그램에서 파일을 열 수 없게 될 수 있다

> #define FOPEN_MAX 20 // studio.h

윈도우즈 FOPEN_MAX의 값은 위와 같이 20으로 정의되어 있는데 , 이 값은 잠재적인 제한 (potential limit)이지 꼭 20개 까지만 파일을 열 수 있다는 것을 의미하지 않는다. 파일을 닫지 않고 프로그램이 종료되었을 때 발생할 수 있는 또 한가지 문제는 파일에 출력된 내용의 일부를 잃어 버릴 수 있다는 것이다. fclose()는 버퍼에 아직 출력되지 않은 내용이 남아있으면 이 내용을 파일에 출력하고 파일을 닫는데 fclose() 호출없이 그냥 프로그램이 종료되면, 버퍼에 남아있던 내용이 파일에 쓰여 지지 않은 채로 파일이 닫히게 된다. 파일에 대한 작업을 모두 마친 후에 fclose()를 호출해서 파일을 닫아주는 것을 잊지 말자

<br/>

## 텍스트 파일의 읽기와 쓰기
우선 텍스트 파일을 읽고 쓰는 방법부터 배워보자

|종류| 입력 함수 |출력함수|
|:--:|:--:|:--:|
|문자 단위 입출력| int fgetc(FILE* fp)|int fputc(int c, FILE *pf)|
|문자열 단위 입출력|char* fgets(FILE *fp)|int fputs(char* s , FILE* fp)|
|형식화된 입출력|int fscanf(FILE* fp, ...)| int fprintf(FILE* fp , ...)|


### 문자 단위의 입출력
문자 단위로 입출력 할때 사용하는 함수는 fgetc() 와 fputc() 이다.

|함수 선언부| 설명|
|:--:|:--:|
|int fgetc(FILE* fp)|파일(fp)에서 하나의 문자를 읽어서 반환. 실패시 EOF 반환|
|int fputc(int ch , FILE* fp)|파일에 하나의 문자를 쓰고 반환한다. 실패시 EOF 반환|

fgetc()는 지정된 파일에서 문자 하나 (1byte)를 읽어서 반환하는데 이 함수의 반환타입이 왜 int 일까 라는 생각이 들것이다. 그 이유는 바로 문자 상수 때문이다. 앞서 2장에서 배운것과 같이 문자 상수는 컴파일 과정에서 int 타입의 상수로 바뀐다.

```c
[ 1 ] - 변경 전
fputc('a' , fp); // 'a'를 fp 에 쓴다.

[ 2 ] - 변경후
fputc(65 , fp); // 'a'를 fp 에 쓴다.
```

예제를 보자

```c
#include <stdio.h>

int main(int argc, char const *argv[])
{
  char* fname1 = "a.txt";
  char* fname2 = "b.txt";


  FILE* fp1 = fopen(fname1 , "r");
  FILE* fp2 = fopen(fname2 , "w");

  int ch = 0;

  while((ch = fgetc(fp1) != EOF)) {
    fputc(ch , fp2);
  }

  if(ferror(fp1) || ferror(fp2)) {
    printf("에러");
  }

  fclose(fp1);
  fclose(fp2);
  return 0;
}
```

### 문자열 단위의 입출력

|함수 선언부| 설명|
|:--:|:--:|
|char* fgets(char* buf , int n , FILE* fp)|파일(fp)에서 최대 n-1개의 문자를 읽어서 버퍼(buf)에 저장 성공 시 buf 를 실패시 NULL 을 반환 대부분 n의 값은 sizeof buf 와 같음|
|int fputs(char* buf , FILE* fp)|버퍼 (buf)에 저장된 문자열을 파일(fp)에 출력 성공시 음수 아닌 정수, 실패시 EOF 반환|

fgets 는 버퍼가 가득차거나 개행 문자 '\n'을 만날때 까지 읽는다 fgets()는 항상 마지막에 널문자 '\0'를 저장하기 때문에 한번에 읽을 수 있는 최대 문자의 개수는 '버퍼의 크기 - 1'이다.

fgets()가 읽은 내용의 마지막에 널 문자를 추가하는 이유는 fgets()가 읽어온 내용이 어디까지인지 fputs()에게 알려주기 위해서 이다. 대부분의 경우 fgets()는 버퍼가 가득 차게 파일의 내용을 읽어 오지만, 파일의 끝부분에서는 버퍼의 일부만 채워질수 있기 때문에 널 문자가 없으면 읽어온 내용이 어디까지인가 알 수 없다.

fgets()의 두 번째 매개변수에는 fgets()가 한번에 읽어올 문자의 개수를 적어줘야 하는데, 이 값이 버퍼의 길이보다 크면 안된다. 이 값이 버퍼의 길이보다 작으면 버퍼의 일부만 사용하기 때문에, 이 값을 버퍼의 길이와 같게 지정하는 것이 일반적이다

```c
fgets(buf , sizeof(buf) , fp);
```

텍스트 파일을 행 당위로 읽어야 하는 경우 , 한 행의최대길이가 얼마인지 확인해서 그에 맞게 버퍼의 크기를 결정해야 한다. 그렇지 않으면, 한 행이 중간에 잘려서 여러번에 걸쳐서 읽게 된다.

즉 버퍼의 길이가 적어도 '한 행의 최대길이 + 2' 가 되어야 한다는 이야기이다. 하나의 버퍼를 반복해서 재사용하기 때문에 버퍼의 길이를 넉넉히 잡아주는 것이 좋다

fgets() 에서는 gets()와 달리 개행 문자를 제거하지 않기 때문에 읽어온 내용을 다른 문자열과 비교하려면 먼저 개행 문자를 제거해야한다.

```c
for(i = 0; !buf[i] || buf[i] != '\n'; i++) {
  buf[i] = '\0' // 개행문자가 있으면, 널 문자로 바꾼다.
}
```

fputs()는 버퍼의 내용을 출력하는데 널 문자 '\0'을 만날때 까지만 출력한다. 그리고 이상적으로 출력이 수행되었을 때는 음수가 아닌 값을 반혼하고, 에러가 발생했을때는 EOF를 반환한다.

```c
while(fgets(buf , sizeof(buf) , in_f) != NULL) {
  fputs(buf , out_f)
}
```

### fgets() 와 gets() 의 비교
fgets() 와 gets()에 대해 혼동하는 경우가 많아서 살펴보자

먼저 fgets()는 이미 설명한 것과 같이 입력 버퍼에서 읽어온 내용의 끝에 널문자 '\0'를 추가한다.

```
입력 버퍼 : 'a' , 'b', 'c' '\n'

str : 'a' , 'b', 'c' , '\n' , '\0'  --> '\0' 추가 
```

이와 달리 gets()는 입력 버퍼에서 읽어온 내용에서 끝의 개행 문자를 널문자로 대체한다. 대신 puts()가 개행 문자 '\n'를 붙여서 출력한다.

```
입력 버퍼 : 'a' , 'b', 'c' '\n'

str : 'a' , 'b', 'c' , '\0' // 개행 문자를 널 문자로 대체 
```

일반적으로 fgets()가 더 안적하고 향상된 함수이지만, 유독 화면 입력에서 입력을 마칠 때 누르는 Enter 키 때문에 끝에 개행문자를 없애주는 gets() 를 더 선호하는 경향이 있다.

<br/>

[ 문자열 단위 입출력 예제 ]
```c
#include <stdio.h>

int main(int argc, char const *argv[])
{

  char* fname1 = "a.txt";
  char* fname2 = "b.txt";

  FILE* in_f = fopen(fname1 , "r");
  FILE* out_f = fopen(fname2 , "w");

  char buf[1024];

  while(fgets(buf , sizeof(buf) , in_f) != NULL) {
    fputs(buf , out_f);
  }

  if(ferror(in_f) || ferror(out_f)) {
    printf("에러");
  }

  
  fclose(in_f);
  fflush(out_f);
  fclose(out_f);
  return 0;
}
```

<br/>

## 형식화된 입출력
여러 값을 정해진 형식에 맞춰서 읽고 쓰는 것을 '형식화된 입출력(formatted input/output)' 이라고 한다. 지끔까지 셀 수 없을 정도로 많이 사용해온 'scanf' 와 printf 가 바로 '형식화된 입출력' 이다.

|함수 선언부| 설명|
|:--:|:--:|
|int fscanf(FILE* fp , char* format, ...) | 파일에서 지정된 형식(format)으로 데이터를 읽는다. 입력받은 값의 개수를 반환. 실패시 EOF|
|int fprinf(FILE* fp , char* format, ...)| 데이터를 지정된 형식(format)으로 파일에 출력한다. 출력한 내용의 길이 (byte)를 반환, 실패시 EOF

scanf , printf 는 화면 입출력만 가능하지만 fscanf 와 fprintf 는 화면 , 파일 입출력도 가능하고 fsacnf 는 scanf 와 달리 공백이나 탭도 입력받을 수 있다. 그 외의 사용 방법은 별 차이가 없다.

형식화된 입출력은 성적처리와 같이 한 행에 여러 값이 포함되어 있는 경우에 유용한데 특히 숫자가 포함된 경우 fprinf와 fscanf 가 변환을 내부적으로 알아서 처리해주므로 편리하다.

> fprinf(fp , "%d" , 12); // 숫자 12를 문자열 "12" 로 변환해서 파일에 출력

fprinf() 와 달리 fputc() 와 fputs()는 숫자를 변환하는 기능이 없기 때문에, 이 함수들로 숫자를 출력하려면 먼저 문자나 문자열로 변환해야 한다.

```c
itoa(12 , buf , 10); // 10 진수 12를 문자열 "12" 로 변환해서 buf 에 저장
fputs(buf , fp); // 버퍼에 저장된 "12"를 파일에 출력
```

파일에서 데이터를 읽어 올때는 출력할 때와 반대로 문자열을 숫자로 변환하는 것이 중요한데 fscanf()는 이 변환을 내부적으로 알아서 처리한다.

```c
int num;

fscanf(fp , "%d" , num); // 파일에서 읽어온 문자를 숫자로 변환하여 num에 저장
```

[ 예제 ]

```c
#include <stdio.h>

typedef struct student {
  int no;
  char name[10];
  int kor, math , eng , totalScore;
  float average;
} Student ;



int main(int argc, char const *argv[])
{
  FILE* fp;

  char* fname = "a.txt";
  int i;
  Student* sp;

  char* format = "%2d %-10s %3d %3d %3d \n"; // 출력 형식

  Student sArr[] = {
    {1 , "ABC" , 100 , 100 ,100},
    {2 , "ABCD" , 20 , 70 ,70},
    {3 , "FD" , 100 , 90 ,50},
    {4 , "FGD" , 40 , 100 ,100},
  };

  const int LEN = sizeof(sArr) / sizeof(Student);

  fp = fopen(fname , "w");

  for(i = 0; i < LEN; i ++) {
    sp = &sArr[i];

    fprintf(fp , format , sp->no , sp->name , sp->kor , sp->math , sp->eng);
    fprintf(stdout , format , sp->no , sp->name , sp->kor , sp->math , sp->eng); // 콘솔 출력
  }

  fclose(fp);
  return 0;
}

/*
 1 ABC        100 100 100 
 2 ABCD        20  70  70
 3 FD         100  90  50
 4 FGD         40 100 100
*/
```

```c
#include <stdio.h>

typedef struct student
{
  int no;
  char name[10];
  int kor, math, eng, totalScore;
  float average;
} Student;

int main(int argc, char const *argv[])
{
  FILE *fp;
  FILE * fp2;
  char *fname = "a.txt";
  char *fname2 = "b.txt";
  int i;
  Student s;

  char *inFormat = "%d %s %d %d %d";                     // 지시자 사이의 공백 개수는 의미가 없음
  char *outFormat = "%2d %-10s %3d %3d %3d %4d %8.2f\n"; // 지시자 사이의 공백 개수는 의미가 없음

  fp = fopen(fname, "r");
  fp2 = fopen(fname2 , "w");

  while (1)
  {
    i = fscanf(fp, inFormat, &s.no, &s.name, &s.kor, &s.math, &s.eng);

    if (i < 5)
      break; // 읽어 들인 값의 개수가 부족하거나 EOF면 반복 종료

    s.totalScore = s.kor + s.math + s.eng;
    s.average = s.totalScore / 3.0f;

    fprintf(fp2, outFormat, s.no, s.name, s.kor, s.math, s.eng, s.totalScore, s.average);
  }

  fclose(fp);
  return 0;
}

/*
 1 ABC        100 100 100  300   100.00
 2 ABCD        20  70  70  160    53.33
 3 FD         100  90  50  240    80.00
 4 FGD         40 100 100  240    80.00
*/
```


<br/>
<br/>

## 이진 파일의 입출력
이진 파일의 입출력을 하려면 파일을 이진 모드 (binary mode)로 열어야 한다. 이진 모드로 파일을 열려면 파일 모드에 'b'를 추가한다.

```c
FILE* frb = fopen(filename , "rb"); // 이진 모드로 파일을 읽을 때
FILE* fwb = fopen(filename , "wb"); // 이진 모드로 파일에 쓸때
```

원래는 텍스트 파일을 읽고 쓸 때도 텍스트 모드(text mode)로 파일을 열어야 하지만 텍스트 모드 't'는 기본 모드(default mode)라서 생략이 가능했다

> FILE* frt = fopen(filename , "rt");

### 이진 모드와 텍스트 모드 차이
텍스트 모드에서는 모든 데이터가 문자로 변환되어 파일에 입출력된다. 반면에 이진모드에서는 아무런 변환없이 데이터를 있는 그대로 파일에 입출력한다.

|파일모드| 출력 |입력|
|:--:|:--:|:--:|
|텍스트 모드(t)|데이터를 문자로 변환|문자를 데이터 변환|
|이진 모드 (b)|변환 없음|변환 없음|

텍스트 모드에서는 입력할 때와 출력할 때 모두 변환이 필요하므로 비효율적이다. 유일한 장점은 사람이 알아보고 직접 수정하기 편한다는 것뿐인데, 파일의 내용이 노출되기를 원하지 않는 경우 이것마저 단점이 된다. 텍스트 모드는 환경설정 파일이나 로그파일같은 경우에 주로 사용되고 대부분은 효율적인 이진 모드로 입출력 한다.

이진모드에서 주의해야 할 점은 '바이트 순서(byte order)' 이다. 바이트 순서가 빅엔디안인 컴퓨터에서 작성된 이진 파일을, 리틀엔디안인 컴퓨터에서 읽을 경우 전혀 다른 값이 되기 때문이다. 바이트 순서 문제는 숫자 데이터인 경우만 해당되며 텍스트 모드에서는 문제가 되지 않는다. 이것을 텍스트 모드의 장점이라고 볼 수 있지만 바이트 순서 문제 때문에 텍스트 모드로 입출력하는 경우는 꽤 드물다.

### 이진 파일의 읽기와 쓰기
이진 파일의 입출력에 쓰는 함수는 fread() 와 fwrite() 오직 두개 뿐이다. 게다가 이 두함수는 이름만 다를 뿐 선언부가 동일하다.

|함수 선언부|설명|
|:--:|:--:|
|size_t fread(void* buf , size_t sz , size_t n , FILE* fp)|파일로 부터 sz 바이트의 데이터를 n개 읽어와 버퍼에 저장하고 읽어온 데이터의 개수를 반환한다. 읽어오는 중에 에러가 발생하거나 파일의 끝에 도달하면 반환값은 n보다 작을 수 있다. sz나 n이 0이면 0을 반환한다.|
|size_t fwrite(void* buf , size_t sz , size_t n , FILE* fp)|버퍼에 저장된 sz바이트의 데이터 n개를 파일에 출력하고 출력에 성공한 데이터의 개수를 반환한다. 출력중에 에러가 발생하면 반환값이 n보다 작을 수 있다 sz나 n이 0이면 0을 반환한다.|


fwrite 는 버퍼에서 'sz * n' 바이트를 파일에 쓰고 fread 는 파일로 부터 'sz * n' 바이트를 읽어서 버퍼에 저장한다. 이진 입출력은 타입이 정해져 있지 않으므로 버퍼의 타입이 'void*' 이고 타입의 크기를 알려주는 매개변수 sz 도 필요하다.

이제 사용법은 알아보자 먼저 변수에 저장된 숫자를 fwrite()로 파일에 출력하는 방법은 다음과 같다.


```c
int i = 10; // 변수 i의 크기는 sizeof(int) * 1

fwrite (&i , sizeof(int) , 1 , fwb); // 지정된 주소 (&i)에서 sizeof(int) * 1바이트를 읽어서 파일에 출력
```

그리고 배열에 저장된 내용을 파일에 출력하는 방법은 다음과 같다

```c
int arr[5] = {0,1,2,3,4};

fwrite(arr , sizeof(int) , 5 , fwb); // 지정된 주소 (arr)에서 sizeof(int) * 5 바이트를 읽어서 파일에 출력
```


[ 예제 - 이미지 파일을 복사 ]
```c
#include <stdio.h>

#define BUF_SZ 4096

int main(int argc, char const *argv[])
{
    char* fname1 = "a.jpg";
    char* fname2 = "b.jpg";

    FILE* fpb1 = fopen(fname1 , "rb");
    FILE* fpb2 = fopen(fname2 , "wb");

    if (fpb1 == NULL || fpb2 == NULL) {
        printf("파일 열기 오류\n");
        return 1;
    }

    char* buf[BUF_SZ];
    size_t t;

    while((t = fread(buf , sizeof(char) , BUF_SZ , fpb1)) == BUF_SZ) {
        fwrite(buf , sizeof(char) , t , fpb2);
    }

    if(ferror(fpb1) || ferror(fpb2)) {
        printf("파일 처리 중 에러 발생\n");
    }

    fclose(fpb1);
    fclose(fpb2);
    return 0;
}
```

<br/>

## 임의 접근 파일
지금까지 파일에 입출력 할때 파일의 맨처음부터 순서대로 읽거나 써왔지만, 파일 위치 지시자의 값을 변경하면 임의의 위치에서 읽고 쓸수 있다. 파일 위치 지시자 (file position indicator)는 파일에 입출력할 위치를 관리하기 위한 변수로 fopen()으로 파일을 열었을 때 , 이 변수의 값은 0이다. 0은 파일의 맨 처음을 의미하며 입출력 함수를 호출할 때마다 파일 위치 지시자의 값은 입출력한 데이터의 크기만큼 자동적으로 증가된다.

```c
FILE *fp = foepn("song.mp3" , "rb"); // 파일 위치 지시자 = 0

fread(buf , 100 ,1 ,fp); // 파일 위치 지시자 = 100
fread(buf , 50 ,1 ,fp); // 파일 위치 지시자 = 150
```

이렇게 자동적으로 관리되기 때문에 지금까지 파일위치 지시자의 존재를 모르고도 편하게 입출력할 수 있었던 것이다. 대부분의 파일 입출력이 순차적이지만, 때때로 파일 위치 지시자의 값을 임의의 위치로 변경해야 할 때도 있다. 예를 들어 음악 파일이나 동영상 파일의 특정 위치로 이동해서 재생한다던가 , 특정 구간을 반복해서 재생하는 경우가 이에 해당한다.

파일 위치 지시자의 값을 변경하는데 사용하는 함수는 fseek 이며, 선언부는 다음과 같다

> int fseek (FILE* fp , long offset , int origin); // 파일 위치 지시자를 변경하는 함수

이 함수는 파일 fp 의 파일위치 지시자가 origin 으로 부터 offset 만큼 떨어진 곳을 가리키도록 변경하는데 변경에 성공하면 0을 , 실패하면 0이 아닌 값을 반환한다. 매개변수 origin 에 지정할 수 있는 값의 종류는 다음과 같다.

```c
#define SEEK_SET 0 // 파일의 맨 처음
#define SEEK_CUR 1 // 파일 위치 지시자의 현재 위치 (current position)
#define SEEK_END 2 // 파일의 끝
```

다음은 fseek()를 호출하는 다양한 예시를 보자

```c
fseek(fp , 5L , SEEK_CUR); // 파일의 현재 위치에서 5 byte 이동
fseek(fp , -5l, SEEK_END); // 파일의 맨 끝에서 이전으로 5byte 이동
```

이 외에도 파일 위치 지시자가 관련된 함수는 다음과 같은 것들이 있다.

```c
void rewind(FILE* fp); // 파일의 맨 처음으로 이동 (파일 위치 지시자의 값을 0으로)
long ftell(FILE* fp); // 파일 위치 지시자의 값을 반환, 오류 발생시 EOF 반환
```

### 파일의 크기
C언어의 표준 라이브러리에는 파일의 크기를 알려주는 함수가 없다. 대신 다음과 같이 ftell()을 이용하면 파일의 크기를 간단히 알아낼 수 있다.

```c
fseek(fp , 0 , SEEK_END);
fileSize = ftell(fp); // 파일 위치 지시자의 값이 파일의 크기
```


[ 10 MB 파일 만들기 ]
```c
#include <stdio.h>

#define BUF_SZ 4096

int main(int argc, char const *argv[])
{
    char* filename = "a.txt";
    FILE* fp = fopen(filename , "w");

    int fileSize = 1024 * 1024 * 10; // 10MB

    fseek(fp , fileSize - 1 , SEEK_SET);

    if(fputc('\0' , fp)  == EOF) {
        printf("파일 생성 실패");
    }

    fclose(fp);

    fp = fopen(filename , "r");

    fseek(fp , 0 , SEEK_END);
    printf("이 파일의 크기는 %ld bytes 입니다. \n" , ftell(fp));
    return 0;
}

/*
이 파일의 크기는 10485760 bytes 입니다. 
*/
```

