#ifndef H_ARRAY_H
#define H_ARRAY_H

#include "xmalloc.h"
#include <stdio.h>

/* 
	Vector functions
 */
#define make_vector(v,n) ((v) = xmalloc((n) * sizeof *(v)))

#define free_vector(v) do { free(v); v = NULL; } while (0)

// prints an n-length vector v using format fmt (string formatting each value)
#define print_vector(fmt, v, n) do {						\
	size_t print_vector_loop_counter;						\
	for (print_vector_loop_counter = 0;						\
			print_vector_loop_counter < (n);				\
			print_vector_loop_counter++)					\
			printf(fmt, (v)[print_vector_loop_counter]);	\
	putchar('\n');											\
} while (0)

/* 
	Matrix functions
 */
#define make_matrix(a, m, n) do { 							\
	size_t make_matrix_loop_counter;						\
	make_vector(a, (m) + 1);								\
	for (make_matrix_loop_counter = 0;						\
	make_matrix_loop_counter < (m);							\
	make_matrix_loop_counter++)								\
		make_vector((a)[make_matrix_loop_counter], (n));	\
	(a)[m] = NULL;											\
} while (0)

#define free_matrix(a) do {									\
	if (a != NULL) {										\
		size_t make_matrix_loop_counter;					\
		for (make_matrix_loop_counter = 0;					\
		(a)[make_matrix_loop_counter] != NULL;				\
		make_matrix_loop_counter++)							\
		free_vector((a)[make_matrix_loop_counter]);	 		\
		free_vector(a);										\
		a = NULL;											\
	}														\
} while (0)

// prints an n x m matrix a using format fmt (string formatting each value)
#define print_matrix(fmt, a, n, m) do {						\
	size_t print_matrix_loop_counter;						\
	for (print_matrix_loop_counter = 0;						\
			print_matrix_loop_counter < (n);				\
			print_matrix_loop_counter++)					\
		print_vector(fmt, (a)[print_matrix_loop_counter], m);\
	putchar('\n');											\
} while (0)




/* 
	3-Array functions
 */
#define make_3array(a, n, m, k) do { 						\
	size_t make_3array_loop_counter;						\
	make_vector(a, (k) + 1);								\
	for (make_3array_loop_counter = 0;						\
	make_3array_loop_counter < (k);							\
	make_3array_loop_counter++)								\
		make_matrix((a)[make_3array_loop_counter], (n), (m));	\
	(a)[k] = NULL;											\
} while (0)

#define free_3array(a) do {									\
	if (a != NULL) {										\
		size_t make_3array_loop_counter;					\
		for (make_3array_loop_counter = 0;					\
		(a)[make_3array_loop_counter] != NULL;				\
		make_3array_loop_counter++)							\
			free_matrix((a)[make_3array_loop_counter]);	 	\
		free_vector(a);										\
		a = NULL;											\
	}														\
} while (0)

// prints an n-length 3array v using format fmt (string formatting each value)
#define print_3array(fmt, a, n, m, k) do {						\
	size_t print_3array_loop_counter;						\
	for (print_3array_loop_counter = 0;						\
			print_3array_loop_counter < (k);				\
			print_3array_loop_counter++)					\
			print_matrix(fmt, (a)[print_3array_loop_counter], (n), (m));	\
	putchar('\n');											\
} while (0)


/* 
	4-Array functions
 */
#define make_4array(a, m, n, k, i) do { 							\
	size_t make_4array_loop_counter;						\
	make_vector(a, (i) + 1);								\
	for (make_4array_loop_counter = 0;						\
	make_4array_loop_counter < (i);							\
	make_4array_loop_counter++)								\
		make_3array((a)[make_4array_loop_counter], (m), (n), (k));	\
	(a)[i] = NULL;											\
} while (0)

#define free_4array(a) do {									\
	if (a != NULL) {										\
		size_t make_4array_loop_counter;					\
		for (make_4array_loop_counter = 0;					\
		(a)[make_4array_loop_counter] != NULL;				\
		make_4array_loop_counter++)							\
			free_3array((a)[make_4array_loop_counter]);		\
		free_vector(a);										\
		a = NULL;											\
	}														\
} while (0)

// prints an (m x n x k x i) 4array a using format fmt (string formatting each value)
#define print_4array(fmt, a, m, n, k, i) do {						\
	size_t print_4array_loop_counter;						\
	for (print_4array_loop_counter = 0;						\
			print_4array_loop_counter < (i);				\
			print_4array_loop_counter++)					\
		print_3array(fmt, (a)[print_4array_loop_counter], (m), (n), (k));\
	putchar('\n');											\
} while (0)

#endif
