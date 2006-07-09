/* ScummVMDS - Scumm Interpreter DS Port
 * Copyright (C) 2002-2004 The ScummVM project and Neil Millstone
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
 
 #ifndef _CDAUDIO_H_
#define _CDAUDIO_H_

namespace DS {
namespace CD {

void setActive(bool active);
void playTrack(int track, int numLoops, int startFrame, int duration);
void stopTrack();
bool checkCD();
bool getActive();
bool isPlaying();
void update();

}
}

#endif
/* ScummVMDS - Scumm Interpreter DS Port
 * Copyright (C) 2002-2004 The ScummVM project and Neil Millstone
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
 
 #ifndef _CDAUDIO_H_
#define _CDAUDIO_H_

namespace DS {
namespace CD {

void setActive(bool active);
void playTrack(int track, int numLoops, int startFrame, int duration);
void stopTrack();
bool checkCD();
bool getActive();
bool isPlaying();
void update();

}
}

#endif
