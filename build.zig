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
        "-std=c++2a",
    };

    const sdl_dep = b.dependency("sdl", .{
        .target = target,
        .optimize = optimise,
    });

    var lib: *std.Build.Step.Compile = undefined;
    if (build_shared) {
        lib = b.addSharedLibrary(.{
            .name = "tails",
            .target = target,
            .optimize = optimise,
        });
    } else {
        lib = b.addStaticLibrary(.{
            .name = "tails",
            .target = target,
            .optimize = optimise,
        });
    }
    lib.linkLibCpp();
    lib.linkLibrary(sdl_dep.artifact("SDL3"));
    lib.addIncludePath(b.path("include"));
    lib.addIncludePath(b.path("src/stb"));

    var sources = std.ArrayList([]const u8).init(b.allocator);
    {
        const tails_src = "src/Tails";
        const abs_tails_src = b.pathJoin(&.{ b.build_root.path.?, "src/Tails" });
        std.debug.print("Absolute Tails src = '{s}'\n", .{abs_tails_src});
        var dir = try std.fs.openDirAbsolute(abs_tails_src, .{ .iterate = true });

        var walker = try dir.walk(b.allocator);
        defer walker.deinit();

        while (try walker.next()) |entry| {
            const ext = std.fs.path.extension(entry.basename);
            if (std.mem.eql(u8, ext, ".cpp")) {
                try sources.append(b.pathJoin(&.{ tails_src, entry.path }));
            }
        }
    }
    lib.addCSourceFiles(.{
        .files = sources.items,
        .flags = compile_flags,
        .language = .cpp,
    });

    const lib_mod = lib.root_module;
    if (enable_asserts)
        lib_mod.addCMacro("TAILS_ENABLE_ASSERTS", "");
    if (enable_profiling)
        lib_mod.addCMacro("TAILS_ENABLE_PROFILING", "");
    if (enable_logging)
        lib_mod.addCMacro("TAILS_ENABLE_LOGGING", "");

    b.installArtifact(lib);

    if (build_examples) {
        const example_exe = b.addExecutable(.{
            .name = "example",
            .target = target,
            .optimize = optimise,
        });
        example_exe.linkLibCpp();
        example_exe.linkLibrary(lib);
        example_exe.addCSourceFiles(.{
            .files = &.{
                "example/main.cpp",
                "example/Player.cpp",
            },
            .flags = compile_flags,
        });
        example_exe.addIncludePath(b.path("include"));
        b.installArtifact(example_exe);
    }
}
