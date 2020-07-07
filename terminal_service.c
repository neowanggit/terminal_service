
#include <string.h>

#ifndef _WIN32
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
#endif

#include <ulfius.h>
#include "terminals.h"

#define PORT 8537
#define PREFIX_V1 "/v1"


terminal terminals[MAX_TERMINALS];
/**
 * callback functions declaration
 */

int callback_post_terminals (const struct _u_request * request, struct _u_response * response, void * user_data);

int callback_get_termials_id (const struct _u_request * request, struct _u_response * response, void * user_data);

int callback_get_termials_all (const struct _u_request * request, struct _u_response * response, void * user_data);

int callback_default (const struct _u_request * request, struct _u_response * response, void * user_data);

int main (int argc, char **argv) {
  int ret;

  // Set the framework port number
  struct _u_instance instance;
  
  y_init_logs("terminal management", Y_LOG_MODE_CONSOLE, Y_LOG_LEVEL_DEBUG, NULL, "Starting terminal management");
  
  if (ulfius_init_instance(&instance, PORT, NULL, NULL) != U_OK) {
    y_log_message(Y_LOG_LEVEL_ERROR, "Error ulfius_init_instance, abort");
    return(1);
  }
  
  u_map_put(instance.default_headers, "Access-Control-Allow-Origin", "*");
  
  // Maximum body size sent by the client is 1 Kb
  instance.max_post_body_size = 1024;
  
  // Endpoint list declaration
  ulfius_add_endpoint_by_val(&instance, "POST", PREFIX_V1, "/terminals", 0, &callback_post_terminals, &terminals);
  ulfius_add_endpoint_by_val(&instance, "GET", PREFIX_V1, "/terminals", 0, &callback_get_termials_all, &terminals);
  ulfius_add_endpoint_by_val(&instance, "GET", PREFIX_V1, "/terminals/:id", 0, &callback_get_termials_id, &terminals);
  
  // default_endpoint declaration
  ulfius_set_default_endpoint(&instance, &callback_default, NULL);
  
  // Start the framework

  ret = ulfius_start_framework(&instance);

  if (ret == U_OK) {
    y_log_message(Y_LOG_LEVEL_DEBUG, "Start framework on port %d", instance.port);
    
    // Wait for the user to press <enter> on the console to quit the application
    getchar();
  } else {
    y_log_message(Y_LOG_LEVEL_DEBUG, "Error starting framework");
  }
  y_log_message(Y_LOG_LEVEL_DEBUG, "End framework");
  
  y_close_logs();
  
  ulfius_stop_framework(&instance);
  ulfius_clean_instance(&instance);
  
  return 0;
}

/**
 * Callback function that to allocate a new id, 
 * save terminal attributes, and return back the attribute with allocated id
 */
int callback_post_terminals(const struct _u_request * request, struct _u_response * response, void * user_data) {
  json_t * json_terminal_attributes = ulfius_get_json_body_request(request, NULL), * json_body = NULL;
  int status_code = 200;
  int index;
  int ret;
  terminal *terminals = (terminal *)user_data;

  if (json_terminal_attributes == NULL) {
    status_code = 400;
    json_body = json_object();
    json_object_set_new(json_body, "error", json_string("JSON parse error"));
  } else {
    index = get_free_terminal(terminals); 
    if ( index == -1){
      status_code = 500;
      json_body = json_object();
      json_object_set_new(json_body, "error", json_string("No available terminal"));
    } else {
      json_body = json_deep_copy(json_terminal_attributes);
      json_object_set_new(json_body, "id", json_integer(index));
      char *dump = json_dumps(json_body,0);
      ret = update_terminal_attribute(terminals, index, dump);
      free(dump);
      if (ret !=0){
        status_code = 500;
        json_object_set_new(json_body, "error", json_string("Saving terminal attribute error"));
      } else {
        status_code = 200;
      }
    }
  }
  
  ulfius_set_json_body_response(response, status_code, json_body);
  json_decref(json_terminal_attributes);
  json_decref(json_body);

  return U_CALLBACK_CONTINUE;
}

/**
 * Callback function that get the attribute of terminal by id
 */
int callback_get_termials_id (const struct _u_request * request, struct _u_response * response, void * user_data) {
  json_t * json_body = NULL;
  int status_code = 200;
  terminal *terminals = (terminal *)user_data;

  const char *id_str = u_map_get(request->map_url, "id");
  int id;
  if (!id_str || (sscanf(id_str,"%d",&id) != 1)) {
    status_code = 400;
    json_body = json_object();
    json_object_set_new(json_body, "error", json_string("id number error"));
  } else {
    char * attribute = get_terminal_attribute(terminals, id);
    if (!attribute) {
      status_code = 400;
      json_body = json_object();
      json_object_set_new(json_body, "error", json_string("terminal not exist"));
    } else {
      json_body = json_loads(attribute, 0, NULL);
      status_code = 200;
    }
  }
  ulfius_set_json_body_response(response, status_code, json_body);
  json_decref(json_body);

  return U_CALLBACK_CONTINUE;
}

/**
 * Callback function that get list of current allcated terminals
 */
int callback_get_termials_all (const struct _u_request * request, struct _u_response * response, void * user_data) {
  json_t * json_body = NULL;
  int status_code = 200;
  terminal *terminals = (terminal *)user_data;

  json_body = json_array();
  for (int id = 0; id < MAX_TERMINALS; id++) {
    char * attribute = get_terminal_attribute(terminals, id);
    if (attribute) {
      json_array_append_new(json_body, json_loads(attribute, 0, NULL));
    }
  }

  ulfius_set_json_body_response(response, status_code, json_body);
  json_decref(json_body);

  return U_CALLBACK_CONTINUE;
}

/**
 * Default callback function called if no endpoint has a match
 */
int callback_default (const struct _u_request * request, struct _u_response * response, void * user_data) {
  ulfius_set_string_body_response(response, 404, "Page not found");
  return U_CALLBACK_CONTINUE;
}
