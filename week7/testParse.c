
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <error.h>


/**
 * Parses a request-line, storing its absolute-path at abs_path
 * and its query string at query, both of which are assumed
 * to be at least of length LimitRequestLine + 1.
 */
bool parse(const char* line, char* abs_path, char* query)
{
  // TODO

  //make sure that the request target complies
  const char* rest = strchr(line, ' ');
  // printf("rest =%s \n", rest);
  rest++;

  if (rest[0] != '/') {
    printf("501 not implemented \n");
    return false;
  }

  char* querySign = strchr(rest, '?');
  char* abs_path_stop = strchr(rest, ' ');
  if (querySign != NULL) {
    if (querySign[1] != ' ') {
      abs_path_stop = querySign;
      char *nextSpace = strchr(querySign, ' ');
      query = strncpy(query, querySign + 1, nextSpace - querySign);
      const char *needle = "\"";
      if (strstr(query, needle) != NULL) {
        printf("400 bad request! request string contains \" \n");
        return false;
      }
    }
    else {
      abs_path_stop = querySign;
    }
  }
  else {
    query[0] = '\0';
  }

  strncpy(abs_path, rest, abs_path_stop - rest);

  char* http_version_start  = strchr(abs_path_stop, ' ');
  // printf("http_version_start =%s \n", http_version_start + 1);
  if (!strcmp(++http_version_start, "HTTP/1.1\r\n") == 0) {
    printf("505 HTTP Version Not Supported \n");
    return false;
  }


  if (!strncmp(line, "GET ", 4) == 0) {
    printf("405 method not allowed \n");
    return false;
  }


  // error(501);
  printf("all good \n");
  return true;
}





int main ()
{

  char *query = malloc(50 * sizeof(char));
  char *abs_path = malloc(50 * sizeof(char));


  parse("GET /stuff/balls/crap?dog=balls HTTP/1.1\r\n", abs_path, query);
  printf("\n");


  printf("query = %s\n", query);

  printf("abs_path = %s\n", abs_path);

  printf("\n");

  parse("GET /stuff/balls/crap?dog=balls HTTP/1.2\r\n", abs_path, query);

  printf("\n");


  parse("GET /stuff?dog=\"balls\" HTTP/1.1\r\n", abs_path, query);
  printf("\n");


  parse("GET stuff", abs_path, query);
  printf("\n");


  parse("PUT stuff", abs_path, query);
  printf("\n");

  parse("GET /hello.html HTTP/1.1\r\n", abs_path,  query);
  printf("\n");


  parse("GET /cat.exe HTTP/1.1\r\n", abs_path,  query);
  printf("\n");





  char *query1 = malloc(50 * sizeof(char));
  char *abs_path1 = malloc(50 * sizeof(char));

  parse("GET /dog.html? HTTP/1.1\r\n", abs_path1,  query1);
  printf("\n");

  printf("sizeof(query) = %li\n", sizeof(query1));


  printf("query = %s\n", query1);

  printf("abs_path = %s\n", abs_path1);



  return (0);
}