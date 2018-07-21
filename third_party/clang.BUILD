CLANG_VERSION = "6.0.1"

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
        "bin/llvm-cov"
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "sanitizer_libs",
    srcs = glob(["lib/clang/" + CLANG_VERSION + "/lib/linux/*.a"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "includes",
    srcs = glob([
        "include/c++/**",
        "lib/clang/" + CLANG_VERSION + "/include/**",
    ]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "runtime_libs",
    srcs = [
        "lib/libc++.so.1",
        "lib/libc++abi.so.1",
    ],
    visibility = ["//visibility:public"],
)
