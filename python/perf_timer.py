import time


class Timer:
    def __init__(self):
        self.start_time = None

    def start(self):
        self.start_time = time.time()

    def stop(self):
        return time.time() - self.start_time


if __name__ == "__main__":
    timer = Timer()

    timer.start()
    time.sleep(1)
    elapsed = timer.stop()
    print(f"Elapsed: {elapsed:.2f}s")
