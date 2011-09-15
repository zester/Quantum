#
# Regular cron jobs for the eggwm package
#
0 4	* * *	root	[ -x /usr/bin/eggwm_maintenance ] && /usr/bin/eggwm_maintenance
