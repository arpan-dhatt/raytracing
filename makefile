CC=clang++
CXX=-Wall -O3

main.out: main.cpp vec3.h ray.h hittable.h sphere.h mat.h cam.h
	$(CC) $(CXX) -o $@ $<
	./main.out image.png 800 500 10 1 1 0 0 0 -2

clean:
	rm *.out *.ppm *.png
