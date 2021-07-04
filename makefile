CC=clang++
CXX=-Wall

main.out: main.cpp vec3.h ray.h hittable.h sphere.h mat.h cam.h
	$(CC) $(CXX) -o $@ $<
	./main.out > image.ppm

clean:
	rm *.out *.ppm
