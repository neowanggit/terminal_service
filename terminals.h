#ifndef __TERMINALS_H__
#define __TERMINALS_H__
#define MAX_TERMINALS 10

#define MAX_ATTRIBUTES_LEN 256

typedef struct {
    int used;
    char attributes_str[MAX_ATTRIBUTES_LEN];
} terminal;

/* 
  search terminal array, return the index of first unused one
  if not found, return -1 
*/

int get_free_terminal(terminal *terminals);

/*
    update the element attribute_str, set used to true(1)
    return 0 on success, otherwise return -1
*/
int update_terminal_attribute(terminal *terminals, int index, char *attribute);

/*
    get the attribute string of the terminal by index, terminal must be used.
    otherwise return NULL.
*/
char *get_terminal_attribute(terminal *terminals, int index);

#endif