#ifndef CNAKE_UTILS_H
#define CNAKE_UTILS_H

/* Get the maximum value for any integer type */
#define MAX_VALUE(type)                                                        \
  ({                                                                           \
    (type) - 1 < 0 ? ((1ULL << (sizeof(type) * 8)) - 1) / 2                    \
                   : (1ULL << (sizeof(type) * 8)) - 1;                         \
  })

/* Get the minimum value for any integer type */
#define MIN_VALUE(type)                                                        \
  ({ (type) - 1 < 0 ? -(((1ULL << (sizeof(type) * 8)) - 1) / 2) : 0; })

#endif
