#include <stdbool.h>

int read_line(char buffer[], int size);
int str_len(char buffer[]);

bool space(char c);
bool tab(char c);
bool blank(char c);
bool blank_sequence(char prev, char cur);

typedef struct {
  int string_length;
  int total_spaces;
  int total_tabs;
  int total_sequences;
  int shortest_sequence;
  int shortest_sequence_total_spaces;
  int shortest_sequence_total_tabs;
} Counts;

Counts counts_new();
char* counts_to_str(Counts counts);

Counts count_blanks(char buffer[]);

int get_tab_stop(Counts counts, int spaces_per_tab);
int get_buffer_size(Counts counts, int spaces_per_tab);

void entab(char from[], char to[], int tab_stop);
