cmd_/home/joelc/CN/shutdown_restart_driver/modules.order := {   echo /home/joelc/CN/shutdown_restart_driver/shutdown.ko; :; } | awk '!x[$$0]++' - > /home/joelc/CN/shutdown_restart_driver/modules.order