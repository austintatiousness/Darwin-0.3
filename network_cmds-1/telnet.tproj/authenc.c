/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*-
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef lint
static char sccsid[] = "@(#)authenc.c	8.1 (Berkeley) 6/6/93";
#endif /* not lint */

#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
#include <sys/types.h>
#include <arpa/telnet.h>
#include <libtelnet/encrypt.h>
#include <libtelnet/misc.h>

#include "general.h"
#include "ring.h"
#include "externs.h"
#include "defines.h"
#include "types.h"

	int
net_write(str, len)
	unsigned char *str;
	int len;
{
	if (NETROOM() > len) {
		ring_supply_data(&netoring, str, len);
		if (str[0] == IAC && str[1] == SE)
			printsub('>', &str[2], len-2);
		return(len);
	}
	return(0);
}

	void
net_encrypt()
{
#ifdef	ENCRYPTION
	if (encrypt_output)
		ring_encrypt(&netoring, encrypt_output);
	else
		ring_clearto(&netoring);
#endif	/* ENCRYPTION */
}

	int
telnet_spin()
{
	return(-1);
}

	char *
telnet_getenv(val)
	char *val;
{
	return((char *)env_getvalue((unsigned char *)val));
}

	char *
telnet_gets(prompt, result, length, echo)
	char *prompt;
	char *result;
	int length;
	int echo;
{
	extern char *getpass();
	extern int globalmode;
	int om = globalmode;
	char *res;

	TerminalNewMode(-1);
	if (echo) {
		printf("%s", prompt);
		res = fgets(result, length, stdin);
	} else if (res = getpass(prompt)) {
		strncpy(result, res, length);
		res = result;
	}
	TerminalNewMode(om);
	return(res);
}
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION) */