#include <ser.h>
#include <ser.c>

#include "main.h"

int0 main (
    int0 argc,
    char** argv
)
{
  struct allocator allocator = allocator_init(0);

  void* file = fopen("exe/perf.json", "r");
  if (unlikely(file == nullptr)) {
    printl("file does not exist");
    return EXIT_FAILURE;
  }

  unsigned int file_size = 0;
  fseek(file, 0L, SEEK_END);
  file_size = ftell(file);
  rewind(file);

  str json = { allocator_push(&allocator, next_mul2(file_size, 64)), file_size };
  int file_read_result = fread(json.chars, file_size, 1, file);
  if (unlikely(file_read_result < 0)) {
    printl("cannot read from file");
    return EXIT_FAILURE;
  }

  struct coordinate result = run(&json, &allocator);
  allocator_release(&allocator);
  fclose(file);

  if (verify(&result))
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;
}

struct coordinate run (
    str* json,
    struct allocator* allocator
)
{
  struct coordinate result = { 0 };
  struct coordinates_data data = { 0 };

  json_decode(json, &data, &coordinates_data_reflection, allocator);
  if (unlikely(failure.occurred)) {
    print("json decode error: ", failure.message);
    return result;
  }

  for (unsigned int i = 0; i < data.coordinates.length; i++) {
    struct coordinate* coord = list_at(&(data.coordinates), i);
    result.x += coord->x;
    result.y += coord->y;
    result.z += coord->z;
  }

  result.x = result.x / data.coordinates.length;
  result.y = result.y / data.coordinates.length;
  result.z = result.z / data.coordinates.length;
  /* printf("Result: { x: %e, y: %e, z: %e }\n", result.x, result.y, result.z); */
  return result;
}

bool verify (
    struct coordinate* result
)
{
  if (result->x >= -4.99e-30 || result->x <= -5.01e-30)
    return false;
	if (result->y <= 4.99e+30 || result->y >= 5.01e+30)
    return false;
	if (result->z <= 0.499 || result->z >= 0.501)
    return false;

  return true;
}
