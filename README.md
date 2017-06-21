# Homemade serial-controlled LED-display

Homemade serial-controlled LED-display using an arduino to control a strip of addressable LEDs.
The arduino is used as server and controlled via serial. It does not create any images by itself, just display the information send via the serial port.

The client part is a ruby-script that can send images to the server to be displayed.
It can be used to display images (.jpg, .png) at the moment and may be exteneded to other formats like animated gifs.
