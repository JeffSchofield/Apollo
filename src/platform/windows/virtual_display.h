#pragma once

#include <functional>

#ifndef FILE_DEVICE_UNKNOWN
#define FILE_DEVICE_UNKNOWN 0x00000022
#endif

#include <ddk/d4iface.h>
#include <ddk/d4drvif.h>
#include <sudovda/sudovda.h>

namespace VDISPLAY {
	enum class DRIVER_STATUS {
		UNKNOWN              = 1,
		OK                   = 0,
		FAILED               = -1,
		VERSION_INCOMPATIBLE = -2,
		WATCHDOG_FAILED      = -3
	};

	extern HANDLE SUDOVDA_DRIVER_HANDLE;

	LONG getDeviceSettings(const wchar_t* deviceName, DEVMODEW& devMode);
	LONG changeDisplaySettings(const wchar_t* deviceName, int width, int height, int refresh_rate);
	std::wstring getPrimaryDisplay();
	bool setPrimaryDisplay(const wchar_t* primaryDeviceName);

	void closeVDisplayDevice();
	DRIVER_STATUS openVDisplayDevice();
	bool startPingThread(std::function<void()> failCb);
	bool setRenderAdapterByName(const std::wstring& adapterName);
	std::wstring createVirtualDisplay(
		const char* s_client_uid,
		const char* s_client_name,
		const char* s_app_name,
		uint32_t width,
		uint32_t height,
		uint32_t fps,
		GUID& guid
	);
	bool removeVirtualDisplay(const GUID& guid);
}