Sample init scripts and service configuration for lunexd
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/lunexd.service:    systemd service unit configuration
    contrib/init/lunexd.openrc:     OpenRC compatible SysV style init script
    contrib/init/lunexd.openrcconf: OpenRC conf.d file
    contrib/init/lunexd.conf:       Upstart service configuration file
    contrib/init/lunexd.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "lunexcore" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes lunexd will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, lunexd requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, lunexd will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that lunexd and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If lunexd is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running lunexd without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/lunex.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/lunexd`  
Configuration file:  `/etc/lunexcore/lunex.conf`  
Data directory:      `/var/lib/lunexd`  
PID file:            `/var/run/lunexd/lunexd.pid` (OpenRC and Upstart) or `/var/lib/lunexd/lunexd.pid` (systemd)  
Lock file:           `/var/lock/subsys/lunexd` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the lunexcore user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
lunexcore user and group.  Access to lunex-cli and other lunexd rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/lunexd`  
Configuration file:  `~/Library/Application Support/LunexCore/lunex.conf`  
Data directory:      `~/Library/Application Support/LunexCore`
Lock file:           `~/Library/Application Support/LunexCore/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start lunexd` and to enable for system startup run
`systemctl enable lunexd`

4b) OpenRC

Rename lunexd.openrc to lunexd and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/lunexd start` and configure it to run on startup with
`rc-update add lunexd`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop lunexd.conf in /etc/init.  Test by running `service lunexd start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy lunexd.init to /etc/init.d/lunexd. Test by running `service lunexd start`.

Using this script, you can adjust the path and flags to the lunexd program by
setting the LUNEXD and FLAGS environment variables in the file
/etc/sysconfig/lunexd. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.lunex.lunexd.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.lunex.lunexd.plist`.

This Launch Agent will cause lunexd to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run lunexd as the current user.
You will need to modify org.lunex.lunexd.plist if you intend to use it as a
Launch Daemon with a dedicated lunexcore user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
