#include "wordle.h"
#include <curl/curl.h>

char errbuf[CURL_ERROR_SIZE];

void curl_error(CURLcode result)
{
  size_t len = strlen(errbuf);
  fprintf(stderr, "libcurl error: (%d) ", result);
  if(len)
    fprintf(stderr, "%s%s", errbuf,
            ((errbuf[len - 1] != '\n') ? "\n" : ""));
  else
    fprintf(stderr, "%s\n", curl_easy_strerror(result));
}

int api_call()
{
  int res_code = 0;

  CURL *client = curl_easy_init();
  if (!client) return 1;

  curl_easy_setopt(client, CURLOPT_URL, WORDLE_URL);
  curl_easy_setopt(client, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(client, CURLOPT_ERRORBUFFER, errbuf);

  CURLcode result = curl_easy_perform(client);
  if(result != CURLE_OK)
  {
    curl_error(result);
    res_code = 1;
  }

  curl_easy_cleanup(client);
  return res_code;
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
  char buffer[BUFFER_SIZE + 1] = {0};
  char* word = NULL;
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

  if (api_call())
  {
    memcpy(buffer, "NOCON", sizeof(buffer));
    dup2(saved_stdout, STDOUT_FILENO);
    word = strdup(buffer);
  }
  else
  {
    fflush(stdout);
    read(out_pipe[0], buffer, BUFFER_SIZE);
    word = parse_json(buffer);
  }
  dup2(saved_stdout, STDOUT_FILENO);
  return word;
}