CC=clang++
CXX=-Wall

main.out: main.cpp vec3.h ray.h hittable.h sphere.h
	$(CC) $(CXX) -o $@ $<
	./main.out > image.ppm

clean:
	rm *.out *.ppm
