
1. What do you mean OSI & TCP/IP model?

  

The OSI (Open Systems Interconnection) model is a conceptual framework that standardizes the functions of a communication system into seven distinct categories, referred to as layers. These layers include the physical, data link, network, transport, session, presentation, and application layers.

  

The TCP/IP (Transmission Control Protocol/Internet Protocol) model is a suite of communication protocols used to interconnect network devices on the internet. It has four layers: network interface, internet, transport, and application. While it performs similar functions to the OSI model, it is simpler and more widely used in the realm of internet communications.

  

| | OSI Model | TCP/IP Model |

| --- | --- | --- |

| Layers | Has 7 layers: Physical, Data Link, Network, Transport, Session, Presentation, Application | Has 4 layers: Network Interface, Internet, Transport, Application |

| Model type | A theoretical model | A practical model |

| Protocol | Protocols are hidden and can be replaced as the technology changes | Protocols are not hidden and cannot be replaced |

| Network services | Network services are provided by Application, Presentation, and Session layers | Network services are provided by Application layer |

| Development | Developed before the invention of the protocols used on the internet | Developed based on the protocols used on the internet |

  

Peer-to-Peer (P2P) Architecture vs Client-Server Architecture

  

In a Peer-to-Peer (P2P) architecture, all nodes (or peers) in the network have equal privileges and responsibilities. Each peer can act as both a client and a server, sharing their own resources (like files, bandwidth, or processing power) directly with other peers.

  

Example: In a file-sharing network like BitTorrent, users can download files directly from other users who have the file, rather than from a central server.

  

In contrast, a Client-Server architecture is a centralized model where one or more client machines are connected to a central server. The server holds the data and resources, and the client machines request these resources from the server.

  

Example: When you access a website, your computer (the client) sends a request to the website's server, which returns the web page to your browser.

  

| | Peer-to-Peer Architecture | Client-Server Architecture |

| --- | --- | --- | | |

| Structure | Decentralized; all peers are equal | Centralized; clients depend on a central server |

| Resource sharing | Direct between peers | Through the central server |

| Performance | Can scale well as more peers join the network; performance depends on the number of active peers | Performance depends on the server's capabilities; may be affected if many clients access it at the same time |

| Security | Can be less secure due to the lack of a central authority | Typically more secure as the server can enforce security policies |

| Use case | File sharing, blockchain networks | Websites, email services, corporate networks |

  
  

2. What are the several layers of OSI model? What is the function of each layer?

  

The OSI model consists of seven layers, each with its own unique function:

  

1. Physical Layer: This is the lowest layer of the OSI model. It's sort of like the 'plumbing' of the network. It's concerned with transmitting raw bit streams over the physical medium such as cables, connectors, etc. This layer includes protocols for how data is sent and received, including voltage levels, timing, and physical connections. Its main function is to convert the digital data into electrical, radio or optical signals.

2. Data Link Layer: Think of this layer as a traffic control system. It manages the interaction of devices on a network, making sure data frames from the physical layer are sent and received without collisions or errors. It provides error-free transmission of frames from one node to another over the physical layer, allowing for error detection and correction. It also defines the protocol for how devices on a network share access to the medium, ensuring that devices can communicate without stepping on each other's toes.

3. Network Layer: This layer is like the network's post office or GPS. It's responsible for routing and transferring data from one point to another across different networks. The network layer is responsible for the delivery of individual packets from the source host to the destination host. It decides on the most efficient path data should take based on network conditions, service requirements, and economic considerations. It's where IP (Internet Protocol) addresses are used.

4. Transport Layer: This is the layer that ensures reliable data transmission between devices. It's like the transport system that ensures that all data packets reach their correct destination without any losses or duplications. This layer is responsible for end-to-end communication over a network. It manages packet sequencing, acknowledgement, error checking, and retransmission of lost or corrupted packets. It includes protocols such as TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) which ensure that data packets are delivered error-free, in sequence, and without losses or duplications.

