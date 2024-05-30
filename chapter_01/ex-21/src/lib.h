#include <stdbool.h>

int read_line(char buffer[], int size);
int str_len(char buffer[]);

bool space(char c);
bool tab(char c);
bool blank(char c);
bool blank_sequence(char prev, char cur);

typedef struct {
  int total_spaces;
  int total_tabs;
  int total_sequences;
  int longest_sequence;
  int total_spaces_in_longest_sequence;
  int total_tabs_in_longest_sequence;
} Counts;

Counts counts_new();
char* counts_to_str(Counts counts);

Counts count_blanks(char buffer[]);
