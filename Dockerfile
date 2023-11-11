# Utilisez une image de base qui contient un système d'exploitation Linux
FROM debian:bullseye-slim

# Mettez à jour les paquets et installez les outils de développement C
RUN apt-get update && apt-get install -y build-essential 

