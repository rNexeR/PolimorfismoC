#include <stdio.h>
#include <stdlib.h>

char Rectangle_vtable[sizeof(void*)];
char Box_vtable[sizeof(void*)];

void Rectangle_ctor(char* this, int w, int h){
	*((void**)this) = Rectangle_vtable;
	*((int*)(this+sizeof(void*))) = w;
	*((int*)(this+sizeof(int) + sizeof(void*))) = h;
}

int Rectangle_get_area(char *this){
	return *((int*)(this+sizeof(void*)))**((int*)(this+sizeof(int)+sizeof(void*)));
}

void Box_ctor(char *this, int w, int h, int l){
	Rectangle_ctor(this, w, h);
	*((void**)this) = Box_vtable;
	*((int*)(this+sizeof(int)*2+sizeof(void*))) = l;	
}

int Box_get_volumen(char* this){
	return Rectangle_get_area(this)**((int*)(this+sizeof(int)*2+sizeof(void*)));
}

void Rectangle_print(char * this){
	int w = *((int*)(this+sizeof(void*)));
	int h = *((int*)(this+sizeof(int)+sizeof(void*)));
	printf("I'm a %s, width: %d heigth: %d\n", "Rectangle", w, h);
}

void Box_print(char * this){
	int w = *((int*)(this+sizeof(void*)));
	int h = *((int*)(this+sizeof(int)+sizeof(void*)));
	int l = *((int*)(this+sizeof(int)*2+sizeof(void*)));
	printf("I'm a %s, width: %d heigth: %d length: %d\n", "Box", w, h, l);
}

void setup_vtable(){
	*((void**)Rectangle_vtable) = &Rectangle_print;
	*((void**)Box_vtable) = &Box_print;
	//printf("%u %u\n", *((void**)&Rectangle_vtable), (void*)&Rectangle_print);
}

void print_polimorfosis(char* rectangle){
	void (*ptr)(char *);
	void* vtable = *((void**)rectangle);
	ptr = *((void**)vtable);
	ptr(rectangle);
}

int main(int argc, char const *argv[])
{
	/* code */
	setup_vtable();

	char* r1 = malloc(2*sizeof(int) + sizeof(void*));
	Rectangle_ctor((char*)r1, 5, 2);

	char* b1 = malloc(3*sizeof(int) + sizeof(void*));
	Box_ctor((char*)b1, 5, 2, 3);

	printf("Area: %d\n", Rectangle_get_area((char*)r1));
	printf("Volumen: %d\n", Box_get_volumen((char*)b1));

	print_polimorfosis(r1);
	print_polimorfosis(b1);

	return 0;
}