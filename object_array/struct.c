/**
Projekt:    Kostra 9. cviceni IZP 2015
Autor:      Marek Zak <izakmarek@fit.vutbr.cz>
Datum:      28. 11. 2015
*/

#include "struct.h"

/**
 * Inizializace objektu. Název objektu kopíruje. Objekt bude mít název
 * roven NULL, pokud se inicializace nezdařila.
 */
void object_ctor(Object *o, int id, char *name)
{
	//printf("SS: %d\n", (int) strlen(name));
	o->id = id;
	if (name == NULL)
		o->name = NULL;
	else
	{
		char *tmp_p = malloc((strlen(name) + 1) * sizeof(char));
		if (tmp_p == NULL)
			o->name = NULL;
		else
		{
			o->name = tmp_p;
			strcpy(o->name, name);
		}
	}
}

/**
 * Záměna dat dvou objektù.
 */
void object_swap(Object *i1, Object *i2)
{
	char tmp_id = i1->id;
	char *tmp_name = malloc((strlen(i1->name) + 1) * sizeof(char));
	strcpy(tmp_name, i1->name);

	i1->id = i2->id;
	char *tmp_p = realloc(i1->name, (strlen(i2->name) + 1) * sizeof(char));
	if (tmp_p != NULL)
		i1->name = tmp_p;
	strcpy(i1->name, i2->name);

	tmp_p = NULL;

	i2->id = tmp_id;
	tmp_p = realloc(i2->name, (strlen(tmp_name) + 1) * sizeof(char));
	if (tmp_p != NULL)
		i2->name = tmp_p;
	strcpy(i2->name, tmp_name);

	free(tmp_name);
}

/**
 * Hluboká kopie objektu src na dst. Vrací dst, pokud se operace povedla,
 * jinak NULL.
 */
Object *object_cpy(Object *dst, Object *src)
{
	object_ctor(dst, src->id, src->name);
	
	if (dst->name == NULL)	
		return NULL;
	else
		return dst;
}

/**
 * Uvolní objekt (resp. jeho jméno) z paměti. 
 * Nastavi jmeno objektu na NULL.
 */
void object_dtor(Object *o)
{
	if (o->name != NULL)
	{
		free(o->name);
		o->name = NULL;
	}
}

/**
 * Vytiske hodnoty daneho objektu.
 */
void print_object(Object *o)
{
    printf("ID: %d, NAME: %s\n", o->id, o->name);
}
