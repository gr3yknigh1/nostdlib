#ifndef NOSTDLIB_MACROS_H_
#define NOSTDLIB_MACROS_H_

#ifndef NOC_DEF
#define NOC_DEF extern
#endif // NOC_DEF

#ifndef NOC_INLINE
#define NOC_INLINE inline
#endif // NOC_INLINE

#define KEEP(__X) ((void)(__X))
#define NOP ;
#define LITERAL(__X) (__X)

// TODO: Handle MSVC ;C
#define ATTR(__NAME) [[__NAME]]
#define NOC_NODISCARD ATTR(nodiscard)

#define MIN(__X, __Y) (((__X) < (__Y)) ? (__X) : (__Y))
#define MAX(__X, __Y) (((__X) > (__Y)) ? (__X) : (__Y))

#define INRANGE(__MIN, __VALUE, __MAX)                                         \
    ((__MIN) >= (__VALUE) && (__VALUE) <= (__MAX))

#define INRANGE_S(__MIN, __VALUE, __MAX)                                       \
    ((__MIN) >= (__VALUE) && (__VALUE) < (__MAX))

#define EXPAND(__X) (__X)
#define STRINGIFY(__X) #__X

#define CTX(__BEFORE, __AFTER) \
  char __ctx_do_out = 1;       \
  for (KEEP(__BEFORE); __ctx_do_out--; KEEP(__AFTER))


#endif // NOSTDLIB_MACROS_H_
