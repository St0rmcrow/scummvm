/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#if defined(DYNAMIC_MODULES) && defined(_WIN32)

#include "backends/plugins/win32/win32-provider.h"
#include "backends/plugins/dynamic-plugin.h"
#include "common/fs.h"

#include <windows.h>

#define PLUGIN_DIRECTORY	""
#define PLUGIN_PREFIX		""
#define PLUGIN_SUFFIX		".dll"


class Win32Plugin : public DynamicPlugin {
private:
	static const TCHAR* toUnicode(const char *x) {
	#ifndef _WIN32_WCE
		return (const TCHAR *)x;
	#else
		static TCHAR unicodeString[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, x, strlen(x) + 1, unicodeString, sizeof(unicodeString) / sizeof(TCHAR));
		return unicodeString;
	#endif
	}


protected:
	void *_dlHandle;
	Common::String _filename;

	virtual VoidFunc findSymbol(const char *symbol) {
		#ifndef _WIN32_WCE
		void *func = (void *)GetProcAddress((HMODULE)_dlHandle, symbol);
		#else
		void *func = (void *)GetProcAddress((HMODULE)_dlHandle, toUnicode(symbol));
		#endif
		if (!func)
			debug("Failed loading symbol '%s' from plugin '%s'", symbol, _filename.c_str());
	
		// FIXME HACK: This is a HACK to circumvent a clash between the ISO C++
		// standard and POSIX: ISO C++ disallows casting between function pointers
		// and data pointers, but dlsym always returns a void pointer. For details,
		// see e.g. <http://www.trilithium.com/johan/2004/12/problem-with-dlsym/>.
		assert(sizeof(VoidFunc) == sizeof(func));
		VoidFunc tmp;
		memcpy(&tmp, &func, sizeof(VoidFunc));
		return tmp;
	}

public:
	Win32Plugin(const Common::String &filename)
		: _dlHandle(0), _filename(filename) {}

	bool loadPlugin() {
		assert(!_dlHandle);
		#ifndef _WIN32_WCE
		_dlHandle = LoadLibrary(_filename.c_str());
		#else
		if (!_filename.hasSuffix("scummvm.dll"))	// skip loading the core scummvm module
			_dlHandle = LoadLibrary(toUnicode(_filename.c_str()));
		#endif
	
		if (!_dlHandle) {
			debug("Failed loading plugin '%s' (error code %d)", _filename.c_str(), (int32) GetLastError());
			return false;
		} else {
			debug(1, "Success loading plugin '%s', handle %08X", _filename.c_str(), (uint32) _dlHandle);
		}

		return DynamicPlugin::loadPlugin();
	}
	void unloadPlugin() {
		if (_dlHandle) {
			if (!FreeLibrary((HMODULE)_dlHandle))
				debug("Failed unloading plugin '%s'", _filename.c_str());
			else
				debug(1, "Success unloading plugin '%s'", _filename.c_str());
			_dlHandle = 0;
		}
	}
};


Win32PluginProvider::Win32PluginProvider() {
}

Win32PluginProvider::~Win32PluginProvider() {
}

PluginList Win32PluginProvider::getPlugins() {
	PluginList pl;
	
	
	// Load dynamic plugins
	// TODO... this is right now just a nasty hack.
	// This should search one or multiple directories for all plugins it can
	// find (to this end, we maybe should use a special prefix/suffix; e.g.
	// instead of libscumm.so, use scumm.engine or scumm.plugin etc.).
	//
	// The list of directories to search could be e.g.:
	// User specified (via config file), ".", "./plugins", "$(prefix)/lib".
	//
	// We also need to add code which ensures what we are looking at is
	// a) a ScummVM engine and b) matches the version of the executable.
	// Hence one more symbol should be exported by plugins which returns
	// the "ABI" version the plugin was built for, and we can compare that
	// to the ABI version of the executable.

	// Load all plugins.
	// Scan for all plugins in this directory
	FilesystemNode dir(PLUGIN_DIRECTORY);
	FSList files;
	if (!dir.getChildren(files, FilesystemNode::kListFilesOnly)) {
		error("Couldn't open plugin directory '%s'", PLUGIN_DIRECTORY);
	}

	for (FSList::const_iterator i = files.begin(); i != files.end(); ++i) {
		Common::String name(i->getName());
		if (name.hasPrefix(PLUGIN_PREFIX) && name.hasSuffix(PLUGIN_SUFFIX)) {
			pl.push_back(new Win32Plugin(i->getPath()));
		}
	}
	
	
	return pl;
}


#endif // defined(DYNAMIC_MODULES) && defined(_WIN32)
