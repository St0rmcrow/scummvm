/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004 Ivan Dubrov
 * Copyright (C) 2004-2005 The ScummVM project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * aint32 with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */
#ifndef GOB_PARSE_H
#define GOB_PARSE_H

namespace Gob {

int16 parse_parseExpr(char stopToken, byte *resultPtr);
void parse_skipExpr(char stopToken);
int16 parse_parseValExpr(void);
int16 parse_parseVarIndex(void);
void parse_printExpr(char stopToken);
void parse_printVarIndex(void);

}				// End of namespace Gob

#endif
