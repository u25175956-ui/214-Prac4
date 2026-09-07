CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -g
TARGET := taskforge
IMAGE := taskforge

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run gdb valgrind \
        docker-build docker-run docker-shell docker-gdb docker-valgrind docker-stop docker-clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)

# --- Docker convenience targets ---
# build the image, then run/gdb/valgrind inside it, then stop/clean when done.

docker-build:
	docker build -t $(IMAGE) .

docker-run:
	docker run --rm -it --name $(IMAGE) $(IMAGE)

docker-shell:
	docker run --rm -it --name $(IMAGE) --entrypoint bash $(IMAGE)

docker-gdb:
	docker run --rm -it --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
		--name $(IMAGE) $(IMAGE) gdb ./$(TARGET)

docker-valgrind:
	docker run --rm -it --name $(IMAGE) --entrypoint make $(IMAGE) valgrind

docker-stop:
	-docker stop $(IMAGE)

docker-clean: docker-stop
	-docker rmi $(IMAGE)
