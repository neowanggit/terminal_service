#include <stdio.h>
#include <string.h>
#include "terminals.h"

/* search terminal array, return the index of first unused one
  if not found, return -1 */
int get_free_terminal(terminal *terminals){
    if (!terminals) {
        return -1;
    }

    for (int i=0; i<MAX_TERMINALS; i++){
        if ( !terminals[i].used ) {
            return i;
        }
    }
    return -1;
}

/*
    update the element attribute_str, set used to true(1)
    return 0 on success, otherwise return -1
*/
int update_terminal_attribute(terminal *terminals, int index, char *attribute){
    if ((index < 0) || (index >= MAX_TERMINALS)) {
        return -1;
    }

    int len = strlen(attribute);
    if (!attribute || len > MAX_ATTRIBUTES_LEN) {
        return -1;
    }

    memcpy(terminals[index].attributes_str, attribute, len);
    terminals[index].used = 1;
    return 0;
}

/*
    get the attribute string of the terminal by index, terminal must be used.
    otherwise return NULL.
*/
char *get_terminal_attribute(terminal *terminals, int index) {
    if (!terminals || (index<0) || (index>=MAX_TERMINALS) ) {
        return NULL;
    }
    if ( !terminals[index].used ) {
        return NULL;
    }
    return terminals[index].attributes_str;
}