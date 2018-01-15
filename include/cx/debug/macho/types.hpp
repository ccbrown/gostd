#pragma once

namespace cx::debug::macho {

enum class Cpu : Uint32 {};
enum class Type : Uint32 {};

enum : Uint32 {
    Magic32  = 0xfeedface,
    Magic64  = 0xfeedfacf,
    MagicFat = 0xcafebabe,
};

struct FileHeader {
    Uint32 Magic;
    Cpu Cpu;
    Uint32 SubCpu;
    Type Type;
    Uint32 Ncmd;
    Uint32 Cmdsz;
    Uint32 Flags;
};

constexpr Int fileHeaderSize32 = 7 * 4;
constexpr Int fileHeaderSize64 = 8 * 4;

enum class LoadCmd : Uint32 {};

constexpr LoadCmd LoadCmdSegment    = LoadCmd(1);
constexpr LoadCmd LoadCmdSymtab     = LoadCmd(2);
constexpr LoadCmd LoadCmdThread     = LoadCmd(4);
constexpr LoadCmd LoadCmdUnixThread = LoadCmd(5);
constexpr LoadCmd LoadCmdDysymtab   = LoadCmd(11);
constexpr LoadCmd LoadCmdDylib      = LoadCmd(12);
constexpr LoadCmd LoadCmdDylinker   = LoadCmd(15);
constexpr LoadCmd LoadCmdSegment64  = LoadCmd(25);

struct Nlist32 {
    Uint32 Name;
    Uint8 Type;
    Uint8 Sect;
    Uint16 Desc;
    Uint32 Value;
};

struct Nlist64 {
    Uint32 Name;
    Uint8 Type;
    Uint8 Sect;
    Uint16 Desc;
    Uint64 Value;
};

struct Symbol {
    String Name;
    Uint8 Type;
    Uint8 Sect;
    Uint16 Desc;
    Uint64 Value;
};

struct Symtab {
    Slice<Symbol> Syms;
};

struct SymtabCmd {
    LoadCmd Cmd;
    Uint32 Len;
    Uint32 Symoff;
    Uint32 Nsyms;
    Uint32 Stroff;
    Uint32 Strsize;
};

} // namespace cx::debug::macho
