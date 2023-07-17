from scripts import *


def main():
    try:
        main_project_builder = ProjectBuilder.MainProjectBuilder()
        main_project_builder.Start()
    except Exception as exc:
        print("\nException: " + str(exc))
    except KeyboardInterrupt as exc:
        print("\nException keyboard interrupt: " + str(exc))
    except:
        print("\nException unknown error")


if __name__ == "__main__":
    main()