5. Session Layer: This is the layer that sets up, coordinates, and terminates conversations. It's like setting a meeting (session) between two devices and deciding when it starts and when it should end. This layer establishes, maintains, and ends communication sessions. These sessions consist of service requests and service responses between applications located in different network devices. It also synchronizes dialogue between the presentation layers of the two hosts and manages their data exchange.

6. Presentation Layer: It's like a translator. The presentation layer is concerned with the syntax and semantics of the information transmitted. It ensures that data is sent in a format that the receiving system can understand, handling data conversion, compression, and encryption. It translates data between the format the network requires and the format the computer.

7. Application Layer: This is the topmost layer of the OSI model. It's like the front-end interface, the layer that software and human users interact with. It provides a set of interfaces for applications to obtain access to networked services, as well as access to the kinds of network services that support applications directly. This includes services such as file transfers, email, and other network software services. It interacts with software applications that implement a communicating component.

  

3. What are the principles behind OSI model?

  

The principles behind the OSI model are centered around the idea of layering and abstraction. Layering helps to simplify the network design, allows interoperability between vendors, prevents changes in one layer from affecting other layers so it doesn't need to be redesigned, and helps to create a modular engineering approach that enables network technology to scale. Here are the key principles:

  

1. Layering: The OSI model divides the complex task of computer-to-computer communication into smaller, manageable layers. Each layer performs a specific function in the process and is transparent to the layers above and below.

2. Abstraction: Each layer in the OSI model only needs to know about the functions of the layers directly above and below it, not the details of how those functions are performed. This abstraction of details allows changes in one layer without affecting the rest of the stack.

3. Standard Interfaces: Each layer in the OSI model provides a standard interface to the layer above it. This means that a change in the way a layer performs its function doesn't affect the rest of the layers as long as the interface remains the same.

4. Modularity: The OSI model is modular, meaning that tasks are divided among multiple modules. This allows for changes or upgrades in one module without disrupting the others.

5. Interoperability: The OSI model allows for interoperability between different systems and networks. As long as all systems follow the OSI standards, they should be able to communicate, regardless of the specific technology or architecture used.1. What do you mean OSI & TCP/IP model?

  

The OSI (Open Systems Interconnection) model is a conceptual framework that standardizes the functions of a communication system into seven distinct categories, referred to as layers. These layers include the physical, data link, network, transport, session, presentation, and application layers.

  

The TCP/IP (Transmission Control Protocol/Internet Protocol) model is a suite of communication protocols used to interconnect network devices on the internet. It has four layers: network interface, internet, transport, and application. While it performs similar functions to the OSI model, it is simpler and more widely used in the realm of internet communications.

  

| | OSI Model | TCP/IP Model |

| --- | --- | --- |

| Layers | Has 7 layers: Physical, Data Link, Network, Transport, Session, Presentation, Application | Has 4 layers: Network Interface, Internet, Transport, Application |

| Model type | A theoretical model | A practical model |

| Protocol | Protocols are hidden and can be replaced as the technology changes | Protocols are not hidden and cannot be replaced |

| Network services | Network services are provided by Application, Presentation, and Session layers | Network services are provided by Application layer |

| Development | Developed before the invention of the protocols used on the internet | Developed based on the protocols used on the internet |

  

Peer-to-Peer (P2P) Architecture vs Client-Server Architecture

  

In a Peer-to-Peer (P2P) architecture, all nodes (or peers) in the network have equal privileges and responsibilities. Each peer can act as both a client and a server, sharing their own resources (like files, bandwidth, or processing power) directly with other peers.

  

Example: In a file-sharing network like BitTorrent, users can download files directly from other users who have the file, rather than from a central server.

  

In contrast, a Client-Server architecture is a centralized model where one or more client machines are connected to a central server. The server holds the data and resources, and the client machines request these resources from the server.

  

Example: When you access a website, your computer (the client) sends a request to the website's server, which returns the web page to your browser.

  


