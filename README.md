# nostdlib

> Attention: For now, this library is just for fun.

The motivation behind this project is to try and imagine different API designs
for the C standard library.

`libc`'s problems:

  - Error handling: We can get return codes from some functions in `libc`, as
  well as the number of bytes written to a buffer and the setting of the global
  `errno` variable, among other things.
  - Inconsistent naming.

Here, I will try to address these issues. Once again, this is all just for
*learning* and *fun* purposes.
