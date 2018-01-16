#pragma once

#include <cx.hpp>
#include <cx/errors.hpp>
#include <cx/os.hpp>

namespace cx::os::exec {

struct ExitError : ProcessState {
    explicit ExitError(Ptr<ProcessState> state) : ProcessState(*state) {}

    String Error() {
        return String(*this);
    }
};

struct Cmd {
    String Path;
    Slice<String> Args;
    Slice<String> Env;
    Ptr<Process> Process;
    Ptr<ProcessState> ProcessState;

    Error Start() {
        if (Process) {
            return errors::New("exec: already started");
        }

        ProcAttr pAttr;
        pAttr.Env = Env.Len() > 0 ? Env : Environ();
        if (auto [p, err] = StartProcess(Path, Args.Len() > 0 ? Args : Slice<String>(Path), &pAttr); err) {
            return err;
        } else {
            Process = p;
        }

        return {};
    }

    Error Wait() {
        if (!Process) {
            return errors::New("exec: not started");
        }
        if (_finished) {
            return errors::New("exec: Wait was already called");
        }
        _finished = true;

        auto [state, err] = Process->Wait();
        ProcessState = state;

        if (err) {
            return err;
        } else if (!state->Success()) {
            return New<ExitError>(state);
        }

        return {};
    }

    Error Run() {
        if (auto err = Start(); err) {
            return err;
        }
        return Wait();
    }

private:
    bool _finished = false;
};

template <typename... Args>
Ptr<Cmd> Command(String name, Args&&... args) {
    auto cmd = New<Cmd>();
    cmd->Path = name;
    cmd->Args = Append(Slice<String>{name}, cpp::forward<Args>(args)...);
    return cmd;
}

} // namespace cx::os::exec
