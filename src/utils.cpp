#include <utils.hpp>

#define MAX_TOKENS 10

int split(char *data, char delimiter, char *tokens) {
  int tokenIndex = 0;

  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] != delimiter) { // 구분자 아닌 경우만 저장
      tokens[tokenIndex++] = data[i];
      if (tokenIndex >= MAX_TOKENS) break; // 토큰 최대 초과 방지
    }
  }
  return tokenIndex; // 저장된 토큰 수 반환
}

