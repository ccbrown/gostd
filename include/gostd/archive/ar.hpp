#pragma once

#include <gostd/io.hpp>
#include <gostd/io/ioutil.hpp>
#include <gostd/errors.hpp>
#include <gostd/time.hpp>
#include <gostd/strconv.hpp>
#include <gostd/strings.hpp>

namespace gostd::archive::ar {

struct Header {
    String Name;
    time::Time ModTime;
    Int Uid;
    Int Gid;
    Int64 Mode;
    Int64 Size;
};

class Reader {
public:
    Reader(io::Reader r) : _r{r} {}

    struct NextResult {
        Ptr<Header> header;
        Error err;
    };

    NextResult Next() {
        if (_err) {
            return {{}, _err};
        }
        auto [header, err] = _next();
        if (err) {
            _err = err;
        }
        return {header, err};
    }

    io::Reader::ReadResult Read(Slice<Byte> b) {
        if (_unread == 0) {
            return {0, io::EOF};
        }
        auto [n, err] = io::LimitedReader{_r, _unread}.Read(b);
        _unread -= Int64(n);
        return {n, err};
    }

private:
    io::Reader _r;
    bool _didReadArchiveHeader = false;
    Int64 _unread = 0;
    Error _err;

    Error _readArchiveHeader() {
        const char expected[] = "!<arch>\n";
        Slice<Byte> buf(sizeof(expected) - 1);
        if (auto [n, err] = io::ReadFull(_r, buf); err) {
            return err;
        }
        if (String(buf) != expected) {
            return errors::New("not an archive: bad header");
        }
        _didReadArchiveHeader = true;
        return {};
    }

    Error _skipUnread() {
        if (!_unread) { return {}; }

        // TODO: optimize for io.Seeker

        auto [skipped, err] = io::CopyN(io::ioutil::Discard, _r, _unread);
        _unread -= skipped;
        if (skipped < _unread) {
            return err;
        }
        return {};
    }

    NextResult _next() {
        if (!_didReadArchiveHeader) {
            if (auto err = _readArchiveHeader(); err) {
                return {{}, err};
            }
        } else if (_unread > 0) {
            if (auto err = _skipUnread(); err) {
                return {{}, err};
            }
        }

        Slice<Byte> buf(16 + 12 + 6 + 6 + 8 + 10 + 1 + 1);

        if (auto [n, err] = io::ReadFull(_r, buf); err) {
            return {{}, err};
        }

        if (buf[buf.Len()-2] != '`' || buf[buf.Len()-1] != '\n') {
            return {{}, errors::New("bad entry")};
        }

        auto str = String(buf);

        auto header = New<Header>();

        header->Name = strings::TrimRight(str.Head(16), " ");
        str = str.Tail(16);

        if (auto [n, err] = strconv::ParseInt(strings::TrimRight(str.Head(12), " "), 10, 64); err) {
            return {{}, errors::New("unable to parse mod time")};
        } else {
            header->ModTime = time::Unix(n, 0);
            str = str.Tail(12);
        }

        if (auto [n, err] = strconv::ParseInt(strings::TrimRight(str.Head(6), " "), 10, 32); err) {
            return {{}, errors::New("unable to parse uid")};
        } else {
            header->Uid = Int(n);
            str = str.Tail(6);
        }

        if (auto [n, err] = strconv::ParseInt(strings::TrimRight(str.Head(6), " "), 10, 32); err) {
            return {{}, errors::New("unable to parse gid")};
        } else {
            header->Gid = Int(n);
            str = str.Tail(6);
        }

        if (auto [n, err] = strconv::ParseUint(strings::TrimRight(str.Head(8), " "), 8, 64); err) {
            return {{}, errors::New("unable to parse mode")};
        } else {
            header->Mode = Int64(n);
            str = str.Tail(8);
        }

        if (auto [n, err] = strconv::ParseInt(strings::TrimRight(str.Head(10), " "), 10, 64); err) {
            return {{}, errors::New("unable to parse size")};
        } else {
            header->Size = n;
            str = str.Tail(10);
        }

        if (strings::HasPrefix(header->Name, "#1/")) {
            auto [nlen, err] = strconv::ParseInt(header->Name.Tail(3), 10, 32);
            if (!err) {
                Slice<Byte> buf(nlen);
                if (auto [_, err] = io::ReadFull(_r, buf); !err) {
                    header->Name = String(bytes::TrimRight(buf, "\0"));
                    header->Size -= nlen;
                }
            }
        }

        _unread = header->Size;
        return {header, {}};
    }
};

} // namespace gostd::archive::ar
