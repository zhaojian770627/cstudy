typedef unsigned long  u32_t;	   /* 32 bit type */
typedef struct { u32_t _[2]; } u64_t;

extern u64_t cvul64(long l1,long l2);

int main(int argc, char *argv[]) {
  u64_t u64;
  unsigned long l1=20;
  unsigned long l2=40;
  u64=cvul64(l1,l2);
  return 0;
}
