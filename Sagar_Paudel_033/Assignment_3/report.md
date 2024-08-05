---
# What happens when you type "www.facebook.com" in the browser

---
## Table of Contents

1. Introduction
2. Purpose of the Report
3. Overview of the Process
4. URL Parsing
   - Components of a URL
5. DNS Lookup
   - Browser Cache
   - OS Cache
   - Router Cache
   - ISP DNS Cache
   - Recursive DNS Lookup
   - DNS Recursive Resolver
- DNS Root Nameserver
   - TLD Nameserver
   - Authoritative Name Server
6. Making a TCP/IP Connection
   - The TCP Handshake Process
     - SYN, or Synchronize Packet
     - SYN-ACK, or Synchronize-Acknowledge Packet
     - ACK, or Acknowledge Packet
   - Post-handshake Connection
   - Additional Note: Several IP Addresses
7. Server-Side Load Balancing and Connection Handling
   - Load Balancing
   - Listening Socket
   - Process the Request
8. Connection Management in the Operating Systems
   - Source Ports for Multiple Connections
   - Handling Multiple Incoming Requests on a Single Port
9. HTTP Request and Response
   - Send the HTTP Request
   - Receive the HTTP Response
- Possible Errors
10. Conclusion
11. References
--- 

## Introduction 

### Purpose of

This report should contain a detailed account of all the technical processes involved when a user clicks a URL, for example, www.facebook.com. This report will assist in breaking down each step from entering the URL into the browser, right down to the time that specific web page displays. A number of complex interactions and technologies are involved in the delivery of this apparently seamless web experience.

### Process Overview

When a user types a URL in their browser and hits enter, the following events occur: the URL gets parsed and then a DNS lookup is performed which is required to resolve the domain name into the IP address. Upon getting the IP address, the browser then establishes a TCP/IP connection with the server. The part of the connection includes three-way handshaking for reliability of communication. First, there is a connection formation by the browser to the server using an HTTP request and, in return, receiving a response in the form of HTTP. In the end, the message response is acted upon, and the page is, at last, shown in the browser. Each step works to show the user the desired web page in the shortest and most efficient way possible.

---
## Detailed Content
### URL Parsing

When a user types facebook.com in the browser and hits enter, the browser initially comprehends the URL and initiates the process of parsing it into elementary parts. This would allow it to identify each of the elements, which it will use in the coming steps.

#### URL components

- **Protocol**: This is, of course, the set of rules for data transfer. For Facebook, it is mostly https:// to indicate that this is a secured method of communication.
- **Domain**: It is the location of the main address of the website. In this case ,it is www.facebook.com for Facebook.
- **Port**: Most of the time, this is implied and will not be in the URL. Port 443 is the default port for HTTPS, and port 80 is the default for HTTP.
- **Path**: This specifies the location of the resource on the server. For instance, when one visits https://www.facebook.com/profile, the path will be /profile.
- **Query String** : Used to pass parameters to the server. For example https://www.facebook.com/search?q=friend where q=friend is the query string.
- **Fragment**: A certain section of a web page to which the browser can be brought by using the fragment identifier. For instance, https://www.facebook.com/home#timeline brings a user to a home page outlined by the #timeline part.
---
### DNS Look-up

After a URL has been parsed, there are the further steps of resolving the domain name into an IP address through a Domain Name System (DNS) lookup. This involves a number of caching stages and recursive queries, so that resolution takes place as quickly and as accurately as possible.

- **Browser Cache**: You can bet the first place the browser is going to look is in its own cache. If there's a recent DNS record already in there, then it'll just use that IP address. That would be completely by-passing all later lookups.

