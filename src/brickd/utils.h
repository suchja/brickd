/*
 * brickd
 * Copyright (C) 2012 Matthias Bolte <matthias@tinkerforge.com>
 *
 * utils.h: Utility functions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BRICKD_UTILS_H
#define BRICKD_UTILS_H

#include <stdint.h>

#define ERRNO_WINAPI_OFFSET 71000000
#define ERRNO_WINSOCK2_OFFSET 72000000

int errno_would_block(void);
int errno_interrupted(void);

const char *get_errno_name(int error_code);
const char *get_libusb_error_name(int error_code);
const char *get_libusb_transfer_status_name(int transfer_status);

typedef void (*FreeFunction)(void *item);

typedef struct {
	int allocated;
	int count;
	int size;
	uint8_t *bytes;
} Array;

#define ARRAY_INITIALIZER { 0, 0, 0, NULL }

int array_create(Array *array, int reserved, int size);
void array_destroy(Array *array, FreeFunction function);

int array_reserve(Array *array, int count);
int array_resize(Array *array, int count, FreeFunction function);

void *array_append(Array *array);
void array_remove(Array *array, int i, FreeFunction function);

void *array_get(Array *array, int i);
int array_find(Array *array, void *item);

void base58_encode(char *str, uint32_t value);

#ifdef __GNUC__
	#if __GNUC_PREREQ(4, 4)
		#define ATTRIBUTE_FMT_PRINTF(fmtpos, argpos) \
			__attribute__((__format__(__gnu_printf__, fmtpos, argpos)))
	#else
		#define ATTRIBUTE_FMT_PRINTF(fmtpos, argpos) \
			__attribute__((__format__(__printf__, fmtpos, argpos)))
	#endif
#else
	#define ATTRIBUTE_FMT_PRINTF(fmtpos, argpos)
#endif

#endif // BRICKD_UTILS_H
