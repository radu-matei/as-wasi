import { Console, Environ, CommandLine } from "../assembly/as-wasi";

export function _start(): void {
  let cmdline = new CommandLine();
  let all_args = cmdline.all();
  all_args.forEach(function (val) {
    Console.log("arg: " + val);
  });
}
