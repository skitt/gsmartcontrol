/**************************************************************************
 Copyright:
      (C) 2008 - 2012  Alexander Shaduri <ashaduri 'at' gmail.com>
 License: See LICENSE_gsmartcontrol.txt
***************************************************************************/
/// \file
/// \author Alexander Shaduri
/// \ingroup gsc
/// \weakgroup gsc
/// @{

#ifndef GSC_SETTINGS_H
#define GSC_SETTINGS_H

#include <cstdint>
#include "rconfig/rconfig_mini.h"



/// Initializes ALL default settings.
/// Absolute paths go to root node, relative ones go to /config and /default.
/// Note: There must be no degradation if /config is removed entirely
/// during runtime. /default must provide every path which /config could
/// have held.
/// ALL runtime (that is, non-config-file-writable) settings go to /runtime.
inline void init_default_settings()
{
	// Populate /default

	rconfig::set_default_data("system/config_autosave_timeout", uint32_t(3*60));  // 3 minutes. 0 to disable.
	rconfig::set_default_data("system/first_boot", true);  // used to show the first-start warning.


#ifndef _WIN32
	rconfig::set_default_data("system/smartctl_binary", "smartctl");  // must be in PATH or use absolute path.
	rconfig::set_default_data("system/tw_cli_binary", "tw_cli");  // must be in PATH or use absolute path.
#else
	rconfig::set_default_data("system/smartctl_binary", "smartctl-nc.exe");  // use no-console version by default.
	rconfig::set_default_data("system/tw_cli_binary", "tw_cli.exe");
	rconfig::set_default_data("system/areca_cli_binary", "cli.exe");  // if relative, an installation path is prepended (if found).
#endif
	// search for "smartctl-nc.exe" in smartmontools installation first.
	rconfig::set_default_data("system/win32_search_smartctl_in_smartmontools", true);
	rconfig::set_default_data("system/win32_smartmontools_regpath", "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\smartmontools");  // in HKLM
	rconfig::set_default_data("system/win32_smartmontools_regpath_wow", "SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\smartmontools");  // in HKLM
	rconfig::set_default_data("system/win32_smartmontools_regkey", "InstallLocation");
	rconfig::set_default_data("system/win32_smartmontools_smartctl_binary", "bin\\smartctl-nc.exe");  // relative to smt install path
	rconfig::set_default_data("system/win32_areca_scan_controllers", int32_t(2));  // 0 - no, 1 - yes, 2 - auto (if areca tools are found)
	rconfig::set_default_data("system/win32_areca_use_cli", int32_t(2));  // 0 - no, 1 - yes, 2 - auto (if it's found)
	rconfig::set_default_data("system/win32_areca_max_controllers", int32_t(4));  // Maximum number of areca controllers (a safety measure). CLI supports 4.
	rconfig::set_default_data("system/win32_areca_enc_max_scan_port", int32_t(36));  // 1-128 (areca with enclosures). The last RAID port to scan if no other method is available
	rconfig::set_default_data("system/win32_areca_enc_max_enclosure", int32_t(3));  // 1-8 (areca with enclosures). The last RAID enclosure to scan if no other method is available
	rconfig::set_default_data("system/win32_areca_neonc_max_scan_port", int32_t(24));  // 1-24 (areca without enclosures). The last RAID port to scan if no other method is available

	rconfig::set_default_data("system/smartctl_options", "");  // default options on ALL commands
	rconfig::set_default_data("system/smartctl_device_options", "");  // dev1:val1;dev2:val2;... format, each bin2ascii-encoded.

	rconfig::set_default_data("system/linux_udev_byid_path", "/dev/disk/by-id");  // linux hard disk device links here
	rconfig::set_default_data("system/linux_proc_partitions_path", "/proc/partitions");  // file in linux /proc/partitions format
	rconfig::set_default_data("system/linux_proc_devices_path", "/proc/devices");  // file in linux /proc/devices format
	rconfig::set_default_data("system/linux_proc_scsi_scsi_path", "/proc/scsi/scsi");  // file in linux /proc/scsi/scsi format
	rconfig::set_default_data("system/linux_proc_scsi_sg_devices_path", "/proc/scsi/sg/devices");  // file in linux /proc/scsi/sg/devices format
	rconfig::set_default_data("system/linux_3ware_max_scan_port", int32_t(23));  // 0-127 (3ware). The last RAID port to scan if no other method is available
	rconfig::set_default_data("system/linux_areca_enc_max_scan_port", int32_t(36));  // 1-128 (areca with enclosures). The last RAID port to scan if no other method is available
	rconfig::set_default_data("system/linux_areca_enc_max_enclosure", int32_t(4));  // 1-8 (areca with enclosures). The last RAID enclosure to scan if no other method is available
	rconfig::set_default_data("system/linux_areca_neonc_max_scan_port", int32_t(24));  // 1-24 (areca without enclosures). The last RAID port to scan if no other method is available
	rconfig::set_default_data("system/solaris_dev_path", "/dev/rdsk");  // path to /dev/rdsk for solaris.
	rconfig::set_default_data("system/unix_sdev_path", "/dev");  // path to /dev. used by other unices
// 	rconfig::set_default_data("system/device_match_patterns", "");  // semicolon-separated PCRE patterns
	rconfig::set_default_data("system/device_blacklist_patterns", "");  // semicolon-separated PCRE patterns

	rconfig::set_default_data("gui/show_smart_capable_only", false);  // show smart-capable drives only
	rconfig::set_default_data("gui/scan_on_startup", true);  // scan drives on startup

	rconfig::set_default_data("gui/smartctl_output_filename_format", "{model}_{serial}_{date}.txt");  // when suggesting filename

	rconfig::set_default_data("gui/icons_show_device_name", false);  // text under icons
	rconfig::set_default_data("gui/icons_show_serial_number", false);  // text under icons


	// Populate /runtime too, just in case. The values don't really matter.

	rconfig::set_data("/runtime/gui/hide_tabs_on_smart_disabled", true);
	rconfig::set_data("/runtime/gui/force_no_scan_on_startup", false);
	// rconfig::set_data("/runtime/gui/add_virtuals_on_startup", "");  // vector<string>
	// rconfig::set_data("/runtime/gui/add_devices_on_startup", "");  // vector<string>

}








#endif

/// @}
