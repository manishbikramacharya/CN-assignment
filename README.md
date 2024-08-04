## CN-assignment

This repo holds the CN assignemnt of our group (Unnamed group).

##Key Points:-
  1. Everyone has created their own folder where they push their work.
  2. Class project is uploaded in the root directory.
  3. Many of the packet tracker work was done together.

##Building the Bittorrent, File upload project.
  1. A Make (and) Tupfile configuration is always present. Projects will get build depending upon the configuration you have (for instance, clang is the compiler of choice for file server while we went with gcc for bittorrent while you could build it with     clang as well, a change to the Make and Tupfile is recommended.)
  2. Dependencies, Most of the work is done in C and Cpp.
  3. The Libraries of choice for Encryption is openssl, for (some network work) Curl is used (Both in Bittorrent). Whereas, Asio is used for the file upload project.
  4. The only thing you have to keep in consideration is, having the libs installed and a similar version of make or tup. (For Bittorrent, We recommend a unix operating system whereas for file upload we recommend windows as they are the native os where          development took place)

##Development choices.
While working on these projects we have made some consideration as evident, the language of choice has been C and Cpp. It is because they are fast and have vast support for libraries. They are also the lnaguage we were most comfortable with. 
We missed the class, on the demo Bittorrent client and could couldn't use codecrafters. 
