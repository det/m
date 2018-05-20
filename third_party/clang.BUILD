package(default_visibility = ['//visibility:public'])

filegroup(
    name = "binaries",
    srcs = [
        "bin/clang",
        "bin/clang++",
        "bin/llvm-dwp",
        "bin/llvm-objcopy",
        "bin/llvm-objdump",
        "bin/lld",
        "bin/llvm-ar",
        "bin/llvm-nm",
        "bin/llvm-cov"
    ],
)

filegroup(
    name = "includes",
    srcs = glob([
        "include/c++/**",
        "lib/clang/6.0.0/include/**",
    ]),
)

filegroup(
    name = "runtime_libs",
    srcs = [
        "lib/libc++.so.1",
        "lib/libc++abi.so.1",
    ],
)
