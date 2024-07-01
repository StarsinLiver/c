// 문자열

// 문자열 (string) 을 char 배열에 저장할 때는 '문자열 상수(문자열 리터럴)' 을 사용한다. 문자열 상수는 문자열을 큰 따옴표 ""로 묶은 것으로 아래의 문장은 char
// 배열에 str 에 "Hello"를 저장한다.

// char str[] = "Hello"


// [ 두 문장은 동일한 문장 ]
// char str[] = "Hello"
// char str[6] = "Hello" // 문자열 길이 (5) + 널 문자 (1) = 6

// [ 널 문자 \0 ]
// 배열의 길이는 변경할 수 없기 때문에 , 한번 선언된 char 배열의 길이는 고정적이다. 하지만 char 배열안에 지정된 문자열은 길이가 얼마든지 달라질 수 있다.
// 만일 문자열의 길이와 꼭 같은 크기의 char 배열만 사용해야 한다면 , 문자열의 길이별로 많은 수의 char 배열이 필요하므로 저장공간의 낭비가 심할 것이다.
// 그래서 생각해낸 좀 더 효율적인 방법이 문자열의 끝을 알려주는 문자를 문자열의 끝에 붙이는 것이다. 이렇게 하면, 넉넉한 크기의 char 배열 하나로 길이가
// 다른 여러 문자열을 다룰 수 있게 된다 

// 널 문자는 문자 상수로 '\0' 이다.
// 이 문자의 아스키코드는 0이며, 출력하면 아무것도 나타나지 않는다. '빈 칸'이 출력되는 '공백(blank, 아스키코드 32)'와 혼돌하지 않도록 주의하자

// [ 문자열의 초기화와 변경 ]
// 배열을 초기화 할 때 괄호 {}를 사용하는 것이 보통이지만, char 배열은 특별히 괄호 {} 외에 큰따옴표 ""도 사용이 가능하다. 앞서 배운것 처럼 큰 따옴표"" 로 초기화 하면
// 널 문자 '\0' 도 포함된다.

// char str[] = "Hello" === char str[] = {'H','e','l','l','o','\0'}

// 만일 char 배열의 기리이가 문자열의 길이보다 크면 나머지 공간은 널 문자 ("\0")로 채워진다.
// char str[10] = {'H','e','l','l','o','\0','\0','\0','\0','\0'}

// 한마디로 밑의 두개 초기화 형태는 같다.
// char str[] = "";
// char str[] = {'\0'}; 



// [ 문자열의 변경 ]
// 괄호{}를 사용한 초기화가 배열을 선언할 때만 가능한 것처럼 , 큰따옴표"" 를 사용한 초기화도 배열을 선언할 때만 가능하다.

// char str[] = "Hello" 
// str = "h" // 에러
// str = {'h'} // 에러

// 한글자씩 변경
// str[0] = '안'
// str[1] = '녕'

// strcpy 를 사용하는 것이 편하다
// strcpy(str , "안녕");

// 문자열 전체를 삭제하고 싶을때는 char 배열의 첫번째 요소에 널 문자를 저장하거나 strcpy() 로 내용이 없는 '빈 문자열(empty string)'을 복사하면 된다.
// 이번에는 널 문자를 저장하는 쪽이 더 낫다

// str[0] = '\0';
// strcpy(str , "");



// [ 팁 ]
// scanf 는 공백 전까지 만 입력을 받기 때문에 문자열만 받을 때는 gets() puts()를 사용하면 좋다.