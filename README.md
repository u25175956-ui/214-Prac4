# 214-Prac4 — TaskForge

TaskForge is a hierarchical work-processing system for a video game quest
system (COS 214 Practical 4). See `COS214_Prac4_2026_Revised.pdf` for the
spec and `TaskForge_UML_ClassDiagram.png` for the design.

Current milestone: **Composite**. `QuestComponent` / `QuestGroup` /
`Objective` / `Quest` / `Questline` / `Campaign` / `QuestJournal` are
implemented. State, Decorator and Iterator are not implemented yet — see the
`NOT YET IMPLEMENTED` notes at the top of `QuestComponent.h` and
`QuestJournal.h`.

## Build and run (local)

Requires `g++` (C++11) and `make`.

```sh
make
./taskforge
```

`make clean` removes build artifacts.

## Build and run (Docker)

No local `g++`/`gdb`/`valgrind` install needed — everything runs inside the
container. All of the below are plain `make` targets (see the Makefile).

```sh
make docker-build     # build the image (runs `make` inside, so this already
                       # proves the project compiles)
make docker-run       # run ./taskforge
make docker-gdb       # run ./taskforge under gdb
make docker-valgrind  # run ./taskforge under valgrind --leak-check=full
make docker-shell     # drop into a bash shell in the container
```

Each of these starts a fresh, self-removing container (`--rm`), so there's
nothing left running afterwards. If you ever need to force-stop or remove a
stuck container/image:

```sh
make docker-stop      # stop a running taskforge container, if any
make docker-clean     # stop it and remove the built image
```

## Layout

- `*.h` / `*.cpp` — source, one class per file.
- `main.cpp` — demo driver exercising the current milestone.
- `Makefile` — builds `taskforge` with `-std=c++11`; also has `run`, `gdb`,
  `valgrind` convenience targets.
- `Dockerfile` — Ubuntu 22.04 image with `g++`, `make`, `gdb`, `valgrind`.
