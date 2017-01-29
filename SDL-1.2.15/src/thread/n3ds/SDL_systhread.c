/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
	  claim that you wrote the original software. If you use this software
	  in a product, an acknowledgment in the product documentation would be
	  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
	  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
//#include "../../SDL_internal.h"

#if SDL_THREAD_N3DS

/* 3DS thread management routines for SDL */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"
#include "../SDL_thread_c.h"
#include <3ds.h>

#define CURRENT_KTHREAD 0xFFFF8000
#define STACKSIZE       (4 * 1024)
#define APPCORE_CPUID   0

static void ThreadEntry(void *arg)
{
	SDL_RunThread(*(void **) arg);
	svcExitThread();
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
	s32 priority = 0x30;

	/* Set priority of new thread to the same as the current thread */
	//svcGetThreadPriority(&priority, CURRENT_KTHREAD);

	thread->handle.threadStack = memalign(32, STACKSIZE);

	Result res;
	res = svcCreateThread(&thread->handle.threadHandle,
		ThreadEntry, 0, &thread->handle.threadStack[STACKSIZE/4],
		priority, APPCORE_CPUID);

	if (res < 0) {
		return SDL_SetError("svcCreateThread() failed");
	}

	return 0;
}

void SDL_SYS_SetupThread(const char *name)
{
	 /* Do nothing. */
}

SDL_threadID SDL_ThreadID(void)
{
	// return (SDL_threadID) sceKernelGetThreadId();
	return (SDL_threadID)0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
	svcWaitSynchronization(thread->handle.threadHandle, U64_MAX);
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
	 /* !!! FIXME: is this correct? */
	svcCloseHandle(thread->handle.threadHandle);
	free(thread->handle.threadStack);
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
	/*s32 value;

	if (priority == SDL_THREAD_PRIORITY_LOW) {
		value = 0x5;
	} else if (priority == SDL_THREAD_PRIORITY_HIGH) {
		value = 0x3F;
	} else {
		value = 0x20;
	}*/

	//return sceKernelChangeThreadPriority(sceKernelGetThreadId(),value);
	return 0;
}

#endif /* SDL_THREAD_N3DS */

/* vim: ts=4 sw=4
 */
