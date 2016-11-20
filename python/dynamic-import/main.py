import sys

def dimport(name): # module name could be a, b or something like a.b.c.d etc.
    def wrapper(func):
        try:
            mod = __import__(name)
            mod.run()
        except ImportError: pass
        # log error?
        return func
    return wrapper


@dimport("a")
def decorator_maina():
    print("Method with A run first")


@dimport("b")
def decorator_mainb():
    print("Method with B run first")


def main():
    if len(sys.argv) > 1:
        modname = sys.argv[-1]
        try:
            mod = __import__(modname)
            mod.run()
        except ImportError:
            print("No valid module found for the name: ", modname, "Failed to import module")

    print("\nNow with @decorators:")
    decorator_maina()
    decorator_mainb()

if __name__ == "__main__":
    main()