- **OS Cache**: When there is no such DNS record at that point in the browser cache, the browser then inquires about the cache of the OS itself, which keeps its own record about the recent DNS queries.
- **Router Cache**: In case the DNS record is absent in the OS cache as well, the request is sent to the local router. A lot of routers maintain their own DNS caches; this usually speeds up the domain lookup for frequently visited domains.
- **ISP DNS Cache**: If the router does not contain the DNS information in its DNS cache, the request goes to the Internet Service Provider's DNS Server. Every ISP maintains a cache of DNS records for its users. This program goes a long way in reducing the load on the global DNS infrastructure and accelerating lookups.
- **Recursive DNS Lookup**: If the requested DNS record is not available with the DNS server of the ISP, then it goes through a process of recursive DNS lookup. It further sends queries hierarchically to various DNS servers to resolve the domain name sent.
- **DNS Recursive Resolver**: This is the beginning of this query. The recursive resolver acts like a middleman and on behalf of the requesting client makes some further queries. It begins looking up the given name in its cache; otherwise, it sends a request to one of the root DNS servers.
- **DNS Root Nameserver**: The root nameservers are those servers which are at the top of the DNS hierarchy. Basically, there are 13 root nameservers scattered in the world. These servers are replicated to ensure redundancy and speed. The root nameserver itself doesn't know the exact IP address of www.facebook.com, but it knows the authoritive servers for the Top-Level-Domain (TLD) .com.
TLD Nameserver: The recursive resolver now sends a query to a TLD nameserver that is responsible for .com domains. This server guides the resolver to the authoritative name server of facebook.com. Authoritative Name Server: The authoritative nameserver for facebook.com knows all the DNS records of every subdomain of facebook.com, one of which may be www.facebook.com. It then sends a reply back to the recursive resolver with the IP address of the Facebook server.
It caches this information in the recursive resolver and serves back the IP address to the browser, thus completing the DNS name lookup. This will allow the browser to establish a connection to the Facebook server and initiate a connection using the resolved IP address.

---
![alt text](<Screenshot 2024-08-05 143331.png>) ![alt text](<Screenshot 2024-08-05 143306.png>)
### Checking the DNS Query and Response

**DNS Query (First Image):**
- **Transaction ID**: `0x1bf`
- **Query Type**: Standard query (0x0100)
- **Questions**: 1
- **Answer RRs**: 0
- **Authority RRs**: 0
- **Additional RRs**: 0
- **Query Name**: `www.facebook.com`
- **Query Type**: AAAA (IPv6 address)

This packet  a DNS query for the AAAA record of `www.facebook.com`.

**DNS Response (Second Image):**
- **Transaction ID**: `0xf909` (matches the query)
- **Query Type**: Standard query response, No error (0x8180)
- **Questions**: 1
- **Answer RRs**: 1
- **Authority RRs**: 1
- **Additional RRs**: 0
- **Answer**: `157.240.20.35` (example IP for Facebook)
- **Authority Name Server**: `c10r.facebook.com`

This packet the DNS response for the AAAA query of `www.facebook.com`.

### Setting TCP/IP Connection

Now, after the DNS lookup has been done and the IP address has been found for the Facebook server, the browser will need to establish a reliable connection to the server. For this, it will use the TCP/IP protocol. It guarantees the data to be delivered accurately and in the correct order. But there is a three-way handshake process in the beginning.

#### The TCP Handshake Process

- **SYN (Synchronize) Packet**: The client, in this case the browser, sends a SYN packet to the server hosting Facebook. The SYN packet contains an initial sequence number, denoted ISN, which is a randomly chosen number and forms the base for the byte sequence. The packet has its TCP header with a flag, SYN, set, pointing out that this is a connection establishment packet.

This is the packet that is ultimately responsible for acknowledging the client's SYN packet immediately after the Facebook server receives the SYN packet from the client. It will acknowledge the client's SYN packet through an acknowledgement number that will be one more than the sequence number sent in the client's own SYN packet. It will synchronize the server's sequence numbers with the client's, including his own initial sequence number in the packet. It does set both the SYN and the ACK flags of the TCP header.
- **ACK Packet**: The client responds to the server's SYN-ACK by an ACK packet. This response packet sends an acknowledgment for the server's SYN-ACK by setting one more than the server's sequence number in the acknowledgment number. The flag is set in the TCP header for the ACK, not the SYN flag; therefore, this step confirms that the connection has been established.
 - **Post Handshake Connection**

Finally, a stable connection between the client and server is set up. At this point, the client and server have state information about the connection, specifically the sequence numbers and acknowledgment numbers. In order to ensure that the data is consistently and sequentially delivered, now the server can send appropriate HTTP responses back to the client for the HTTP requests that the client is going to initiate.

#### Additional Note: Multiple IP Addresses

DNS resolver can return multiple IP addresses for one single domain to the application, for instance, www.facebook.com; then load balance and provide redundancy of the service. Generally, the browser would be opting to connect using the first IP address as returned by the DNS server, but in case the connection does not get through using the first IP address, it would still be able to try with an IP address using an alternate one for that matter. This mechanism increases service availability and reliability.

Server-Side Load Balancing and Connection Handling

