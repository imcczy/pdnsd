/* list.h - Dynamic array and list handling
 * Copyright (C) 2001 Thomas Moestl
 *
 * This file is part of the pdnsd package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* $Id */

#ifndef LIST_H
#define LIST_H

/*
 * The size of this should always be a multiple of 4 on all supported architectures.
 * Otherwise, we need further glue.
 */
struct darray_head {
	int tpsz;	/* size of the type we hold (including padding) */
	int nel;	/* number of elements in array */
	int ael;	/* number of allocated elements */
	int dummy;	/* dummy for alignment */
};

typedef struct darray_head *darray;

/*
 * This will work for i386 and alpha. If someday we support and architecture
 * with different alignment needs, this needs to be fixed.
 */
#define DA_ALIGNSZ(sz) (((((sz)-1)/8)+1)*8)

#define DA_CREATE(tp) (da_create(sizeof(tp)))
#define DA_INDEX(a,i,tp) ((tp *)(da_index(a,i)))
/* Used often, so make special-case macro here */
#define DA_LAST(a, tp) ((tp *)(da_index(a, (a)->nel-1)))

/*
 * Some or all of these should be inline.
 * They aren't macros for type safety.
 */
darray da_create(int sz);
darray da_grow(darray a, int n);
darray da_resize(darray a, int n);
char *da_index(darray a, int i);
int da_nel(darray a);
void da_free(darray a);

/* Number of elements to over-allocate by default */
#define DA_PREALLOC	5

#endif /* def LIST_H */