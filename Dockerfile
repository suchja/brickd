FROM c-dev-env:latest
MAINTAINER Jan Suchotzki <jan@lernmoment.de>

# Installiere notwendige Pakete zum kompilieren von brickd
RUN apt-get update && apt-get install -y --no-install-recommends \
				pkg-config \
				libusb-1.0-0-dev \
				libudev-dev \
	&& rm -rf /var/lib/apt/lists/*

ENV GIT_USER tinkerforge

# Quellcode für den Brick Daemon holen und kompilieren
# TODO: Überprüfen der Checksumme wäre gut. Es gibt aber scheinbar keine.
RUN mkdir -p /usr/src/ \
	&& cd /usr/src \
	&& git clone https://github.com/$GIT_USER/brickd.git brickdaemon\
	&& cd /usr/src/brickdaemon/src \
	&& git clone https://github.com/$GIT_USER/daemonlib.git daemonlib\
	&& cd /usr/src/brickdaemon/src/brickd \
	&& make \
	&& make install

WORKDIR /usr/src/brickdaemon/src

# Port vom Brick Daemon für andere Container bekannt machen
EXPOSE 4223

# Brick Daemon starten
CMD ["brickd/brickd"]
