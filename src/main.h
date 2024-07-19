#include <inttypes.h>
#include <stdbool.h>
#define MAX_INPUT_LEN 100

enum exit_code {
  all_fine = 0,
  no_parameters = -1,
  many_parameters = -2,
  parameter_twice = -3,
  two_incorrect_parameters = -4,
};

typedef struct {
  bool from_exists;
  bool to_exists;
  int64_t from;
  int64_t to;
} bounds_t;

void insertion_sort(int64_t *array, uint8_t len);

bounds_t *bounds_init();

void arg_check(bounds_t *bounds, char *argument, int8_t *exit_code);

bounds_t *parse_commandline_args(int argc, char *argv[], int8_t *exit_code);

void parse_input(bounds_t *bounds, int8_t *exit_code);
