// #include <utils.hpp>

// #define MAX_TOKENS 10

// 문자열을 구분자로 나누는 함수 (2차원 배열 사용)
int split(char *data, char delimiter, char tokens[][10]) {
  int tokenIndex = 0, charIndex = 0;
  for (int i = 0; data[i] != '\0'; i++) {
    if (data[i] == delimiter) {
      tokens[tokenIndex][charIndex] = '\0';
      tokenIndex++;
      charIndex = 0;
    } else {
      tokens[tokenIndex][charIndex++] = data[i];
      if (charIndex >= 9) break; // 토큰 최대 길이 방지
    }
  }
  tokens[tokenIndex][charIndex] = '\0';
  return tokenIndex + 1; // 토큰 개수 반환
}
