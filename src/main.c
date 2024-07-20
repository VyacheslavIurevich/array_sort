#include "main.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void insertion_sort(int64_t *array, uint8_t len);

bounds_t *bounds_init() {
  bounds_t *bounds = (bounds_t *)malloc(sizeof(bounds_t));

  bounds->from_exists = false;
  bounds->to_exists = false;
  bounds->from = 0;
  bounds->to = 0;

  return bounds;
}

static void arg_check(bounds_t *bounds, char *argument, int8_t *exit_code) {

  if (strncmp(argument, "--from=", 7) == 0) {
    if (bounds->from_exists == true)
      *exit_code = parameter_twice;
    bounds->from_exists = true;
    bounds->from = atoll(argument + 7);
  } else {
    if (strncmp(argument, "--to=", 5) == 0) {
      if (bounds->to_exists)
        *exit_code = parameter_twice;
      bounds->to_exists = true;
      bounds->to = atoll(argument + 5);
    }
  }
}

static bounds_t *parse_commandline_args(int argc, char *argv[],
                                        int8_t *exit_code) {
  bounds_t *bounds = NULL;

  if (argc < 2)
    *exit_code = no_parameters;
  else if ((argc == 2) || (argc == 3)) {
    bounds = bounds_init(bounds);
    arg_check(bounds, argv[1], exit_code);
    if (argc == 3)
      arg_check(bounds, argv[2], exit_code);
    if ((!bounds->from_exists) && (!bounds->to_exists))
      *exit_code = two_incorrect_parameters;
  } else
    *exit_code = many_parameters;

  return bounds;
}

static void parse_input(bounds_t *bounds, int8_t *exit_code) {
  int64_t curr_num, to_sort[MAX_INPUT_LEN], to_compare[MAX_INPUT_LEN];
  uint8_t i = 0, j, cnt = 0;
  bool first_out = true, first_err = true;
  while (scanf("%ld", &curr_num) == 1) {
    if ((bounds->from_exists) && (curr_num <= bounds->from)) {
      if (first_out) {
        printf("%ld", curr_num);
        first_out = false;
      } else
        printf(" %ld", curr_num);
    }
    if ((bounds->to_exists) && (curr_num >= bounds->to)) {
      if (first_err) {
        fprintf(stderr, "%ld", curr_num);
        first_err = false;
      } else
        fprintf(stderr, " %ld", curr_num);
    }
    if ((!bounds->from_exists) ||
        ((bounds->from_exists) && (curr_num > bounds->from))) {
      if ((!bounds->to_exists) ||
          ((bounds->to_exists) && (curr_num < bounds->to))) {
        to_compare[i] = curr_num;
        to_sort[i++] = curr_num;
      }
    }
  }
  if (i) {
    insertion_sort(to_sort, i);
    for (j = 0; j < i; ++j) {
      if (to_sort[j] != to_compare[j])
        ++cnt;
    }
    *exit_code = cnt;
  }
}

int main(int argc, char *argv[]) {
  int8_t exit_code = all_fine;

  bounds_t *bounds = parse_commandline_args(argc, argv, &exit_code);
  if (exit_code == all_fine)
    parse_input(bounds, &exit_code);

  if (bounds)
    free(bounds);

  return exit_code;
}
