/*
 Copyright (C) 1999-2004 IC & S  dbmail@ic-s.nl

 This program is free software; you can redistribute it and/or 
 modify it under the terms of the GNU General Public License 
 as published by the Free Software Foundation; either 
 version 2 of the License, or (at your option) any later 
 version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

/* $Id: imap4.h 1891 2005-10-03 10:01:21Z paul $
 * 
 * imap4.h
 */

#ifndef _IMAP4_H
#define _IMAP4_H

#include "dbmail.h"

#define IMAP_SERVER_VERSION VERSION
//#define IMAP_CAPABILITY_STRING "IMAP4 IMAP4rev1 AUTH=LOGIN ACL NAMESPACE SORT"
#define IMAP_CAPABILITY_STRING "IMAP4 IMAP4rev1 AUTH=LOGIN ACL NAMESPACE"
#define IMAP_TIMEOUT_MSG "* BYE dbmail IMAP4 server signing off due to timeout\r\n"

/* max number of BAD/NO responses */
#define MAX_FAULTY_RESPONSES 5

/* max number of retries when synchronizing mailbox with dbase */
#define MAX_RETRIES 20

#define null_free(p) { dm_free(p); p = NULL; }


int IMAPClientHandler(clientinfo_t * ci);

typedef struct {
	int itemtype;		/* the item to be fetched */
	int argstart;		/* start index in the arg array */
	int argcnt;		/* number of args belonging to this bodyfetch */
	guint64 octetstart, octetcnt;	/* number of octets to be retrieved */

	char partspec[IMAP_MAX_PARTSPEC_LEN];	/* part specifier (i.e. '2.1.3' */

} body_fetch_t;


typedef struct {
/*  int nbodyfetches;
  body_fetch_t *bodyfetches;
*/
//	body_fetch_t bodyfetch; 
	GList *bodyfetch;

	int noseen;		/* set the seen flag ? */

	/* temporary additions: */
	int setseen;
	int isfirstfetchout;
	/* end temp additions */
	
	int msgparse_needed;
	int hdrparse_needed;

	int getBodyTotal, getBodyTotalPeek;
	int getInternalDate, getFlags, getUID;
	int getMIME_IMB, getEnvelope, getSize;
	int getMIME_IMB_noextension;
	int getRFC822Header, getRFC822Text;
	int getRFC822, getRFC822Peek;
} fetch_items_t;



typedef struct {
	int state;		/* IMAP state of client */
	u64_t userid;		/* userID of client in dbase */
	mailbox_t mailbox;	/* currently selected mailbox */
} imap_userdata_t;

typedef enum {
	IMAP_STORE_FLAG_SEEN,
	IMAP_STORE_FLAG_ANSWERED,
	IMAP_STORE_FLAG_DELETED,
	IMAP_STORE_FLAG_FLAGGED,
	IMAP_STORE_FLAG_DRAFT,
	IMAP_STORE_FLAG_RECENT
} imap_store_flag_t;

#endif
