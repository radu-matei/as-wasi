import { Console, Socket, Time } from "../assembly/as-wasi";

export function _start(): void {
  let s = new Socket(2130706433, 3333);

  s.write("writing to an echo TCP server and waiting for a response");
  let res = s.receive();
  Console.write(res.toUpperCase());
}
