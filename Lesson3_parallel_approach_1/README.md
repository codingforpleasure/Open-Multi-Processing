The first parallel approach is introduced here in the code,
I have declared array of 4 cells, each thread operates indepently and does the task,
eventualy on the last phase we traverse over the array of partial results and summerise them.

BUT suprsingly the runtime of the program falls back behind, it doesn't scale well.
The reason for this is "False Sharing", since the 4 array elements are stored in cache1 line,
and each time we fetch the . We are not sharing any data among the cores,
and since the array is stored on the cache we get a bouncing effect.

Here is a great explanation thaken from Wikipedia:
"By far the most common usage of this term is in modern multiprocessor CPU caches,
where memory is cached in lines of some small power of two word size (e.g., 64 aligned, contiguous bytes).
If two processors operate on independent data in the same memory address region storable in a single line,
the cache coherency mechanisms in the system may force the whole line across the bus or interconnect with every data write,
forcing memory stalls in addition to wasting system bandwidth.
False sharing is an inherent artifact of automatically synchronized cache protocols and can also exist in environments
such as distributed file system or databases, but current prevalence is limited to RAM caches."
