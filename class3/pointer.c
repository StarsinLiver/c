int main(int argc, char const *argv[])
{
  int arr[4] = { 0 , 1 , 2 ,3};

  int* ptr = &arr[0];
  int* lptr = &arr;


  while(ptr == lptr) {
    printf("*ptr : %d" , *ptr);
    ptr++;
  }
  return 0;
}

