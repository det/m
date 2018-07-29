filegroup(
    name = "binaries",
    srcs = [
        "bin/clang",
        "bin/clang++",
        "bin/llvm-dwp",
        "bin/llvm-objcopy",
        "bin/llvm-objdump",
        "bin/ld.lld",
        "bin/llvm-ar",
        "bin/llvm-nm",
        "bin/llvm-cov",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "clang_libs",
    srcs = glob(["lib/clang/6.0.1/lib/linux/*.a"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "includes",
    srcs = glob([
        "include/c++/**",
        "lib/clang/6.0.1/include/**",
    ]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "runtime_libs",
    srcs = [
        "lib/libc++.so.1",
        "lib/libc++abi.so.1",
        "lib/libunwind.so.1",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "static_libs",
    srcs = [
        "lib/libc++.a",
        "lib/libc++abi.a",
        "lib/libunwind.a",
    ],
    visibility = ["//visibility:public"],
)
