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
 
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t real_size = size * nmemb;
  t_curl_data *mem = (struct s_curl_data *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + real_size + 1);
  if(!ptr)
  {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, real_size);
  mem->size += real_size;
  mem->memory[mem->size] = 0;
 
  return real_size;
}

void configure_curl(CURL *curl, t_curl_data* chunk)
{
  char url[BUFFER_SIZE];
  snprintf(url, BUFFER_SIZE, WORDLE_URL, WORD_SIZE, DIFFICULTY);
  
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
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
  CURL *curl;
  CURLcode result;
  t_curl_data chunk = {0};
  char* word = strdup("NOCON");

  curl = curl_easy_init();
  if (!curl)
    return word;

  configure_curl(curl, &chunk);

  result = curl_easy_perform(curl);
  if(result != CURLE_OK)
    curl_error(result);

  curl_easy_cleanup(curl);

  if (chunk.size)
  {
    free(word);
    word = parse_json(chunk.memory);
  }
  return word;
}