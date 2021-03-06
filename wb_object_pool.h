#ifndef __CELL_POOL_H_
#define __CELL_POOL_H_

#include <stdint.h>
#include "wb_spin_lock.h"

/*对象初始化函数指针*/
typedef int32_t(*ob_constructor_t)(void* ob);
/*对象撤销函数指针*/
typedef void(*ob_destructor_t)(void* ob);
/*合法性校验函数指针*/
typedef int32_t(*ob_check_t)(void* ob);
/*对象复位函数指针*/
typedef void(*ob_reset_t)(void* ob, int32_t flag);

typedef struct CACHE_ALIGN cell_pool_s
{
	void**				ptr;		/*object array*/
	size_t				ob_size;	/*对象占用的空间字节数*/

	spin_lock_t			mutex;		/*latch*/
	int32_t				array_size;	/*ptr数组的长度*/
	int32_t				curr;		/*当前空闲的ptr位置*/

	ob_constructor_t	constructor; /*对象初始化函数指针*/
	ob_destructor_t		destructor;	/*对象撤销回收函数指针*/
	ob_check_t			check;		
	ob_reset_t			reset;

	char*				name;		/*pool name*/
}cell_pool_t;

cell_pool_t*			pool_create(const char* name, size_t ob_size, size_t array_size, ob_constructor_t constructor, ob_destructor_t destructor, 
										ob_check_t check, ob_reset_t reset);

void					pool_destroy(cell_pool_t* pool);

void*					pool_alloc(cell_pool_t* pool);

void					pool_free(cell_pool_t* pool, void* ob);

void					pool_print(cell_pool_t* pool);

int32_t					get_pool_info(cell_pool_t* pool, char* buf);

#endif





