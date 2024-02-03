const std = @import("std");
const raylib = @import("libs/raylib/src/build.zig");

// Working in zig 0.12.0
pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const exe = b.addExecutable(.{
        .name = "cnake",
        .target = target,
        .optimize = optimize,
    });

    exe.linkLibrary(try raylib.addRaylib(b, target, optimize, .{}));
    exe.addIncludePath(.{ .path = "libs/raylib/src" });
    exe.addCSourceFiles(.{
        .files = &.{"src/main.c"},
        .flags = &.{ "-std=gnu99", "-D_GNU_SOURCE" },
    });

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);

    // const unit_tests = b.addTest(.{
    //     .root_source_file = .{ .path = "src/main.zig" },
    //     .target = target,
    //     .optimize = optimize,
    // });

    // const run_unit_tests = b.addRunArtifact(unit_tests);

    // const test_step = b.step("test", "Run unit tests");
    // test_step.dependOn(&run_unit_tests.step);
}
