This folder contains client-server common code.
It's organised into separate Conan package, so it can be used independently
for client and server. Because of this this folder can be moved to separate
repository where it can be developed and published independently.
But from my current experience this is not that convenient, because
it is not that rare to change something inside this folder for client
or server specific code.