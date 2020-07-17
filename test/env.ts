import { Console, Environ } from "../assembly/as-wasi";

export function _start(): void {
  let env = new Environ();
  let all_vars = env.all();
  all_vars.forEach(function (val) {
    Console.log(val.key + "=" + val.value);
  });

  //   let home = env.get("HOME")!;
  //   Console.log(home);
}
