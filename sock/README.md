# Socket based communication for CBSD

## Wishfull thinking

`class Socket` is responsible for `accept`ing new connections and when new client arrives, new thread is created. In this thread, `class Worker` communicates via `class Client`. Ideally, `class Client` should implement operators for stream handling, message splitting, identification and delivery. For those purposes `class Message` will be used:
```
Socket s("/tmp/cbsd.sock");
while(1)
{
  auto clientId = s.waitForClient();
  Message m("some message");
  Client c(clientId);
  c >> m;
}
```

The actual use will involve putting the above code into a threading function on every new client connection.

## Protocol

To denotify message dirrection, in the documentation the following arrows will be used:

* `-->` from client to server
* `<--` from server to client

They are not used in the protocol, but are just there to help understanding the messages/protocol.

```
--> <size> <jail name> start
<-- <size> <jail name> output <payload>
```

Most CBSD commands have similar syntax. To send CBSD specific command to, for example, configure some part of CBSD:

```
--> <size> cbsd config ...
<-- <size> cbsd output ...
```

To get the <size>, code should read byte by byte until <space> is found. It should be converted to number of bytes that the rest of the message have, and than that more bytes should be read from socket. The rest is parsing which is specific to client/server and type of command being sent/read.
