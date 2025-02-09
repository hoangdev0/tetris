#include "path.h"
const char *paths[] = {
#define X(name, path) path,
	PATH_LIST
#undef X
};

const char *getPath(Path path)
{
	return paths[path];
}