|                     | Peer-to-Peer Architecture | Client-Server Architecture |
| ------------------- | ------------------------- | -------------------------- |
| Structure           | Decentralized; all peers are equal | Centralized; clients rely on a central server |
| Resource Sharing    | Directly between peers | Via the central server |
| Performance         | Scales well with more peers; depends on active peer count | Relies on server capacity; can be impacted by high client demand |
| Security            | Less secure without central authority | Generally more secure with server-enforced policies |
| Use Cases           | File sharing, blockchain networks | Web services, email, enterprise networks |

  

2. What are the several layers of OSI model? What is the function of each layer?

  

The OSI model consists of seven layers, each with its own unique function:

  

1. Physical Layer: This is the lowest layer of the OSI model. It's sort of like the 'plumbing' of the network. It's concerned with transmitting raw bit streams over the physical medium such as cables, connectors, etc. This layer includes protocols for how data is sent and received, including voltage levels, timing, and physical connections. Its main function is to convert the digital data into electrical, radio or optical signals.

2. Data Link Layer: Think of this layer as a traffic control system. It manages the interaction of devices on a network, making sure data frames from the physical layer are sent and received without collisions or errors. It provides error-free transmission of frames from one node to another over the physical layer, allowing for error detection and correction. It also defines the protocol for how devices on a network share access to the medium, ensuring that devices can communicate without stepping on each other's toes.

3. Network Layer: This layer is like the network's post office or GPS. It's responsible for routing and transferring data from one point to another across different networks. The network layer is responsible for the delivery of individual packets from the source host to the destination host. It decides on the most efficient path data should take based on network conditions, service requirements, and economic considerations. It's where IP (Internet Protocol) addresses are used.

4. Transport Layer: This is the layer that ensures reliable data transmission between devices. It's like the transport system that ensures that all data packets reach their correct destination without any losses or duplications. This layer is responsible for end-to-end communication over a network. It manages packet sequencing, acknowledgement, error checking, and retransmission of lost or corrupted packets. It includes protocols such as TCP (Transmission Control Protocol) and UDP (User Datagram Protocol) which ensure that data packets are delivered error-free, in sequence, and without losses or duplications.

5. Session Layer: This is the layer that sets up, coordinates, and terminates conversations. It's like setting a meeting (session) between two devices and deciding when it starts and when it should end. This layer establishes, maintains, and ends communication sessions. These sessions consist of service requests and service responses between applications located in different network devices. It also synchronizes dialogue between the presentation layers of the two hosts and manages their data exchange.

6. Presentation Layer: It's like a translator. The presentation layer is concerned with the syntax and semantics of the information transmitted. It ensures that data is sent in a format that the receiving system can understand, handling data conversion, compression, and encryption. It translates data between the format the network requires and the format the computer.

7. Application Layer: This is the topmost layer of the OSI model. It's like the front-end interface, the layer that software and human users interact with. It provides a set of interfaces for applications to obtain access to networked services, as well as access to the kinds of network services that support applications directly. This includes services such as file transfers, email, and other network software services. It interacts with software applications that implement a communicating component.

  

3. What are the principles behind OSI model?

  

The principles behind the OSI model are centered around the idea of layering and abstraction. Layering helps to simplify the network design, allows interoperability between vendors, prevents changes in one layer from affecting other layers so it doesn't need to be redesigned, and helps to create a modular engineering approach that enables network technology to scale. Here are the key principles:

  

1. Layering: The OSI model divides the complex task of computer-to-computer communication into smaller, manageable layers. Each layer performs a specific function in the process and is transparent to the layers above and below.

2. Abstraction: Each layer in the OSI model only needs to know about the functions of the layers directly above and below it, not the details of how those functions are performed. This abstraction of details allows changes in one layer without affecting the rest of the stack.

3. Standard Interfaces: Each layer in the OSI model provides a standard interface to the layer above it. This means that a change in the way a layer performs its function doesn't affect the rest of the layers as long as the interface remains the same.

4. Modularity: The OSI model is modular, meaning that tasks are divided among multiple modules. This allows for changes or upgrades in one module without disrupting the others.

5. Interoperability: The OSI model allows for interoperability between different systems and networks. As long as all systems follow the OSI standards, they should be able to communicate, regardless of the specific technology or architecture used.