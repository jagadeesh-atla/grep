#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to escape special characters
char* escape_string(const char* str) {
  if (str == NULL) return NULL;

  // Calculate the new length considering the escape characters
  size_t len = strlen(str);
  size_t new_len = len;
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == '\\' || str[i] == '\"' || str[i] == '\'' || str[i] == '\n' ||
        str[i] == '\t') {
      new_len++;
    }
  }

  // Allocate memory for the new escaped string
  char* escaped_str = (char*)malloc(new_len + 1);  // +1 for the null terminator
  if (!escaped_str) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  // Build the escaped string
  size_t j = 0;
  for (size_t i = 0; i < len; ++i) {
    switch (str[i]) {
      case '\\':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\\';
        break;
      case '\"':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\"';
        break;
      case '\'':
        escaped_str[j++] = '\\';
        escaped_str[j++] = '\'';
        break;
      case '\n':
        escaped_str[j++] = '\\';
        escaped_str[j++] = 'n';
        break;
      case '\t':
        escaped_str[j++] = '\\';
        escaped_str[j++] = 't';
        break;
      default:
        escaped_str[j++] = str[i];
    }
  }
  escaped_str[j] = '\0';

  return escaped_str;
}

int main() {
  const char* original =
      "This is a test string.\nIt contains \"quotes\", 'single quotes', and "
      "\\backslashes\\.";
  char* escaped = escape_string(original);

  printf("Original: %s\n", original);
  printf("Escaped: %s\n", escaped);

  // Free the allocated memory
  free(escaped);

  return 0;
}