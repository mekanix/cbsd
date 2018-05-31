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
  c << m;
}
```

The actual use will involve putting the above code into a threading function on every new client connection.

## Protocol

Client to server commands should be: `<type> <command> [args]` which should get reply from server notifying the client what's the `ID` of the command it just executed, so that `ID` will be used when sending the output of the actuall command run by server.
* type - "command", "input", etc. in form of `<type name> [type args]`
* command - one of CBSD commands like scripts in `tools`, import/export of image, etc.
* args - the same args that CBSD CLI has now?

To support multiple clients synchronization, at least ID of the message is required. Let's assume following use case:
* there are two clients connected
* both of them are creating a jail
* one of them wants to get output of both jail creation scripts

In this case, every message going out from server should contain ID, except special ones, like notifying clients that server is going down, etc. Example of a message:
`<id> <type> <size> <payload>`

* id - command ID that this message refers to
* type - "output", "command", etc.
* size - size of the attached payload
* payload - the actual message being sent

For the long message it is required to be split into multiple message, which should be small enough that `<id> <type> <size> <payload>` can be sent/received in one call. If that can not be guaranteed, our "end of message" marker should be invented.
