#pragma once

#include <gostd/bytes.hpp>
#include <gostd/fmt.hpp>
#include <gostd/io.hpp>
#include <gostd/encoding/binary.hpp>
#include <gostd/debug/macho/types.hpp>

namespace gostd::debug::macho {

struct FormatError {
    FormatError(Int64 off, String msg) : off{off}, msg{msg} {}

    Int64 off;
    String msg;

    String Error() const {
        return msg + fmt::Sprint(" in record at byte", off);
    }
};

struct File : FileHeader {
    encoding::binary::ByteOrder ByteOrder;
    Uint32 Magic;
    Ptr<Symtab> Symtab;

    auto parseSymtab(Slice<Byte> symdat, Slice<Byte> strtab, Slice<Byte> cmddat, SymtabCmd* hdr, Int64 offset) {
        struct { Ptr<macho::Symtab> st; Error err; } ret;
        auto bo = ByteOrder;
        Slice<Symbol> symtab(hdr->Nsyms);
        auto b = New<bytes::Reader>(symdat);
        for (Int i = 0; i < symtab.Len(); ++i) {
            auto& sym = symtab[i];
            Uint64 nameOffset;
            if (Magic == Magic64) {
                Nlist64 n;
                if (auto err = encoding::binary::Read(b, bo, &n); err) {
                    ret.err = err;
                    return ret;
                }
                nameOffset = n.Name;
                sym.Type = n.Type;
                sym.Sect = n.Sect;
                sym.Desc = n.Desc;
                sym.Value = n.Value;
            } else {
                Nlist32 n;
                if (auto err = encoding::binary::Read(b, bo, &n); err) {
                    ret.err = err;
                    return ret;
                }
                nameOffset = n.Name;
                sym.Type = n.Type;
                sym.Sect = n.Sect;
                sym.Desc = n.Desc;
                sym.Value = n.Value;
            }
            if (nameOffset >= strtab.Len()) {
                ret.err = New<FormatError>(offset, "invalid name in symbol table");
                return ret;
            }
            sym.Name = reinterpret_cast<const char*>(&strtab[nameOffset]);
        }
        ret.st = New<macho::Symtab>();
        ret.st->Syms = symtab;
        return ret;
    }
};

auto NewFile(io::ReaderAt r) {
    struct { Ptr<File> f; Error err; } ret;
    auto f = New<File>();

    auto sr = New<io::SectionReader>(r, 0, (Uint64(1)<<63)-1);

    Slice<Byte> ident(4);
    if (auto [n, err] = r.ReadAt(ident, 0); err) {
        ret.err = err;
        return ret;
    }

    auto be = encoding::binary::BigEndian.Uint32(ident);
    auto le = encoding::binary::LittleEndian.Uint32(ident);

    if ((be | 1) == Magic64) {
        f->ByteOrder = encoding::binary::BigEndian;
        f->Magic = be;
    } else if ((le | 1) == Magic64) {
        f->ByteOrder = encoding::binary::LittleEndian;
        f->Magic = le;
    } else {
        ret.err = New<FormatError>(0, "invalid magic number");
        return ret;
    }

    if (auto err = encoding::binary::Read(sr, f->ByteOrder, dynamic_cast<FileHeader*>(&*f)); err) {
        ret.err = err;
        return ret;
    }

    auto offset = f->Magic == Magic64 ? fileHeaderSize64 : fileHeaderSize32;

    Slice<Byte> dat(f->Cmdsz);
    if (auto [_, err] = r.ReadAt(dat, offset); err) {
        ret.err = err;
        return ret;
    }

    auto bo = f->ByteOrder;

    for (Int i = 0; i < f->Ncmd; ++i) {
        if (dat.Len() < 8) {
            ret.err = New<FormatError>(offset, "command block too small");
            return ret;
        }

        auto cmd = LoadCmd(bo.Uint32(dat));
        auto siz = bo.Uint32(dat.Tail(4));
        if (siz < 8 || siz > dat.Len()) {
            ret.err = New<FormatError>(offset, "invalid command block size");
            return ret;
        }

        auto cmddat = dat.Head(siz);
        dat = dat.Tail(siz);
        offset += siz;

        // TODO: support more commands
        switch (cmd) {
        case LoadCmdSymtab: {
            SymtabCmd hdr;
            auto b = New<bytes::Reader>(cmddat);
            if (auto err = encoding::binary::Read(b, bo, &hdr); err) {
                ret.err = err;
                return ret;
            }
            Slice<Byte> strtab(hdr.Strsize);
            if (auto [_, err] = r.ReadAt(strtab, hdr.Stroff); err) {
                ret.err = err;
                return ret;
            }
            auto symsz = f->Magic == Magic64 ? 16 : 12;
            Slice<Byte> symdat(hdr.Nsyms * symsz);
            if (auto [_, err] = r.ReadAt(symdat, hdr.Symoff); err) {
                ret.err = err;
                return ret;
            }
            auto [st, err] = f->parseSymtab(symdat, strtab, cmddat, &hdr, offset);
            if (err) {
                ret.err = err;
                return ret;
            }
            f->Symtab = st;
            break;
        }
        default:
            break;
        }
    }

    ret.f = f;
    return ret;
}

} // namespace gostd::debug::macho
