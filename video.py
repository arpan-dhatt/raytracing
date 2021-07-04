import multiprocessing as mp
import subprocess
import os
import shutil

WIDTH = 400
HEIGHT = 250
FPS = 30
SECONDS = 1
RENDER_PROGRAM = "./main.out"
IMAGE_FOLDER = "./images/"
VIDEO_OUTPUT = "./video.mp4"
SAMPLES_PER_FRAME = 1
MAX_PROCESSES = 4
TARGET = (0, 0, -2.5)
STARTING = (1, 0.25, -4)
END = (1, 0.25, -2)

FRAMES = FPS * SECONDS

def scale(v: tuple, s: float):
    return (v[0]*s, v[1]*s, v[2]*s)

def add(v1: tuple, v2: tuple):
    return (v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2])

def sub(v1: tuple, v2: tuple):
    return (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2])

def render_image(frame: int):
    print(f"{frame}/{FRAMES}")
    pos = add(scale(sub(END, STARTING), frame/FRAMES), STARTING)
    target = TARGET
    subprocess.run(list(map( str, [RENDER_PROGRAM, IMAGE_FOLDER + f"image-{frame}.png", WIDTH, HEIGHT, SAMPLES_PER_FRAME, pos[0], pos[1], pos[2], target[0], target[1], target[2]])));
    return True

def use_ffmpeg():
    subprocess.run(["ffmpeg", "-start_number", "0", "-i", "./images/image-%d.png", "-pix_fmt", "yuv420p", VIDEO_OUTPUT])

if __name__ == "__main__":
    if os.path.isdir(IMAGE_FOLDER):
        shutil.rmtree(IMAGE_FOLDER, ignore_errors=True)
    os.mkdir(IMAGE_FOLDER)
    if os.path.isfile(VIDEO_OUTPUT):
        os.remove(VIDEO_OUTPUT)
    print("Beginning Render")
    with mp.Pool(processes=MAX_PROCESSES) as pool:
        pool.map(render_image, range(FRAMES))
    use_ffmpeg()
