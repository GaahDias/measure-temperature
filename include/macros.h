#define try(t) if (t != NULL)
#define panic(args...)                                                               \
  printf(BRED "Exception " RESET args );                                     \
  exit(1)
#define forEach(item, array) \
    for(int keep = 1, \
            count = 0,\
            size = sizeof (array) / sizeof *(array); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (array) + count; keep; keep = !keep)
#define success(args...) printf(BGRN "Success " RESET args)
#define message(args...) printf(BCYN "Message " RESET args)
#define warn(args...)    printf(BYEL "Warn " RESET args)
