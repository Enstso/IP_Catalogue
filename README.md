## Introduction

**IP Catalogue** is a console application designed to catalog IPv4 addresses. It offers several key features, including persistent storage of IP addresses, filtering addresses based on a mask, displaying addresses in various formats (binary, hexadecimal, decimal), and validating input to ensure compliance with IPv4 standards.

## Features

### 1) Persistence
The program permanently stores IP addresses, meaning added addresses are saved between program executions. This allows users to build and maintain a catalog of IP addresses over time.

### 2) Mask-Based Filtering
Users can filter stored IP addresses based on a specified mask. By providing an IP address and a mask, the program returns stored IPs that match the given mask.

### 3) Binary/Hexadecimal/Decimal Display
IP addresses can be displayed in binary, hexadecimal, and decimal formats. This flexibility allows users to view IPs in the format best suited to their needs.

### 4) Validation
The program enforces strict validation to ensure only authentic IP addresses are allowed. Invalid entries include unauthorized characters, out-of-range values (0-255), missing segments, or misplaced dots.

Examples of invalid entries:
- `afs.213.sf.23ew`
- `300.192.1.2`
- `-12.23.12.23`
- `172.45.223..1`

## Main Loop

The program operates as an interactive menu and will not exit unless explicitly requested by the user. The following options are available in the menu:
- **a** - Add a new IP address
- **l** - List stored IP addresses
- **s** - Search similar addresses by mask
- **d** - Delete an IP address
- **q** - Quit

### Example Interaction

```plaintext
a - Add a new IP address.
l - List IP addresses.
s - Search similar by mask.
d - Delete an IP.
q - Quit.

Please choose one: a

Enter IP Address: 192.168.1.1
Enter Mask Address: 255.255.0.0

The IP Address: 192.168.1.1 and The Mask: 255.255.0.0 are added successfully!
```
The program continues to interact with the user until the quit option (**q**) is selected.


## How to Run the Program

If you do not have GCC or are using a non-Unix environment, you can use [docker](https://docs.docker.com/) and follow steps 2 and 3.

1. Clone the project repository.

2. Build the Docker image from the Dockerfile:
 ```bash
docker build -t c-img .
```
3. Run the Docker container:
 ```bash
docker run -ti -v $(pwd):/IP_Catalogue c-img
```

4. Compile the main.c program inside the container:
 
 ```bash
 gcc main.c
```

5. Run the compiled program:
```bash
 ./a.out
```

6. Follow the interactive menu instructions to use the application's features.

## Notes
Ensure you have the necessary permissions to store data on the file system. This is required to persist IP addresses across program sessions.
