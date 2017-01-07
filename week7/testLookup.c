
#include <stdio.h>
#include <string.h>
#include <ctype.h>



const char* lookup(const char* path)
{
  // TODO
  int dotPos = strlen(path);
  char c = path[dotPos - 1];
  while (c != '.') {
    dotPos--;
    c = path[dotPos];
  }

  char extension[5];
  int pos = 0;
  dotPos++;
  char ch = path[dotPos];

  while (ch != '\0') {
    extension[pos] = ch;
    dotPos++;
    pos++;
    ch = tolower(path[dotPos]);
  }
  extension[pos] = '\0';


  if (strcmp(extension, "html") == 0) {
    return "text/html";

  }
  else if (strcmp(extension, "css") == 0) {
    return "text/css";

  }
  else if (strcmp(extension, "gif") == 0) {
    return "image/gif";

  }
  else if (strcmp(extension, "ico") == 0) {
    return "image/x-icon";

  }
  else if (strcmp(extension, "jpg") == 0) {
    return "image/jpeg";

  }
  else if (strcmp(extension, "js") == 0) {
    return "text/javascript";

  }
  else if (strcmp(extension, "php") == 0) {
    return "text/x-php";

  }
  else if (strcmp(extension, "png") == 0) {
    return "image/png";

  }

  return NULL;
}




int main ()
{


  printf("lookup asdf.html = %s\n", lookup("asdf.html"));

  printf("lookup asdf.js = %s\n", lookup("asdf.js"));

  printf("lookup asdf.pNG = %s\n", lookup("asdf.pNG"));

  printf("lookup asdf.pNG = %s\n", lookup("asdf.SDF"));



  return (0);
}