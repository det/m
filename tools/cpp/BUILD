cc_toolchain_suite(
    name = "cc-toolchain",
    toolchains = {
        "x86_64|clang": ":ubuntu_x86_64_clang_toolchain",
    },
)

filegroup(name = "empty")

filegroup(
    name = "clang_wrappers",
    srcs = glob(["wrappers/*.sh"]) + [
        "@clang//:binaries",
        "@clang//:clang_libs",
    ],
)

filegroup(
    name = "clang_all",
    srcs = [
        ":clang_wrappers",
        "@clang//:includes",
        "@clang//:runtime_libs",
    ],
)

cc_toolchain(
    name = "ubuntu_x86_64_clang_toolchain",
    all_files = ":clang_all",
    compiler_files = ":clang_wrappers",
    cpu = "x86_64",
    dwp_files = ":clang_wrappers",
    dynamic_runtime_libs = ["@clang//:runtime_libs"],
    linker_files = ":clang_wrappers",
    objcopy_files = ":clang_wrappers",
    static_runtime_libs = ["@clang//:static_libs"],
    strip_files = ":clang_wrappers",
    supports_param_files = True,
    visibility = ["//visibility:public"],
)
