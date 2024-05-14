
int read_line(char buffer[], int size);
int str_len(char buffer[]);

int space(char c);
int tab(char c);
int blank(char c);
int blank_seq(char prev, char cur);

void count_blanks(char buffer[], int counts[5]);
