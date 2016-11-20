import sys

def main():
    if len(sys.argv) > 1:
        modname = sys.argv[-1]
        try:
            mod = __import__(modname)
            mod.run()
        except ImportError:
            print("No valid module found for the name: ", modname, "Failed to import module")

if __name__ == "__main__":
    main()