Once the TCP connection has been established, the HTTP request will arrive to Facebook's infrastructure. The following are the usual next steps to ensure the request is handled and processed efficiently:

#### Load Balancing

* **DNS Load Balancing**: DNS Load Balancing achieves traffic distribution by returning various IP addresses under the same host name. This way, it balances the workload between various servers, ensuring high performance and reliability. Pure round-robin, least connections, or even an IP hash may be techniques used to distribute requests across many IPs, each of which is a different load balancer. Now, when your request reaches one of those IPs, it will hit a load balancer.

**Load Balancer Role**: The role of load balancer is to distribute incoming requests among a pool of back-end servers, that is, ensuring no server gets heaped up with requests. #### Listening Socket - **First-Line Connection Handling**: On port 80 for HTTP, and on port 443 for HTTPS, there is a listening socket over the server. The socket

It then goes into an infinite loop, waiting to accept incoming connection requests. Once the server has received a connection request on this port, it simply accepts the connection and creates a new socket that shall be used only for communicating with your client.

#### Processing the Request

* **Parsing the Request**: The server reads, from the socket, an HTTP request. It involves parsing, on the request line – for example, GET /index.html HTTP/1.1 – headers, and any body content.

- **Response Generation**: The server processes the request and generates the appropriate HTTP response. That might involve database queries, file fetching, or computation.
- **Response Sent**: The generated HTTP response is then received back to your client by the server over a specific socket. In this, there is a status line (for example HTTP/1.1 200 OK), headers, and a body.
---

Connection Management in Operating Systems

#### Multiple Connections Using Source Ports

**Assigning Unique Source Ports**: For instance, let's say that you open several web browsers or open several tabs within the same browser. Your operating system gives each of them a unique source port. It does this since, in such an event, the response to the server shall return to the application that initiated the request or to the particular tab in the browser that created the request. The OS monitors every movement in the table holding active connections, tracking the source and destination IPs and ports, to avoid any form of conflict.

- Example: 
    - Firefox (localhost:33123) <-> stackoverflow.com (69.59.196.211:80)
    - Chrome (localhost:33124) <-> stackoverflow.com (69.59.196.211:80)
#### Handling Multiple Incoming Requests on

**Listening and Dedicated Sockets**: Proper use of the socket and concurrency mechanisms allows any type of web server to handle the incoming requests of many users over one port, i.e., port 80. As soon as one client is in contact with the server, a "listening socket" is used to accept a connection. And for each user, a "dedicated connection socket" is established. Now, this dedicated socket will handle the communication with that particular client, which indicates that the server can easily be in many connections at a time.

- **Concurrency Mechanisms**: The Server can implement multi-threading, multi-processing, or asynchronous I/O to process these concurrent connections efficiently. In this way, even if all the requests arrive at the same port, it would be possible for the server to treat every single request differently and reply adequately to each user.
---
### HTTP Request and Response

After the TCP/IP connection is established, a browser communicates with the server using the Hypertext Transfer Protocol Secure (HTTPS). The HTTPS protocol ensures that data being shared between the client and server is encrypted and safe. This section explains the analysis of the HTTP request that is sent by the client and the response that comes back from the server.

![alt text](<Screenshot 2024-08-05 143418.png>) ![alt text](<Screenshot 2024-08-05 143405.png>)

### Checking the HTTPS Request and Request Acknowledgment

**HTTPS SYN Packet (Third Image):**
- **Source Port**: `61629`
- **Destination Port**: `443` (HTTPS)
- **Sequence Number**: `0`
- **ACK Number**: `0`
- **TCP Flags**: `SYN` (0x002)
- **Window Size**: `64800`

This packet is the initial SYN packet sent from the client to the server to initiate a TCP connection on port 443 for HTTPS.

**HTTPS SYN-ACK Packet (Fourth Image):**
- **Source Port**: `443` (HTTPS)
- **Destination Port**: `61629`
- **Sequence Number**: `0`
- **ACK Number**: `1`
- **TCP Flags**: `SYN, ACK` (0x012)
- **Window Size**: `65535`

This packet is the SYN-ACK packet sent from the server back to the client, acknowledging the receipt of the SYN packet and establishing the connection.

### Explanation of the HTTPS Request and SYN-ACK Packets

#### HTTPS SYN Packet
1. **Ethernet II**:
   - Source: `Intel_3b:92:69`
   - Destination: `NetisTechnol_11:90:50`

