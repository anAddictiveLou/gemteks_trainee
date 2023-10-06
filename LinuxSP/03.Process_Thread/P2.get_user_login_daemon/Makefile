get_usr_login: 
# Compile the program
	gcc -o get_usr_login main.c ./src/*.c -I./inc 
# Move the executable file to the /usr/sbin directory
	sudo mv get_usr_login /usr/sbin/
# Copy "daemon_auto.service", in the /etc/systemd/system directory
	sudo cp get_usr_login.service /etc/systemd/system
# Reload the systemd daemon 
	sudo systemctl daemon-reload
# Enable the service to start at boot time 
	sudo systemctl enable get_usr_login.service
# Start the service 
	sudo systemctl start get_usr_login.service