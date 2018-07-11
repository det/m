load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "clang",
    build_file = "//:third_party/clang.BUILD",
    sha256 = "fa5416553ca94a8c071a27134c094a5fb736fe1bd0ecc5ef2d9bc02754e1bef0",
    strip_prefix = "clang+llvm-6.0.1-x86_64-linux-gnu-ubuntu-14.04",
    url = "http://releases.llvm.org/6.0.1/clang+llvm-6.0.1-x86_64-linux-gnu-ubuntu-14.04.tar.xz",
)

http_archive(
    name = "com_google_googletest",
    sha256 = "7fa65a00af56aac6d96743aec9d38e6d7259ebfa5e3d72d529a696dc1f221f49",
    strip_prefix = "googletest-59202300f1a774068608caff0351cc084fe79e7c",
    url = "https://github.com/google/googletest/archive/59202300f1a774068608caff0351cc084fe79e7c.tar.gz",
)

http_archive(
    name = "com_github_google_benchmark",
    sha256 = "904f5d19a6804396f16c95a823fabc6bc69913d628a124c96c4cd00358a72b09",
    strip_prefix = "benchmark-e90801ae475f23877319d67b96c07bf0c52405f3",
    url = "https://github.com/google/benchmark/archive/e90801ae475f23877319d67b96c07bf0c52405f3.tar.gz",
)

http_archive(
    name = "fmt",
    build_file = "//:third_party/fmt.BUILD",
    sha256 = "73d4cab4fa8a3482643d8703de4d9522d7a56981c938eca42d929106ff474b44",
    strip_prefix = "fmt-5.1.0",
    url = "https://github.com/fmtlib/fmt/archive/5.1.0.tar.gz",
)
