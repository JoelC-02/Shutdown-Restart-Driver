cmd_/home/joelc/CN/shutdown_restart_driver/shutdown.mod := printf '%s\n'   shutdown.o | awk '!x[$$0]++ { print("/home/joelc/CN/shutdown_restart_driver/"$$0) }' > /home/joelc/CN/shutdown_restart_driver/shutdown.mod