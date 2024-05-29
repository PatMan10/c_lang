
int read_line(char buffer[], int size);
int str_len(char buffer[]);

int space(char c);
int tab(char c);
int blank(char c);
int blank_sequence(char prev, char cur);

typedef struct {
  int total_spaces;
  int total_tabs;
  int total_sequences;
  int longest_sequence;
  int total_spaces_in_longest_sequence;
  int total_tabs_in_longest_sequence;
} Counts;

Counts counts_new();

void count_blanks(char buffer[], int counts[5]);
