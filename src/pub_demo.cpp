#include "zenoh.hxx"

using namespace zenoh;

int main(int argc, char **argv) {
    Config config;
    auto session = expect<Session>(open(std::move(config)));
    // Publish without creating a Publisher object
    session.put("demo/example/simple", "Simple2!");

    // Publish from a Publisher object
    auto publisher = expect<Publisher>(session.declare_publisher("demo/example/simple"));
    publisher.put("Simple1!");
}