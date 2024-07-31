# Computer Network Assignment 1

1. what is your ip address?

An Internet Protocol address (IP address) is a numerical label assigned to each device participating in a computer network that uses the Internet Protocol for communication. IP addresses serve two main purposes: identifying the host or network interface, and providing the location of the host in the network.

There are two versions of IP addresses: IPv4 and IPv6. IPv4 addresses are most commonly used. They consist of four sets of digits, each ranging from 0 to 255, separated by periods (e.g., 192.168.0.1). However, due to the vast growth of the internet, the number of available IPv4 addresses is insufficient. As a result, IPv6 was developed, which has a much larger address space. IPv6 addresses consist of eight groups of four hexadecimal digits, separated by colons (e.g., 2001:0db8:85a3:0000:0000:8a2e:0370:7334).

It's important to note that IP addresses can be either static or dynamic. Static IPs remain constant, whereas dynamic IPs change every time a device connects to the internet. ISPs generally assign dynamic IPs to residential users, while businesses might use static IPs.

Please note that it's crucial to protect your IP address, as it can provide information about your location and internet service provider. Using services like VPNs can help hide your IP address, improving your online privacy and security.

Regarding my ip address, I am using windows as my OS so I can type ipconfig in cmd to get all my ip adresses.

1. What is your network address?

A network address is a unique identifier for a device on a network. It is used to identify each device that is connected to the network and allows data to be properly routed. Network addresses are used in almost all digital networks, including the internet, telephone networks, and private local area networks (LANs).

Network addresses are part of the broader system of IP addresses. An IP address is split into two parts: the network address and the host address. The network address identifies the specific network on which a device is located, while the host address identifies the specific device on that network. Together, the network and host addresses allow for precise routing of data.

For example, consider the IP address 192.168.0.15. In this case, '192.168.0' is the network address, and '15' is the host address. All devices on the same network would have '192.168.0' as their network address, but each would have a unique host address.

The network address can also be used to set up subnets, which divide an IP network into multiple network segments. This can be useful for managing network traffic and improving network performance.

It's important to note that network addresses, like IP addresses, can be either static or dynamic. A static network address is manually assigned and remains constant. In contrast, a dynamic network address is assigned each time a device connects to the network and can change over time.

1. What is your broadcast address?

A broadcast address is an IP address that allows information to be sent to all machines on a given network rather than a specific machine. It is the highest address in the network range, and it is used for network-wide communication. In binary terms, the broadcast address is created by taking the network address and setting all the host bits to 1.

To calculate the broadcast address, you would take the network address and set all the host bits to 1. Here is an example with a Class C network, which has a subnet mask of 255.255.255.0:

1. Let's say your IP address is 192.168.1.1
2. Your network address is 192.168.1.0
3. Your broadcast address would then be 192.168.1.255

In Windows, you can see your broadcast address by using the `ipconfig` command in the command prompt. This will show you your IP address, subnet mask, and default gateway. To see the broadcast address, you can use the `arp -a` command. Please note that this might not work in all cases, as Windows does not store the broadcast address in the same way as Unix-based systems do.

1. How many end devices can your network support?

The number of end devices your network can support is determined by the subnet mask of your network, which in turn defines the number of available host addresses.

For example, if you have a Class C network with a subnet mask of 255.255.255.0, your network can support up to 254 end devices. This is because the last octet of the IP address is used for host addresses, and with 8 bits, you can have 256 combinations. However, the first address (where all host bits are set to 0, e.g., 192.168.1.0) is reserved for the network address, and the last address (where all host bits are set to 1, e.g., 192.168.1.255) is reserved for the broadcast address. Therefore, you're left with 256 - 2 = 254 usable IP addresses for end devices.

To calculate how many end devices your network can support, you can use the formula 2^n - 2, where n is the number of host bits.

To see how many end devices your network currently supports on a Windows operating system, open Command Prompt and use the command `arp -a`. This will display a list of devices currently connected to your network. However, this method only shows devices that your computer has interacted with recently, so it may not show all connected devices if your network is large.