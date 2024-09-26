from threading import Thread


class Worker(Thread):
    def run(self) -> None:
        print("hello")


if __name__ == "__main__":
    w = Worker()
    w.start()
    w.join()
