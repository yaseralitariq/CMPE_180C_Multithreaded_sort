# CMPE_180C_Multithreaded_sort
•	The multi-threaded sort uses multiple CPU cores as multiple threads to sort an array faster than one CPU core. The following steps are followed by the multi-threading sort algorithm:
a.	Divide array into equal-sized groups equal to the number of threads
b.	Use either quick sort or merge sort on each group (one thread per group)
i.	Merge sort is used if a stable sort is required.  A stable sort preserves the order of ties.
ii.	Quick sort is faster but is not a stable sort.
c.	Merge the sorted groups together using a bottom-up merge sort approach.
i.	The final merge of the sorted groups can be done by merging the sorted groups as soon as a pair is finished using a single-threaded merge
