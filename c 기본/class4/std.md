# 표준 입출력

## stdin , stdout , stderr

```
표준 입력 (standard input) : 키보드로부터 데이터를 입력받는 것
표준 출력 (standard output) : 화면에 데이터 출력
```

표준 입출력에 사용되는 대표적인 함수는 여려분이 이미 잘 알고 있는 scanf 와 prinf가 있고 파일에 형식화된 입출력을 하는 함수인 fscanf 와 fprinf 로도 표준 입출력을 할 수 있다.

```c
[ 1 ]
printf("%d" , 12);
scanf("%d" , &name);

[ 2 ]
fprinf(stdout , "%d" , 12);
fscanf(stdin , "%d" , &num);
```

이처럼 파일입출력에 사용되는 함수로 표준입출력이 가능한 이유는 표준 입출력을 위한 구조체 FILE 타입의 변수가 기본적으로 제공되기 때문이다. 표준 입출력에 사용되는 FILE 구조체는 모두 3개이며  stdin , stdout , stderr 는 이들의 포인터 (FILE*) 이다. 이 포인터들을 이용하면 파일 입출력과 똑같은 방법으로 표준 입출력이 가능하다.

