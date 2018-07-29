cc_toolchain_suite(
    name = "cc-toolchain",
    toolchains = {
        "x86_64|clang": ":ubuntu_x86_64_clang_toolchain",
    },
)

filegroup(name = "empty")

filegroup(
    name = "clang_wrapper",
    srcs = glob(["wrappers/*.sh"]) + [
        "@clang//:binaries",
        "@clang//:clang_libs",
    ],
)

filegroup(
    name = "clang_all",
    srcs = [
        ":clang_wrapper",
        "@clang//:includes",
        "@clang//:runtime_libs",
    ],
)

cc_toolchain(
    name = "ubuntu_x86_64_clang_toolchain",
    all_files = ":clang_all",
    compiler_files = ":clang_wrapper",
    cpu = "x86_64",
    dwp_files = ":clang_wrapper",
    dynamic_runtime_libs = ["@clang//:runtime_libs"],
    linker_files = ":clang_wrapper",
    objcopy_files = ":clang_wrapper",
    static_runtime_libs = ["@clang//:static_libs"],
    strip_files = ":clang_wrapper",
    supports_param_files = True,
    visibility = ["//visibility:public"],
)
