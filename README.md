# Compile-time function routing

Function routing consists of modifying an application or its modules so that instead of calling a function that they invoke in their source code, for instance, `fun1()`, they call instead of an alternate function `fun2()` without modifying their source code.

Function routing helps create test versions of our applications and modules, in which we replace missing dependencies with simulators or just mock functions. Also, it can control the flow of data across the application, just as we do in this project.

# Changing printf() by a logging function

In this project, we demonstrate how to redirect all calls to `printf()` to a custom implementation: `timestamped_printf()`. Such redirection happens at compile time using compile flags (`-D` to be specific).

The C language does not offer a standard logging library, and it is easy to ask our developers to use `printf()` for logging in their modules. Later, during module integration and linkage, we can change all these references to `printf()` to alternate, feature-richer implementations. We find this particularly useful for those big projects where we would like to have common logging facilities across several modules that compose an application or framework.

To build this project, run `./scripts/build.sh`. When the build finishes, you will find the original application in `./out/bin/regular`, which shows the typical behavior of `./source/application.c`.

```
hello, world!
hello, from another_function.
```

Also, after the build is complete, a second executable `./out/bin/patched` runs the same application replacing all instances of printf() in application.c by `timestamped_printf()` (defined in `./source/timestamped_logger.c`)

```
2022-06-24 00:20:24,666966 - main() - hello, world!
2022-06-24 00:20:24,667062 - another_function() - hello, from another_function.
```
