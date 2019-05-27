#include <cstdio>
#include <cstring>

void copy(const char* src, const char* dst) {
  FILE *src_file, *dst_file;
  char c;
  
  src_file = fopen(src, "r");
  dst_file = fopen(dst, "w");

  while ( (c = fgetc(src_file)) != EOF ) {
    fputc(c, dst_file);
  }

  fclose(src_file);
  fclose(dst_file);
}

int main() {
  FILE *file;
  char buff[32];
  
  file = fopen("testfile.txt", "w");

  while (scanf("%31c", buff) != EOF) {
    fwrite(buff, sizeof(char), strlen(buff), file);
  }

  fclose(file);

  file = fopen("testfile.txt", "r");

  printf("testfile.txt: \n");

  while (fread(buff, sizeof(char), sizeof(buff), file) != 0) {
    printf("%s", buff);
  }

  fclose(file);

  copy("testfile.txt", "file2.txt");
}
