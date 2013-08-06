#include "runtime_api.h"
UnionType u;

void print_object(UnionType _o)
{
	void *o = _o.o;
	switch (TYPE(o)) {
	case Int:
		printf("%d", to_Int(o));
		break;
	case Double:
		fprintf(stderr, "%f", _o.d);
		break;
	case String:
		printf("%s", to_String(o));
		break;
	case Array:
		print(to_Array(o));
		break;
	case ObjectType: {
		Object *object = to_Object(o);
		print_object(object->v);
		break;
	}
	default:
		break;
	}
}

void print(ArrayObject *array)
{
	size_t size = array->size;
	size_t i = 0;
	for (i = 0; i < size; i++) {
		print_object(array->list[i]);
	}
}

void say(ArrayObject *array)
{
	print(array);
	printf("\n");
}

void debug_print(UnionType o)
{
	fprintf(stderr, "===== debug_print ======\n");
	print_object(o);
	fprintf(stderr, "=============\n");
}
/*
Value shift(ArrayObject *args)
{
	Value ret;
	size_t size = args->size;
	if (size > 1) return ret;
	if (size == 1) {
		Value o = args->list[0];
		TYPE_CHECK(o, Array);
		ArrayObject *array = to_Array(o);
		ret = array->list[0];
		array->size--;
		memmove(array->list, array->list + 1, array->size * sizeof(Value));
	} else {
		fprintf(stderr, "fetch from function argument\n");
	}
	return ret;
}

Value push(ArrayObject *args)
{
	size_t size = args->size;
	Value ret = NULL;
	if (size != 2) {
		fprintf(stderr, "Type Error!: near by push\n");
	} else {
		Value array = args->list[0];
		Value value = args->list[1];
		TYPE_CHECK(array, Array);
		ArrayObject *base = to_Array(array);
		void *tmp;
		if (!(tmp = malloc(sizeof(Value) * (base->size + 1)))) {
			fprintf(stderr, "ERROR!!: cannot allocated memory\n");
		} else {
			memcpy(tmp, base->list, sizeof(Value) * base->size);
			base->list = (Value *)tmp;
			base->list[base->size] = value;
			base->size++;
			ret = INT_init(base->size);
		}
	}
	return ret;
}
*/
/*
Object *map(ArrayObject *args)
{
	Object *block = args->list[0];
	Object *array = args->list[1];
	Object *ret;
	for (i = 0; i < size; i++) {
		Object *map_arg = array->list[0];
		Function *map_func = (Function *)block->o.value;
		ret->list[i] = map_func(map_arg);
	}
	ret->type = Array;
	ret->v.ovalue = mapped_array;
	return ret;
}
*/

Object *new_Object(void)
{
	return (Object *)malloc(sizeof(Object));
}

Value Object_addObject(Value a, Value b)
{
	Value ret;
	fprintf(stderr, "type = [%d]\n", TYPE(ret.o));
	setResultByObjectObject(ret, a, b, +);
	fprintf(stderr, "ret = [%f]\n", ret.d);
	return ret;
}
/*
Value Object_subObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, -);
	return ret;
}

Value Object_mulObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, *);
	return ret;
}

Value Object_divObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, /);
	return ret;
}

Value Object_eqObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, ==);
	return ret;
}

Value Object_neObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, !=);
	return ret;
}

Value Object_gtObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, >);
	return ret;
}

Value Object_ltObject(Value a, Value b)
{
	Value ret;
	setResultByObjectObject(ret, a, b, >);
	return ret;
}
*/
/*
Object *Object_addInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, +);
	return ret;
}

Object *Object_subInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = (_a->type == ObjectType) ? to_Object(_a) : _a;
	setResultByObjectInt(ret, a, b, -);
	return ret;
}

Object *Object_mulInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, *);
	return ret;
}

Object *Object_divInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, /);
	return ret;
}

Object *Object_eqInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, ==);
	return ret;
}

Object *Object_neInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, !=);
	return ret;
}

Object *Object_gtInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectInt(ret, a, b, >);
	return ret;
}

Object *Object_ltInt(Object *_a, int b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = (_a->type == ObjectType) ? to_Object(_a) : _a;
	setResultByObjectInt(ret, a, b, <);
	return ret;
}

Object *Object_addInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, +);
	return ret;
}

Object *Object_subInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, -);
	return ret;
}

Object *Object_mulInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, *);
	return ret;
}

Object *Object_divInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, /);
	return ret;
}

Object *Object_eqInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, ==);
	return ret;
}

Object *Object_neInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, !=);
	return ret;
}

Object *Object_gtInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, >);
	return ret;
}

Object *Object_ltInt2(int a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByIntObject(ret, a, b, <);
	return ret;
}

Object *Object_addDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, +);
	return ret;
}

Object *Object_subDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, -);
	return ret;
}

Object *Object_mulDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, *);
	return ret;
}

Object *Object_divDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, /);
	return ret;
}

Object *Object_eqDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, ==);
	return ret;
}

Object *Object_neDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, !=);
	return ret;
}

Object *Object_gtDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, >);
	return ret;
}

Object *Object_ltDouble(Object *_a, double b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *a = to_Object(_a);
	setResultByObjectDouble(ret, a, b, <);
	return ret;
}

Object *Object_addDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, +);
	return ret;
}

Object *Object_subDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, +);
	return ret;
}

Object *Object_mulDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, *);
	return ret;
}

Object *Object_divDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, /);
	return ret;
}

Object *Object_eqDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, ==);
	return ret;
}

Object *Object_neDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, !=);
	return ret;
}

Object *Object_gtDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, >);
	return ret;
}

Object *Object_ltDouble2(double a, Object *_b)
{
	Object *ret = (Object *)malloc(sizeof(Object));
	Object *b = to_Object(_b);
	setResultByDoubleObject(ret, a, b, <);
	return ret;
}

*/
/*
int Object_isTrue(Value a)
{
	int ret = 0;
	switch (TYPE(a)) {
	case Int:
		ret = (to_Int(a) != 0);
		break;
	case Double:
		ret = (to_Double(a) != 0);
		break;
	default:
		break;
	}
	return ret;
}
*/
