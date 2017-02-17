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

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "SDL_config.h"

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"
#include "../SDL_thread_c.h"
#include <3ds.h>

#define CURRENT_KTHREAD 0xFFFF8000
#define STACKSIZE       (4 * 1024)
#define APPCORE_CPUID   0

void ThreadEntry(void *arg)
{
	SDL_RunThread(arg);
	//svcExitThread();
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
	s32 priority = 0x2F;

	/* Set priority of new thread to the same as the current thread */
	//svcGetThreadPriority(&priority, CURRENT_KTHREAD);
	thread->handle = threadCreate(ThreadEntry, args,
		STACKSIZE, priority, -2, false);
	/*if (thread->handle == NULL) {
		SDL_SetError("Thread creation failed");
		return -1;
	}*/

	return 0;
}

void SDL_SYS_SetupThread(void)
{
	 //Nothing, probably
}

Uint32 SDL_ThreadID(void)
{
	//Incompatible with SDL API, this function will NOT return
	//a valid thread ID when called from the main thread.
	Thread current = threadGetCurrent();
	Handle handle = threadGetHandle(current);
	u32 threadID;
	svcGetThreadId(&threadID, handle);

	return threadID;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
	threadJoin(thread->handle, U64_MAX);
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
	threadFree(thread->handle);
}

