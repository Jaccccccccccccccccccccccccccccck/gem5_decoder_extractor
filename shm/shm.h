#ifndef __SHM_SLIM_H__
#define __SHM_SLIM_H__

#include <stdint.h>
#include <stdbool.h>

typedef unsigned long shm_offt;

#ifdef __cplusplus
extern "C" {
#endif
	int shm_init(void*, char *shm_filename);
	void shm_deinit(void);

	void * get_shm_user_base(void);

	shm_offt shm_malloc(size_t size);
	shm_offt shm_calloc(size_t count, size_t size);
	void     shm_free(shm_offt shm_ptr);
#ifdef __cplusplus
}
#endif

#define SHM_OFFT_TO_ADDR(offset) ((void *)((uint8_t *)get_shm_user_base() + offset))

#define SHM_ADDR_TO_OFFT(address) ((shm_offt)((uint8_t *)address - (uint8_t *)get_shm_user_base()))

#define SHM_NULL ((shm_offt)0)

#endif /* __SHM_SLIM_H__ */
