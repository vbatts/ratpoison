/* Copyright (C) 2000-2003 Shawn Betts
 *
 * This file is part of ratpoison.
 *
 * ratpoison is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * ratpoison is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA
 */

#include "ratpoison.h"

int
screen_width (rp_screen *s)
{
  return DisplayWidth (dpy, s->screen_num) - defaults.padding_right - defaults.padding_left;
}

int
screen_height (rp_screen *s)
{
  return DisplayHeight (dpy, s->screen_num) - defaults.padding_bottom - defaults.padding_top;
}

int
screen_left (rp_screen *s)
{
  return defaults.padding_left;
}

int
screen_right (rp_screen *s)
{
  return screen_left (s) + screen_width (s);
}

int
screen_top (rp_screen *s)
{
  return defaults.padding_top;
}

int
screen_bottom (rp_screen *s)
{
  return screen_top (s) + screen_height (s);
}

/* Returns a pointer to a list of frames. */
struct list_head *
screen_copy_frameset (rp_screen *s)
{
  struct list_head *head;
  rp_frame *cur;

  /* Init our new list. */
  head = xmalloc (sizeof (struct list_head));
  INIT_LIST_HEAD (head);

  /* Copy each frame to our new list. */
  list_for_each_entry (cur, &s->frames, node)
    {
      list_add_tail (&(frame_copy (cur))->node, head);
    }

  return head;
}

/* Set head as the frameset, deleting the existing one. */
void
screen_restore_frameset (rp_screen *s, struct list_head *head)
{
  frameset_free (&s->frames);
  INIT_LIST_HEAD (&s->frames);

  /* Hook in our new frameset. */
  list_splice (head, &s->frames);
}

/* Given a list of frames, free them, but don't remove their numbers
   from the numset. */
void
frameset_free (struct list_head *head)
{
  rp_frame *frame;
  struct list_head *iter, *tmp;

  list_for_each_safe_entry (frame, iter, tmp, head, node)
    {
      /* FIXME: what if frames has memory inside its struct
	 that needs to be freed? */
      free (frame);
    }
}

rp_frame *
screen_get_frame (rp_screen *s, int frame_num)
{
  rp_frame *cur;

  list_for_each_entry (cur, &s->frames, node)
    {
      if (cur->number == frame_num)
	return cur;
    }
  
  return NULL;
}