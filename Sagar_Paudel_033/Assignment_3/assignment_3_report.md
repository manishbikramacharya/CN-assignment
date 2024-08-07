Report on "What Happens When You Search facebook.com in a Browser"
Table of Contents
Introduction
Overview of the OSI Model
Detailed Analysis of Each Layer
Physical Layer
Data Link Layer
Network Layer
Transport Layer
Session Layer
Presentation Layer
Application Layer
Conclusion
References
Introduction
This report will explain what happens when you type "facebook.com" in a web browser and press Enter. I will describe this process using the seven layers of the OSI (Open Systems Interconnection) model. Each layer helps to make sure you can see the Facebook page correctly and safely. This report is for computer network students and includes all the technical details.

Overview of the OSI Model
The OSI model helps us understand how different network processes work in seven layers. These layers are:

Physical Layer
Data Link Layer
Network Layer
Transport Layer
Session Layer
Presentation Layer
Application Layer
Detailed Analysis of Each Layer


Physical Layer

The Physical layer deals with the physical connection between devices and the transmission of raw data bits.
When you press Enter after typing "facebook.com," your computer’s network interface card (NIC) creates electrical signals (for wired networks) or radio waves (for wireless networks). These signals travel through cables, fiber optics, or air to reach a router or modem.


Data Link Layer

The Data Link layer manages node-to-node data transfer and error correction. It uses MAC (Media Access Control) addresses to identify devices on the same network.
Your NIC adds your device’s MAC address to the data frames. These frames go to the nearest router or switch, which uses the MAC address to find the correct destination within the local network. Error detection methods, like checksums, check the data integrity.


Network Layer

The Network layer handles data routing, packet forwarding, and addressing using IP (Internet Protocol) addresses.
Your browser sends a DNS (Domain Name System) request to translate "facebook.com" into an IP address. This request goes to a DNS server, usually provided by your ISP (Internet Service Provider). The DNS server replies with Facebook’s server IP address. The data packets are then routed through several routers to reach Facebook’s server. Routing algorithms and protocols like OSPF (Open Shortest Path First) or BGP (Border Gateway Protocol) help determine the best path.


Transport Layer

The Transport layer ensures reliable data transfer through segmentation, error handling, and flow control. It uses TCP (Transmission Control Protocol) or UDP (User Datagram Protocol).
Your browser creates a TCP connection with Facebook’s server using a three-way handshake. This involves sending a SYN (synchronize) packet, receiving a SYN-ACK (synchronize-acknowledge) packet, and sending an ACK (acknowledge) packet. Once connected, data is broken into smaller packets, each with a sequence number for reassembly at the destination. Error detection and correction ensure data integrity.


Session Layer

The Session layer manages sessions between applications. It sets up, maintains, and ends connections.
The session layer manages the communication session between your browser and Facebook’s server. It ensures sessions are properly authenticated and terminates the session after data exchange.


Presentation Layer

The Presentation layer translates data between the application layer and the lower layers. It handles data encryption, decryption, compression, and translation.
Data from your browser is encrypted using SSL (Secure Sockets Layer) or TLS (Transport Layer Security) for secure transmission. The encrypted data is sent to Facebook’s server, where it is decrypted for processing.


Application Layer

The Application layer is closest to the end-user and interacts with software applications to provide communication services.
When you type "facebook.com" into your browser, an HTTP or HTTPS request is created by the application layer. The request is sent to Facebook’s server, which processes it and sends back the HTML content. Your browser then shows the Facebook homepage for you to use.


Conclusion

Understanding what happens when you type "facebook.com" in a browser requires knowing the OSI model and the roles of each layer in data transmission. From physical signal transmission to displaying the web page, each layer performs specific tasks to ensure reliable, efficient, and secure communication. This detailed analysis provides a good understanding of these processes, highlighting the importance of each OSI layer in network communications.

References

https://www.linkedin.com/pulse/what-happens-when-you-type-httpswwwgooglecom-your-browser-terer-8e9bf/

https://dev.to/antonfrattaroli/what-happens-when-you-type-googlecom-into-a-browser-and-press-enter-39g8

https://chatgpt.com/

google search

