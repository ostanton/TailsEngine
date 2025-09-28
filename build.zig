const std = @import("std");

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimise = b.standardOptimizeOption(.{});

    const enable_asserts = b.option(
        bool,
        "asserts",
        "Enable/disable asserts. Always disabled in release builds (default - true)",
    ) orelse true;

    const enable_profiling = b.option(
        bool,
        "profiling",
        "Enable/disable profiling (default - true)",
    ) orelse true;

    const enable_logging = b.option(
        bool,
        "logging",
        "Enable/disable logging macros (default - true)",
    ) orelse true;

    const build_shared = b.option(
        bool,
        "shared",
        "Whether to build a shared library instead of static (default - false)",
    ) orelse false;

    const build_examples = b.option(
        bool,
        "examples",
        "Whether to build the examples (default - true)",
    ) orelse true;

    const compile_flags = &[_][]const u8{
        "-Wall",
        "-Werror",
        "-std=c++20",
    };

    const lib_mod = b.addModule("tails", .{
        .target = target,
        .optimize = optimise,
        .link_libcpp = true,
    });

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = optimise,
    });

    lib_mod.linkLibrary(sdl_dep.artifact("SDL3"));

    lib_mod.addIncludePath(b.path("include"));
    lib_mod.addIncludePath(b.path("src/stb"));

    var sources = std.ArrayList([]const u8).empty;
    {
        const tails_src = "src/Tails";
        var dir = try std.fs.openDirAbsolute(
            b.pathJoin(&.{
                b.build_root.path.?,
                tails_src,
            }),
            .{
                .iterate = true,
            },
        );

        var walker = try dir.walk(b.allocator);
        defer walker.deinit();

        while (try walker.next()) |entry| {
            const ext = std.fs.path.extension(entry.basename);
            if (std.mem.eql(u8, ext, ".cpp")) {
                try sources.append(b.allocator, b.pathJoin(&.{ tails_src, entry.path }));
            }
        }
    }

    lib_mod.addCSourceFiles(.{
        .files = sources.items,
        .flags = compile_flags,
        .language = .cpp,
    });

    if (enable_asserts)
        lib_mod.addCMacro("TAILS_ENABLE_ASSERTS", "");
    if (enable_profiling)
        lib_mod.addCMacro("TAILS_ENABLE_PROFILING", "");
    if (enable_logging)
        lib_mod.addCMacro("TAILS_ENABLE_LOGGING", "");

    const lib = b.addLibrary(.{
        .name = "tails",
        .linkage = if (build_shared) .dynamic else .static,
        .root_module = lib_mod,
    });

    b.installArtifact(lib);

    if (build_examples) {
        const example_mod = b.createModule(.{
            .target = target,
            .optimize = optimise,
            .link_libcpp = true,
        });

        example_mod.linkLibrary(lib);
        example_mod.addCSourceFiles(.{
            .files = &.{
                "example/main.cpp",
                "example/Player.cpp",
            },
            .flags = compile_flags,
            .language = .cpp,
        });
        example_mod.addIncludePath(b.path("include"));

        const example_exe = b.addExecutable(.{
            .name = "example",
            .root_module = example_mod,
        });

        b.installArtifact(example_exe);
    }
}
