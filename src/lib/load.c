/*****************************************************************************
 * pce                                                                       *
 *****************************************************************************/

/*****************************************************************************
 * File name:     src/lib/load.c                                             *
 * Created:       2004-08-02 by Hampa Hug <hampa@hampa.ch>                   *
 * Last modified: 2004-08-02 by Hampa Hug <hampa@hampa.ch>                   *
 * Copyright:     (C) 2004 Hampa Hug <hampa@hampa.ch>                        *
 *****************************************************************************/

/*****************************************************************************
 * This program is free software. You can redistribute it and / or modify it *
 * under the terms of the GNU General Public License version 2 as  published *
 * by the Free Software Foundation.                                          *
 *                                                                           *
 * This program is distributed in the hope  that  it  will  be  useful,  but *
 * WITHOUT  ANY   WARRANTY,   without   even   the   implied   warranty   of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  General *
 * Public License for more details.                                          *
 *****************************************************************************/

/* $Id$ */


#include <stdlib.h>
#include <stdio.h>

#include "ihex.h"
#include "load.h"


int pce_load_blk_bin (mem_blk_t *blk, const char *fname)
{
  FILE *fp;

  fp = fopen (fname, "rb");
  if (fp == NULL) {
    return (1);
  }

  fread (blk->data, 1, blk->size, fp);

  fclose (fp);

  return (0);
}

int pce_load_mem_hex (memory_t *mem, const char *fname)
{
  int  r;
  FILE *fp;

  fp = fopen (fname, "rb");
  if (fp == NULL) {
    return (1);
  }

  r = ihex_load_fp (fp, mem, (ihex_set_f) &mem_set_uint8_rw);

  fclose (fp);

  return (r);
}

int pce_load_mem_bin (memory_t *mem, const char *fname, unsigned long base)
{
  int  c;
  FILE *fp;

  fp = fopen (fname, "rb");
  if (fp == NULL) {
    return (1);
  }

  c = fgetc (fp);
  while (c != EOF) {
    mem_set_uint8 (mem, base, c & 0xff);
    base += 1;
    c = fgetc (fp);
  }

  fclose (fp);

  return (0);
}