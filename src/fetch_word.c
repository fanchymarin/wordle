#include "wordle.h"
#include <curl/curl.h>

char errbuf[CURL_ERROR_SIZE];

void curl_error(CURL *client, CURLcode result)
{
  size_t len = strlen(errbuf);
  fprintf(stderr, "\nlibcurl: (%d) ", result);
  if(len)
    fprintf(stderr, "%s%s", errbuf,
            ((errbuf[len - 1] != '\n') ? "\n" : ""));
  else
    fprintf(stderr, "%s\n", curl_easy_strerror(result));  curl_easy_cleanup(client);
  exit(EXIT_FAILURE);
}

void api_call()
{
  CURL *client = curl_easy_init();
  if (!client) return ;

  curl_easy_setopt(client, CURLOPT_URL, WORDLE_URL);
  curl_easy_setopt(client, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(client, CURLOPT_ERRORBUFFER, errbuf);

  CURLcode result;
  result = curl_easy_perform(client);
  if(result != CURLE_OK) curl_error(client, result);
  curl_easy_cleanup(client);
}

char* parse_json(char *response)
{
  char *ch;
  ch = strtok(response, "\"");
  ch = strtok(NULL, "\"");
  return strdup(ch);
}

char* fetch_word()
{
  char buffer[BUF_LEN+1] = {0};
  int out_pipe[2];
  int saved_stdout;

  saved_stdout = dup(STDOUT_FILENO);
  if(pipe(out_pipe))
  {
    perror("Error creating pipe");
    return NULL;
  }

  dup2(out_pipe[1], STDOUT_FILENO);
  close(out_pipe[1]);

  api_call();
  fflush(stdout);

  read(out_pipe[0], buffer, BUF_LEN);
  dup2(saved_stdout, STDOUT_FILENO);
  return parse_json(buffer);
}