2. **Internet Protocol Version 6** (IPv6):
   - Source Address: `2404:7c00:4a:132e:3dba:707d:a1b5:4feb`
   - Destination Address: `2a03:2880:f12f:183:face:b00c:0:25de`

3. **Transmission Control Protocol** (TCP):
   - **Source Port**: `61629`
   - **Destination Port**: `443`
   - **Sequence Number**: `0` (Initial sequence number)
   - **Acknowledgment Number**: `0` (Not yet acknowledged)
   - **Header Length**: `32 bytes`
   - **Flags**: `SYN` (0x002)
   - **Window Size**: `64800`
   - **Options**: Maximum segment size, Window scale, No-Operation (NOP), SACK permitted

The SYN packet initiates the TCP connection by sending the initial sequence number and window size to the server, along with TCP options such as the maximum segment size and window scaling.

#### HTTPS SYN-ACK Packet
1. **Ethernet II**:
   - Source: `NokiaShangha_6e:54:e0`
   - Destination: `Intel_3b:92:69`

2. **Internet Protocol Version 6** (IPv6):
   - Source Address: `2a03:2880:f12f:183:face:b00c:0:25de`
   - Destination Address: `2404:7c00:4a:132e:3dba:707d:a1b5:4feb`

3. **Transmission Control Protocol** (TCP):
   - **Source Port**: `443`
   - **Destination Port**: `61629`
   - **Sequence Number**: `0`
   - **Acknowledgment Number**: `1` (Acknowledges the client’s SYN packet)
   - **Header Length**: `32 bytes`
   - **Flags**: `SYN, ACK` (0x012)
   - **Window Size**: `65535`
   - **Options**: Maximum segment size, Window scale, No-Operation (NOP), SACK permitted

The SYN-ACK packet acknowledges the client's SYN packet and establishes the server's sequence and acknowledgment numbers. The server also sends its TCP options back to the client.

### Possible Errors

During the process of sending the HTTP request and receiving the answer, namely, the HTTP response, several kinds of mistakes may appear. These are the following:

- **DNS Errors**:

- **DNS Lookup Failed**: Because of the domain name not resolving to the IP address, the browser fails to.
- **DNS Timeout**: Failure in the response of the DNS Server.
- **TCP/IP Errors:**
- **Connection Refused**: It refuses the connection as a result of firewall settings on the server.
- **Connection Timeout**: No response received from the server in a reasonable time.
- **TLS/SSL Errors:**
- **SSL Certificate Error**: The server's SSL certificate has expired, or it is not valid.
  - **Handshake Failure**: The process of the TLS handshake has failed, so it cannot establish a secure communication session.
- **HTTP Errors**:
  - **404 Not Found**: The server is unable to locate the resource you are looking for.
  - **500 Internal Server Error**: The server has found itself in an unexpected state.
  - **403 Forbidden**: You don't have enough permission; hence, the server will refuse your request.
- **502 Bad Gateway**: Gateway server receives a malformed response form the upstream server.
---
## Conclusion

There are some complex steps that go on in the background when you click a URL to serve that webpage to your browser in an efficient and reliable way. So the first thing is parsing the URL that a browser makes on a click which means a browser breaks the URL into its components. A recursive lookup is involved at this point, with plenty of caching layers. Next, with the IP address in place, the browser will open a connection to the server using a three-way handshake so far as a TCP / IP connection is concerned. The established connection is therefore reliable. The server receives the HTTP request and processes it in response to sending an adequate HTTP response. Server-side load balancing mechanisms divide incoming traffic among a certain number of servers so that performance and availability are improved. One learns these processes and appreciates the complexity and efficiency in modern web infrastructure that surely guarantees reliability in quick access to web services.

---

## References

-

 Fielding, R. et al. "Hypertext Transfer Protocol -- HTTP/1.1." RFC 2616, 1999. URL: [RFC 2616](https://tools.ietf.org/html/rfc2616)

- Albitz, P., & Liu, C. "DNS and BIND." O'Reilly Media, 5th Edition, 2006. URL: DNS and BIND
- Stevens, W. R. "TCP/IP Illustrated, Volume 1: The Protocols." Addison-Wesley, 1994. URL: TCP/IP Illustrated
- Incapsula, "What is Load Balancing?" Imperva, 2021. URL: Load Balancing
- Rescorla, E. "The Transport Layer Security (TLS) Protocol Version 1

